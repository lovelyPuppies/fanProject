

#ifndef MODEL_TIMECLOCKDISPSTATE_H_
#define MODEL_TIMECLOCKDISPSTATE_H_

#include <avr/io.h>

enum {HOUR_MIN, SEC_MIL};

uint8_t Model_getTimeClockDispStateData();
void Model_setTimeClockDispStateData(uint8_t state);

#endif /* MODEL_TIMECLOCKDISPSTATE_H_ */