// blinking led with systick timer
#include <stdio.h>
#include <stdint.h>
#include "stm32f446xx.h"

#include "uart.h"
#include "led.h"
#include "systick.h"



int main(void)
{
	led_init();
	uart2_tx_init();

	while(1)
	{
		led_toggle();
		printf("one second has passed\n\r");
		systickDelayMs(1000);

	}

}








