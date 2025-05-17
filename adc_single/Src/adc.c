/*
 * adc.c
 *
 *  Created on: Jan 4, 2025
 *      Author: Aryan
 */

#include "stm32f446xx.h"
#include "adc.h"

#define GPIOCEN             (1U<<2)
#define ADC1EN              (1U<<8)
#define ADC_CH10             0xA
#define ADC_SEQ_LEN_1        0x0
#define CR2_ADON            (1U<<0)
#define CR2_SWSTART         (1U<<30)
#define SR_EOC              (1U<<1)

void pc0_adc_init(void)
{
	/*****configure the ADC GPIO pin***/

	/*enable clock access to gpio*/
	RCC->AHB1ENR |= GPIOCEN;

	/*set mode of PC0 to analog*/
	GPIOC->MODER |= (1U<<0);
	GPIOC->MODER |= (1U<<1);


	/****configure adc module****/

	/*enable clock to ADC module*/
	RCC->APB2ENR |= ADC1EN;

	/*conversion seq start*/
	// in seq reg put the order of the channels which need to sampled.
	//eg - 2,5,4,1 channels then in sq1 put binary of 2 then in sq 2 - binary of 5, then in seq3- bin 4, in seq4 - bin 1
	//we did adc1 channel_10 so we put 1010
	ADC1->SQR3 |= ADC_CH10;

	/*conversion seq length*/
	ADC1->SQR1 = ADC_SEQ_LEN_1; //we are not doing or operation beacuse we dont care about other bits as there are no other channels we put in seq. just length is defined

	/*enable ADC module*/
	ADC1->CR2 |= CR2_ADON;


}

void start_conversion(void)
{
	/****start conversion****/

	//we are doing software start for conversion but we can do timer to trigger the conversion as well
	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read(void)
{
	/*wait for conversion to be complete*/
	while(!(ADC1->SR & SR_EOC)){}
	/* read converted result */
	return (ADC1->DR);
}





