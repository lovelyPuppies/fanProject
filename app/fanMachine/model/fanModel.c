#include "fanModel.h"

static uint8_t _fanSpeedState = FAN_SPEED_STATE_INITIAL_VALUE;
static FanControlModeState _fanControlModeState = FAN_CONTROL_MODE_STATE_INITIAL_VALUE;
static FanShutdownTimerInputState _fanShutdownTimerInputState = FAN_SHUTDOWN_TIMER_INPUT_NONE;
static uint16_t _fanShutdownTimerDuration = FAN_SHUTDOWN_TIMER_INPUT_NONE;
static Boolean _isInputEntered = FALSE;

uart_t fanUart;
//
//// imitate Aspect-Oriented Programming (AOP)
//static Boolean _shutdownFanOnManualSpeedChangeAttempt()
//{
  //// if FAN_CONTROL_MODE_AUTO but user want to control fanSpeed, turn off FAN_CONTROL_MODE_AUTO.
  //if (_fanControlModeState == FAN_CONTROL_MODE_AUTO){
    //setFanSpeedState(0);
    //return TRUE;
  //}
  //return FALSE; // else
//}
//



uint8_t getFanSpeedState() {
  return _fanSpeedState;
}
void setFanSpeedState(uint8_t fanSpeedState)
{
  _fanSpeedState = fanSpeedState;
}
void setFanSpeedStateToNext()
{
  _fanSpeedState = (_fanSpeedState+1) % FAN_SPEED_STATE_NUM;
}




uint8_t getFanControlModeState() {
  return _fanControlModeState;
}
void setFanControlModeState(FanControlModeState fanControlModeState)
{
  _fanControlModeState = fanControlModeState;
}
void setFanControlModeStateNext()
{
  _fanControlModeState = (_fanControlModeState+1) % FAN_CONTROL_MODE_STATE_NUM;
}



uint8_t getFanShutdownTimerInputState() {
  return _fanShutdownTimerInputState;
}
void setFanShutdownTimerInputState(FanShutdownTimerInputState fanShutdownTimerInputState)
{
  _fanShutdownTimerInputState = fanShutdownTimerInputState;
}
void setFanShutdownTimerInputStateToNext()
{
  switch (_fanShutdownTimerInputState){
    case FAN_SHUTDOWN_TIMER_INPUT_NONE:
    _fanShutdownTimerInputState = FAN_SHUTDOWN_TIMER_INPUT_3_MINUTE;
    break;
    case FAN_SHUTDOWN_TIMER_INPUT_3_MINUTE:
    _fanShutdownTimerInputState = FAN_SHUTDOWN_TIMER_INPUT_5_MINUTE;
    break;
    case FAN_SHUTDOWN_TIMER_INPUT_5_MINUTE:
    _fanShutdownTimerInputState = FAN_SHUTDOWN_TIMER_INPUT_7_MINUTE;
    break;
    case FAN_SHUTDOWN_TIMER_INPUT_7_MINUTE:
    _fanShutdownTimerInputState = FAN_SHUTDOWN_TIMER_INPUT_NONE;
    break;
  }
}


Boolean getFanShutdownTimerDuration() {
  return _fanShutdownTimerDuration;
}
void setFanShutdownTimerDuration(FanShutdownTimerInputState fanShutdownTimerInputState) // can be 0, 180, 300, 420 second
{
  _fanShutdownTimerDuration = fanShutdownTimerInputState;
}


Boolean getIsInputEntered() {
  return _isInputEntered;
}
void setIsInputEntered(Boolean value)
{
  _isInputEntered = value;
}