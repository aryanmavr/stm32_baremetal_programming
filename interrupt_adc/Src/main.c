// interrupt ADC continuous conversion and finding voltage
#include <stdio.h>
#include <stdint.h>
#include "stm32f446xx.h"

#include "uart.h"
#include "adc.h"

volatile uint32_t voltage = 0;
volatile uint32_t sensor_value = 0;

uint32_t voltage_convert(uint32_t sensor_value);
static void adc_callback(void);

int main(void)
{

	uart2_tx_init();
	pc0_adc_intrrupt_init();
	start_conversion();
	while(1)
	{

	}

}

uint32_t voltage_convert(uint32_t sensor_value)
{
	return (sensor_value*3.3)/4095;

}

static void adc_callback(void)
{
	sensor_value = ADC1->DR;
	voltage = voltage_convert(sensor_value);
	printf("Sensor value : %d\n\r",(int)sensor_value);
	printf("voltage is : %d\n\r",(int)voltage);
}

void ADC_IRQHandler(void)
{
	/*check for eoc in sr*/
	if((ADC1->SR & SR_EOC) != 0)
	{
		/*clear eoc*/
		ADC1->SR &= ~SR_EOC;

		/*do something*/
		adc_callback();
	}
}
