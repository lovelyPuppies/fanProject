#ifndef GPIO_H_
#define GPIO_H_

#define _countof(array) (sizeof(array) / sizeof(array[0])) // ⚠️ use only array is not pointer!!

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
enum {OUTPUT, INPUT};
enum {GPIO_PIN_RESET, GPIO_PIN_SET};


void gpio_initDataDirectionRegister(volatile uint8_t* DDR, uint8_t dir);
void gpio_initDataDirectionRegisterPins(volatile uint8_t* DDR, uint8_t direction, uint8_t numPins, ...);
void gpio_initDataDirectionRegisterPinsAsArray(volatile uint8_t* DDR, uint8_t state, size_t numPinsArrayLength, uint8_t* numPinsArray);
void gpio_writePortDataRegister(volatile uint8_t* PORT, uint8_t data);
void gpio_writePortDataRegisterPins(volatile uint8_t* PORT, uint8_t state, uint8_t numPins, ...);
void gpio_writePortDataRegisterPinsAsArray(volatile uint8_t* PORT, uint8_t state, size_t numPinsArrayLength,  uint8_t* numPinsArray);
uint8_t gpio_readPinInputRegister(volatile uint8_t* PIN);
uint8_t gpio_readPinInputRegisterPin(volatile uint8_t* PIN, uint8_t pinNum);

#endif /* GPIO_H_ */