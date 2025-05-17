//timer 1second

#include "stm32f446xx.h"

#define TIME2EN              (1U<<0)
#define CR1EN                (1U<<0)


void tim2_1hz_init(void)
{
	/*enable clk access to tim2	*/
	RCC->APB1ENR |= TIME2EN;

	/* set prescaler value*/
	TIM2->PSC = 1600-1; // 16 000 000/1600 = 10 000

	/*set auto-reload value*/
	TIM2->ARR = 10000 - 1; //10 000 / 10 000 = 1

	/* clear counter*/
	TIM2->CNT = 0;

	/*enable timer*/
	TIM2->CR1 |= CR1EN;
}


