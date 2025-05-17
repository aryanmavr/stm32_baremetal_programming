//LED Blink and LED Toggle without libraries using structures
//port: A
//pin: 5
#include <stdint.h>

#define PERIPH_BASE             (0x40000000UL)
#define AHB1PERIPH_OFFSET       (0x00020000UL)
#define AHB1PERIPH_BASE         (PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET            (0x0000UL)

#define GPIOA_BASE              (AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET              (0x3800UL)
#define RCC_BASE                (AHB1PERIPH_BASE + RCC_OFFSET)


#define GPIOAEN                 (1U<<0) // 0b 0000 0000 0000 0000 0000 0000 0000 0001

#define PIN5                    (1U<<5)
#define LED_PIN                  PIN5




typedef struct{
	volatile uint32_t dummy[12]; //check the ref manual for the sequence of registers
	volatile uint32_t AHB1ENR;   //if too many registers create a dummy array of registers to keep the reg at right place
}RCC_TypeDef;

typedef struct
{
	volatile uint32_t MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
	volatile uint32_t DUMMY[4];
	volatile uint32_t ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */

} GPIO_TypeDef;


#define RCC        ((RCC_TypeDef *)RCC_BASE) //dont forget to put brackets.
#define GPIOA      ((GPIO_TypeDef *)GPIOA_BASE)


 int main(void)
 {
	 /*enable clock access to GPIOA*/
	 RCC->AHB1ENR |= GPIOAEN; // we did an or operation so that no other bit other than our intended bit is changed

	 /*set PA5 as output pin*/
	 GPIOA->MODER |= (1U<<10);
	 GPIOA->MODER &= ~(1U<<11);

	 while(1)
	 {
		 /* set PA5 high*/
		 //GPIOA_OD_R |= LED_PIN;

		 /*toggle LED*/
		 GPIOA->ODR ^= LED_PIN;
		 for(int i = 0; i< 100000; i++){}
	 }

 }
