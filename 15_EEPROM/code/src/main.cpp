/*
 * main.cpp
 *
 *  Created on: Oct 16, 2021
 *      Author: Mahmoud Mohamed Younis
 */
/* inclusions */
#include "../EEPROM/EEPROM.h"
#include "../lcd/lcd16x2.h"

int main(void){
	// lcd object.
	lcd lcd;
	uint8_t data_pins[4] = {PD0, PD1, PD2, PD3};
	uint8_t control_pins[3] = {PD5, PD6, PD7};

	lcd.init(&DDRD, &PORTD, &DDRD, &PORTD, data_pins, control_pins);

	// write byte to EEPROM.
	lcd.clear();
	lcd.print_string("Write to EEPROM..");
	lcd.print_string_to("ADD=0x01; char=", 1, 0);
	EEPROM_write(0x01, 'X');
	lcd.print_character('X');

	_delay_ms(2000);

	// read byte from EEPROM.
	lcd.clear();
	lcd.print_string("now read x01 add");

	_delay_ms(2000);

	lcd.clear();
	uint8_t __byte;
	lcd.print_string("read from EEPROM..");
	lcd.print_string_to("ADD=0x01; char=", 1, 0);
	EEPROM_read(0x01, &__byte);
	lcd.print_character(__byte);

	for(;;);

	return 0;
}



