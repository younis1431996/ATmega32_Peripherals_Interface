/*
 * Timer0.cpp
 *
 *  Created on: Oct 4, 2021
 *      Author: Mahmoud Mohamed Younis
 */
/* inclusions */
#include "Timer0.h"

/* 1.Delay generation -> normal mode */
#if timer0_mode == 1

/* MCU frequency = 8MHZ.
 * pre-scaler = 1/64.
 * Tclk = 0.125 [usec].
 * T[timer] = 64*0.125 = 8 [usec].
 * # of counts = 1 [msec]/8 [usec] = 125.
 * initial value (TCNT0) = 255 - 126 + 1(roll over)= 131
 */
void timer0_delay_ms_(uint16_t __ms){
	for(uint16_t i=0; i<__ms; i++){
		// load initial value for 1 msec delay.
		TCNT0 = 131;

		// Normal mode.
		TCCR0 &= ~(1<<WGM01);
		TCCR0 &= ~(1<<WGM00);

		// pre-scaler = 1/64.
		TCCR0 |= (1<<CS00);
		TCCR0 |= (1<<CS01);
		TCCR0 &= ~(1<<CS02);

		// Wait for TOV0 to roll over.
		while( (TIFR&(1<<TOV0)) == 0);

		// Turn off timer.
		TCCR0 = 0x00;

		// Clear TOV0.
		TIFR |= (1<<TOV0);
	}
	return;
}

/* MCU frequency = 8MHZ.
 * no pre-scaler.
 * Tclk = 0.125 [usec].
 * T[timer] = 1*0.125 = 0.125 [usec].
 * number of counts = 1 [usec]/0.125 [usec] = 8.
 * initial value (TCNT0) = 255 - 8 + 1(roll over) = 248.
 */
void timer0_delay_us_(uint16_t __us){
	for (uint16_t i=0; i<__us; i++){
		// load initial value.
		TCNT0 = 248;

		// Normal mode.
		TCCR0 &= ~(1<<WGM01);
		TCCR0 &= ~(1<<WGM00);

		// no pre-scaler.
		TCCR0 |=  (1<<CS00);
		TCCR0 &= ~(1<<CS01);
		TCCR0 &= ~(1<<CS02);

		// Wait for TOV0 to roll over.
		while( (TIFR&(1<<TOV0)) == 0);

		// Turn off timer.
		TCCR0 = 0x00;

		// Clear TOV0.
		TIFR |= (1<<TOV0);
	}
	return;
}

#endif /* TIMER0_MODE_ == 1*/

/*--------------------------------------------------------------------------------------------*/

/* 2.Delay generation -> output compare mode */
#if timer0_mode == 2
/*
 * OCR0 = time delay / timer[clk]
 * time delay = 1000[usec], timer[clk] = 64*0.125 = 8[usec]
 * OCR0 = 1000/8  = 125
 */
void timer0_delay_ms_(uint16_t __ms){
	for(uint16_t i=0; i<__ms; i++){
		// load OCR0 initial value for 1 msec delay.
		OCR0 = 125;

		// load TCNT0 with 0x00.
		TCNT0 = 0;

		// CTC mode.
		TCCR0 |=  (1<<WGM01);
		TCCR0 &= ~(1<<WGM00);

		// pre-scaler = 1/64.
		TCCR0 |= (1<<CS00);
		TCCR0 |= (1<<CS01);
		TCCR0 &= ~(1<<CS02);

		// CTC, normal mode.
		TCCR0 &= ~(1<<COM00);
		TCCR0 &= ~(1<<COM01);

		// Wait for TOV0 to roll over.
		while( (TIFR&(1<<OCF0)) == 0);

		// Turn off timer.
		TCCR0 = 0x00;

		// Clear OCF0.
		TIFR |= (1<<OCF0);
	}
	return;
}

/*
 * OCR0 = time delay / timer[clk] - 1(roll-over)
 * time delay = 1[usec], timer[clk] = 1*0.125 = 0.125[usec]
 * OCR0 = 1/0.125  = 8
 */
