/*
 * main.cpp
 *
 *  Created on: Oct 15, 2021
 *      Author: Mahmoud Mohamed Younis
 */
/* inclusion */
#include "../TWI/ATmega32_TWI.h"

/* main function */
int main(void){
	// I2C init
	TWI_int(0x01);

	uint8_t _byte = '\0';

	DDRD |= 0x01;

	for(;;){
		TWI_slave_read_byte(&_byte);
		if(_byte == '0')
			PORTD ^= 0x01;
		_delay_ms(500);

		TWI_slave_write_byte('1');
		_delay_ms(500);
	}
}



