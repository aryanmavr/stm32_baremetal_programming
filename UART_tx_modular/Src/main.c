#include <stdio.h>
#include <stdint.h>
#include "stm32f446xx.h" // selected the correct board model from stm32f4xx.h file

#include "uart.h"




int main(void)
{
	uart2_tx_init();

	while(1)
	{
		printf("Hello! I'm Aryan \n\r");
	}

}







