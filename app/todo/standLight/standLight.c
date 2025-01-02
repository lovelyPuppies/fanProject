//#include "standLight.h"
//
//// Button
//static button_t btnNext, btnPrev;
//static button_t* btnArr[] = {&btnNext, &btnPrev};
//static const size_t BUTTON_SIZE = _countof(btnArr);
//
//// LED
//static uint8_t ledPortData;
//static led_t led1, led2, led3, led4, led5, led6, led7, led8;
//static led_t *ledArr[] = {&led1, &led2, &led3, &led4, &led5, &led6, &led7, &led8};
//static const size_t LED_SIZE = _countof(ledArr);
//static enum LEDState lastLightLedI = MAX_0;	// default is Turn off.
//
//// time
//static size_t i;
//
//static void checkBtnEvent(){
	//// input
	//int releasedBtnPinNum = getReleasedButtonPinNum(btnArr, BUTTON_SIZE);
//
	//// button process
	//switch (releasedBtnPinNum){
		//case 0:
		//lastLightLedI = (lastLightLedI == MAX_8) ? 0 : lastLightLedI+2;
		//break;
		//case 1:
		//lastLightLedI = (lastLightLedI == MAX_0) ? 8 : lastLightLedI-2;
		//break;
		//default:
		//break;
	//}
//
//}
//static void updateStopwatchTransition(){
	//// led process
	//led_t* led = ledArr[0];
	//ledPortData = 0x00;
	//for (i= 0; i < lastLightLedI; i++){
		//ledPortData |= (1 << i);
	//}
	//led->setLedPortData(led, ledPortData);
	//led->displayLed(led);
//}
//
////
//
//void initStandLight(){
	//// Button
	//initButton(&btnNext, &DDRA, &PINA, 0);
	//initButton(&btnPrev, &DDRA, &PINA, 1);
	//
	//// LED
	//initLed(&led1, &DDRD, &PORTD, 0);
	//initLed(&led2, &DDRD, &PORTD, 1);
	//initLed(&led3, &DDRD, &PORTD, 2);
	//initLed(&led4, &DDRD, &PORTD, 3);
	//initLed(&led5, &DDRD, &PORTD, 4);
	//initLed(&led6, &DDRD, &PORTD, 5);
	//initLed(&led7, &DDRD, &PORTD, 6);
	//initLed(&led8, &DDRD, &PORTD, 7);
	//ledPortData = 0x00;
//
//}
//
//void runStandLight(){
	//checkBtnEvent();
	//updateStopwatchTransition();
//}