/*
 * main.cpp
 *
 *  Created on: Oct 11, 2021
 *      Author: Mahmoud Mohamed Younis
 */

/* inclusions */
#include "../ATmega32_USART/ATmega32_USART.h"

int main()
{
	// initialize USART protocol.
	ATmega32_USART_baud_rate_init(9600);

	/* Synchronous Mode */
	//ATmega32_USART_sync_mode_enable();
	//ATmega32_USART_sync_mode_disable();

	ATmega32_USART_TX_enable();
	ATmega32_USART_RX_enable();
	ATmega32_USART_char_size(8);

	char received_char[50];

	while(1)
	{
		ATmega32_USART_receive_str(received_char);
		ATmega32_USART_transmit_str(received_char);

	}
}




