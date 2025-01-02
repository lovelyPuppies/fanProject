
#ifndef MODEL_STOPWATCHSTATE_H_
#define MODEL_STOPWATCHSTATE_H_

#include <avr/io.h>

enum {STOP, RUN, RESET};

uint8_t getStopwatchStateData();
void Model_setStopWatchStateData(uint8_t state);

#endif /* MODEL_STOPWATCHSTATE_H_ */