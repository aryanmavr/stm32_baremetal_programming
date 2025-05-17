#include <stdio.h>
#include <stdint.h>
#include "stm32f446xx.h" // selected the correct board model from stm32f4xx.h file

#include "uart.h"
#include "led.h"




static void dma_callback(void);


int main(void)
{

	char message[31] = "Hi I'm aryan\n\r";
	uart2_txrx_interrupt_init();
	led_init();
	dma1_stream6_init((uint32_t) message, (uint32_t) &USART2->DR, 31);

	while(1)
	{


	}

}

static void dma_callback(void)
{
	led_toggle();
}

void DMA1_Stream6_IRQHandler(void)
{
	/*check for transfer complete interrupt*/
	if(DMA1->HISR & HISR_TCIF6)
	{
		/*clear flag*/
		DMA1->HIFCR |= HIFCR_CTCIF6;

		/*do some callback*/
		dma_callback();
	}
}




