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
	// I2C init.
	TWI_int(0x11);

	uint8_t _byte = '\0';

	DDRD |= 0x01;

	for(;;){
		TWI_master_write_byte(0x01, '0');
		_delay_ms(500);

		TWI_master_read_byte(0x01, &_byte);
		if(_byte == '1')
			PORTD ^= 0x01;

		_delay_ms(500);
	}

	return 0;
}



