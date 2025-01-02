#include "Button.h"

uint8_t Button_getPressedState(button_t* btn)
{
  //uint8_t curState = *btn->PIN & (1<<btn->pinNum);
  uint8_t curState = gpio_readPinInputRegisterPin(btn->pinInputRegister, btn->pinNum);
  if((curState == BUTTON_PRESSED_STATE_PUSHED) && (btn->prevPressedState == BUTTON_PRESSED_STATE_RELEASED))
  {
    btn->prevPressedState = BUTTON_PRESSED_STATE_PUSHED;
    return BUTTON_PRESSED_STATE_PUSHED;
  }
  else if ((curState != BUTTON_PRESSED_STATE_PUSHED) && (btn->prevPressedState == BUTTON_PRESSED_STATE_PUSHED))
  {
    btn->prevPressedState = BUTTON_PRESSED_STATE_RELEASED;
    return BUTTON_PRESSED_STATE_RELEASED;
  }
  return BUTTON_PRESSED_STATE_NONE;
}




int Button_getReleasedButtonPinNumAsArray(button_t **btnArr, size_t buttonCount){
  for (size_t i= 0; i < buttonCount; i++){
    if (Button_getPressedState(btnArr[i]) == BUTTON_PRESSED_STATE_RELEASED){
      return btnArr[i]->pinNum;
      break;
    }
  }
  return BUTTON_PRESSED_STATE_NONE;
}


void Button_init(button_t *btn, volatile uint8_t* ddr, volatile uint8_t* pinInputRegister, uint8_t pinNum)
{
	btn->DDR = ddr;
	btn->pinInputRegister = pinInputRegister;
	btn->pinNum = pinNum;
	btn->prevPressedState = 1;
	//*btn->DDR &= ~(1<<btn->pinNum);
	gpio_initDataDirectionRegisterPins(btn->DDR, INPUT, 1, btn->pinNum);
}