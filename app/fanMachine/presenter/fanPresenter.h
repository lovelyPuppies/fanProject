
#ifndef PRESENTER_H_
#define PRESENTER_H_

#define	LCD_CONTROL_DDR		DDRB
#define	LCD_CONTROL_PORT	PORTB
#define	LCD_DATA_BUS_DDR	DDRC
#define	LCD_DATA_BUS_PORT	PORTC

#define	LCD_RS				4
#define	LCD_RW				6
#define	LCD_E				7

#define FND_SEGMENT_DDR DDRF
#define FND_DIGIT_DDR DDRE
#define FND_SEGMENT_PORT PORTF
#define FND_DIGIT_PORT PORTE
#define FND_DIGIT_1_PIN 7
#define FND_DIGIT_2_PIN 6
#define FND_DIGIT_3_PIN 5
#define FND_DIGIT_4_PIN 4

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "../../../peripheral/fnd/fnd.h"
#include "../../../peripheral/lcd/lcd.h"
#include "../../../utility/clockTimer.h"
#include "../model/fanModel.h"


void fanPresenter_formatFnd(uint8_t minute, uint8_t second);
void fanPresenter_clearFnd();
void fanPresenter_displaytoLcd(uint8_t minute, uint8_t second);
void fanPresenter_displayFndISR();

void fanPresenter_init();

#endif /* PRESENTER_H_ */