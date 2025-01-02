#include "fanService.h"

static clockTimer_t fanShutdownTimer;
static clockTimer_t fanControlAutoModeTimer;
static clockTimer_t clockTimer;       // for presenter
static motor_t motor;

static uint8_t fanControlModeAutoCycleSecond = FAN_CONTROL_MODE_AUTO_CYCLE_SECOND_INITIAL_VALUE;

//static buzzer_t buzzer;

// ● Note that some update is run in ISR
void _fanService_updateByCurrentState(){
  //// ● It is run during 100ms for each second. It means that delay time range may be 0 ~ 900ms.
  //static uint16_t processTick = 100;
  //if(clockTimer.millisecond >= processTick){
  //return;
  //}
  
  uint8_t fanSpeedState = getFanSpeedState();
  FanControlModeState fanControlModeState = getFanControlModeState();
  uint16_t fanShutdownTimerDuration = getFanShutdownTimerInputState();
  
  
  // check whether fanControlAutoModeTimer is over or not than fanControlModeAutoCycleSecond.
  if ((fanSpeedState != 0) &&
  (fanControlModeState == FAN_CONTROL_MODE_AUTO) &&
  (fanControlAutoModeTimer.second >= fanControlModeAutoCycleSecond)) {
    uint16_t randomDutyCycle = (uint16_t)((rand() % 10)+1)*10; // duty cycle can be 1 ~ 100 (interval 10). +1 ensures that fan is not off
    motor.dutyCycle = randomDutyCycle;
    motor.setFanSpeed(&motor, motor.dutyCycle);
    // pro-process
    fanControlModeAutoCycleSecond = (randomDutyCycle % 2)+1; // fanControlModeAutoCycleSecond can be 1 ~ 3 second. +1 ensures that to prevent meaningless change of duty cycle.
    fanControlAutoModeTimer.setTime(&fanControlAutoModeTimer, 0, 0, 0, 0);
  }
  
  // check whether fanShutdownTimer is over or not than fanShutdownTimerDuration.
  if (fanShutdownTimerDuration != FAN_SHUTDOWN_TIMER_INPUT_NONE){
    if (fanShutdownTimer.getTotalSecond(&fanShutdownTimer) >= fanShutdownTimerDuration){
      setFanShutdownTimerDuration(FAN_SHUTDOWN_TIMER_INPUT_NONE);
      setFanSpeedState(0);
    }
  }

}


// ● update when only State is changed like React for performance.
static void _fanService_updateByChangedState(){
  static uint8_t prevFanSpeedState = FAN_SPEED_STATE_INITIAL_VALUE;
  static FanControlModeState prevFanControlModeState = FAN_CONTROL_MODE_STATE_INITIAL_VALUE;
  uint8_t fanSpeedState = getFanSpeedState();
  FanControlModeState fanControlModeState = getFanControlModeState();
  FanShutdownTimerInputState fanShutdownTimerInputState = getFanShutdownTimerInputState();

  
  //// check fanSpeedState
  if (prevFanSpeedState != fanSpeedState){
    if (prevFanSpeedState == 0){ // 0 -> 1 ~ 3
      motor.powerOn(&motor);
      motor.setFanSpeed(&motor, fanSpeedState*33); // fanSpeedState can be 1, 2, 3 in this line;
    }
    else { // 1 ~ 3 -> (???)
      if (fanSpeedState == 0){
        motor.powerOff(&motor);
        setIsInputEntered(FALSE);
        if (fanShutdownTimerInputState != FAN_SHUTDOWN_TIMER_INPUT_NONE){
          fanShutdownTimer.setTime(&fanShutdownTimer, 0, 0, 0, 0);
          setFanShutdownTimerInputState(FAN_SHUTDOWN_TIMER_INPUT_NONE);
          fanPresenter_clearFnd();
          setFanControlModeState(FAN_CONTROL_MODE_MANUAL);
        }
        
        }else {
        motor.setFanSpeed(&motor, fanSpeedState*33); // fanSpeedState can be 1, 2, 3 in this line;
      }
    }
    // pro-process
    prevFanSpeedState = fanSpeedState;
  }

  
  //// check fanControlModeState
  if (prevFanControlModeState != fanControlModeState){
    if (fanControlModeState == FAN_CONTROL_MODE_AUTO){
      fanControlAutoModeTimer.setTime(&fanControlAutoModeTimer, 0, 0, 0, 0);
      fanControlModeAutoCycleSecond = FAN_CONTROL_MODE_AUTO_CYCLE_SECOND_INITIAL_VALUE;
    }
    //else { // fanControlModeState == FAN_CONTROL_MODE_MANUAL  ... None
    // pro-process
    prevFanControlModeState = fanControlModeState;
  }
  
  
  //// check fanShutdownTimerInputState, isInputEntered, fanShutdownTimerDuration
  Boolean isInputEntered = getIsInputEntered();
  // when Shutdown Timer is processing, same new Shutdown Timer is input, it is set
  if (isInputEntered == TRUE){
    if (fanShutdownTimerInputState != FAN_SHUTDOWN_TIMER_INPUT_NONE){
      fanShutdownTimer.setTime(&fanShutdownTimer, 0, 0, 0, 0);
      setFanShutdownTimerDuration(fanShutdownTimerInputState);

      // pro-process
      setIsInputEntered(FALSE);
      
      //// temp...
      //setFanShutdownTimerInputState(FAN_SHUTDOWN_TIMER_INPUT_NONE); // ?이거 넣으면 종료가 안됨..
    }
  }
}


