#include "lcdI2c.h"
/////////////////// TODO
//
//uint8_t lcdControlData; // xxxx xxxx >> Data bus 4bit + control 4 bit
//
//void sendLedI2CData(uint8_t sla_w, uint8_t data){
	//transmitByteOnI2c(sla_w, data);
//}
//
//void lcdCmdMode(){ // instruction mode
	//lcdControlData &= ~(1<<LCD_RS);
	//sendLedI2CData(LCD_SLA_W, lcdControlData);
//}
//void lcdCharMode(){ // char mode
	//lcdControlData |= 1<<LCD_RS;
	//sendLedI2CData(LCD_SLA_W, lcdControlData);
//}
//
//
//
//void lcdWriteMode(){
	//lcdControlData &= ~(1<<LCD_RW);
	//sendLedI2CData(LCD_SLA_W, lcdControlData);
//}
//
//void enableLow(){
	//lcdControlData &= ~(1<<LCD_E);
	//sendLedI2CData(LCD_SLA_W, lcdControlData);
	//_delay_ms(1);
//}
//void enableHigh(){
	//// RS pin : bit 1 set
	//lcdControlData |= 1<<LCD_E;
	//sendLedI2CData(LCD_SLA_W, lcdControlData);
	//_delay_ms(1);
//}
//
//void writeNibbleLcd(uint8_t data){
	//enableHigh();
	//lcdControlData = (lcdControlData & 0x0f) | (data & 0xf0);
	//sendLedI2CData(LCD_SLA_W, lcdControlData);
	//enableLow();
//}
//
//void writeByteLcd(uint8_t data){ // 최소 단위 1바이트. 8비트를 모두 보내야 한다.  data bus 가 비트래도.
	//// 8 bit PORTC write
	//writeNibbleLcd(data);
	//data<<=4;
	//writeNibbleLcd(data);
//}
//
//void writeLcdCmdData(uint8_t data){
	//lcdCmdMode();
	//lcdWriteMode();
	//enableHigh();
	//writeByteLcd(data);
	//enableLow();
	//
//}
//void writeLcdCharData(uint8_t data){
	//lcdCharMode();
	//lcdWriteMode();
	//enableHigh();
	//writeByteLcd(data);
	//enableLow();
	//
//}
//void lcdBackLightOn(){
	//lcdControlData |= 1<<LCD_BACKLIGHT;
	//sendLedI2CData(LCD_SLA_W, lcdControlData);
//}
//void lcdBackLightOff(){
	//lcdControlData &= ~(1<<LCD_BACKLIGHT);
	//sendLedI2CData(LCD_SLA_W, lcdControlData);
//}
//
//
//void LCD_writeString(char *str)
//{
	//for(int i=0; str[i] ; i++)
	//{
		//writeLcdCharData(str[i]);
	//}
//}
//
//
//void LCD_gotoXY(uint8_t row, uint8_t col)
//{
	//col%= 16; row %=2;
	//uint8_t lcdregisterAddress = (0x40 * row ) + col;
	//uint8_t command = 0x80 + lcdregisterAddress;
	//writeLcdCmdData(command);
//}
//
//void LCD_writeStringXY(uint8_t row, uint8_t col, char *str)
//{
	//LCD_gotoXY(row,col);
	//LCD_writeString(str);
//}
//
//void LCD_clearDisplay()
//{
	//writeLcdCmdData(LCD_4bit_DISPLAY_CLEAR);
//}
//// ⚠️ it must be executed one-time if same LCD device is used between services in app. refer to RESET FUNCTION part of DataSheet
//void initLcdI2c(){
	//initI2c();
	//
	//lcdControlData = 0;
//
	//_delay_ms(15); // wait 15ms
	//lcdCmdMode();
	//lcdWriteMode();
	//writeNibbleLcd(0x30);
	//_delay_ms(5);
	//writeNibbleLcd(0x30);
	//_delay_ms(1);
	//writeNibbleLcd(0x30);
	//_delay_ms(1);
	//writeNibbleLcd(0x20);
	//
	//writeLcdCmdData(LCD_4bit_FUNCTIOIN_SET); // FUNCTION SET
	//writeLcdCmdData(LCD_4bit_DISPLAY_OFF);	// Display ON/OFF Control (OFF)
	//writeLcdCmdData(LCD_4bit_DISPLAY_CLEAR);	// Display clear	// ?
	//writeLcdCmdData(LCD_4bit_ENTRY_MODE_SET);	// Entry mode TODO:?? 	
	//
	//// 
	//writeLcdCmdData(LCD_4bit_DISPLAY_ON);	// Display ON/OFF Control (ON)
	//lcdBackLightOn();	// Display ON/OFF Control (ON)
//}
//
