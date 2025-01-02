
#include "led.h"
/////////////////////// TODO
//
//static void _turnOnAllLed(led_t* led){
	//writePortDataRegister(led->port, 0xff);
//}
//
//static void _turnOffAllLed(led_t* led){
	//writePortDataRegister(led->port, 0x00);
//}
//
//
//// setter
//static void _setLedPortData(led_t* led, uint8_t portData){
	//led->portData = portData;
//}
//
//static void _displayLed(led_t* led){
	//writePortDataRegister(led->port, led->portData);
//}
//
//static uint8_t _getBlinkLedPortData(led_t* led, uint8_t operand){
	//return led->portData ^ operand;
//}
//void initLed(led_t *led, volatile uint8_t* ddr, volatile uint8_t* port, uint8_t portNum){
	//led->ddr = ddr;
	//led->port = port;
	//led->portNum = portNum;
	//
	//led->portData = 0x00;
	//initDataDirectionRegisterPin(led->ddr, OUTPUT, led->portNum);
	//
	//led->turnOnAllLed = _turnOnAllLed;
	//led->turnOffAllLed = _turnOffAllLed;
	//led->setLedPortData = _setLedPortData;
	//led->displayLed = _displayLed;
	//led->getBlinkLedPortData = _getBlinkLedPortData;
//}
//
//// utilities
//void led_shiftRight(led_t** ledArr, uint8_t ledArrLength){
  //static uint8_t ledIndex = 0;
  //// turn off the current led
  //*(ledArr[ledIndex]->port) &= ~(1 << ledArr[ledIndex]->portNum);
  //ledIndex = (ledIndex+1) % ledArrLength;
  //// turn on the next led
  //*(ledArr[ledIndex]->port) |= (1 << ledArr[ledIndex]->portNum);
//}
//
//void led_shiftLeft(led_t** ledArr, uint8_t ledArrLength){
  //static uint8_t ledIndex = 0;
  //// turn off the current led
  //*(ledArr[ledIndex]->port) &= ~(1 << ledArr[ledIndex]->portNum);
  //ledIndex = (ledIndex == 0) ? ledArrLength-1 : ledIndex-1;
  //// turn on the next led
  //*(ledArr[ledIndex]->port) |= (1 << ledArr[ledIndex]->portNum);
//}
//
//
//void led_bloomingFlower(led_t** ledArr, uint8_t ledArrLength){
  //uint8_t i, j;
  //uint8_t mid = ledArrLength/2;
  //if (ledArrLength % 2 == 0){
    //i = (mid == 0) ? 0 : mid-1;
    //j = mid;
  //}
  //else {
    //i = mid;
    //j = mid;
  //}
  //while (i >= 0 && j <= ledArrLength-1){
    //*(ledArr[i]->port) |= (1 << ledArr[i]->portNum);
    //*(ledArr[j]->port)|= (1 << ledArr[j]->portNum);
    //i--;
    //j++;
    //_delay_ms(500);
  //}  
//}
//
//void led_fallingFlower(led_t** ledArr, uint8_t ledArrLength){
  //uint8_t i = 0;
  //uint8_t j = ledArrLength-1;
  //while (i <= j){
    //*(ledArr[i]->port) &= ~(1 << ledArr[i]->portNum);
    //*(ledArr[j]->port) &= ~(1 << ledArr[j]->portNum);
    //i++;
    //j--;
    //_delay_ms(500);
  //}
//}
//// 
//
///*
//void ledLeftShift()
//{
  //ledData = (ledData >> 7) | (ledData <<1);
  //LED_PORT = ledData;
//}
//
//void ledRightShift()
//{
  //ledData = (ledData << 7) | (ledData >>1);
  //LED_PORT = ledData;
//}
//
//void ledAllBlink()
//{
  //static uint8_t ledBlinkData = 0x00;
  //ledBlinkData ^= 0xff;
  //LED_PORT = ledBlinkData;
