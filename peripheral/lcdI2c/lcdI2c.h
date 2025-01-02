/////////////////// TODO

//#ifndef LCDI2C_H_
//#define LCDI2C_H_
//
//#define _countof(array) (sizeof(array) / sizeof(array[0]))
//#define F_CPU 16000000UL
//
//#define LCD_RS 0
//#define LCD_RW 1
//#define LCD_E 2
//#define LCD_BACKLIGHT 3 // Write is 0 bit?
//
//#define LCD_SLA 0x27	// address of LCD device (A2, A1, A0)
//#define LCD_SLA_W LCD_SLA<<1 // Write is 0 bit?
//
//#define LCD_4bit_FUNCTIOIN_SET 0x28 // FUNCTION SET. 0b00111000 . 0010 NFxx. N:(2-line/1-line). F(5*10 dots / 5*8 dots)
//#define LCD_4bit_DISPLAY_OFF 0x08	// Display ON/OFF Control (OFF) 0b00001000
//#define LCD_4bit_DISPLAY_CLEAR 0x01 // Display clear	0b000000001 // ?
//#define LCD_4bit_ENTRY_MODE_SET 0x06 // Entry mode set  // ? 0b00000110. set move direction of (cursor and display)
//#define LCD_4bit_DISPLAY_ON 0x0c	// Display ON/OFF Control (ON) 0b00001100
//#define LCD_CMD_SET_CURSOR_ADDR 0x80
//
//
//#include <avr/io.h>
//#include <util/delay.h>
//#include <stddef.h>
//#include <stdint.h>
//#include <stdlib.h>
//#include "../../peripheral/i2c/i2c.h"
//
//
//void sendLedI2CData(uint8_t sla_w, uint8_t data);
//void lcdCmdMode(); // instruction mode
//void lcdCharMode(); // char mode
//void lcdWriteMode();
//void enableLow();
//void enableHigh();
//void writeNibbleLcd(uint8_t data);
//
//void writeByteLcd(uint8_t data); // 최소 단위 1바이트. 8비트를 모두 보내야 한다.  data bus 가 비
//void writeLcdCmdData(uint8_t data);
//void writeLcdCharData(uint8_t data);
//void lcdBackLightOn();
//void lcdBackLightOff();
//void LCD_writeString(char *str);
//void LCD_gotoXY(uint8_t row, uint8_t col);
//void LCD_writeStringXY(uint8_t row, uint8_t col, char *str);
//void LCD_clearDisplay();
//void initLcdI2c();
//
//
//
//
//
//#endif /* LCDI2C_H_ */
//
///*
//e.g. 
//
	//// 1 Byte DAta를 송수신 하는 상황
	//initLcdI2c();
	//char buff[30];
	//uint16_t counter = 0;
	//while(1){
		//sprintf(buff, "Counter :%02d", counter++);
		//LCD_writeStringXY(0, 3, buff);
		//_delay_ms(100);
//
	//}
//
//*/
///*
//Using LCM MODULE: TC1602A-01T DataSheet ; https://cdn-shop.adafruit.com/datasheets/TC1602A-01T.pdf
//* COMMAND TABLE
  //Symbol stands for:
  //in Instruction: Entry Mode Set
    //- I/D (Increment/Decrement) bit  :  (1 bit  /  0 bit)  :  (오른쪽 방향 / 왼쪽 방향)
	  //문자를 쓰거나 읽은 후 커서의 이동 방향을 설정 
    //- S (Shift) bit
      //문자를 쓰거나 읽은 후 디스플레이의 이동 여부를 설정. (1 bit  /  0 bit)  :  (이동 / 이동하지 않음)
  //in Function Set
    //- N (Number of Lines) bit  :  (1  bit /  0 bit)  :  (2-line / 1-line)
	//- F (Font Type) bit  :  (1  bit  / 0 bit)  :  (5*10 dot fonts / 5*8 dot fonts)
	  //문자 폰트의 종류를 설정.
//
//PCF8574A Remote 8-Bit I/O Expander for I2C Bus
//https://www.ti.com/lit/ds/symlink/pcf8574a.pdf
//A0 A1 A2 에 납떔을 해서 0 비트로 만들고 LCD 에 임의의 주소를 부여할 수 있다. (여러 LCD 를 사용 시) 0 1 0 0 A2 A1 A0
//
//e.g. app main.c -> LCD Driver -> I2C -> LCD
//
//PCF8574 remote 8-bit i/o expander for i2c bus
//schematic
//
//..? A1 A2 A3에 납떔을 하면 쇼트가 난다고 한다.
//Board Schemetic
	//https://www.electro-tech-online.com/attachments/1698939342987-png.143197/
//*/