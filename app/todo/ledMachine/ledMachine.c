//#include "ledMachine.h"
//
//static button_t btnNext, btnPrev;
//static button_t* btnArr[] = {&btnNext, &btnPrev};
//static const size_t BUTTON_SIZE = _countof(btnArr);
//static int releasedBtnPinNum = -1;
//
//// Led
//static led_t led1, led2, led3, led4;
//static led_t* ledArr[] = {&led1, &led2, &led3, &led4};
//static const size_t LED_SIZE = _countof(ledArr);
//static int blinkedLedI = 0;
//
//// time
//static size_t timeticks = 0;
//static size_t prevTime = 0;
//
//static uint8_t operand;
//
//void initLedMachine(){
//
	//// Button
	//// 버튼 이름을 index 로 주고 for 문 돌리는 것보다, 조금 길어지더라도 이름으로 변수를 주고 한줄씩 초기화하는 것이 가독성이 좋을듯.
	//initButton(&btnNext, &DDRA, &PINA, 0);
	//initButton(&btnPrev, &DDRA, &PINA, 1);
//
	//// Led
	//initLed(&led1, &DDRD, &PORTD, 0);
	//initLed(&led2, &DDRD, &PORTD, 1);
	//initLed(&led3, &DDRD, &PORTD, 2);
	//initLed(&led4, &DDRD, &PORTD, 3);
//}
//
//void runLedMachine()	{
	////// in While loop!!! -=======TODO:
	////PORTD=0xff;
	////// ● 입력 -> 상태 유지/변경 (다음 루프에서 처리) -> 동일 루프에서 현재 루프 시작할 때의 상태에 대한 처리.
	////// delay
	//_delay_ms(1);
	//timeticks +=1;
	//led_t* led;
//
	////// input
	//releasedBtnPinNum = getReleasedButtonPinNum(btnArr, BUTTON_SIZE);
//
	//// button process
	//switch (releasedBtnPinNum){
		//case 0:
		//blinkedLedI = (blinkedLedI+1) % LED_SIZE;	// ● 상태는 내가 관리 하는 것.
		//led = ledArr[blinkedLedI];
		//led->setLedPortData(led, 0x00);  //● ledData 는 LED port 에 넣을 것. ● 이렇게 초기화를 해주어야 뒤에서 XOR 연산 시, 변경된 LedData로 들어간다.
		//break;
		//case 1:
		//blinkedLedI = (blinkedLedI > 0) ? blinkedLedI-1 : LED_SIZE-1;
		//led = ledArr[blinkedLedI];
		//led->setLedPortData(led, 0x00);
		//break;
		//default:
		//led = ledArr[0];
		//break;
	//}
//
	///////// MVP 패턴으로 나누고 300초 .. 이거 바꾸고 정리 가능.정리 필요 ;;;;
//
	//// process
	//if (timeticks-prevTime == 300){
		//prevTime = timeticks;
	//
		//operand = 1 << led->portNum;
		//led->setLedPortData(led, led->getBlinkLedPortData(led, operand));
		//led->displayLed(led);
	//}
//}
//
