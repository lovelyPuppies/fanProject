#include "Service_StopWatch.h"

static clockTimer_t clockTimer;


void stopwatch_init()
{
	ClockTimer_init(&clockTimer, 0, 0, 0, 0);
}

void stopwatch_update()
{
	uint8_t stopWatchState;
	stopWatchState = getStopwatchStateData();
		
	if(stopWatchState == RUN)
	{
		clockTimer.increaseMillisecondInClockMode(&clockTimer);
	}
	
}

void stopwatch_run()
{
	uint8_t timeModeState;
	timeModeState = getClockMachineModeStateData();
	
	uint8_t stopWatchState;
	stopWatchState = getStopwatchStateData();
	
	if(timeModeState != STOPWATCH) return;
		
	if(stopWatchState == RESET)
	{
		clockTimer.setTime(&clockTimer, 0, 0, 0, 0);
	}
	displayStopWatchData(clockTimer.hour, clockTimer.minute, clockTimer.second, clockTimer.millisecond);
}
