

#ifndef SERVICE_TIMECLOCK_H_
#define SERVICE_TIMECLOCK_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "../Model/Model_timeClockDispState.h"
#include "../Model/Model_TimeModeState.h"
#include "../Presenter/Presenter.h"
#include "../../../utility/clockTimer.h"




void timeClock_init();
void timeClock_increaseMilisec();
void timeClock_run();

#endif /* SERVICE_TIMECLOCK_H_ */