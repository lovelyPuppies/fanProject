#include "Model_TimeModeState.h"

uint8_t timeModeStateData;

uint8_t getClockMachineModeStateData()
{
	return timeModeStateData;
}

void setClockMachineModeStateData(uint8_t state)
{
	timeModeStateData = state;
}