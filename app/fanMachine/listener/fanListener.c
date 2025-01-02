#include "fanListener.h"

// Button
static button_t buttonFanSpeed, buttonFanControlMode, buttontnFanTimer, buttonEnter;
static button_t* btnArr[] = {&buttonFanSpeed, &buttonFanControlMode, &buttontnFanTimer, &buttonEnter};
static const size_t BUTTON_SIZE = 4;

static void _fanListner_processButtonFanSpeed(){
  FanControlModeState fanControlModeState = getFanControlModeState();
  if (fanControlModeState == FAN_CONTROL_MODE_AUTO) return;

  setFanSpeedStateToNext();
}
static void _fanListner_processButtonFanControlMode(){
  setFanControlModeStateNext();
}
static void _fanListner_processButtonFanShutdownTimer(){
  setFanShutdownTimerInputStateToNext();
}

static void _fanListner_processButtonEnter(){
  FanShutdownTimerInputState fanShutdownTimerInputState = getFanShutdownTimerInputState();
  if (fanShutdownTimerInputState != FAN_SHUTDOWN_TIMER_INPUT_NONE){
    setIsInputEntered(TRUE);
  }
}
//

static void _fanListener_checkUartEvent(){
  if (!fanUart.isEmpty(&fanUart)){
    volatile uint8_t* rxString = fanUart.dequeue(&fanUart);
    //printf("%s\n", rxString);     // for Debugging

    if(!strcmp((char*) rxString, "FAN_SPEED_STATE_0")){
      setFanControlModeState(0);
    }
    else if (!strcmp((char*) rxString, "FAN_SPEED_STATE_1")){
      setFanControlModeState(1);
    }
    else if (!strcmp((char*) rxString, "FAN_SPEED_STATE_2")){
      setFanControlModeState(2);
    }
    else if (!strcmp((char*) rxString, "FAN_SPEED_STATE_3")){
      setFanControlModeState(3);
    }
    else if (!strcmp((char*) rxString, "FAN_CONTROL_MODE_AUTO")){
      setFanControlModeState(FAN_CONTROL_MODE_AUTO);
    }
    else if (!strcmp((char*) rxString, "FAN_CONTROL_MODE_MANUAL")){
      setFanControlModeState(FAN_CONTROL_MODE_MANUAL);
    }
    else if (!strcmp((char*) rxString, "FAN_TIMER_TYPE_NONE")){
      setFanShutdownTimerInputState(FAN_SHUTDOWN_TIMER_INPUT_NONE);
      setIsInputEntered(TRUE);
    }
    else if (!strcmp((char*) rxString, "FAN_TIMER_TYPE_3_MINUTE")){
      setFanShutdownTimerInputState(FAN_SHUTDOWN_TIMER_INPUT_3_MINUTE);
      setIsInputEntered(TRUE);
    }
    else if (!strcmp((char*) rxString, "FAN_TIMER_TYPE_5_MINUTE")){
      setFanShutdownTimerInputState(FAN_SHUTDOWN_TIMER_INPUT_5_MINUTE);
      setIsInputEntered(TRUE);
    }
    else if (!strcmp((char*) rxString, "FAN_TIMER_TYPE_7_MINUTE")){
      setFanShutdownTimerInputState(FAN_SHUTDOWN_TIMER_INPUT_7_MINUTE);
      setIsInputEntered(TRUE);
    }
  }
}

static void _fanListener_checkButtonEvent(){
  // button input
  int releasedBtnPinNum = Button_getReleasedButtonPinNumAsArray(btnArr, BUTTON_SIZE);
  if (releasedBtnPinNum == BUTTON_PRESSED_STATE_NONE) return;

  // button process
  switch (releasedBtnPinNum){
    case BUTTON_FAN_SPEED_PIN_NUM:
    _fanListner_processButtonFanSpeed();
    break;
    
    case BUTTON_FAN_CONTROL_MODE_PIN_NUM:
    _fanListner_processButtonFanControlMode();
    break;
    
    case BUTTON_FAN_TIMER_PIN_NUM:
    _fanListner_processButtonFanShutdownTimer();
    break;
    
    case BUTTON_ENTER_PIN_NUM:
    _fanListner_processButtonEnter();
    break;
  }
}

//
void fanListener_checkEvent()
{
  _fanListener_checkButtonEvent();
  _fanListener_checkUartEvent();
  // Uart Data is received in ISR, but pop occurs in fanListener.
}

void fanListener_init(){
  // Button
  Button_init(&buttonFanSpeed, &BUTTON_FAN_SPEED_DDR, &BUTTON_FAN_SPEED_PIN, BUTTON_FAN_SPEED_PIN_NUM);
  Button_init(&buttonFanControlMode, &BUTTON_FAN_CONTROL_MODE_DDR, &BUTTON_FAN_CONTROL_MODE_PIN, BUTTON_FAN_CONTROL_MODE_PIN_NUM);
  Button_init(&buttontnFanTimer, &BUTTON_FAN_TIMER_DDR, &BUTTON_FAN_TIMER_PIN, BUTTON_FAN_TIMER_PIN_NUM);
  Button_init(&buttonEnter, &BUTTON_ENTER_DDR, &BUTTON_ENTER_PIN, BUTTON_ENTER_PIN_NUM);
}