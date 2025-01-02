#ifndef PWM_H_
#define PWM_H_

#define _countof(array) (sizeof(array) / sizeof(array[0]))

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stddef.h>
#include <stdint.h>

#include "../gpio/gpio.h"
#define FAST_PWM1_ICR ICR1
#define FAST_PWM3_ICR ICR3
#define FAST_PWM1_A_OCR OCR1A
#define FAST_PWM1_B_OCR OCR1B
#define FAST_PWM1_C_OCR OCR1C
#define FAST_PWM3_A_OCR OCR3A
#define FAST_PWM3_B_OCR OCR3B
#define FAST_PWM3_C_OCR OCR3C

#define FAST_PWM1_DDR DDRB
#define FAST_PWM3_DDR DDRE
#define FAST_PWM1_A_PIN_NUM 5
#define FAST_PWM1_B_PIN_NUM 6
#define FAST_PWM1_C_PIN_NUM 7
#define FAST_PWM3_A_PIN_NUM 3
#define FAST_PWM3_B_PIN_NUM 4
#define FAST_PWM3_C_PIN_NUM 5


typedef enum {
  PWM_TIMER_COUNTER_NUM_1,
  PWM_TIMER_COUNTER_NUM_3
} PWM_TIMER_COUNTER_NUM;
typedef enum {
  PWM_CHANNEL_A,
  PWM_CHANNEL_B,
  PWM_CHANNEL_C
} PWM_CHANNEL;

typedef struct _pwm {
  volatile uint16_t *ICR;
  volatile uint16_t *OCR;
  volatile uint8_t *DDR;
  uint8_t pinNum;
  
  void (*resetTcnt)(struct _pwm* self);
  void (*enableFastPwmCompareMode)(struct _pwm* self);
  void (*disableFastPwmCompareMode)(struct _pwm* self);

  void (*setIcr)(struct _pwm* self, uint16_t value);
  void (*setOcr)(struct _pwm* self, uint16_t value);
  void (*setDutyCycle)(struct _pwm* self, uint16_t dutyCycle);
  void (*setHertz)(struct _pwm* self, uint16_t value, uint8_t dutyCycle);
} pwm_t;

void Pwm_init(pwm_t* pwm, PWM_TIMER_COUNTER_NUM pwmTimerCounterNum, PWM_CHANNEL pwmChannel);


#endif /* PWM_H_ */



/*
// fnd, i2c (일단 뺴기만 해놓자), button 정리
// PWM,, 부저.. Timer/Counter: prescaler - >TCNT 사용해야함... 사양서.. (OC3A/AIN1) PE3
- 주파수를 바꾸고 싶다 => TOP 값을 바꾸면 됌.

>> specification: ...
Figure 40. Phase Correct PWM Mode, Timing Diagram
Figure 46. 16-bit Timer/Counter Block Diagram     112p
From Prescaler -> TCLK -> Timer/Counter(+1)
... OCRxN (comparsion operation("=")
-  -> Waveform Generation -> OCxA
-  -> ICRx... Fixed TOP Values
// inverting output Compare mode
16-bit Timer/Counter Register Description 132
// TTCR1A TCCR1B TCCR3B
// COM bit setting. (Output mode)
Timer/Counter3 Control Register A – TCCR3A
Table 59. Compare Output Mode, Fast PWM
non-inverting mode, inverting mode ...
Table 60. Compare Output Mode, Phase Correct and Phase and Frequency Correct PWM
Table 61. Waveform Generation Mode Bit Description
● Fast PWM vs Phase Correct

ICR Register 로 TCLK 의 TOP 값을 바꿔서 파형을 조정한다.

==== Requirements
set Prescaler
enable PWM
set ICR regsiter
set OCR3A REgsiter




*/