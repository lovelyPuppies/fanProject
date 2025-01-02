#include "Service_TimeClock.h"

static clockTimer_t clockTimer;


void timeClock_init()
{
  ClockTimer_init(&clockTimer, 10, 14, 46, 0);
}

void timeClock_increaseMilisec()
{
  clockTimer.increaseMillisecondInClockMode(&clockTimer);
}

void timeClock_run()
{
	uint8_t timeModeState;
	timeModeState = getClockMachineModeStateData();
	
	if(timeModeState != TIMECLOCK) return;	
	
	displayTimeClockData(clockTimer.hour, clockTimer.minute, clockTimer.second, clockTimer.millisecond);
}

