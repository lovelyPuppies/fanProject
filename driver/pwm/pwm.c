#include "pwm.h"
// specification: 16-bit Timer/Counter (Timer/Counter 1 and Timer/Counter3 )
// Ten Independent Interrupt Sources (TOV1, OCF1A, OCF1B, OCF1C, ICF1, TOV3, OCF3A, OCF3B, OCF3C, and ICF3)



// p136 Table 62. Clock Select Bit Description
static void _Pwm_1_setPrescaler64(){
  TCCR1B |= (0 << CS12) | (1 << CS11) | (1 << CS10);  // PreScaler 1/64
}
static void _Pwm_3_setPrescaler64(){
  TCCR3B |= (0 << CS32) | (1 << CS31) | (1 << CS30);  // PreScaler 1/64
}

// p134 Table 61. Waveform Generation Mode Bit Description
static void _Pwm_1_initWaveformGenerationMode(){
  TCCR1A |= (1 << WGM11) | (0 << WGM10); // Fast PWM p134 set for Mode 14. TOP: ICRn
  TCCR1B |= (1 << WGM13) | (1 << WGM12); // Fast PWM p134 set for Mode 14. TOP: ICRn
}
static void _Pwm_3_initWaveformGenerationMode(){
  TCCR3A |= (1 << WGM31) | (0 << WGM30); // Fast PWM p134 set for Mode 14. TOP: ICRn
  TCCR3B |= (1 << WGM33) | (1 << WGM32); // Fast PWM p134 set for Mode 14. TOP: ICRn
}




// p133 Table 59. Compare Output Mode, Fast PWM
static void _Pwm_1A_enableFastPwmCompareMode(){
  // Clear OCnA/OCnB/OCnC on compare match, set OCnA/OCnB/OCnC at BOTTOM, (non-inverting mode)
  TCCR1A |= 1<<COM1A1 | 0 << COM1A0;
}
static void _Pwm_1B_enableFastPwmCompareMode(){
  TCCR1B |= 1<<COM1B1 | 0 << COM1B0;
}
static void _Pwm_1C_enableFastPwmCompareMode(){
  TCCR1C |= 1<<COM1C1 | 0 << COM1C0;
}

static void _Pwm_3A_enableFastPwmCompareMode(){
  TCCR3A |= 1<<COM3A1 | 0 << COM3A0;
}
static void _Pwm_3B_enableFastPwmCompareMode(){
  TCCR3B |= 1<<COM3B1 | 0 << COM3B0;
}
static void _Pwm_3C_enableFastPwmCompareMode(){
  TCCR3C |= 1<<COM3C1 | 0 << COM3C0;
}


static void _Pwm_1A_disableFastPwmCompareMode(){
  TCCR1A &= ~(1<<COM1A1 | 1 << COM1A0);
}
static void _Pwm_1B_disableFastPwmCompareMode(){
  TCCR1B &= ~(1<<COM1B1 | 1 << COM1B0);
}
static void _Pwm_1C_disableFastPwmCompareMode(){
  TCCR1C &= ~(1<<COM1C1 | 1 << COM1C0);
}

static void _Pwm_3A_disableFastPwmCompareMode(){
  TCCR3A &= ~(1<<COM3A1 | 1 << COM3A0);
}
static void _Pwm_3B_disableFastPwmCompareMode(){
  TCCR3B &= ~(1<<COM3B1 | 1 << COM3B0);
}
static void _Pwm_3C_disableFastPwmCompareMode(){
  TCCR3C &= ~(1<<COM3C1 | 1 << COM3C0);
}

// ● TCNT3 = 0을 호출하는 주된 이유는 정확한 타이밍을 유지하고, 각 주파수 변경 후 다음 딜레이를 정확하게 설정하기 위함. 타이머가 예상치 못하게 오버플로우하거나, 이전 값의 영향을 받지 않도록 방지함.
static void _Pwm_1_resetTnct(){
  TCNT1 = 0;
}
static void _Pwm_3_resetTnct(){
  TCNT3 = 0;
}



////// ====== common function between Timer/Counter1, Timer/Counter3 in PWM mode. ===== ~
void _Pwm_setIcr(pwm_t* pwm, uint16_t value){
  *(pwm->ICR) = value;
  if (value < *(pwm->OCR)){
    *(pwm->OCR) = value;
  }
}


void _Pwm_setOcr(pwm_t* pwm, uint16_t value) {
  *(pwm->OCR) = value;
  if (value > *(pwm->ICR)){
    *(pwm->ICR) = value;
  }
}
void _Pwm_setDutyCycle(pwm_t* pwm, uint16_t dutyCycle){
  if (dutyCycle > 100){
    dutyCycle = 100;
  }
  *(pwm->OCR) = *(pwm->ICR) * dutyCycle / 100;
}


// when PreScaler is 64, F_CPU is 16000000. f_PWM = 1/(16000000/64)Hz.
void _Pwm_setHertz(pwm_t* pwm, uint16_t value, uint8_t dutyCycle){
  // Audio frequency band: 20Hz ~ 20kHz
  // from ● f_PWM = f_CPU / (N * (ICR3 + 1))
  *(pwm->ICR) = (250000 / value) - 1;  // Input Capture Register (ICRn)
  _Pwm_setDutyCycle(pwm, dutyCycle);
}

