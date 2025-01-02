#ifndef BUTTON_H_
#define BUTTON_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../driver/gpio/gpio.h"

enum ButtonPressedState {BUTTON_PRESSED_STATE_NONE=-1, BUTTON_PRESSED_STATE_PUSHED, BUTTON_PRESSED_STATE_RELEASED};

typedef struct _button  {
  volatile uint8_t* DDR;
  volatile uint8_t* pinInputRegister;
  uint8_t pinNum;
  uint8_t prevPressedState;
  // If prevState not used in Struct type, it must be written in getState() function as static qualifier.
  
} button_t;

void Button_init(button_t *btn, volatile uint8_t* DDR, volatile uint8_t* pinInputRegister, uint8_t pinNum);
uint8_t Button_getPressedState(button_t* btn);
int Button_getReleasedButtonPinNumAsArray(button_t **btnArr, size_t buttonCount);

#endif /* BUTTON_H_ */

// 

/* Button
===== Device Specification =====
- Pull-up circuit
*/