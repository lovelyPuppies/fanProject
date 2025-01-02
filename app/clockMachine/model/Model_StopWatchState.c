#include "Model_StopWatchState.h"

uint8_t stopWatchStateData;


uint8_t getStopwatchStateData()
{
	return stopWatchStateData;
}

void Model_setStopWatchStateData(uint8_t state)
{
	stopWatchStateData = state;
}