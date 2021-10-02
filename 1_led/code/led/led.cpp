/*
 * led.cpp
 *
 *  Created on: Sep 23, 2021
 *      Author: Mahmoud Mohamed Younis
 */
/* inclusions. */
#include "led.h"

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * \ function	- init.
 *
 * \ arguments	- DDRx  = Data Direction Register.
 * 				- PORTx = Output Port.
 * 				- PINn  = Number of connected pin.
 * 				- state = 0 if led is pulled-up or 1 if led is pulled-down.
 *
 * \ details	- Initialize led according to input state.
 *
 * \ return		- void.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
void LED :: init(volatile uint8_t *DDRx, volatile uint8_t *PORTx, uint8_t PINn,uint8_t state){
	// save led hardware configuration.
	LED :: DDR   = DDRx;
	LED :: PORT  = PORTx;
	LED :: pin   = PINn;
	LED :: state = state;

	// Configure pin as output.
	*DDR |= (1<<pin);

	// Insert nop for synchronization
	__asm__("nop");

	// led is initially low.
	if(state == 0)
		*PORT |= (1<<pin);
	else if(state == 1)
		*PORT &= ~(1<<pin);
}
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * \ function	- turn on.
 *
 * \ arguments	- void.
 *
 * \ details	- turn on led.
 *
 * \ return		- void.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
void LED :: turn_on(void){
	// according to state.
	if(state == 0)
		*PORT &= ~(1<<pin);
	else if(state == 1)
		*PORT |= (1<<pin);
}

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * \ function	- turn off.
 *
 * \ arguments	- void.
 *
 * \ details	- turn off led.
 *
 * \ return		- void.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
void LED :: turn_off(void){
	// according to state.
	if(state == 0)
		*PORT |= (1<<pin);
	else if(state == 1)
		*PORT &= ~(1<<pin);
}
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * \ function	- toggle.
 *
 * \ arguments	- void.
 *
 * \ details	- toggle configured pin.
 *
 * \ return		- void.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
void LED :: toggle(void){
	*PORT ^= (1<<pin);
}
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * \ function	- blink.
 *
 * \ arguments	- unsigned int time in milliseconds.
 *
 * \ details	- toggle configured pin every one (time) delay.
 *
 * \ return		- void.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
void LED :: blink(uint16_t time){
	*PORT ^= (1<<pin);
	_delay_ms(time);
}
