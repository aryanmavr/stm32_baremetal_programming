#include "stm32f446xx.h"
#include "systick.h"



#define SYSTICK_LOAD_VAL          16000  //16mhz clock so 16000 cycles gives us a delay of 1ms
#define CTRL_ENABLE              (1U<<0)
#define CTRL_CLKSRC              (1U<<2)
#define CTRL_COUNTFLAG           (1U<<16)



void systickDelayMs(int delay)
{
	/*Reload with number of clocks per millisecond*/
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	/*Clear systick current value register */
	SysTick->VAL = 0;

	/*Enable systick and select internal clk src*/
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;


	for(int i=0; i<delay ; i++){
		/*Wait until the COUNTFLAG is set*/
		while(!(SysTick->CTRL & CTRL_COUNTFLAG)){}
	}

	SysTick->CTRL = 0;
}