// ● f_PWM = f_CPU / (PrescalerValue * (ICR3 + 1)).
// {dutyCycle} is a percentage (0-100).
// if you want to pass icr as optional, set -1;




// ... e.g. TIMER1, Fast PWM mode, Top ICR1, DutyCycle OCR1A, Non-Inverting Mode
// 📝 PWM Disabled off is Default value! if you want that, use enableFastPwmCompareMode();
void Pwm_init(pwm_t* pwm, PWM_TIMER_COUNTER_NUM pwmTimerCounterNum, PWM_CHANNEL pwmChannel) {
  // ● Dynamic Dispatch
  switch(pwmTimerCounterNum){
    case PWM_TIMER_COUNTER_NUM_1:
    _Pwm_1_setPrescaler64();
    _Pwm_1_initWaveformGenerationMode();
    
    pwm->ICR = &FAST_PWM1_ICR;
    pwm->DDR = &FAST_PWM1_DDR;
    pwm->resetTcnt = _Pwm_1_resetTnct;
    
    
    switch(pwmChannel){
      case PWM_CHANNEL_A:
      pwm->OCR = &FAST_PWM1_A_OCR;
      pwm->pinNum = FAST_PWM1_A_PIN_NUM;
      pwm->enableFastPwmCompareMode = _Pwm_1A_enableFastPwmCompareMode;
      pwm->disableFastPwmCompareMode = _Pwm_1A_disableFastPwmCompareMode;
      break;
      case PWM_CHANNEL_B:
      pwm->OCR = &FAST_PWM1_B_OCR;
      pwm->pinNum = FAST_PWM1_B_PIN_NUM;
      pwm->enableFastPwmCompareMode = _Pwm_1B_enableFastPwmCompareMode;
      pwm->disableFastPwmCompareMode = _Pwm_1B_disableFastPwmCompareMode;
      break;
      case PWM_CHANNEL_C:
      pwm->OCR = &FAST_PWM1_C_OCR;
      pwm->pinNum = FAST_PWM1_C_PIN_NUM;
      pwm->enableFastPwmCompareMode = _Pwm_1C_enableFastPwmCompareMode;
      pwm->disableFastPwmCompareMode = _Pwm_1C_disableFastPwmCompareMode;
      break;
    }
    break;
    
    
    
    case PWM_TIMER_COUNTER_NUM_3:
    _Pwm_3_setPrescaler64();
    _Pwm_3_initWaveformGenerationMode();
    
    pwm->ICR = &FAST_PWM3_ICR;
    pwm->DDR = &FAST_PWM3_DDR;
    pwm->resetTcnt = _Pwm_3_resetTnct;
    
    switch(pwmChannel){
      case PWM_CHANNEL_A:
      pwm->OCR = &FAST_PWM3_A_OCR;
      pwm->pinNum = FAST_PWM3_A_PIN_NUM;
      pwm->enableFastPwmCompareMode = _Pwm_3A_enableFastPwmCompareMode;
      pwm->disableFastPwmCompareMode = _Pwm_3A_disableFastPwmCompareMode;

      break;
      case PWM_CHANNEL_B:
      pwm->OCR = &FAST_PWM3_B_OCR;
      pwm->pinNum = FAST_PWM3_B_PIN_NUM;
      pwm->enableFastPwmCompareMode = _Pwm_3B_enableFastPwmCompareMode;
      pwm->disableFastPwmCompareMode = _Pwm_3B_disableFastPwmCompareMode;
      break;
      case PWM_CHANNEL_C:
      pwm->OCR = &FAST_PWM3_C_OCR;
      pwm->pinNum = FAST_PWM3_C_PIN_NUM;
      pwm->enableFastPwmCompareMode = _Pwm_3C_enableFastPwmCompareMode;
      pwm->disableFastPwmCompareMode = _Pwm_3C_disableFastPwmCompareMode;
      break;
    }
    break;
    
  }
  //
  pwm->setIcr = _Pwm_setIcr;
  pwm->setOcr = _Pwm_setOcr;
  pwm->setDutyCycle = _Pwm_setDutyCycle;
  pwm->setHertz = _Pwm_setHertz;
  
  //// pro-process
  // ... e.g. Set PB5 (OC1A pin) as output. OC1A (Output Compare and PWM Output A for Timer/Counter1)
  // Set ICR3 for 1kHz frequency (16000000 / (64 * 250) - 1). ICR3 use 16bit Register so that Max value is 2^16 (65536).
  // ● pwm->enableFastPwmCompareMode(pwm); // PWM Disable off is Default value! if you want that, use enableFastPwmCompareMode();
  *(pwm->DDR) |= (1<<pwm->pinNum);
  //gpio_initDataDirectionRegisterPins(pwm->DDR, OUTPUT, 1, pwm->pinNum)
  *(pwm->ICR) = 249;
}



/*



🛍️ e.g.
setPwmHertz(1046); // 6 Octave C
_delay_ms(100);
pwm1_resetTnct();
setPwmHertz(2093); // 7 Octave
_delay_ms(100);
pwm1_resetTnct();
*/