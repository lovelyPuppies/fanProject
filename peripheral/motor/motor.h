#ifndef FAN_H_
#define FAN_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../driver/pwm/pwm.h"

typedef struct _motor {
  pwm_t *pwm;
  uint8_t dutyCycle;
  
  void (*setFanSpeed)(struct _motor* self, uint8_t dutyCycle);
  void (*powerOn)(struct _motor* self);
  void (*powerOff)(struct _motor* self);
} motor_t;

void Motor_init(motor_t* fan, PWM_TIMER_COUNTER_NUM pwmTimerCounterNum, PWM_CHANNEL pwmChannel);

#endif /* FAN_H_ */


/*
How to use
🛍️ e.g.
  motor_t motor;
  Motor_init(&motor, PWM_TIMER_COUNTER_NUM_3, PWM_CHANNEL_A);
  motor.powerOn(&motor);
  motor.setFanSpeed(&motor, 10);
  _delay_ms(2000);
  motor.setFanSpeed(&motor, 90);
  _delay_ms(2000);
  motor.powerOff(&motor);
  
*/
