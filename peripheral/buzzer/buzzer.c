#include "buzzer.h"

static void _Buzzer_setHertz(buzzer_t* buzzer, uint16_t value, uint8_t dutyCycle) {
  buzzer->pwm->setHertz(buzzer->pwm, value, dutyCycle);
}

static void _Buzzer_setSoundDutyCycle(buzzer_t* buzzer, uint8_t dutyCycle) {
  buzzer->pwm->setDutyCycle(buzzer->pwm, dutyCycle);
}

static void _Buzzer_soundOn(buzzer_t* buzzer) {
  buzzer->pwm->enableFastPwmCompareMode(buzzer->pwm);
}
static void _Buzzer_soundOff(buzzer_t* buzzer) {
  buzzer->pwm->disableFastPwmCompareMode(buzzer->pwm);
}

void Buzzer_init(buzzer_t* buzzer, PWM_TIMER_COUNTER_NUM pwmTimerCounterNum, PWM_CHANNEL pwmChannel){
  static pwm_t pwm;
  buzzer->pwm = &pwm;
  Pwm_init(&pwm, pwmTimerCounterNum, pwmChannel);
  
  buzzer->dutyCycle = 50; // default value
  
  buzzer->setHertz= _Buzzer_setHertz;
  buzzer->setSoundDutyCycle = _Buzzer_setSoundDutyCycle;
  buzzer->soundOn = _Buzzer_soundOn;
  buzzer->soundOff = _Buzzer_soundOff;
  
  //if OCR
  //buzzer->soundOn = ;
}