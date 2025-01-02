#include "clockTimer.h"
#define MAX_MILLISECOND 1000
#define MAX_SECOND 60
#define MAX_MINUTE 60
#define MAX_HOUR 24

static void _ClockTimer_increaseMillisecondInClockMode(clockTimer_t* timer){
  timer->millisecond = (timer->millisecond + 1) % MAX_MILLISECOND;
  if (timer->millisecond) return;
  
  timer->second = (timer->second+1) % MAX_SECOND;
  if (timer->second) return;
  
  timer->minute = (timer->minute+1) % MAX_MINUTE;
  if (timer->minute) return;
  
  timer->hour = (timer->hour+1) % MAX_HOUR;
  return;
}

static void _ClockTimer_addMillisecondInModifyMode(clockTimer_t* clockTimer, uint16_t value){
  clockTimer->millisecond = (clockTimer->millisecond + 10) % MAX_MILLISECOND;
}

static void _ClockTimer_addSecondInModifyMode(clockTimer_t* clockTimer, uint8_t value){
  clockTimer->second = (clockTimer->second + 1) % MAX_SECOND;
}

static void _ClockTimer_addMinuteInModifyMode(clockTimer_t* clockTimer, uint8_t value){
  clockTimer->minute = (clockTimer->minute + 1) % MAX_MINUTE;
}

static void _ClockTimer_addHourInModifyMode(clockTimer_t* clockTimer, uint8_t value){
  clockTimer->hour = (clockTimer->hour + 1) % MAX_HOUR;
}

static void _ClockTimer_setTime(clockTimer_t* clockTimer, uint8_t hour, uint8_t minute, uint8_t second, uint8_t millisecond){
  clockTimer->hour = hour;
  clockTimer->minute = minute;
  clockTimer->second = second;
  clockTimer->millisecond = millisecond;
}

static void _ClockTimer_setTimeFromTotalSecond(clockTimer_t* clockTimer, uint32_t totalSeconds){
 clockTimer->hour = totalSeconds / HOUR_TO_SECOND_MULTIPLIER;
 totalSeconds %= HOUR_TO_SECOND_MULTIPLIER;
 clockTimer->minute = totalSeconds / MINUTE_TO_SECOND_MULTIPLIER;
 clockTimer->second = totalSeconds % MINUTE_TO_SECOND_MULTIPLIER;
 clockTimer->millisecond = 0;
}

static uint32_t _ClockTimer_getTotalSecond(clockTimer_t* clockTimer){
  return (clockTimer->hour * HOUR_TO_SECOND_MULTIPLIER) + (clockTimer->minute * MINUTE_TO_SECOND_MULTIPLIER) + clockTimer->second;
}

void ClockTimer_init(clockTimer_t* clockTimer, uint8_t hour, uint8_t minute, uint8_t second, uint16_t millisecond){
  clockTimer->hour = hour;
  clockTimer->minute = minute;
  clockTimer->second = second;
  clockTimer->millisecond = millisecond;
  //
  
  clockTimer->increaseMillisecondInClockMode = _ClockTimer_increaseMillisecondInClockMode;
  clockTimer->addMillisecondInModifyMode = _ClockTimer_addMillisecondInModifyMode;
  clockTimer->addSecondInModifyMode = _ClockTimer_addSecondInModifyMode;
  clockTimer->addMinuteInModifyMode = _ClockTimer_addMinuteInModifyMode;
  clockTimer->addHourInModifyMode = _ClockTimer_addHourInModifyMode;
  clockTimer->setTime = _ClockTimer_setTime;
  clockTimer->setTimeFromTotalSecond = _ClockTimer_setTimeFromTotalSecond;
  clockTimer->getTotalSecond = _ClockTimer_getTotalSecond;

}
