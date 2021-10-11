/*
 * main.cpp
 *
 *  Created on: Oct 2, 2021
 *      Author: Mahmoud Mohamed Younis
 */

/* inclusions */
#include <avr/io.h>
#include "../External_interrupts/EX_interrupts.h"


// main function.
int main(void){
	// initialize LEDs's DDR.
	DDRC |= (1<<PC0) | (1<<PC1) | (1<<PC2);

	// LEDs are initially low.
	PORTC &= ~(1<<PC0) & ~(1<<PC1) & ~(1<<PC2);

	// Activate INT0.
	EX_interrupt_0_init('0');

	// Activate INT1.
	EX_interrupt_1_init('1');

	// Activate INT2.
	EX_interrupt_2_init('0');

	while(1); // do nothing.

	return 0;
}

ISR(INT0_vect){
	PORTC ^= (1<<PC0);
}

ISR(INT1_vect){
	PORTC ^= (1<<PC1);
}

ISR(INT2_vect){
	PORTC ^= (1<<PC2);
}




