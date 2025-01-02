#ifndef FANLISTENER_H_
#define FANLISTENER_H_

#define F_CPU 16000000UL

#define BUTTON_FAN_SPEED_DDR DDRA
#define BUTTON_FAN_SPEED_PIN PINA
#define BUTTON_FAN_SPEED_PIN_NUM 0
#define BUTTON_FAN_CONTROL_MODE_DDR DDRA
#define BUTTON_FAN_CONTROL_MODE_PIN PINA
#define BUTTON_FAN_CONTROL_MODE_PIN_NUM 1
#define BUTTON_FAN_TIMER_DDR DDRA
#define BUTTON_FAN_TIMER_PIN PINA
#define BUTTON_FAN_TIMER_PIN_NUM 2
#define BUTTON_ENTER_DDR DDRA
#define BUTTON_ENTER_PIN PINA
#define BUTTON_ENTER_PIN_NUM 3

#include <avr/io.h>
#include <util/delay.h>
#include "../model/fanModel.h"
#include "../../../peripheral/button/button.h"
#include "../../../driver/uart/uart.h"

void fanListener_init();
void fanListener_checkEvent();


#endif /* FANLISTENER_H_ */