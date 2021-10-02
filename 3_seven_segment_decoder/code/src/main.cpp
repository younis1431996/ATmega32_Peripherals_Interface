/*
 * main.cpp
 *
 *  Created on: Sep 24, 2021
 *      Author: Mahmoud Mohamed Younis
 */
/* inclusion */
#include "../seven_segment/_7_segment_decoder.h"

int main(void){
	uint8_t counter = 0;
	// Create object.
	_binary_7_segment_ _7_seg_1;

	// _7_seg_1 hardware configuration.
	volatile uint8_t *DDRx[4]  = { &DDRA, &DDRB, &DDRC, &DDRD };
	volatile uint8_t *PORTx[4] = { &PORTA, &PORTB, &PORTC, &PORTD };
			 uint8_t pin[4]    = { PA0, PB1, PC2, PD3};

	/* initialization */
	_7_seg_1.init(DDRx, PORTx, pin);

	for(;;){
		_7_seg_1.display(counter);
		_delay_ms(1000);
		counter++;
		if(counter==10)
			counter=0;
	}


	return 0;
}


