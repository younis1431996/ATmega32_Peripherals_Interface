/*
 * main.cpp
 *
 *  Created on: Oct 1, 2021
 *      Author: Mahmoud Mohamed Younis
 */
/* inclusions */
#include "../lcd/lcd16x2.h"
#include "../keypad/keypad.h"

int main(void){
	// Create lcd object.
	lcd lcd;
	const char *string = " Keypad_4x3:";
	uint8_t data_pins[4] = {PC0, PC1, PC2, PC3};
	uint8_t control_pins[3] = {PC5, PC6, PC7};

	// create keypad object.
	keypad_4x3_ keypad;
	uint8_t R_pins[4] = {PB0, PB1, PB2, PB3};
	uint8_t C_pins[3] = {PB4, PB5, PB6};
	uint8_t key_map[4][3] = { {'1', '2', '3'},
							  {'4', '5', '6'},
							  {'7', '8', '9'},
							  {'*', '0', '#'},
	};
	uint8_t key = '\0';

	// Initialization.
	lcd.init(&DDRC, &PORTC, &DDRC, &PORTC, data_pins, control_pins);
	keypad.init(&DDRB, &PINB, &PORTB, &DDRB, &PORTB, R_pins, C_pins,key_map);

	// Displaying.
	lcd.print_string(string);
	lcd.move_cursor_to(1, 0);

	for(;;){
		keypad.read(&key);
		if(key != '\0'){
			lcd.print_character(key);
			key = '\0';
		}
	}
	return 0;
}



