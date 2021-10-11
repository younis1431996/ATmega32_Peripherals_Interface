/*
 * ADC.h
 *
 *  Created on: Oct 7, 2021
 *      Author: Mahmoud Mohamed Younis
 */

#ifndef ADC_ADC_H_
#define ADC_ADC_H_
/* inclusions */
#include <avr/io.h>
#include <util/delay.h>

/* Steps to Program ADC */
/* 1.Make the ADC channel pin as an input.
 * 2.Set ADC enable bit in ADCSRA, select the conversion speed using ADPS2 : 0.
 *   For example, we will select devisor 128.
 * 3.Select ADC reference voltage using REFS1: REFS0 in ADMUX register.
 *   for example, we will use AVcc as a reference voltage.
 * 4.Select the ADC input channel using MUX4 : 0 in ADMUX, for example, we will use channel 0.
 *   So our value in register ADCSRA = 0x87 and ADMUX = 0x40.
 * 5.Start conversion by setting bit ADSC in ADCSRA. E.g.ADCSRA |= (1<<ADSC);
 * 6.Wait for conversion to complete by polling ADIF bit in ADCSRA register.
 * 7.After the ADIF bit gone high, read ADCL and ADCH register to get digital output.
 *   Notice that read ADCL before ADCH; otherwise result will not be valid.
 */

// 1.initialization
void ATmega32_ADC_init(uint8_t freq_divisor);


// 2.initialize channel.
void ATmega32_ADC_channel_select(uint8_t channel);

// 3.Select V reference.
void ATmega32_ADC_V_REF(uint8_t v_ref);

// 4.start conversion.
void ATmega32_ADC_start_convertion(void);

// 5.Check conversion.
bool ATmega32_ADC_check_conversion(void);

// 6.Read Data.
int ATmega32_ADC_read(void);

// Disable;
void ATmega32_ADC_disable(void);

#endif /* ADC_ADC_H_ */
