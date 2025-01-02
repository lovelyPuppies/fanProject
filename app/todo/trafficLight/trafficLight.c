///*
//=== Functions ===
//- maintain Time ticks for Delay between Stop (Manual Button. not Manual Control) and Start Auto
//*/
//#include "trafficLight.h"
//
//// Button
//static button_t btn1, btn2, btn3;
//static button_t* btnArr[] = {&btn1, &btn2, &btn3};
//static const size_t BUTTON_SIZE = _countof(btnArr);
//static int releasedBtnPinNum = -1;
//
//// LED
//static led_t ledUpDownRed, ledUpDownYellow, ledUpDownGreen, ledSidesGreen, ledSidesYellow, ledSidesRed;
//static led_t* ledArr [] = {&ledUpDownRed, &ledUpDownYellow, &ledUpDownGreen, &ledSidesGreen, &ledSidesYellow, &ledSidesRed};
//static const size_t LED_SIZE = _countof(ledArr);
//
//
//static uint8_t ledPatterns[4] = {UpDownRed | SidesGreen, UpDownRed | SidesYellow, upDownGreen | SidesRed, upDownYellow | SidesRed};
//static size_t ledPatternsDelay[4] = {3000, 1000, 3000, 1000};
//static uint8_t ledPatternIndex = 0;
//
//
//// time
//static size_t timeticks = 0;
//static size_t prevTime = 0;
//
//// State
//static enum TrafficState trafficState = AUTO;
//
//void updateLedPattern(){
	//led_t* led = ledArr[0];
	//led->setLedPortData(led, ledPatterns[ledPatternIndex]);
	//led->displayLed(led);
//}
//void prepareNextLedPattern(){
	//timeticks = 0;
	//prevTime = 0;
	//ledPatternIndex = (ledPatternIndex+1) % 4;
//}
//
//// define Entry Action
//void doAutoState(){
	//if (timeticks - prevTime == ledPatternsDelay[ledPatternIndex]){
		//prepareNextLedPattern();
		//updateLedPattern();
	//}
//}
//
//void doManualState(){
	////
//}
//
//void doManualControlState(){
	//prepareNextLedPattern();
	//updateLedPattern();
	//timeticks = 0;
	//prevTime = 0;
	//
	//// pro-process
	//trafficState = MANUAL;
//}
//
//// test
//void testLed2(){
	//DDRF = 0b00000001;		// 위/아래 빨강
	//_delay_ms(200);
	//DDRF = 0b00000010;		// 위/아래 노랑
	//_delay_ms(200);
	//DDRF = 0b00000100;		// 위/아래 초록
	//_delay_ms(200);
	//DDRF = 0b00001000;		// 양 옆 초록
	//_delay_ms(200);
	//DDRF = 0b00010000;		// 양 옆 노랑
	//_delay_ms(200);
	//DDRF = 0b00100000;		// 양 옆 빨강
//}
//
//void initTrafficLight(){
	//initButton(&btn1, &DDRA, &PINA, 0);
	//initButton(&btn2, &DDRA, &PINA, 1);
	//initButton(&btn3, &DDRA, &PINA, 2);
	//
	//initLed(&ledUpDownRed, &DDRF, &PORTF, 0);
	//initLed(&ledUpDownYellow, &DDRF, &PORTF, 1);
	//initLed(&ledUpDownGreen, &DDRF, &PORTF, 2);
	//initLed(&ledSidesGreen, &DDRF, &PORTF, 3);
	//initLed(&ledSidesYellow, &DDRF, &PORTF, 4);
	//initLed(&ledSidesRed, &DDRF, &PORTF, 5);
	//
	//
	//updateLedPattern();
	//prepareNextLedPattern();
//}
//void executeTrafficLight(){
	//if (trafficState == AUTO){
		//_delay_ms(1);
		//timeticks += 1;
	//}
	//
	//// Button Input
	//releasedBtnPinNum = getReleasedButtonPinNum(btnArr, BUTTON_SIZE);
//
	//// Button Process
	//switch (releasedBtnPinNum){
		//case 0:
		//trafficState = AUTO;
		//break;
		//case 1:
		//trafficState = MANUAL;
		//break;
		//case 2:
		//if (trafficState == MANUAL){
			//trafficState = MANUAL_CONTROL;
		//}
		//break;
	//}
	//
	//// LED process (entry action)
	//switch (trafficState) {
		//case AUTO:
		//doAutoState();
		//break;
		//case MANUAL:
		//doManualState();
		//break;
		//case MANUAL_CONTROL:
		//doManualControlState();
//
//
	//}
//}