/*
 * EX_interrupts.h
 *
 *  Created on: Oct 2, 2021
 *      Author: Mahmoud Mohamed Younis
 */

#ifndef EXTERNAL_INTERRUPTS_EX_INTERRUPTS_H_
#define EXTERNAL_INTERRUPTS_EX_INTERRUPTS_H_
/* inclusions */
#include <avr/io.h>
#include <avr/interrupt.h>

/* Macro to disable all interrupts. */
#ifndef disable_all_interrupts
#define disable_all_interrupts() 	cli()
#endif

/* External Interrupt #0 */
void EX_interrupt_0_init(uint8_t mode);
void EX_interrupt_0_mode_select();
void EX_interrupt_0_Enable(void);
void EX_interrupt_0_Disable(void);

/* External Interrupt #1 */
void EX_interrupt_1_init(uint8_t mode);
void EX_interrupt_1_Enable(void);
void EX_interrupt_1_Disable(void);

/* External Interrupt #2 */
void EX_interrupt_2_init(uint8_t mode);
void EX_interrupt_2_Enable(void);
void EX_interrupt_2_Disable(void);

#endif /* EXTERNAL_INTERRUPTS_EX_INTERRUPTS_H_ */
