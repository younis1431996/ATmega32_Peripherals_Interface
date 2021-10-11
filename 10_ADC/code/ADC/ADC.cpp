/*
 * ADC.cpp
 *
 *  Created on: Oct 7, 2021
 *      Author: Mahmoud Mohamed Younis
 */
/* inclusions */
#include "ADC.h"

// 1.initialization
void ATmega32_ADC_init(uint8_t freq_divisor){
	// Enable ADC.
	ADCSRA |= (1<<ADEN);

	// Select Prescaler .
	if(freq_divisor == 2){
		ADCSRA |= 0x01;
	}else if(freq_divisor == 4){
		ADCSRA |= 0x02;
	}else if(freq_divisor == 8){
		ADCSRA |= 0x03;
	}else if(freq_divisor == 16){
		ADCSRA |= 0x04;
	}else if(freq_divisor == 32){
		ADCSRA |= 0x05;
	}else if(freq_divisor == 64){
		ADCSRA |= 0x06;
	}else if(freq_divisor == 128){
		ADCSRA |= 0x07;
	}
}

// 2.initialize channel.
void ATmega32_ADC_channel_select(uint8_t channel){
	/* set channel as input */
	DDRA = ~(1<<channel);

	/* Mask register */
	ADMUX &= 0xE0;

	/* Set input channel to read */
	ADMUX |= (channel & 0x0f);
}

// 3.Select V reference.
/* 0 >> AREF pin.
 * 1 >> AVCC pin i.e. Vcc 5 V.
 * 2 >> Internal 2.
 */
void ATmega32_ADC_V_REF(uint8_t v_ref){
	if(v_ref == 0){
		ADMUX &= ~(1<<REFS0);
		ADMUX &= ~(1<<REFS1);
	}
	else if(v_ref == 1){
		ADMUX |=  (1<<REFS0);
		ADMUX &= ~(1<<REFS1);
	}
	else if(v_ref == 2){
		ADMUX |= (1<<REFS0);
		ADMUX |= (1<<REFS1);
	}
	return;
}

// 6.start conversion.
void ATmega32_ADC_start_convertion(void){
	ADCSRA |= (1<<ADSC);
}

// 7.Check conversion.
bool ATmega32_ADC_check_conversion(void){
	while((ADCSRA&(1<<ADIF))==0);
	_delay_us(10);
	return true;
}

// 8.Read Data.
int ATmega32_ADC_read(void){
	/* Read lower byte*/
	int ADC_Data_L = (int)ADCL;

	/* Read higher 2 bits and Multiply with weight */
	int ADC_Data_H = (int)ADCH*256;

	/* add two values. */
	ADC_Data_H += ADC_Data_L;

	/* return value. */
	return ADC_Data_H;
}

// Disable;
void ATmega32_ADC_disable(void){
	ADCSRA &= ~(1<<ADEN);
	return;
}


