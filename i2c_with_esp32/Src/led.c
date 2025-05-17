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

void led_init(void)
{
	/*1.Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*2.Set PA5 as output pin*/
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);
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


