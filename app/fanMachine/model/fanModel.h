#ifndef FANMODEL_H_
#define FANMODEL_H_

#include <avr/io.h>
#include <stdint.h>
#include "../../../utility/boolean.h"
#include "../../../driver/uart/uart.h"

extern uart_t fanUart;



#define FAN_SPEED_STATE_NUM 4     // Off, Low speed, Medium Speed, High Speed
#define FAN_SPEED_STATE_INITIAL_VALUE 0


typedef enum {
  FAN_CONTROL_MODE_AUTO,
  FAN_CONTROL_MODE_MANUAL
} FanControlModeState;
#define FAN_CONTROL_MODE_STATE_NUM 2
#define FAN_CONTROL_MODE_STATE_INITIAL_VALUE FAN_CONTROL_MODE_MANUAL
#define FAN_CONTROL_MODE_AUTO_CYCLE_SECOND_INITIAL_VALUE 1
#define FAN_CONTROL_MODE_MANUAL_DUTY_CYCLE_INITIAL_VALUE 50


typedef enum {
  FAN_SHUTDOWN_TIMER_INPUT_NONE=0,        // second
  FAN_SHUTDOWN_TIMER_INPUT_3_MINUTE=3, // second
  FAN_SHUTDOWN_TIMER_INPUT_5_MINUTE=4, // second
  FAN_SHUTDOWN_TIMER_INPUT_7_MINUTE=5 // second
} FanShutdownTimerInputState;
#define FAN_SHUTDOWN_TIMER_INPUT_STATE_NUM 4
#define FAN_SHUTDOWN_TIMER_INPUT_TOTAL_SECOND_INITIAL_VALUE 0

uint8_t getFanSpeedState();
void setFanSpeedState(uint8_t _fanSpeedState);
void setFanSpeedStateToNext();

uint8_t getFanControlModeState();
void setFanControlModeState(FanControlModeState _controlModeState);
void setFanControlModeStateNext();

uint8_t getFanShutdownTimerInputState();
void setFanShutdownTimerInputState(FanShutdownTimerInputState _fanTimerInputTypeState);
void setFanShutdownTimerInputStateToNext();

Boolean getFanShutdownTimerDuration();
void setFanShutdownTimerDuration(FanShutdownTimerInputState fanShutdownTimerInputState); // can be 0, 180, 300, 420 second

Boolean getIsInputEntered();
void setIsInputEntered(Boolean value);

#endif /* FANMODEL_H_ */