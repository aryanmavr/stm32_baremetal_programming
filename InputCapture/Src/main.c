// capture timestamp from our pa5 timer to our pa6 timer. connect jumper cable from pa5 to pa6
#include <stdio.h>
#include <stdint.h>
#include "stm32f446xx.h"

#include "uart.h"
#include "timer.h"


uint32_t timestamp = 0;

int main(void)
{

	tim2_pa5_output_compare();
	tim3_pa6_input_capture();

	while(1)
	{

		/*wait until edge is captured*/
		while(!(TIM3->SR & SR_CC1IF)){}

		/*read captured value*/
		timestamp = TIM3->CCR1;
	}

}