void timer0_delay_us_(uint16_t __us){
	for(uint16_t i=0; i<__us; i++){
		// load OCR0 initial value for 1 usec delay.
		OCR0 = 7;

		// load TCNT0 with 0x00.
		TCNT0 = 0;

		// CTC mode.
		TCCR0 |=  (1<<WGM01);
		TCCR0 &= ~(1<<WGM00);

		// pre-scaler = 1.
		TCCR0 |= (1<<CS00);
		TCCR0 &= ~(1<<CS01);
		TCCR0 &= ~(1<<CS02);

		// CTC, normal mode.
		TCCR0 &= ~(1<<COM00);
		TCCR0 &= ~(1<<COM01);

		// Wait for TOV0 to roll over.
		while( (TIFR&(1<<OCF0)) == 0);

		// Turn off timer.
		TCCR0 = 0x00;

		// Clear OCF0.
		TIFR |= (1<<OCF0);
	}
	return;
}

#endif /* TIMER0_MODE_ == 2*/

/*--------------------------------------------------------------------------------------------*/

/* Square wave generation --> OC0[PB3], duty-cycle = 50% */
#if timer0_mode == 3
/* Period of square wave = 2 * OCR0 * T[timer].
 *
 * OCR0 = Period of square wave / 2*T[timer].
 *
 * T[timer] = 0.125 * pre-scaler.
 *
 * OCR0 = Period of square wave / 2*0.125 * pre-scaler.
 *
 * OCR0 = Period of square wave / 0.25* pre-scaler
 *
 * 1.Select CTC mode.
 * 2.Program OC0 to toggle if compare match.
 * 3.Set PB0[OC0] as output.
 */
void timer0_square_wave_generation_OC0_(double _freq_HZ_){
	// Define all my pres-scalers.
	double prescaler[5] = {1024.0, 256.0, 64.0, 8.0, 1.0};

	// Define TCCR0 values to achieve pre-scaler.
	uint8_t TCCR0_value[5] = {0x1D, 0x1C, 0x1B, 0x1A, 0x19};

	// Configure PB3 [OC0] as output.
	DDRB |= (1<<PB3);

	// Calculate total period.
	double total_period = (1.0) / (_freq_HZ_);

	// Calculate T_on
	double T_on = (total_period) / (2.0);

	// Get the best pre-scaler value.
	double best_prescaler_value = 0;
	double temp = (T_on) * (8*pow(10, 6));;
	double OCR0_value = 0 ;
	for(uint8_t i=0; i<5; i++){
		// Check every pre-scaler value
		if(prescaler[i] < temp){
			best_prescaler_value = prescaler[i];
		}
	}
	// Calculate the approximate value of OCR0. (-1) for toggle clock.
	OCR0_value = lround( (temp/best_prescaler_value) ) - 1;

	// Load OCR0.
	OCR0 = (uint8_t)OCR0_value;

	// Load TCCR0.
	for(uint8_t i=0; i<5; i++){
		if(best_prescaler_value == prescaler[i])
			TCCR0 = TCCR0_value[i];
	}
	//TCCR0 = 0x1C;

}

#endif /* TIMER0_MODE_ == 3*/

/*--------------------------------------------------------------------------------------------*/

/* 4.Square wave generation any pin + best frequency approximation */
#if timer0_mode == 4

void timer0_square_wave_generation_interrupt_method(volatile uint8_t *PRT, uint8_t pin, double __freq_HZ_){
	// Calculate total period.
	double total_period = (1.0) / (__freq_HZ_);


	// Calculate T_on in [sec].
	double T_on_s = (total_period) / (2.0);

	// Calculate T_on in [usec].
	double T_on_us = T_on_s * pow(10, 6);

	// configure OC0 as output.
	DDRB |= (1<<PB3);
	DDRD |= (1<<PD1);

	// Enable global interrupt.
	sei();

	// Enable Timer/Counter0 Output Compare Match Interrupt.
	TIMSK |= (1<<OCIE0);

	// Set OCR0 value.
	OCR0 = (7);

	// Configure Timer0 -> Waveform Generation CTC mode, Compare Output Mode (Toggle OC0 on compare match) and pre-scaler = 8.
	TCCR0 = 0x89;
}

ISR(TIMER0_COMP_vect){
	PORTD ^= (1<<PD1);
}
#endif /* TIMER0_MODE_ == 4 */

/* 5.PWM generation */

#if timer0_mode == 5
void timer0_PWM_init(uint8_t Duty_Cycle){
	TCCR0=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS02);
	TCNT0=0;
	OCR0=0;
	DDRB |=(1<<PB3);
	OCR0=Duty_Cycle;
}
#endif /* TIMER0_MODE_ == 5 */

