/*
 * main.cpp
 *
 *  Created on: Oct 11, 2021
 *      Author: Mahmoud Mohamed Younis
 */
/* inclusions */
#include <avr/io.h>
#include <util/delay.h>

/* Analog comparator functions */
void ATmega32_analog_comparator_enable(void){
	SFIOR &= (1<<ACME);
}

uint8_t ATmega32_analog_comparator_output(void){
	ACSR &= 0x00;
	if(ACSR & (1<<ACO)){
		return 1;
	}
	else if( (ACSR & (1<<ACO) ) == 0){
		return 0;
	}
	return '\0';
}
void ATmega32_analog_comparator_disable(void){
	ACSR |= (1<<ACD);
}

/* main function */
int main(void){
	DDRD = 0xFF;

	ATmega32_analog_comparator_enable();

	for(;;){
		PORTD = ATmega32_analog_comparator_output();
		_delay_ms(50);
	}
	return 0;
}

