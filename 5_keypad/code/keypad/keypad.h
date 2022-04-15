/*
 * keypad.h
 *
 *  Created on: Oct 1, 2021
 *      Author: Mahmoud Mohamed Younis
 */

#ifndef KEYPAD_KEYPAD_H_
#define KEYPAD_KEYPAD_H_
/* inclusions */
#include <avr/io.h>
#include <util/delay.h>
/*
 * * * * * * * * * * * * * * *
 * \class		 Keypad_4x3_ *
 * * * * * * * * * * * * * * *
 */
class keypad_4x3_{
public:
	// initialization function.
	void init(volatile uint8_t *column_DDRx, volatile uint8_t *column_PINx,  volatile uint8_t *column_PUDx,
			  volatile uint8_t *row_DDRx, volatile uint8_t *row_PRTx,
			  uint8_t  R_pin[4], uint8_t  C_pin[3], uint8_t key_map[4][3]){
		/* Save hardware configuration. */
		// 1.Columns.
		column_DDR = column_DDRx;
		column_PIN = column_PINx;
		column_PUD = column_PUDx;
		for(uint8_t c=0; c<3; c++){
			column_pin[c] = C_pin[c];
		}

		// 2.Rows.
		row_DDR = row_DDRx;
		row_PRT = row_PRTx;
		for(uint8_t r=0; r<4; r++){
			row_pin[r] = R_pin[r];
		}

		/* Save key map. */
		for(uint8_t r=0; r<4; r++){
			for(uint8_t c=0; c<3; c++){
				map[r][c] = key_map[r][c];
			}
		}

		/* Configure columns as input, plus activate pull-up resistors. */
		for(uint8_t c=0; c<3; c++){
			// 1.Configure pins as input.
			*column_DDR &= ~(1<<column_pin[c]);
			// Insert nop for synchronization
			__asm__("nop");

			// 2.Activate PUR.
			*column_PUD |= (1<<column_pin[c]);
			// Insert nop for synchronization
			__asm__("nop");
		}

		/* Configure rows as output. */
		for(uint8_t r=0; r<4; r++){
			// 1.Configure pins as output.
			*row_DDR |= (1<<row_pin[r]);
			// Insert nop for synchronization
			__asm__("nop");

			// 2. All pins initially low.
			*row_PRT &= ~(1<<row_pin[r]);
			// Insert nop for synchronization
			__asm__("nop");
		}
	}

	void read(uint8_t *key){
		/* Idea: activate only one row then read all columns.
		 * when a key is pressed i already know it's row and
		 * it's column.
		 * Note that: row is active low.
		 */
		for(uint8_t r=0; r<4; r++){
			// 1.Deactivate all rows.
			*row_PRT |= (1<<row_pin[0]);
			*row_PRT |= (1<<row_pin[1]);
			*row_PRT |= (1<<row_pin[2]);
			*row_PRT |= (1<<row_pin[3]);

			// 2.Activate specific row.
			*row_PRT &= ~(1<<row_pin[r]);

			// 3.Read all columns then return key value.
			for(uint8_t c=0; c<3; c++){
				if(is_pressed(column_pin[c]) == true){
					*key = map[r][c];
					return;
				}

				// Insert nop for synchronization
				__asm__("nop");
			}
		}
		/*----------------------------------------------------*/
		/*       Second method to write read function         */
		/*----------------------------------------------------*/
		/* // 1.Activate first row.
		*row_PRT &=  ~(1<<row_pin[0]);
		*row_PRT |=  (1<<row_pin[1]);
		*row_PRT |=  (1<<row_pin[2]);
		*row_PRT |=  (1<<row_pin[3]);

		// 1.1.Read first column.
		if(is_pressed(column_pin[0]) == true){
			*key = map[0][0];
			return;
		}
		// 1.2.Read second column.
		else if(is_pressed(column_pin[1]) == true){
			*key = map[0][1];
			return;
		}
		// 1.3.Read third column.
		else if(is_pressed(column_pin[2]) == true){
			*key = map[0][2];
			return;
		}

		// Insert nop for synchronization
		__asm__("nop");

		// 2.Activate second row.
		*row_PRT |=  (1<<row_pin[0]);
		*row_PRT &= ~(1<<row_pin[1]);
		*row_PRT |=  (1<<row_pin[2]);
		*row_PRT |=  (1<<row_pin[3]);

		// 2.1.Read first column.
		if(is_pressed(column_pin[0]) == true){
			*key = map[1][0];
			return;
		}
		// 2.2.Read second column.
		else if(is_pressed(column_pin[1]) == true){
			*key = map[1][1];
			return;
		}
		// 2.3.Read third column.
		else if(is_pressed(column_pin[2]) == true){
			*key = map[1][2];
			return;
		}

		// Insert nop for synchronization
		__asm__("nop");

		// 3.Activate third row.
		*row_PRT |=  (1<<row_pin[0]);
		*row_PRT |=  (1<<row_pin[1]);
		*row_PRT &= ~(1<<row_pin[2]);
		*row_PRT |=  (1<<row_pin[3]);

		// 3.1.Read first column.
		if(is_pressed(column_pin[0]) == true){
			*key = map[2][0];
			return;
		}
		// 3.2.Read second column.
		else if(is_pressed(column_pin[1]) == true){
			*key = map[2][1];
			return;
		}
		// 3.3.Read third column.
		else if(is_pressed(column_pin[2]) == true){
			*key = map[2][2];
			return;
		}

		// Insert nop for synchronization
		__asm__("nop");

		// 4.Activate fourth row.
		*row_PRT |=  (1<<row_pin[0]);
		*row_PRT |=  (1<<row_pin[1]);
		*row_PRT |=  (1<<row_pin[2]);
		*row_PRT &= ~(1<<row_pin[3]);

		// 4.1.Read first column.
		if(is_pressed(column_pin[0]) == true){
			*key = map[3][0];
			return;
		}
		// 4.2.Read second column.
		else if(is_pressed(column_pin[1]) == true){
			*key = map[3][1];
			return;
		}
		// 4.3.Read third column.
		else if(is_pressed(column_pin[2]) == true){
			*key = map[3][2];
			return;
		}*/
		/*----------------------------------------------------*/
	}

private:
	volatile uint8_t *column_DDR;
	volatile uint8_t *column_PIN;
	volatile uint8_t *column_PUD;
	volatile uint8_t *row_DDR;
	volatile uint8_t *row_PRT;
			 uint8_t  row_pin[4];
			 uint8_t  column_pin[3];
			 uint8_t  map[4][3];

	bool read_pin(uint8_t pin){
		// PIN register value.
		uint8_t PINR_value = 0x00;

		// connected pin value.
		bool pin_value = false;

		// Read PIN register.
		PINR_value = *column_PIN;

		// Mask to read the certain pin.
		pin_value = (bool) (PINR_value & (1<<pin));

		// Insert nop for synchronization
		__asm__("nop");
		__asm__("nop");

		return pin_value;
	}

	bool is_pressed(uint8_t pin){
		// pressed key state value.
		bool ispressed = false;

		/* stability loop. */
		// key is pressed when red_pin function return zero.
		while(read_pin(pin) == false){
			ispressed = true;
		}

		return ispressed;
	}
};

#endif /* KEYPAD_KEYPAD_H_ */