void fanService_run()
{
  // Listener
  fanListener_checkEvent();
  
  // Service
  _fanService_updateByCurrentState(); //!! order!! updateByCurrentState must be preceded than updateByChangedState.
  _fanService_updateByChangedState();

  
  // Display
  uint32_t totalSeconds = fanShutdownTimer.getTotalSecond(&fanShutdownTimer);
  uint8_t minute = 0;
  uint8_t second = 0;
  
  uint16_t fanShutdownTimerDuration = getFanShutdownTimerDuration();
  if (fanShutdownTimerDuration != 0){
    totalSeconds = (fanShutdownTimerDuration - totalSeconds);
    //totalSeconds %= HOUR_TO_SECOND_MULTIPLIER; // ignore hour
    minute = totalSeconds / MINUTE_TO_SECOND_MULTIPLIER;
    second = totalSeconds % MINUTE_TO_SECOND_MULTIPLIER;
  }
  
  fanPresenter_formatFnd(minute, second);
  fanPresenter_displaytoLcd(minute, second);
  
  // ● format and display Code is run during 100ms for each second.
  //static uint16_t processTick = 100;
  //if(clockTimer.millisecond >= processTick){
  //return;
  //}

}


void fanService_processTimerIsr(){
  uint8_t fanSpeedState = getFanSpeedState();
  FanControlModeState fanControlModeState = getFanControlModeState();
  uint16_t fanShutdownTimerDuration = getFanShutdownTimerDuration();

  // process for clockTimer
  clockTimer.increaseMillisecondInClockMode(&clockTimer);
  
  // process for fanAutoModeTimer
  if ((fanSpeedState != 0) && (fanControlModeState == FAN_CONTROL_MODE_AUTO)){
    fanControlAutoModeTimer.increaseMillisecondInClockMode(&fanControlAutoModeTimer);
  }
  
  // process for fanShutdownTimer
  if ((fanSpeedState != 0) && (fanShutdownTimerDuration != FAN_SHUTDOWN_TIMER_INPUT_NONE)){
    fanShutdownTimer.increaseMillisecondInClockMode(&fanShutdownTimer);
  }
}


void fanService_receiveUartIsr(){
  if (fanUart.isFull(&fanUart)) return;
  uint8_t rxData = fanUart.getRxData(&fanUart);
  fanUart.enqueue(&fanUart, rxData);
}



void fanService_init()
{
  Uart_init(&fanUart, UART_CHANNEL_1);
  ClockTimer_init(&fanShutdownTimer, 0, 0, 0, 0);
  ClockTimer_init(&fanControlAutoModeTimer, 0, 0, 0, 0);
  ClockTimer_init(&clockTimer, 0, 0, 0, 0);
  Motor_init(&motor, PWM_TIMER_COUNTER_NUM_3, PWM_CHANNEL_A);
  //Buzzer_init(&buzzer, PWM_TIMER_COUNTER_NUM_1, PWM_CHANNEL_A);
}

