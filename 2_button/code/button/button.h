/*
 * button.h
 *
 *  Created on: Sep 23, 2021
 *      Author: Mahmoud Mohamed Younis
 */

#ifndef BUTTON_BUTTON_H_
#define BUTTON_BUTTON_H_
/* inclusions */
#include <avr/io.h>
#include <util/delay.h>

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * \class		- button
 *
 * \details		- Class controls buttons.
 * 				- Can control button by initialization, is-pressed, turn-off, state functions.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
class button{
public:
	void init(volatile uint8_t *DDRx, volatile uint8_t *PINx, uint8_t PINn);
	bool is_pressed(void);
	void set_state_value(uint16_t number_of_states);
	void state_value(void);
	void reset_current_state(void);
	uint16_t current_state;

	// default constructor.
	button(){
		current_state = 0;
	}

private:
	volatile uint8_t  *DDR;
	volatile uint8_t  *PIN;
			 uint8_t   pin;
			 uint16_t  state;
	bool read_pin(void);
};



#endif /* BUTTON_BUTTON_H_ */
