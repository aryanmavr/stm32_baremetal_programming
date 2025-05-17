// blinking led with systick timer
#include <stdio.h>
#include <stdint.h>
#include "stm32f446xx.h"

#include "uart.h"
#include "led.h"
#include "timer.h"



int main(void)
{
	led_init();
	uart2_tx_init();
	tim2_1hz_init();

	while(1)
	{
		/*wait for UIF to occur*/
		while(!(TIM2->SR & SR_UIF)){}

		/*clear the UIF bit*/
		TIM2->SR &= ~SR_UIF;

		led_toggle();
		printf("one second has passed(TMEOUT)\n\r");


	}

}








