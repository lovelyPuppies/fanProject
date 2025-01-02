/////////////////////// TODO
//
//#ifndef LED_H_
//#define LED_H_
//#define _countof(array) (sizeof(array) / sizeof(array[0]))
//
//#define F_CPU 16000000UL
//#include <avr/io.h>
//#include <util/delay.h>
//#include <stddef.h>
//#include <stdint.h>
//#include "../../peripheral/gpio/gpio.h"
//
//enum LedState {TURN_OFF, TURN_ON};
	//
//typedef struct _led {
	//volatile uint8_t* ddr;
	//volatile uint8_t* port;
	//uint8_t portNum;
	//
	//uint8_t portData;
	//
	//void (*turnOnAllLed)(struct _led* self);
	//void (*turnOffAllLed)(struct _led* self);
	//void (*setLedPortData)(struct _led* self, uint8_t portData);
	//void (*displayLed)(struct _led* self);
	//uint8_t (*getBlinkLedPortData)(struct _led* self, uint8_t operand);
	//
//} led_t;
//
//void initLed(led_t *led, volatile uint8_t* ddr, volatile uint8_t* port, uint8_t portNum);
//
//// utilities
//void led_shiftRight(led_t** ledArr, uint8_t ledArrLength);
//void led_shiftLeft(led_t** ledArr, uint8_t ledArrLength);
//void led_bloomingFlower(led_t** ledArr, uint8_t ledArrLength);
//void led_fallingFlower(led_t** ledArr, uint8_t ledArrLength);
//
//
//#endif /* LED_H_ */