
#ifndef LISTENER_H_
#define LISTENER_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../../peripheral/button/button.h"
#include "../Model/Model_StopWatchState.h"
#include "../Model/Model_TimeModeState.h"
#include "../Model/Model_timeClockDispState.h"

void initListener();
void Listener_eventCheck();
void checkStopwatchEvent();
void checkClockEvent();


#endif /* LISTENER_H_ */