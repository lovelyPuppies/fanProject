
#ifndef MODEL_TIMEMODESTATE_H_
#define MODEL_TIMEMODESTATE_H_

#include <avr/io.h>

enum {STOPWATCH, TIMECLOCK};

uint8_t getClockMachineModeStateData();
void setClockMachineModeStateData(uint8_t state);

#endif /* MODEL_TIMEMODESTATE_H_ */