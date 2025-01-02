#include "motor.h"

static void _motor_setMotorSpeed(motor_t* fan, uint8_t dutyCycle) {
  fan->pwm->setDutyCycle(fan->pwm, dutyCycle);
}

static void _Motor_powerOn(motor_t* fan) {
  fan->pwm->enableFastPwmCompareMode(fan->pwm);
}
static void _Motor_powerOff(motor_t* fan) {
  fan->pwm->disableFastPwmCompareMode(fan->pwm);
}


void Motor_init(motor_t* motor, PWM_TIMER_COUNTER_NUM pwmTimerCounterNum, PWM_CHANNEL pwmChannel){
  static pwm_t pwm;
  motor->pwm = &pwm;
  Pwm_init(&pwm, pwmTimerCounterNum, pwmChannel);
  
  motor->dutyCycle = 50; // default value
  
  motor->setFanSpeed = _motor_setMotorSpeed;
  motor->powerOn = _Motor_powerOn;
  motor->powerOff = _Motor_powerOff;
}