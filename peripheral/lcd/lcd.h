#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../driver/gpio/gpio.h"


#define LCD_8bit_FUNCTION_SET		0x38  // 0b00111000
#define LCD_8bit_DISPLAY_OFF				0x08  // 0b00001000
#define LCD_8bit_DISPLAY_CLEAR			0x01   // 0b000000001
#define LCD_8bit_ENTRY_MODE_SET			0x06  // 0b00000110
#define LCD_8bit_DISPLAY_ON				0x0C    // 0b00001100
#define LCD_CMD_SET_CURSOR_ADDR   0x80    // 0b00000100

enum LcdReadWriteMode {LCD_READ_MODE, LCD_WRITE_MODE};
enum LcdLowHighState {LCD_LOW_STATE=0, LCD_LOW_HIGH=1};
enum LcdDataMode {LCD_DATA_MODE_INSTRUCTION=0, LCD_DATA_MODE_DATA_BUS=1};


typedef struct _lcd {
  volatile uint8_t* dataBusDDR;
  volatile uint8_t* dataBusPort;
  volatile uint8_t* contrlDDR;
  volatile uint8_t* contrlPort;
  
  uint8_t controlRegisterSelectPinNum;
  uint8_t controlReadWritePinNum;
  uint8_t controlEnableSignalPinNum;
  
  void (*writeLcdStringToXy)(struct _lcd* self, char *str, uint8_t row, uint8_t col);
  void (*clearDisplay)(struct _lcd* self);
  
  // ⚠️ it must be executed one-time if same LCD device is used between services in app. refer to RESET FUNCTION part of Datasheet
  void (*preprocessLcdTurnOn)(struct _lcd* self);
  
} lcd_t;


void Lcd_init(lcd_t* lcd, volatile uint8_t* dataBusDDR, volatile uint8_t* dataBusPort, volatile uint8_t* contrlDDR, volatile uint8_t* contrlPort, uint8_t controlRegisterSelectPinNum, uint8_t controlReadWritePinNum, uint8_t controlEnableSignalPinNum);


#endif


/*
// ⚠️ Not use ISR that interrupts every 1ms. because LCD requires minimum 2 millisecond to write enable bit and disable bit.It causes display Busy state.

Using LCM MODULE: TC1602A-01T DataSheet ; https://cdn-shop.adafruit.com/datasheets/TC1602A-01T.pdf

====================
INTERFACE PIN FUNCTIONS
  - 4 RS (Register Select):
	0: Instruction Register (for write), Busy flag-Address Counter (for read
	1: Data Register (for read and write)
  - 5 R/W (Read and Write): Low: Write mode.

CONNECTION WITH MCU
  * MPU Interface 4-bit/8-Bit
  
AC CHARACTERISTICS
  *(1) Write Mode (Writing data from MPU to SPLC780D1
    - Write Mode Timing Diagram (Writing data from MPU to SPLC780D1)
	📝
	  아랫줄이 Low 이고 윗줄이 High 일 때 상태.
	  Write 모드이고, Enable bit 가 Falling Edge 가 될 때 값이 쓰여진다.
● COMMAND TABLE

RESET FUNCTION
--------------------
 "VIH"는 "Input High Voltage"를, "VIL"는 "Input Low Voltage" 의미.
tSP1, tSP2: 셋업 타임 (Setup Time)으로, 신호가 유효해지기 위해 필요한 시간
tPW: 펄스 폭 (Pulse Width)으로, 신호가 유효 상태를 유지하는 시간
tHD1, tHD2: 홀드 타임 (Hold Time)으로, 신호가 유효 상태를 유지해야 하는 최소 시간
tR: 상승 시간 (Rise Time)으로, 신호가 낮은 상태에서 높은 상태로 변하는 시간
tF: 하강 시간 (Fall Time)으로, 신호가 높은 상태에서 낮은 상태로 변하는 시간
*/
