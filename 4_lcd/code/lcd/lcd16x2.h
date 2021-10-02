/*
 * lcd16x2.h
 *
 *  Created on: Sep 27, 2021
 *      Author: Mahmoud Mohamed Younis
 */

#ifndef LCD_LCD16X2_H_
#define LCD_LCD16X2_H_
/* inclusions */
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcd16x2_commands.h"

/* lcd class. */
/* lcd will be initialized to a 4-bit mode, 2-lines and 5x8 dots. */
/* some functions will able to change lcd mode and type custom characters. */
class lcd{
public:
	// initialization function.
	// control pins array as following ==> RS, RW and EN.
	void init(volatile uint8_t *Data_DDRx, volatile uint8_t *Data_PORTx,
			  volatile uint8_t *Control_DDRx, volatile uint8_t *Control_PORTx,
			           uint8_t data_pins[4], uint8_t control_pins[3]);
	/* send command. */
	void send_command(uint8_t command);

	/* print character */
	void print_character(uint8_t character);

	/* print character to x, y position*/
	void print_character_to(uint8_t characetr, uint8_t x, uint8_t y);

	/* print string */
	void print_string(const char *str);

	/* print string to x, y position*/
	void print_string_to(const char *str, uint8_t x, uint8_t y);

	/* print number */
	void print_number(float number);

	/* print number to x, y position*/
	void print_number_to(float number, uint8_t x, uint8_t y);

	/* move cursor to x, y position */
	void move_cursor_to(uint8_t x, uint8_t y);

	/* clear lcd*/
	void clear(void);

	/* return to x=0, y=0 position */
	void return_home(void);

	/* new line */
	void new_line(void);

	// constructor.
	lcd(void){
		// init lcd to 4-bit mode, 2-lines and 5x8 dots.
		function = 2;
	}
private:
	// Hardware configuration.
	volatile uint8_t *Data_DDR;
	volatile uint8_t *Data_PORT;
	volatile uint8_t *Control_DDR;
	volatile uint8_t *Control_PORT;
			 uint8_t  Data_pins[4];
			 uint8_t  RS;
			 uint8_t  RW;
			 uint8_t  EN;
	/* flag to set the function of the lcd. */
	/* f=0 4-bits, 1-line, 5x8 dots.        */
	/* f=1 4-bits, 1-line, 5x10 dots.       */
    /* f=2 4-bits, 2-lines, 5x8 dots.       */
	/* f=3 8-bits, 1-line, 5x8 dots. 	    */
	/* f=4 8-bits, 1-line, 5x10 dots.	    */
	/* f=5 8-bits, 2-lines, 5x8 dots.       */
			 uint8_t function;
	void set_data_pin(uint8_t pin){
		*Data_PORT |= (1<<pin);
	}

	void reset_data_pin(uint8_t pin){
		*Data_PORT &= ~(1<<pin);
	}

	 char* float_to_str(float number){
		// Container.
		char str[9];
		char str_after_point[4];

		// get int part.
		int int_part = (int)number;

		// get float part.
		float float_part = number - int_part;

		// convert int part into string.
		itoa(int_part, str, 10);

		// shift float point by 3 digits.
		if (float_part <= 0.9 && float_part >=0.0){
			float_part *= 10;
			itoa((int)float_part, str_after_point, 10);
			strcat(str, ".");
		} else if(float_part <= 0.99 && float_part >=0.00){
			float_part *= 100;
			itoa((int)float_part, str_after_point, 10);
			strcat(str, ".0");
		}

		// Convert float part into string.
		strcat(str, str_after_point);
		return str;
	}
};



#endif /* LCD_LCD16X2_H_ */
