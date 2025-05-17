// blinking led with systick timer
#include <stdio.h>
#include <stdint.h>
#include "stm32f446xx.h"

#include "uart.h"
#include "led.h"
#include "systick.h"

static void systick_callback(void);

int main(void)
{
	led_init();
	uart2_tx_init();
	systick_1hz_interrupt();

	while(1)
	{


	}

}


static void systick_callback(void)
{
	led_toggle();
	printf("one second has passed\n\r");
}

void SysTick_Handler(void)
{
	//Do something...
	systick_callback();
}








