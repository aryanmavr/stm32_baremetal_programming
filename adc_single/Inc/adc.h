/*
 * adc.h
 *
 *  Created on: Jan 4, 2025
 *      Author: Dell
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void pc0_adc_init(void);
void start_conversion(void);
uint32_t adc_read(void);

#endif /* ADC_H_ */
