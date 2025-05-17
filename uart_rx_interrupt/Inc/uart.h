/*
 * uart.h
 *
 *  Created on: Jan 1, 2025
 *      Author: Aryan
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f446xx.h"
#include <stdint.h>


#define SR_RXNE                 (1U << 5)

void uart2_txrx_interrupt_init(void);
void uart2_txrx_init(void);
char uart2_read(void);

#endif /* UART_H_ */
