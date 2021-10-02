/*
 * button.cpp
 *
 *  Created on: Sep 23, 2021
 *      Author: Mahmoud Mohamed Younis
 */
/* inclusion */
#include "button.h"

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * \ function	- init.
 *
 * \ arguments	- DDRx  = Data Direction Register.
 * 				- PINx = Input Port.
 * 				- PINn  = Number of connected pin.
 *
 * \ details	- Initialize button.
 *
 * \ return		- void.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
void button :: init(volatile uint8_t *DDRx, volatile uint8_t *PINx, uint8_t PINn){
	// Save button hardware configuration.
	button :: DDR = DDRx;
	button :: PIN = PINx;
	button :: pin = PINn;

	// configure pin as an input.
	*DDR &= ~(1<<pin);

	// Insert nop for synchronization
	__asm__("nop");
}
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * \ function	- is-pressed.
 *
 * \ arguments	-void.
 *
 * \ details	- give me if button is pressed or not.
 *
 * \ return		- bool.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
bool button :: is_pressed(void){
	return button :: read_pin();
}
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * \ function	- set-state-value.
 *
 * \ arguments	- unsigned char number_of_states.
 *
 * \ details	- save the number of states.
 *
 * \ return		- void.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
void button :: set_state_value(uint16_t number_of_states){
	// if overflow happened.
	if(number_of_states >= 255)
		button :: state = 255;

	// Save number of states.
	button :: state = number_of_states;
}
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * \ function	- state-value.
 *
 * \ arguments	- void.
 *
 * \ details	- this function enables user to use one button like up-to 256 buttons.
 * 				- when button pressed, the state value will increment.
 * 				- by knowing the current state value, multi-options applying.
 *
 * \ return		- unsigned char sate value.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
void button :: state_value(void){
	bool ispressed = false;
	while(button :: is_pressed() == true)
	{
		ispressed = true;
	}

	if(ispressed == true){
		button :: current_state++;
		if(button :: current_state > button :: state)
			button :: current_state = 1;
	}
}
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * \ function	- state-value.
 *
 * \ arguments	- void.
 *
 * \ details	- this function enables user to use one button like up-to 256 buttons.
 * 				- when button pressed, the state value will increment.
 * 				- by knowing the current state value, multi-options applying.
 *
 * \ return		- void.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
bool button :: read_pin(void){
	// PIN register value.
	uint8_t PINR_value = 0x00;

	// connected pin value.
	bool pin_value;

	// Read PIN register.
	PINR_value = *PIN;

	// Mask to read the specific pin.
	pin_value = (bool) (PINR_value & (1<<pin));

	// Insert nop for synchronization
	__asm__("nop");

	return pin_value;
}
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * \ function	- reset-current-statee.
 *
 * \ arguments	- void.
 *
 * \ details	- set current state to it's initial value => 0;
 *
 * \ return		- void.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
void button :: reset_current_state(void){
	button :: current_state = 0;
}



