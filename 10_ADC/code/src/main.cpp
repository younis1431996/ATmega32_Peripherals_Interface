/*
 * main.cpp
 *
 *  Created on: Oct 7, 2021
 *      Author: Mahmoud Mohamed Younis
 */
/* inclusions */
#include <util/delay.h>
#include "../lcd/lcd16x2.h"
#include "../ADC/ADC.h"

// lcd hardware configuration.
#define lcd_data_DDR		&DDRD
#define lcd_data_PTR		&PORTD
#define lcd_control_DDR		&DDRD
#define lcd_control_PTR		&PORTD

/* main function */
int main(void){
	// lcd object.
	lcd lcd;

	// lcd initialization.
	uint8_t lcd_data_pins[4] = {PD0, PD1, PD2, PD3};
	uint8_t lcd_control_pins[3] = {PD4, PD5, PD6};
	lcd.init(lcd_data_DDR, lcd_data_PTR, lcd_control_DDR, lcd_control_PTR, lcd_data_pins, lcd_control_pins);

	// Move lcd cursor.
	lcd.move_cursor_to(1, 0);

	// initialize ADC.
	ATmega32_ADC_init(128);

	ATmega32_ADC_V_REF(1);

	int ADC_value = '\0';
	// endless loop.
	for(;;){
		lcd.clear();
		lcd.print_string_to("ADC, Channel[0]", 0, 0);
		ATmega32_ADC_channel_select(PA0);
		ATmega32_ADC_start_convertion();
		if(ATmega32_ADC_check_conversion()){
			ADC_value = ATmega32_ADC_read();
			lcd.print_number_to(ADC_value, 1, 0);
		}

		_delay_ms(2000);

		lcd.clear();
		lcd.print_string_to("ADC, Channel[4]", 0, 0);
		ATmega32_ADC_channel_select(PA4);
		ATmega32_ADC_start_convertion();
		if(ATmega32_ADC_check_conversion()){
			ADC_value = ATmega32_ADC_read();
			lcd.print_number_to(ADC_value, 1, 0);
		}

		_delay_ms(2000);
		ADC_value = '\0';
	}

	// exit program.
	return 0;
}


