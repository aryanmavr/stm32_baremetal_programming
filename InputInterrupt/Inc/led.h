/*
 * led.h
 *
 *  Created on: Jan 2, 2025
 *      Author: Aryan
 */

#ifndef LED_H_
#define LED_H_

#include "stm32f446xx.h"

void led_init(void);
void led_on();
void led_off();
void led_toggle();

#endif /* LED_H_ */
