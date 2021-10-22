/*
 * lcd16x2_commands.h
 *
 *  Created on: Sep 27, 2021
 *      Author: Mahmoud Mohamed Younis
 */

#ifndef LCD_LCD16X2_COMMANDS_H_
#define LCD_LCD16X2_COMMANDS_H_
// Note: All following commands from Data sheet.

/* Clears entire display and sets DDRAM address 0 in address counter. */
#define clear_display							 (0x01)

/* Sets DDRAM address 0 in address counter.
 * Also returns display from being shifted to original position.
 * DDRAM contents remain unchanged.
 * delay time = 1.52 ms, ~= 2 ms */
#define Return_Home								 (0x02)

/*Sets cursor move direction and specifies display shift.
 * These operations are performed during data write and read.
 * delay time = 37 us, ~= 40 us*/

// >> decrement cursor, shift cursor to left.
#define decrement_cursor					     (0x04)

// >> increment cursor, shift cursor to right.
#define increment_cursor					     (0x06)

/* Sets entire display on/off, cursor on/off, and blinking of cursor position character.
 * delay time = 37us, ~= 40 us*/

// >> display off and cursor off.
#define display_off_cursor_off				     (0x08)

// >> display on and cursor off.
#define display_on_cursor_off		  	         (0x0C)

// display on and cursor on, no blinking.
#define display_on_cursor_on_no_blinking		 (0x0E)

/* display on and cursor blinking*/
#define display_on_cursor_blinking			     (0x0F)

/* Moves cursor and shifts display without changing DDRAM contents.
 * delay time = 37 us, ~= 40 us*/
// >> Cursor move to the left.
#define cursor_move_to_the_left					 (0x10)

// >> Cursor move to the right.
#define cursor_move_to_the_right			     (0x14)

// >> display move to the left.
#define display_move_to_the_left				 (0x18)

// >> display move to the right.
#define display_move_to_the_right				 (0x1C)

/* Sets interface data length (DL), number of display lines (N), and character font (F).
 * delay time = 37 us, ~= 40 us*/
// >> 4-bit mode.
#define _4_bits_1_line_5x8_dots					 (0x20)
#define _4_bits_1_line_5x10_dots				 (0x24)
#define _4_bits_2_lines_5x8_dots				 (0x28)

// >> 8-bit mode.
#define _8_bits_1_line_5x8_dots					 (0x30)
#define _8_bits_1_line_5x10_dots				 (0x34)
#define _8_bits_2_lines_5x8_dots				 (0x38)

/* beginning to the 1st line */
/* 0x8n, n = 0:F ==> n is the cursor position. */
#define force_cusror_to_start_with_1st_row	     (0x80)

/* beginning to the 2nd line */
/* 0xCn, n = 0:F ==> n is the cursor position. */
#define force_cusror_to_start_with_2nd_row	     (0xC0)

/* init lcd mode. */
#define __init__							     (0x32)
#endif /* LCD_LCD16X2_COMMANDS_H_ */
