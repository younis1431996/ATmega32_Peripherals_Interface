/*
 * Timer0.h
 *
 *  Created on: Oct 4, 2021
 *      Author: Mahmoud Mohamed Younis
 */

#ifndef TIMER0_TIMER0_H_
#define TIMER0_TIMER0_H_

/* inclusions */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>

/* * * * * * * * * * * * * * * * Timer-0 programming * * * * * * * * * * * * * * * */
/* Modes:
 *  1.Delay generation -> normal mode.
 *  2.Delay generation -> output compare mode.
 *  3.Square wave generation --> OC0[PB3], duty-cycle = 50%.
 *  4.Square wave generation any pin + best frequency approximation.
 *  5.PWM generation.
 */

#define timer0_mode 5

/* 1.Delay generation -> normal mode */
#if timer0_mode == 1

void timer0_delay_ms_(uint16_t __ms);
void timer0_delay_us_(uint16_t __us);

#endif /* TIMER0_MODE_ == 1*/

/* 2.Delay generation -> output compare mode */
#if timer0_mode == 2

void timer0_delay_ms_(uint16_t __ms);
void timer0_delay_us_(uint16_t __us);

#endif /* TIMER0_MODE_ == 2 */

/* 3.Square wave generation --> OC0[PB3], duty-cycle = 50%. */
#if timer0_mode == 3

void timer0_square_wave_generation_OC0_(double _freq_HZ_);

#endif /* TIMER0_MODE_ == 3*/

/* 4.Square wave generation any pin + best frequency approximation */
#if timer0_mode == 4

void timer0_square_wave_generation_interrupt_method(volatile uint8_t *PRT, uint8_t pin,
									double __freq_HZ_);
#endif /* TIMER0_MODE_ == 4*/

/* 5.PWM generation */
#if timer0_mode == 5

void timer0_PWM_init(uint8_t Duty_Cycle);

#endif /* TIMER0_MODE_ == 5*/

#endif /* TIMER0_TIMER0_H_ */
