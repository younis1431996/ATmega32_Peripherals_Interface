/*
 * main.cpp
 *
 *  Created on: Oct 12, 2021
 *      Author: Mahmoud Mohamed Younis
 */
/* inclusions */
#include <util/delay.h>
#include "../ATmega32_SPI/ATmega32_SPI.h"

int main(void){
	// 7-seg
	DDRD  |= 0x0F;
	PORTD &= 0xF0;

	// SPI init.
	ATmega32_SPI_slave_init();

	// counter.
	int8_t count = 0;
	for(;;){
		ATmega32_SPI_slave_read(&count);
		PORTD = count;
	}
	return 0;
}




