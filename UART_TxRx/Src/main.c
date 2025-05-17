#include <stdio.h>
#include <stdint.h>
#include "stm32f446xx.h" // selected the correct board model from stm32f4xx.h file

#include "uart.h"
#include "led.h"


char pass;


int main(void)
{

	uart2_txrx_init();
	led_init();

	while(1)
	{

		pass = uart2_read();
		if(pass == '5')
		{
			led_on();
		}
		else
		{
			led_off();
		}
	}

}







