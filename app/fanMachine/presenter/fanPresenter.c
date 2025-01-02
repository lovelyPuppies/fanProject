#include "fanPresenter.h"

static lcd_t lcd;
static fnd_t fnd;


void fanPresenter_formatFnd(uint8_t minute, uint8_t second)
{
  // format FND String
  uint16_t fndNum = minute*100 + second;
  fnd.setFndNum(&fnd, fndNum);
}

void fanPresenter_clearFnd(){
  fnd.turnOff(&fnd);
}

void fanPresenter_displaytoLcd(uint8_t minute, uint8_t second)
{
  //// format LCD String
  char buff[30];
  char* fanInputStr = "";
  char* fanSpeedStr = "";
  char* fanTimerStr = "";
  uint8_t fanSpeedState = getFanSpeedState();
  FanControlModeState fanControlModeState = getFanControlModeState();
  FanShutdownTimerInputState fanShutdownTimerInputState = getFanShutdownTimerInputState();
  
  // format LCD fanInputStr
  switch (fanShutdownTimerInputState){
    case FAN_SHUTDOWN_TIMER_INPUT_NONE: fanInputStr = "==== Fan ===="; break;
    case FAN_SHUTDOWN_TIMER_INPUT_3_MINUTE: fanInputStr ="Timer 3 Minute"; break;
    case FAN_SHUTDOWN_TIMER_INPUT_5_MINUTE: fanInputStr ="Timer 5 Minute"; break;
    case FAN_SHUTDOWN_TIMER_INPUT_7_MINUTE: fanInputStr ="Timer 7 Minute"; break;
  }
  
  // format LCD fanSpeedStr
  if (fanControlModeState == FAN_CONTROL_MODE_AUTO){
    fanSpeedStr = "AUTO";
  }
  else {
    switch (fanSpeedState){
      case 0: fanSpeedStr = "OFF"; break;
      case 1: fanSpeedStr = "S1"; break;
      case 2: fanSpeedStr = "S2"; break;
      case 3: fanSpeedStr = "S3"; break;
      default: fanSpeedStr = ""; break;
    }
  }
  // format LCD fanTimerStr
  sprintf(fanTimerStr,"%02d:%02d", minute, second);
  
  
  
  // display to LCD
  sprintf(buff,"%14s", fanInputStr);
  lcd.writeLcdStringToXy(&lcd, buff, 0, 1);
  
  sprintf(buff,"%4s & %5s", fanSpeedStr, fanTimerStr);
  lcd.writeLcdStringToXy(&lcd, buff, 1, 2);
}


void fanPresenter_displayFndISR()
{
  uint16_t fanShutdownTimerDuration = getFanShutdownTimerDuration();
  if (fanShutdownTimerDuration != FAN_SHUTDOWN_TIMER_INPUT_NONE){
    fnd.displayFnd(&fnd);
  }
}


void fanPresenter_init()
{
  static uint8_t fndDigitPinNumArr[4] = {FND_DIGIT_4_PIN, FND_DIGIT_3_PIN, FND_DIGIT_2_PIN, FND_DIGIT_1_PIN};
  Fnd_init(&fnd, &FND_SEGMENT_DDR, &FND_DIGIT_DDR, &FND_SEGMENT_PORT, &FND_DIGIT_PORT, _countof(fndDigitPinNumArr), fndDigitPinNumArr);
  Lcd_init(&lcd, &LCD_DATA_BUS_DDR, &LCD_DATA_BUS_PORT, &LCD_CONTROL_DDR, &LCD_CONTROL_PORT, LCD_RS, LCD_RW, LCD_E);
  lcd.clearDisplay(&lcd);
}