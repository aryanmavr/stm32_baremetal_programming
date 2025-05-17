//timer 1second

#include "stm32f446xx.h"
#include "led.h"

#define TIME2EN              (1U<<0)
#define CR1EN                (1U<<0)
#define OC_TOGGLE            ((1U<<4)|(1U<<5))
#define CCER_CC1E            (1U<<0)

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


void tim2_pa5_output_compare(void)
{

	/*led pa5*/
	led_init();

	/*enable clk access to tim2	*/
	RCC->APB1ENR |= TIME2EN;

	/* set prescaler value*/
	TIM2->PSC = 1600-1; // 16 000 000/1600 = 10 000

	/*set auto-reload value*/
	TIM2->ARR = 10000 - 1; //10 000 / 10 000 = 1

	/*set output compare toggle mode*/
	TIM2->CCMR1 |= OC_TOGGLE;
	/*enable tim2 ch1 in compare mode*/
	TIM2->CCER |= CCER_CC1E;

	/* clear counter*/
	TIM2->CNT = 0;

	/*enable timer*/
	TIM2->CR1 |= CR1EN;
}


