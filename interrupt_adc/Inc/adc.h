
#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>


#define SR_EOC			(1U<<1)


void pc0_adc_intrrupt_init(void);
void start_conversion(void);
uint32_t adc_read(void);

#endif /* ADC_H_ */
