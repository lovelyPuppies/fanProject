#include "clockMachine.h"

void initClockMachine()
{
	initListener();
	stopwatch_init();
	timeClock_init();
	initStopwatchPresenter();
	initTimerCounter0Interrupt();
	initTimerCounter2Interrupt();
	
	Model_setStopWatchStateData(STOP);
	Model_setTimeClockDispStateData(HOUR_MIN);
	setClockMachineModeStateData(TIMECLOCK);
}

void runClockMachine()
{
	Listener_eventCheck();
	stopwatch_run();
	timeClock_run();
}