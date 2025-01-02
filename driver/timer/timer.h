#ifndef TIM0_H_
#define TIM0_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void initTimerCounter0Interrupt();
void initTimerCounter2Interrupt();

#endif /* TIM0_H_ */


/////////////////////////// TODO
//#ifndef TIMER_H_
//#define TIMER_H_
//
//#define F_CPU 16000000UL
//#include <avr/io.h>
//#include <avr/interrupt.h>
//#include <util/delay.h>
//#include <stddef.h>
//#include <stdint.h>
//
//
//void initTimer(uint8_t timerCounterNum);
//#endif