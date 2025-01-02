
#ifndef SERVICE_STOPWATCH_H_
#define SERVICE_STOPWATCH_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "../Model/Model_StopWatchState.h"
#include "../Model/Model_TimeModeState.h"
#include "../Presenter/Presenter.h"
#include "../../../utility/clockTimer.h"

void stopwatch_init();
void stopwatch_update();
void stopwatch_run();

#endif /* SERVICE_STOPWATCH_H_ */