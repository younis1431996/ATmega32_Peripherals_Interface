/*
 * main.cpp
 *
 *  Created on: Sep 23, 2021
 *      Author: Mahmoud Mohamed Younis
 */
/* inclusion */
#include "../led/led.h"

int main(void){
	// Create objects.
	LED led_pull_up;
	LED led_pull_down;

	// initialization.
	led_pull_up.init(&DDRD, &PORTD, PD0, 0);
	led_pull_down.init(&DDRB, &PORTB, PB2, 1);

	// pull-up scenario.
	led_pull_up.turn_on();
	_delay_ms(1000);
	led_pull_up.turn_off();
	_delay_ms(1000);
	led_pull_up.toggle();

	// pull-own scenario.
	led_pull_down.turn_on();
	_delay_ms(1000);
	led_pull_down.turn_off();
	_delay_ms(1000);
	led_pull_down.toggle();
	_delay_ms(1000);

	// Blinking.
	for(;;){
		led_pull_up.toggle();
		led_pull_down.toggle();
		_delay_ms(1000);
	}
	return 0;
}



