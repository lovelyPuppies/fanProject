#ifndef CLOCKTIMER_H_
#define CLOCKTIMER_H_

#define _countof(array) (sizeof(array) / sizeof(array[0])) // ⚠️ use only array is not pointer!!

#define HOUR_TO_SECOND_MULTIPLIER 3600 // 60 * 60
#define MINUTE_TO_SECOND_MULTIPLIER 60 // 60

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stddef.h>
#include <stdint.h>

typedef struct _clockTimer {
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint16_t millisecond;
	
	void (*increaseMillisecondInClockMode)(struct _clockTimer* self);
	void (*addMillisecondInModifyMode)(struct _clockTimer* self, uint16_t value);
	void (*addSecondInModifyMode)(struct _clockTimer* self, uint8_t value);
	void (*addMinuteInModifyMode)(struct _clockTimer* self, uint8_t value);
	void (*addHourInModifyMode)(struct _clockTimer* self, uint8_t value);
	void (*setTime)(struct _clockTimer* self, uint8_t hour, uint8_t minute, uint8_t second, uint8_t millisecond);
  void (*setTimeFromTotalSecond)(struct _clockTimer* self, uint32_t totalSeconds);

  uint32_t (*getTotalSecond)(struct _clockTimer* self);

} clockTimer_t;

void ClockTimer_init(clockTimer_t* timer, uint8_t hour, uint8_t minute, uint8_t second, uint16_t millisecond);

#endif /* TIMER_H_ */