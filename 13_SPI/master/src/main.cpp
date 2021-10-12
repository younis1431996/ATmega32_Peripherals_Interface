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
	// SPI init.
	ATmega32_SPI_master_init(16);

	// counter.
	uint8_t count = 0;

	for(;;){
		ATmega32_SPI_master_write(count);
		count++;
		if(count == 16)
			count = 0;
		_delay_ms(500);
	}
	return 0;
}



