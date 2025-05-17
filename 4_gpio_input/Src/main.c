#include "stm32f446xx.h" // selected the correct board model from stm32f4xx.h file



#define GPIOAEN                 (1U << 0)
#define GPIOCEN                 (1U << 2)


#define PIN5                    (1U<<5)
#define PIN13                   (1U<<13)
#define LED_PIN                  PIN5
#define BTN_PIN                  PIN13 //user button


int main(void)
{
	// enabling clock to port A and port C
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;

	//setting the PA5 as output
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	//setting the PC13 as input
	GPIOC->MODER &= ~(1U<<26);
	GPIOC->MODER &= ~(1U<<26);


	while(1)
	{
		/*button is active low. so initially there will be 1 in idr.
		  so led will be ON initially
		  when we press button the idr will have 0. so the the LED will turn OFF
		  to detect press we need detect low signal*/

		if(GPIOC->IDR & BTN_PIN) // checking if 13th bit in idr is set or not
		{
			GPIOA->BSRR = LED_PIN; //LED ON. setting the BS5 at 5 pos to set the pin5.
		}
		else
		{
			GPIOA->BSRR = (1U<<21); //LED off setting the BR5 at pos 21 to reset the pin5.
		}
	}

}
