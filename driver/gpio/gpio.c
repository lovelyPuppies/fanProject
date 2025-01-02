#include "gpio.h"

void gpio_initDataDirectionRegister(volatile uint8_t* DDR, uint8_t direction)
{
	if(direction == OUTPUT)
	{
		*DDR = 0xff;
	}
	else
	{
		*DDR = 0x00;
	}	
}

// Variadic function
void gpio_initDataDirectionRegisterPins(volatile uint8_t* DDR, uint8_t direction, uint8_t numPins, ...) {
  va_list argptr;
  va_start(argptr, numPins);

  uint8_t mask = 0;
  for (int i = 0; i < numPins; i++) {
    uint8_t pinNum = va_arg(argptr, int);
    mask |= 1 << pinNum;
  }
  va_end(argptr);

  if (direction == OUTPUT) {
    *DDR |= mask;
    } else {
    *DDR &= ~mask;
  }
}
void gpio_initDataDirectionRegisterPinsAsArray(volatile uint8_t* DDR, uint8_t state, size_t numPinsArrayLength, uint8_t* numPinsArray){
  uint8_t mask = 0;

  for (int i = 0; i < numPinsArrayLength; i++) {
    mask |= 1 << numPinsArray[i];
  }

  if (state == OUTPUT) {
    *DDR |= mask;
    } else {
    *DDR &= ~mask;
  }
}


void gpio_writePortDataRegister(volatile uint8_t* PORT, uint8_t data)
{
	*PORT = data;
}


void gpio_writePortDataRegisterPins(volatile uint8_t* PORT, uint8_t state, uint8_t numPins, ...) {
  va_list args;
  va_start(args, numPins);

  uint8_t mask = 0;

  for (int i = 0; i < numPins; i++) {
    uint8_t pinNum = va_arg(args, int);
    mask |= 1 << pinNum;
  }

  va_end(args);

  if (state == GPIO_PIN_SET) {
    *PORT |= mask;
    } else {
    *PORT &= ~mask;
  }
}
void gpio_writePortDataRegisterPinsAsArray(volatile uint8_t* PORT, uint8_t state, size_t numPinsArrayLength,  uint8_t* numPinsArray){
  uint8_t mask = 0;

  for (int i = 0; i < numPinsArrayLength; i++) {
    mask |= 1 << numPinsArray[i];
  }

  if (state == GPIO_PIN_SET) {
    *PORT |= mask;
    } else {
    *PORT &= ~mask;
  }
}


uint8_t gpio_readPinInputRegister(volatile uint8_t* PIN)
{
	return *PIN;	
}

uint8_t gpio_readPinInputRegisterPin(volatile uint8_t* PIN, uint8_t pinNum)
{
  
	 return ((*PIN & (1 << pinNum)) != 0); // == 1 일 떄와 다르다. 0 이외는 모두 1을 반환하는 것과 1 이외의 값  ...
}