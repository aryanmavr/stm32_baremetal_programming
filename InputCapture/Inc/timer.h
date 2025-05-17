#ifndef TIMER_H_
#define TIMER_H_

#define SR_UIF     (1U<<0)  ///check UIF to check if timeout occured
#define SR_CC1IF   (1U<<1) //Check if the edge has been captured. interrupt flag

void tim2_1hz_init(void);
void tim2_pa5_output_compare(void);
void tim3_pa6_input_capture(void);

#endif /* TIMER_H_ */
