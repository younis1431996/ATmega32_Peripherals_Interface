/*
 * main.cpp
 *
 *  Created on: Sep 27, 2021
 *      Author: Mahmoud Mohamed Younis
 */
#include <avr/io.h>
#include "../lcd/lcd16x2.h"

int main(void){
	// Create object.
	lcd lcd;
	uint8_t data_pins[4] = {PC0, PC1, PC2, PC3};
	uint8_t control_pins[3] = {PC5, PC6, PC7};

	lcd.init(&DDRC, &PORTC, &DDRC, &PORTC, data_pins, control_pins);

	lcd.print_character_to('M', 1, 5);
	_delay_ms(1000);
	lcd.clear();


	for(;;);
	return 0;
}