//}
///*
//* GPIO.c
//*
//* Created: 2024-07-25 오후 2:09:48
//* Author : iot04
//*/
//#define F_CPU 16000000UL
//#include <avr/io.h>
//#include <util/delay.h>
//#include <avr/interrupt.h>
//#include <stddef.h>
//#define BUTTON_0 0
//#define BUTTON_1 1
//#define BUTTON_2 2
//#define BUTTON_3 3
//
//#define BUTTON_PIN PINA
//#define BUTTON_DDR DDRA
//#define BUTTON_PORT PORTA
//
//#define LED_DDR DDRD
//#define LED1_PORT PORTD
//#define LED2_DDR DDRF
//#define LED2_PORT PORTF
//
//#define LED_DELAY 200
//
//
//
//enum Led1State {ROUND_TRIP_RIGHT, ROUND_TRIP_LEFT, ALL_BLINK, ALL_OFF};
//unsigned char led1_pattern = 0b00000001;
//
//enum Led2State {UpDownRed = 0b00000001, upDownYellow = 0b00000010, upDownGreen = 0b00000100, SidesGreen = 0b00001000, SidesYellow = 0b00010000, SidesRed = 0b00100000};
//unsigned char led2availablePattern[4] = {UpDownRed | SidesGreen, UpDownRed | SidesYellow, upDownGreen | SidesRed, upDownYellow | SidesRed};
//
//unsigned char led2Index = 0;
//unsigned char led2_pattern; // if """unsigned char led2_pattern = led2availablePattern[led2Index];""", Error; initializer element is not constant.
//volatile size_t remained_delay = 0;
//
//enum ButtonState {AUTO, MANUAL, MANUAL_CONTROL};
//volatile enum ButtonState buttonState = AUTO;
//volatile unsigned char buttonPressed = 0;
//
//
//
//void testLed2(){
  //LED2_DDR = 0xff;
  //_delay_ms(LED_DELAY);
  //LED2_PORT = 0xff;
  //_delay_ms(LED_DELAY);
  //LED2_PORT = 0b00000001;		// 위/아래 빨강
  //_delay_ms(LED_DELAY);
  //LED2_PORT = 0b00000010;		// 위/아래 노랑
  //_delay_ms(LED_DELAY);
  //LED2_PORT = 0b00000100;		// 위/아래 초록
  //_delay_ms(LED_DELAY);
  //LED2_PORT = 0b00001000;		// 양 옆 초록
  //_delay_ms(LED_DELAY);
  //LED2_PORT = 0b00010000;		// 양 옆 노랑
  //_delay_ms(LED_DELAY);
  //LED2_PORT = 0b00100000;		// 양 옆 빨강
//}
//
//void ledLeftShift(){
  //led1_pattern = (led1_pattern << 1) | (led1_pattern >> 7);
  //LED1_PORT = led1_pattern;
  //
//}
//void ledRightShift(){
  //led1_pattern = (led1_pattern << 7) | (led1_pattern >> 1);	// 🚣
  //LED1_PORT = led1_pattern;
//}
//
//void ledAllBlink(){
  //static uint8_t ledBlinkData = 0x00;	// 🚣
  //ledBlinkData ^= 0xff;
  //LED1_PORT = ledBlinkData;
//}
//void ledAllOff(){
  //LED1_PORT = 0b00000000;
//}
//
//
//
//// TODO 버튼 눌럿을 떄 한번만 실행되는 문장을 넣으려면 버튼 눌렀을 떄 무한루프가 하나 더 있어야 할듯. 무한루프 전에 초기화되는 값 넣고.
//// BUtton_right, button_left 의 마지막 상태가 공유되어야 한다. 무조건 그래야 할듯.
//
//void init(void){
  //LED_DDR = 0xff;
  //LED2_DDR |= ((1<<0) | (1<<1) | (1<<2) | (1<<3)| (1<<4) | (1<<5));
  //
  //BUTTON_DDR &= ~((1<<BUTTON_0) | (1<<BUTTON_1) | (1<<BUTTON_2) | (1<<BUTTON_3));				// 핀을 입력으로 쓰겠다.
  //BUTTON_PORT = 0xff;	// ART MEGA128 에서 제공하는 기능. 에매모호한 상황인 플로팅 현상을 해결해준다.
//
//}
//
//
//void delay_by_one(void){
  //_delay_ms(1);
  //remained_delay-=1;
//}
//
//void autoState(){
  //if (remained_delay > 0){
    //delay_by_one();
  //}
  //else{
    //updateLed2Pattern();
    //remained_delay += (led2Index % 2 == 0) ? 3000 : 1000;
    //led2Index = ++led2Index % 4;
  //}
//}
//void manualState(){
  //remained_delay = 0;
//}
//
//void manualControlState(){
  //led2Index = ++led2Index % 4;
  //updateLed2Pattern();
  //buttonState = MANUAL;
//}
//int main(void)
//{
  //init();
//
  //
  //enum Led1State led1_state = ROUND_TRIP_RIGHT;
  //
  //unsigned char button_input;
  //
  //while (1)
  //{
//
//
  //}
