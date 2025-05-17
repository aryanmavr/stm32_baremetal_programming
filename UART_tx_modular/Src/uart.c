/*
 * uart.c
 *
 *  Created on: Jan 1, 2025
 *      Author: Aryan
 */
#include "uart.h"

#define GPIOAEN                 (1U << 0)
#define UART2EN                 (1U << 17)

#define CR1_UE                  (1U << 13)
#define CR1_TE                  (1U << 3)
#define SR_TXE                  (1U << 7)

#define SYS_FREQ                16000000  //default freq
#define APB1_CLK                SYS_FREQ

#define UART_BAUDRATE           115200


static void uart_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);


void uart2_write(int ch);

int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}

void uart2_tx_init(void)
{
	/*****configure uart gpio pin******/

	/* enable clock access to gpioa*/
	RCC->AHB1ENR |= GPIOAEN;

	/* set pa2 mode to alternate function mode*/
	GPIOA->MODER |= (1U << 5);
	GPIOA->MODER &= ~(1U <<4);

	/* set pa2 alternate function type to UART_TX (AF07) */
	//check for the function type in alternate function map in datasheet
	// THE alternate func reg ( low 0-7 and high 8-15 ) in header file there is only AFR together
	//when reffering to lower 8 use index 0 and for upper 8 use index 1
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	/******configure uart module ********/
	/* enable clock access to uart2 */
	RCC->APB1ENR |= UART2EN;

	/* configure baudrate */
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	/* configure the transfer direction */
	//check ref manual for cr1
	USART2->CR1 = CR1_TE; //by reseting other bits and setting only TE we are keeping the uart at default values and Transmit

	/* enable uart module */
	//now we enable usart2
	USART2->CR1 |= CR1_UE;
}

void uart2_write(int ch)
{
	/*****check if data reg is empty by checking Status reg TXE bit****/
	while(!(USART2->SR & SR_TXE)){}

	/*send the char to data reg*/
	USART2->DR = (ch & 0xFF); // we do and with 0xFF because our data is 8 bit
}

static void uart_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk, uint32_t BaudRate)
{
	//we can use this function for any uart
	USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}


static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	//empirical formula that calculates the value that is to be fed into baudrate reg
	return ((PeriphClk + (BaudRate/2U))/ BaudRate);
}
