/*
 * led.c
 *
 *  Created on: Jan 1, 2025
 *      Author: Aryan
 */

#include "led.h"

#define GPIOAEN				   (1U<<0)
#define GPIOA_5				   (1U<<5)

#define LED_PIN				   GPIOA_5
#define AFR5_TIM               (1U<<20)

void led_init(void)
{
	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*Set PA5 as alternate function mode*/
	GPIOA->MODER |= (1U<<11);
	GPIOA->MODER &= ~(1U<<10);

	/*set PA5 alternate function type to tim2_ch1 (af01) (check the chart)*/
	GPIOA->AFR[0] |= AFR5_TIM;

}

void led_on()
{
	GPIOA->ODR |= LED_PIN;
}

void led_off()
{
	GPIOA->ODR &= ~LED_PIN;
}

void led_toggle()
{
	GPIOA->ODR ^= LED_PIN;
}


