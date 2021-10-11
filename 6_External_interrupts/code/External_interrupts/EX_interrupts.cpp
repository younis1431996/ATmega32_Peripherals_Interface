/*
 * EX_interrupts.cpp
 *
 *  Created on: Oct 2, 2021
 *      Author: Mahmoud Mohamed Younis
 */
/* inclusions */
#include "EX_interrupts.h"

/* Steps to activate an external interrupt.
 * 1.Select external interrupt mode.
 * 2.Enable external interrupt bit.
 * 3.Enable global interrupts.
 */

/* External interrupt #0 */
void EX_interrupt_0_init(uint8_t mode){
	// Select INT0 mode.
	switch(mode){
	// The low level of INT0 generates an interrupt request.
	case '0':
		MCUCR &= ~(1<<ISC00);
		MCUCR &= ~(1<<ISC01);
		break;

	// Any logical change on INT0 generates an interrupt request.
	case '1':
		MCUCR |=  (1<<ISC00);
		MCUCR &= ~(1<<ISC01);
		break;

	// The falling edge of INT0 generates an interrupt request.
	case '2':
		MCUCR &= ~(1<<ISC00);
		MCUCR |=  (1<<ISC01);
		break;

	// The rising edge of INT0 generates an interrupt request.
	case '3':
		MCUCR |= (1<<ISC00);
		MCUCR |= (1<<ISC01);
		break;
	}

	// Enable external interrupt 0.
	GICR |= (1<<INT0);

	// Enable global interrupts.
	sei();
}

void EX_interrupt_0_Enable(void){
	// Enable external interrupt 0.
	GICR |= (1<<INT0);
}

void EX_interrupt_0_Disable(void){
	// Disable external interrupt 0.
	GICR &= ~(1<<INT0);
}

/*-------------------------------------------------------------------------------------*/

/* External Interrupt #1 */
void EX_interrupt_1_init(uint8_t mode){
	// Select INT1 mode.
	switch(mode){
	// The low level of INT1 generates an interrupt request.
	case '0':
		MCUCR &= ~(1<<ISC10);
		MCUCR &= ~(1<<ISC11);
		break;

	// Any logical change on INT1 generates an interrupt request.
	case '1':
		MCUCR |= (1<<ISC10);
		MCUCR &= ~(1<<ISC11);
		break;

	// The falling edge of INT1 generates an interrupt request.
	case '2':
		MCUCR &= ~(1<<ISC10);
		MCUCR |= (1<<ISC11);
		break;

	// The rising edge of INT1 generates an interrupt request.
	case '3':
		MCUCR |= (1<<ISC10);
		MCUCR |= (1<<ISC11);
		break;
	}

	// Enable external interrupt 1.
	GICR |= (1<<INT1);

	// Enable global interrupts.
	sei();
}

void EX_interrupt_1_Enable(void){
	// Enable external interrupt 1.
	GICR |= (1<<INT1);
}

void EX_interrupt_1_Disable(void){
	// Disable external interrupt 1.
	GICR &= ~(1<<INT1);
}

/*-------------------------------------------------------------------------------------*/

/* External Interrupt #2 */
void EX_interrupt_2_init(uint8_t mode){
	// Select INT2 mode.
	switch(mode){
	// The falling edge of INT2 generates an interrupt request.
	case '0':
		MCUCSR &= ~(1<<ISC2);
		break;

	// The rising edge of INT2 generates an interrupt request.
	case '1':
		MCUCSR |= (1<<ISC2);
		break;
	}

	// Enable external interrupt 2.
	GICR |= (1<<INT2);

	// Enable global interrupts.
	sei();
}

void EX_interrupt_2_Enable(void){
	// Enable external interrupt 2.
	GICR |= (1<<INT2);
}

void EX_interrupt_2_Disable(void){
	// Disable external interrupt 2.
	GICR &= ~(1<<INT2);
}
