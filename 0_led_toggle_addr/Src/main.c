//LED Blink and LED Toggle without libraries
//port: A
//pin: 5

#define PERIPH_BASE             (0x40000000UL)
#define AHB1PERIPH_OFFSET       (0x00020000UL)
#define AHB1PERIPH_BASE         (PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET            (0x0000UL)

#define GPIOA_BASE              (AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET              (0x3800UL)
#define RCC_BASE                (AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET         (0x30UL)
#define RCC_AHB1EN_R            (*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET)) // ahb enable reg. we have to enable clock for a particular port . we enable it for port A by GPIOAEN (1U<<0)

#define MODE_R_OFFSET           (0x00UL)
#define GPIOA_MODE_R            (*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET)) //mode reg. input/output mode.we have to configure two bits in this reg accordingly. we configure in code

#define OD_R_OFFSET             (0x14UL)
#define GPIOA_OD_R              (*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))//output data reg. we write to this to on/off the led

#define GPIOAEN                 (1U<<0) // 0b 0000 0000 0000 0000 0000 0000 0000 0001

#define PIN5                    (1U<<5)
#define LED_PIN                  PIN5




/*
 * (1U<<10) //set bit 10 to 1
 * &=~(1U<<11) // set bit 11 to 0*/




 int main(void)
 {
	 /*enable clock access to GPIOA*/
	 RCC_AHB1EN_R |= GPIOAEN; // we did an or operation so that no other bit other than our intended bit is changed

	 /*set PA5 as output pin*/
	 GPIOA_MODE_R |= (1U<<10);
	 GPIOA_MODE_R &= ~(1U<<11);

	 while(1)
	 {
		 /* set PA5 high*/
		 //GPIOA_OD_R |= LED_PIN;

		 /*toggle LED*/
		 GPIOA_OD_R ^= LED_PIN;
		 for(int i = 0; i< 100000; i++){}
	 }

 }
