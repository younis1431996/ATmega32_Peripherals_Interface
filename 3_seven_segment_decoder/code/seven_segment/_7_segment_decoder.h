/*
 * _7_segment_decoder.h
 *
 *  Created on: Sep 24, 2021
 *      Author: Mahmoud Mohamed Younis
 */

#ifndef SEVEN_SEGMENT__7_SEGMENT_DECODER_H_
#define SEVEN_SEGMENT__7_SEGMENT_DECODER_H_
/* inclusions */
#include <avr/io.h>
#include <util/delay.h>

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * \class		- _binary_7_segment_
 *
 * \details		- Class contains hardware configuration of a 7-segment.
 * 				- Has each pin configuration.
 * 				- Can write the value to each pin alone.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
class _binary_7_segment_{
public:
	void init(volatile uint8_t *DDR[4], volatile uint8_t *PORT[4], uint8_t data_pin[4]);
	void display(uint8_t number);

private:
	volatile uint8_t *DDR[4];
	volatile uint8_t *PORT[4];
			 uint8_t data_pin[4];
	void set_pin(volatile uint8_t *PORTx, uint8_t pin);
	void reset_pin(volatile uint8_t *PORTx, uint8_t pin);
};
#endif /* SEVEN_SEGMENT__7_SEGMENT_DECODER_H_ */
