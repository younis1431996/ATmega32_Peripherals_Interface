/*
 * _7_segment_decoder.cpp
 *
 *  Created on: Sep 24, 2021
 *      Author: Mahmoud Mohamed Younis
 */
/* inclusion */
#include "_7_segment_decoder.h"

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * \ function	- init.
 *
 * \ arguments	- array of pin class contains:-
 * 					- DDRx  = Data Direction Register.
 * 					- PORTx = Output Port.
 * 					- PINn  = Number of connected pin.
 *
 * \ details	- Initialize each pin alone.
 *
 * \ return		- void.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
void _binary_7_segment_ :: init(volatile uint8_t *DDRx[4], volatile uint8_t *PORTx[4], uint8_t pin[4]){
	// Save hardware configuration.
	for(uint8_t i=0; i<4; i++){
		_binary_7_segment_ :: DDR[i]      = DDRx[i];
		_binary_7_segment_ :: PORT[i]     = PORTx[i];
		_binary_7_segment_ :: data_pin[i] = pin[i];

		// Configure as output.
		*DDR[i] |= (1<<data_pin[i]);
	}
}
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * \ function	- display.
 *
 * \ arguments	- unsigned char number to display from 0 to 9.
 *
 * \ details	- set value to each pin, bit level.
 *
 * \ return		- void.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
void _binary_7_segment_:: display(uint8_t number){
	// counter.
	uint8_t i=0;
	//mask value.
	uint8_t value=0, j=0;
	// masking.
	bool bit = false;

	// loop writes data.
	for(i=0; i<4; i++){
		j = (1<<i);
		value = number & j;
		bit = (bool) value;
		j = 0;
		if(bit == true)
			set_pin(PORT[i], data_pin[i]);
		else if(bit == false)
			reset_pin(PORT[i], data_pin[i]);
		// Insert nop for synchronization
		__asm__("nop");
	}
}
/* Set pin to logic 1 */
void _binary_7_segment_:: set_pin(volatile uint8_t *PORTx, uint8_t pin){
	*PORTx |= (1<<pin);
}
/* set pin to logic 0 */
void _binary_7_segment_:: reset_pin(volatile uint8_t *PORTx, uint8_t pin){
	*PORTx &= ~(1<<pin);
}


