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
	DDRD |= (1<<PD3);
	led_pull_up.init(&DDRD, &PORTD, PD0, 0);

	for(;;);
	return 0;
}



