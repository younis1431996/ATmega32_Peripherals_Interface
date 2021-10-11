/*
 * main.cpp
 *
 *  Created on: Oct 4, 2021
 *      Author: Mahmoud Mohamed Younis
 */
/* inclusions */
#include "../Timer0/Timer0.h"

int main(void){
/* 1.Delay generation -> normal mode */
#if timer0_mode == 1
	// configure led pin as output.
	DDRC |= (1<<PC0);
	// initialized low.
	PORTC &= ~(1<<PC0);

	// Endless loop.
	for(;;){
		// Delay generation.
		timer0_delay_ms_(1000);

		// toggle PC0.
		PORTC ^= (1<<PC0);
	}

	// Exit.
	return 0;

#endif /* _DELAY_GENERATION_NORMAL_MODE_ */

/*------------------------------------------------------------------------------------*/

/* 2.Delay generation -> output compare mode */
#if timer0_mode == 2
	// configure led pin as output.
	DDRC |= (1<<PC1);
	// initialized low.
	PORTC &= ~(1<<PC1);

	// Endless loop.
	for(;;){
		// Delay generation.
		timer0_delay_ms_(1000);

		// toggle PC0.
		PORTC ^= (1<<PC1);
	}

	// Exit.
	return 0;

#endif /* _DELAY_GENERATION_OUTPUT_COMPARE_MODE_ */

/*------------------------------------------------------------------------------------*/

#if timer0_mode == 3

	timer0_square_wave_generation_OC0_(2000000);

#endif /* SQUARE_WAVE_GENERATION */

/*------------------------------------------------------------------------------------*/

#if timer0_mode == 4
	DDRD |= (1<<PD1);
	timer0_square_wave_generation_interrupt_method(&PORTD, PD1, 1000);

#endif /* SQUARE_WAVE_GENERATION */

/*------------------------------------------------------------------------------------*/

#if timer0_mode == 5

	timer0_PWM_init(40);

#endif /* SQUARE_WAVE_GENERATION */

}





