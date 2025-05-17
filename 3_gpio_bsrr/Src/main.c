#include "stm32f446xx.h" // selected the correct board model from stm32f4xx.h file

#define GPIOAEN                 (1U << 0)
#define PIN5                    (1U<<5)
#define LED_PIN                  PIN5


int main(void)
{
	RCC->AHB1ENR |= GPIOAEN; // setting clock to port A
	GPIOA->MODER |= (1U<<10); // setting the PA5 as output
	GPIOA->MODER &= ~(1U<<11); //setting the PA5 as output

	while(1)
	{
		GPIOA->BSRR = LED_PIN; // setting the BS5 at 5 pos to set the pin5
		for(int i=0; i< 500000; i++){}

		GPIOA->BSRR = (1U<<21); // setting the BR5 at pos 21 to reset the pin5
		for(int i=0; i< 500000; i++){}
	}

}
