/*
 * lcd16x2.cpp
 *
 *  Created on: Sep 27, 2021
 *      Author: Mahmoud Mohamed Younis
 */
/* Inclusions */
#include "lcd16x2.h"
#include "lcd16x2_commands.h"

/* Initialization function. */
/**************************************************************************************
 * 1. Wait for 15ms, Power-on initialization time for LCD16x2.
 * 2. Send 0x02 command which initializes LCD 16x2 in 4-bit mode.
 * 3. Send 0x28 command which configures LCD in 2-line, 4-bit mode, and 5x8 dots.
 * 4. Send any Display ON command (0x0E, 0x0C)
 * 5. Send 0x06 command (increment cursor)
 * 				LCD mode is 4-bit mode
 **************************************************************************************/
void lcd :: init(volatile uint8_t *Data_DDRx, volatile uint8_t *Data_PORTx,
		         volatile uint8_t *Control_DDRx, volatile uint8_t *Control_PORTx,
		                  uint8_t data_pins[4], uint8_t control_pins[3]){
	// Hardware configuration.
	lcd :: Data_DDR = Data_DDRx;
	lcd :: Data_PORT = Data_PORTx;
	lcd :: Control_DDR = Control_DDRx;
	lcd :: Control_PORT = Control_PORTx;

	// configure data pins.
	for(uint8_t i=0; i<4; i++){
		lcd :: Data_pins[i] = data_pins[i];

		// configure pins as output.
		*Data_DDR |= (1<<Data_pins[i]);
	}

	// Configure control pins.
	lcd :: RS = control_pins[0];
	lcd :: RW = control_pins[1];
	lcd :: EN = control_pins[2];

	// configure pins as output.
	*Control_DDR |= (1<<RS);
	*Control_DDR |= (1<<RW);
	*Control_DDR |= (1<<EN);

	/* LCD Power ON delay always > 15 ms. */
	_delay_ms(20);

	/* Send for 4 bit initialization of LCD  */
	lcd :: send_command(__init__);
	_delay_ms(1);

	/* send some commands for configuration. */
	// >> 4-bit mode, 2-lines and 5x8 dots.
	lcd :: send_command(_4_bits_2_lines_5x8_dots);
	_delay_ms(1);

	// >> display on, cursor on.
	lcd :: send_command(display_on_cursor_on_no_blinking);
	_delay_ms(1);

	// >> cursor will shift to the right.
	lcd :: send_command(increment_cursor);
	_delay_ms(1);

	// >> clear display screen.
	lcd :: send_command(clear_display);
	_delay_ms(1);
}

/* Send command. */
/**********************************************************************************
 * 1. First, send a Higher nibble of command.
 * 2. Make RS pin low, RS=0 (command REG.)
 * 3. Make RW pin low, RW=0 (write operation) or connect it to ground.
 * 4. Give High to Low pulse at Enable (E).
 * 5. Send lower nibble of command.
 * 6. Give High to Low pulse at Enable (E).
 * 	  RS = pins[0]
 * 	  RW = pins[1]
 * 	  EN = pins[2]
 **********************************************************************************/
void lcd :: send_command(uint8_t command){
	/* store command in 8-bit register. */
	bool cmd_arr[8];
	for (uint8_t i=0; i<8; i++){
		cmd_arr[i] = (bool) (command&(1<<i));
	}

	/* sending upper nibble. */
	for(uint8_t i=4; i<=7; i++){
		if(cmd_arr[i] == true)
			set_data_pin(Data_pins[i-4]);
		else if(cmd_arr[i] == false)
			reset_data_pin(Data_pins[i-4]);

		/* Synchronization */
		__asm__("nop");
	}

	/* RS=0, command register. */
	*Control_PORT &= ~(1<<RS);

	/* Enable pulse */
	*Control_PORT |= (1<<EN);
	_delay_ms(1);
	*Control_PORT &= ~ (1<<EN);
	_delay_ms(1);

	/* Sending lower nibble */
	for(uint8_t i=0; i<=3; i++){
		if(cmd_arr[i] == true)
			set_data_pin(Data_pins[i]);
		else if(cmd_arr[i] == false)
			reset_data_pin(Data_pins[i]);

		/* Synchronization */
		__asm__("nop");
	}

	/* Enable pulse */
	*Control_PORT |= (1<<EN);
	_delay_ms(1);
	*Control_PORT &= ~ (1<<EN);
	_delay_ms(1);

	// End function.
	return;
}

