
// ADC continuous conversion and finding voltage
#include <stdio.h>
#include <stdint.h>
#include "stm32f446xx.h"

#include "uart.h"
#include "adc.h"

volatile uint32_t voltage = 0;
volatile uint32_t sensor_value = 0;

uint32_t voltage_convert(uint32_t sensor_value);

int main(void)
{

	uart2_tx_init();
	pc0_adc_init();
	start_conversion();
	while(1)
	{
		sensor_value = adc_read();
		voltage = voltage_convert(sensor_value);
		printf("Sensor value : %d\n\r",(int)sensor_value);
		printf("voltage is : %d\n\r",(int)voltage);
	}

}

uint32_t voltage_convert(uint32_t sensor_value)
{
	return (sensor_value*3.3)/4095;

}