//}
//
//
////// Button (1, 2, 3, 4) to control 8 LED
////while (1)
////{
////// input
////button_input = BUTTON_PIN;	// 안눌렀을 때 1, 누르면 0. 눌렀을 떄 한 번만 작동하는듯 ㅇㅇ 계속 if문 조건식을 통과하지 못한다.?   // 연결이 안된 PA4 ~ PA7까지는 값이 몇인지 알 수 없다. 플로팅.현상.
////if ((button_input & (1 << BUTTON_0) )== 0){
////led_state = ROUND_TRIP_RIGHT;
////}
////if ((button_input & (1 << BUTTON_1)) == 0){
////led_state = ROUND_TRIP_LEFT;
////}
////if ((button_input & (1 << ALL_BLINK)) == 0){
////led_state = ALL_BLINK;
////}
////if ((button_input & (1 << BUTTON_3)) == 0){
////led_state = ALL_OFF;
////}
////
////
////switch (led_state){
////case ROUND_TRIP_RIGHT:
////ledRightShift();
////break;
////
////case ROUND_TRIP_LEFT:
////ledLeftShift();
////break;
////
////case ALL_BLINK:
////ledAllBlink();
////break;
////
////case ALL_OFF:
////ledAllOff();
////break;
////}
////_delay_ms(LED_DELAY);
////}
////
////int i;
////
//////unsigned char direction = 1;			// LED 진행 방향
////
////unsigned char output_count_at_a_time = 1;
////unsigned char initial_bit_tweaker = 0b00000001;
////
////for (i = 0; i < output_count_at_a_time-1; i++){
////initial_bit_tweaker = (initial_bit_tweaker << 1) | initial_bit_tweaker;
////}
////
//////unsigned char bit_tweaker = initial_bit_tweaker;
////
////	while (1)
////{
////ledAllBlink();
////_delay_ms(LED_DELAY);
////// input
////button_input = BUTTON_PIN;	// 안눌렀을 때 1, 누르면 0.   // 연결이 안된 PA4 ~ PA7까지는 값이 몇인지 알 수 없다. 플
////if ((button_input & (1 << BUTTON_RIGHT) )== 0){
////button_mode = ROUND_TRIP_RIGHT;
////initial_bit_tweaker = 0b00000001;
////}
////if ((button_input & (1 << BUTTON_LEFT)) == 0){
////button_mode = ROUND_TRIP_LEFT;
////initial_bit_tweaker = 0b10000000;
////}
////if ((button_input & (1 << ALL_BLINK)) == 0){
////button_mode = ALL_BLINK;
////}
////if ((button_input & (1 << BUTTON_OFF)) == 0){
////button_mode = ALL_OFF;
////}
////
////// output
//
////
//
////TODO: output_count_at_a_time
////// Round trip. 초기값 direction = 0
////if (led_pattern == 0b10000000 || led_pattern == 0b00000001)
////direction = direction^1;
////(direction) ? (led_pattern <<= 1) : (led_pattern >>= 1);
//
///// Left to Right
////led_pattern = (led_pattern >> 7 | led_pattern << 1);
//
////// Right to Left
////led_pattern = (led_pattern << 7 | led_pattern >> 1);
//
//
//// ?? 어떻게 개ㅜㅅ.. 주기는 led_pattern 이 bit count 를 쓰면 될거같은데 C language 에는 bit count가 없다.
////// Turn on 1 ~ 8 and Turn off 1 ~ 8
//
//
////}
//
//
//// 1 ~ 7 turn on. 1 ~ 7 turn off
////if (bit_tweaker == 0b10000000){
////bit_tweaker = 0b00000001;
////direction ^= 1;
////}
////else{
////bit_tweaker <<= 1;
////}
////
////(direction) ? (led_pattern |= bit_tweaker) : (led_pattern ^= bit_tweaker);
////
//
////
////int main(void)
////{
/////* Replace with your application code */
////
////float operand = 2.0;
////while (1)
////{
////if (LED_DDR == 0b10000000) {
////operand = 0.5;
////}
////else if (LED_DDR == 0b00000001){
////operand = 2.0;
////}
////LED_DDR = (int)(LED_DDR * operand);
////
////LED_PORT = 0xff;
////_delay_ms(500);
////LED_PORT = 0x00;
////}
////
////
////}
//
//
////// Round Trip (Left to Right)
////for (i = 0; i < output_count_at_a_time; i++){
////
////if ((bit_tweaker & 0b10000000) == 0b10000000){
////bit_tweaker = initial_bit_tweaker;
////direction ^= 1;
////}
////else{
////bit_tweaker <<= 1;
////}
////
////(direction) ? (led_pattern |= bit_tweaker) : (led_pattern ^= bit_tweaker);
////}
//
//// Round Trip (Right to Left)
////for (i = 0; i < output_count_at_a_time; i++){
////if ((bit_tweaker & 0b00000001) == 0b00000001){
////bit_tweaker = initial_bit_tweaker;
////direction ^= 1;
////}
////else{
////bit_tweaker >>= 1;
////}
////
////(direction) ? (led_pattern |= bit_tweaker) : (led_pattern ^= bit_tweaker);
////}
////break;
//
////initial_bit_tweaker = 0b00000001;
//
////initial_bit_tweaker = 0b10000000;
//