/* Print character. */
/****************************************************************
 * 1. First, send a Higher nibble of data.
 * 2. Make RS pin high, RS=1 (data register.)
 * 3. Make RW pin low, RW=0 (write operation) or connect it to ground.
 * 4. Give High to Low pulse at Enable (E).
 * 5. Send lower nibble of data.
 * 6. Give High to Low pulse at Enable (E).
 */
void lcd :: print_character(uint8_t character){
	/* store character in 8-bit register. */
	bool char_arr[8];
	for (uint8_t i=0; i<8; i++)
		char_arr[i] = (bool) (character&(1<<i));

	/* sending upper nibble. */
	for(uint8_t i=4; i<=7; i++){
		if(char_arr[i] == true)
			set_data_pin(Data_pins[i-4]);
		else if(char_arr[i] == false)
			reset_data_pin(Data_pins[i-4]);

		/* Synchronization */
		__asm__("nop");
	}
	/* RS=1, data register. */
	*Control_PORT |= (1<<RS);
	/* Enable pulse */
	*Control_PORT |= (1<<EN);
	_delay_ms(1);
	*Control_PORT &= ~ (1<<EN);
	_delay_ms(1);

	/* Sending lower nibble */
	for(uint8_t i=0; i<=3; i++){
		if(char_arr[i] == true)
			set_data_pin(Data_pins[i]);
		else if(char_arr[i] == false)
			reset_data_pin(Data_pins[i]);

		/* Synchronization */
		__asm__("nop");
	}

	/* Enable pulse */
	*Control_PORT |= (1<<EN);
	_delay_ms(1);
	*Control_PORT &= ~ (1<<EN);
	_delay_ms(1);

	// End function.
	return;
}

/* Print character to (x,y) position. */
void lcd :: print_character_to(uint8_t characetr, uint8_t x, uint8_t y){
	lcd :: move_cursor_to(x, y);
	lcd :: print_character(characetr);
	return;
}

/* Print string. */
void lcd :: print_string(const char *str){
	unsigned int i = 0;
	for (i=0; i<strlen(str); i++){
		if(i<16)
			lcd :: print_character(str[i]);
		else{
			lcd :: move_cursor_to(1, i-16);
			lcd :: print_character(str[i]);
		}

	}
	return;
}

/* Print string to (x,y) position. */
void lcd :: print_string_to(const char *str, uint8_t x, uint8_t y){
	lcd :: move_cursor_to(x, y);
	lcd :: print_string(str);
	return;
}

/* move cursor to custom position. */
void lcd :: move_cursor_to(uint8_t x, uint8_t y){
	if (x == 0 && y<16)
		/* Command of first row and required position<16 */
		lcd :: send_command( (y & 0x0F)|force_cusror_to_start_with_1st_row);
	/* Command of second row and required position<16 */
	else if (x == 1 && y<16)
		lcd :: send_command( (y & 0x0F)|force_cusror_to_start_with_2nd_row);
}

/* print number */
void lcd :: print_number(float number){
	char *string;

	string = float_to_str(number);

	lcd :: print_string(string);
}

/* print number to x, y position*/
void lcd :: print_number_to(float number, uint8_t x, uint8_t y){
	lcd :: move_cursor_to(x, y);
	lcd :: print_number(number);
}

/* clear lcd*/
void lcd :: clear(void){
	lcd :: send_command(clear_display);
	_delay_ms(2);
	lcd :: send_command(Return_Home);
	_delay_ms(2);
}

/* return to x=0, y=0 position */
void lcd :: return_home(void){
	lcd :: send_command(Return_Home);
	_delay_ms(2);
}
