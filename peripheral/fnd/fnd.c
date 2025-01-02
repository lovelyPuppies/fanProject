#include "fnd.h"


void test(){
  // PORTG 의 0x01 은 내부 LED 와 연결되어 있어서 테스트가 용이하다.

  for (int i = 0; i<4; i++){
    PORTE = ~(1<<(i+4));	// common-Cathode type
    for (int j =0; j < 8; j++){
      PORTF = 1 << j;
      _delay_ms(100);
    }
    _delay_ms(100);
  }
  _delay_ms(100);
  PORTE = 0x00;
  PORTF = 0xff;
  _delay_ms(100);
  PORTE = 0xff;
  PORTF = 0x00;
}


// setter
static void _Fnd_setFndNum(fnd_t* fnd, uint16_t value){
  fnd->value = value;
}

// setter
static void _Fnd_setFndColonFlag(fnd_t* fnd, uint8_t value){
  fnd->colonFlag = value;
}

static void _Fnd_turnOff(fnd_t* fnd){
  gpio_writePortDataRegisterPinsAsArray(fnd->digitPort, GPIO_PIN_SET, fnd->digitPortPinNumArrLength, fnd->digitPortPinNumArr);
}


/*
● It includes formatting process for display.

● It seems correct to only read value and fndDigitState.
  It is inefficient to set segmentPortData and digitPortData in every loop  as variables inside the struct and then loop again to display based on those variables.
  It is more efficient to calculate only when displaying.
  ⚠️ Additionally, atomicity cannot be guaranteed, leading to abnormal values.
*/
static void _Fnd_displayFnd(fnd_t* fnd) {
  static const uint8_t fndNumPattern[10] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01100111};
  static const uint8_t colonPattern = 0b10000000;
  uint16_t fndNum = fnd->value;
  uint8_t fndDigitState = (fnd->digitState+1) % 5;;
	
	switch (fndDigitState)
	{
  	case 0 :
    // ● Refresh all digits to OFF in order to remove afterimage
    gpio_writePortDataRegisterPinsAsArray(fnd->digitPort, GPIO_PIN_SET, fnd->digitPortPinNumArrLength, fnd->digitPortPinNumArr);
    
    gpio_writePortDataRegister(fnd->segmentPort, fndNumPattern[fndNum/1000%10]);
    gpio_writePortDataRegister(fnd->digitPort, clearSpecificBit(*(fnd->digitPort), fnd->digitPortPinNumArr[fndDigitState]));
  	break;
    
    
  	case 1 :
    // ● Refresh all digits to OFF in order to remove afterimage
    gpio_writePortDataRegisterPinsAsArray(fnd->digitPort, GPIO_PIN_SET, fnd->digitPortPinNumArrLength, fnd->digitPortPinNumArr);
    
    gpio_writePortDataRegister(fnd->segmentPort, fndNumPattern[fndNum/100%10]);
    gpio_writePortDataRegister(fnd->digitPort, clearSpecificBit(*(fnd->digitPort), fnd->digitPortPinNumArr[fndDigitState]));
  	break;
    
    
  	case 2 :
    // ● Refresh all digits to OFF in order to remove afterimage
    gpio_writePortDataRegisterPinsAsArray(fnd->digitPort, GPIO_PIN_SET, fnd->digitPortPinNumArrLength, fnd->digitPortPinNumArr);
    
    gpio_writePortDataRegister(fnd->segmentPort, fndNumPattern[fndNum/10%10]);
    gpio_writePortDataRegister(fnd->digitPort, clearSpecificBit(*(fnd->digitPort), fnd->digitPortPinNumArr[fndDigitState]));
  	break;
  	case 3 :
    // ● Refresh all digits to OFF in order to remove afterimage
    gpio_writePortDataRegisterPinsAsArray(fnd->digitPort, GPIO_PIN_SET, fnd->digitPortPinNumArrLength, fnd->digitPortPinNumArr);
    
    gpio_writePortDataRegister(fnd->segmentPort, fndNumPattern[fndNum%10]);
    gpio_writePortDataRegister(fnd->digitPort, clearSpecificBit(*(fnd->digitPort), fnd->digitPortPinNumArr[fndDigitState]));
  	break;
  	
    case 4 :
    // ● Refresh all digits to OFF in order to remove afterimage
    gpio_writePortDataRegisterPinsAsArray(fnd->digitPort, GPIO_PIN_SET, fnd->digitPortPinNumArrLength, fnd->digitPortPinNumArr);
    
    if (fnd->colonFlag) {
      gpio_writePortDataRegister(fnd->segmentPort, colonPattern);
     }
  	else {
      gpio_writePortDataRegister(fnd->segmentPort, 0);
    }      
    gpio_writePortDataRegister(fnd->digitPort, clearSpecificBit(*(fnd->digitPort), 5));
  	break;
	}
  
  fnd->digitState = fndDigitState;
}



void Fnd_init(fnd_t* fnd, volatile uint8_t* segmentDDR, volatile uint8_t* digitDDR, volatile uint8_t* segmentPort, volatile uint8_t* digitPort, size_t digitPortPinNumArrLength, uint8_t* digitPortPinNumArr){
  fnd->segmentDDR = segmentDDR;
  fnd->digitDDR = digitDDR;
  
  fnd->segmentPort = segmentPort;
  fnd->digitPort = digitPort;
  fnd->digitPortPinNumArrLength = digitPortPinNumArrLength;
  fnd->digitPortPinNumArr = digitPortPinNumArr;
  
  //
  gpio_initDataDirectionRegister(segmentDDR, OUTPUT);
  fnd->max_digit_state = _countof(digitPortPinNumArr) + 1; // +1 is Colon flag state
  gpio_initDataDirectionRegisterPinsAsArray(digitDDR, OUTPUT, digitPortPinNumArrLength, digitPortPinNumArr);

    
  fnd->value = 0;
  
  fnd->digitState = 0;
  
  fnd->colonFlag = 0;
  
  fnd->setFndNum = _Fnd_setFndNum;
  fnd->setFndColonFlag = _Fnd_setFndColonFlag;
  fnd->displayFnd = _Fnd_displayFnd;
  fnd->turnOff = _Fnd_turnOff;
}


/*
전략 패턴 (Strategy Pattern): 객체의 행위를 캡슐화하고, 런타임에 다양한 행위를 바꿀 수 있도록 함.
의존성 주입 (Dependency Injection): 객체의 의존성을 외부에서 주입하여 결합도를 낮추고, 유연성과 테스트 용이성을 높임.
*/