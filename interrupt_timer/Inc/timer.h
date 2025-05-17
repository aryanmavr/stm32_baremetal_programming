#ifndef TIMER_H_
#define TIMER_H_

#define SR_UIF     (1U<<0)  ///check UIF to check if timeout occured

void tim2_1hz_init(void);
void tim2_1hz_interrupt_init(void);
#endif /* TIMER_H_ */
