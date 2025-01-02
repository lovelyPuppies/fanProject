#ifndef BUZZER_H_
#define BUZZER_H_


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../driver/pwm/pwm.h"


typedef struct _buzzer {
  pwm_t *pwm;
  uint8_t dutyCycle;
  
  void (*setHertz)(struct _buzzer* self, uint16_t value, uint8_t dutyCycle);
  void (*setSoundDutyCycle)(struct _buzzer* self, uint8_t dutyCycle);
  void (*soundOn)(struct _buzzer* self);
  void (*soundOff)(struct _buzzer* self);
  
} buzzer_t;

void Buzzer_init(buzzer_t* buzzer, PWM_TIMER_COUNTER_NUM pwmTimerCounterNum, PWM_CHANNEL pwmChannel);

#endif /* BUZZER_H_ */

/*
How to use
  🛍️ e.g.
    buzzer_t buzzer;
    Buzzer_init(&buzzer, PWM_TIMER_COUNTER_NUM_1, PWM_CHANNEL_A);
    buzzer.setHertz(&buzzer, 300, 10);
    _delay_ms(1000);
    buzzer.soundOff(&buzzer);

*/
