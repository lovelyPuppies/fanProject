#include "Model_timeClockDispState.h"

uint8_t timeClockDispStateData;

uint8_t Model_getTimeClockDispStateData()
{
	return timeClockDispStateData;
}

void Model_setTimeClockDispStateData(uint8_t state)
{
	timeClockDispStateData = state;
}