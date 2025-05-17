#include <stdio.h>
#include <stdint.h>
#include "stm32f446xx.h" // selected the correct board model from stm32f4xx.h file

#include "uart.h"
#include "led.h"


char key;

static void uart_callback(void);


int main(void)
{

	uart2_txrx_interrupt_init();
	led_init();

	while(1)
	{

		key = uart2_read();
		if(key == '5')
		{
			led_on();
		}
		else
		{
			led_off();
		}
	}

}

static void uart_callback(void)
{
	key = USART2->DR;
	if(key == '5')
	{
		led_on();
	}
	else
	{
		led_off();
	}
}

void USART2_IRQHandler(void)
{
	/*ChecK if RXNE is set*/

	if(USART2->SR & SR_RXNE)
	{
		//DO something
		uart_callback();
	}
}




