/*
 * main.cpp
 *
 *  Created on: Sep 23, 2021
 *      Author: Mahmoud Mohamed Younis
 */
/* inclusion */
#include "../button/button.h"

int main(void){
	// Create objects.
	button BTN1, BTN2;

	// initialization.
	BTN1.init(&DDRB, &PINB, PB0);
	BTN2.init(&DDRB, &PINB, PB1);

	// BTN2 have 2 states.
	BTN2.set_state_value(3);

	DDRD |= 0x1F;

	/* endless loop */
	for(;;){
		// BTN1.
		if(BTN1.is_pressed() == true){
			PORTD |= (1<<PD0);
			__asm__("nop");
		} else if(BTN1.is_pressed() == false){
			PORTD &= ~(1<<PD0);
			__asm__("nop");
		}

		// BTN2.
		BTN2.state_value();
		if(BTN2.current_state == 1){
			PORTD |= (1<<PD1);
			PORTD &= ~(1<<PD2);
			PORTD &= ~(1<<PD3);
		}
		else if(BTN2.current_state == 2){
			PORTD &= ~(1<<PD1);
			PORTD |= (1<<PD2);
			PORTD &= ~(1<<PD3);
		}
		else if(BTN2.current_state == 3){
			PORTD &= ~(1<<PD1);
			PORTD &= ~(1<<PD2);
			PORTD |= (1<<PD3);
		}
	}

	return 0;
}


