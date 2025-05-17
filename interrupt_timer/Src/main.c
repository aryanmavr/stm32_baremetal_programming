// blinking led with systick timer
#include <stdio.h>
#include <stdint.h>
#include "stm32f446xx.h"

#include "uart.h"
#include "led.h"
#include "timer.h"

static void tim2_callback(void);

int main(void)
{
	led_init();
	uart2_tx_init();
	tim2_1hz_interrupt_init();

	while(1)
	{


	}

}

static void tim2_callback(void)
{
	led_toggle();
	printf("one second has passed(TMEOUT)\n\r");

}


void TIM2_IRQHandler(void)
{
	/*clear update interrupt flag*/
	TIM2->SR &=~ SR_UIF;
	/*do something*/
	tim2_callback();
}







