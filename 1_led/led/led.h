/*
 * led.h
 *
 *  Created on: Sep 23, 2021
 *      Author: Mahmoud Mohamed Younis
 */

#ifndef LED_LED_H_
#define LED_LED_H_
/* inclusions*/
#include <avr/io.h>
#include <util/delay.h>

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * \class		  LED
 *
 * \details		- Class controls two types of led connections.
 * 				- Pull-up and Pull-down connections.
 * 				- Can control led by initialization, turn-on, turn-off, toggle and blink functions.
 * 				- state variable in init function if led is pull-up => 0 else pull-down => 1.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
class LED{
public:
	void init(unsigned volatile char *DDRx,uint8_t volatile *PORTx, uint8_t PINn,uint8_t state);	// initialization.
	void turn_on(void);			 // Turn led on.
	void turn_off(void);		 // Turn led offs.
	void toggle(void);			 // led toggle state.
	void blink(uint16_t time);   // led blink function.

private:
	unsigned volatile char  *DDR;
	uint8_t volatile  *PORT;
			 uint8_t   pin;
			 uint8_t   state;
};





#endif /* LED_LED_H_ */
