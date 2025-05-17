//gpio interrupt
#include <stdio.h>
#include <stdint.h>
#include "stm32f446xx.h"
#include "led.h"
#include "uart.h"
#include "exti.h"

static void exti_callback(void);

int main(void)
{
	pc13_exti_init();
	led_init();
	uart2_tx_init();

	while(1)
	{


	}

}


static void exti_callback(void)
{
	printf("BTN Pressed....\n\r");
	led_toggle();

}
void EXTI15_10_IRQHandler(void) // the irq handler name should be same as in the vector table
{
	if((EXTI->PR & LINE13) != 0)
	{
		/*clear PR flag*/
		EXTI->PR |= LINE13;
		/*routine*/
		exti_callback();

	}
}







