
#include "lcd.h"
uint8_t isLcdPreprocessBeforeTurnOn = 0;

static void _Lcd_setLcdMode(lcd_t* lcd, uint8_t lcdMode){
  switch (lcdMode) {
    case LCD_DATA_MODE_INSTRUCTION:
    gpio_writePortDataRegisterPins(lcd->contrlPort, GPIO_PIN_RESET, 1, lcd->controlRegisterSelectPinNum);
    break;
    case LCD_DATA_MODE_DATA_BUS:
    gpio_writePortDataRegisterPins(lcd->contrlPort, GPIO_PIN_SET, 1, lcd->controlRegisterSelectPinNum);
    break;
  }
}
static void _Lcd_setReadWriteMode(lcd_t* lcd, uint8_t readWriteMode){
  switch (readWriteMode) {
    case LCD_READ_MODE:
    gpio_writePortDataRegisterPins(lcd->contrlPort, GPIO_PIN_SET, 1, lcd->controlReadWritePinNum);
    break;
    case LCD_WRITE_MODE:
    gpio_writePortDataRegisterPins(lcd->contrlPort, GPIO_PIN_RESET, 1, lcd->controlReadWritePinNum);
    break;
  }
}


static void _Lcd_setEnableSignal(lcd_t* lcd, uint8_t lcdEnableSignal){
  switch (lcdEnableSignal) {
    case LCD_LOW_STATE: // Write when Falling edge
    gpio_writePortDataRegisterPins(lcd->contrlPort, GPIO_PIN_RESET, 1, lcd->controlEnableSignalPinNum);
    break;
    case LCD_LOW_HIGH:
    gpio_writePortDataRegisterPins(lcd->contrlPort, GPIO_PIN_SET, 1, lcd->controlEnableSignalPinNum);
    break;
  }
  _delay_ms(1);
}

static void _Lcd_setLcdPortData(lcd_t* lcd, uint8_t portData){
  gpio_writePortDataRegister(lcd->dataBusPort, portData);
}

static void _Lcd_writeLcdCmdData(lcd_t* lcd, uint8_t data){
  _Lcd_setLcdMode(lcd, LCD_DATA_MODE_INSTRUCTION);
  _Lcd_setReadWriteMode(lcd, LCD_WRITE_MODE);
  _Lcd_setEnableSignal(lcd, LCD_LOW_HIGH);
  _Lcd_setLcdPortData(lcd, data);
  _Lcd_setEnableSignal(lcd, LCD_LOW_STATE);
}

static void _Lcd_writeLcdCharData(lcd_t* lcd, uint8_t data){
  _Lcd_setLcdMode(lcd, LCD_DATA_MODE_DATA_BUS);
  _Lcd_setReadWriteMode(lcd, LCD_WRITE_MODE);
  _Lcd_setEnableSignal(lcd, LCD_LOW_HIGH);
  _Lcd_setLcdPortData(lcd, data);
  _Lcd_setEnableSignal(lcd, LCD_LOW_STATE);
}

// row can be 0 or 1.
static void _Lcd_writeLcdStringToXy(lcd_t* lcd, char *str, uint8_t row, uint8_t col){
  col %= 16; row %=2;	// the device have 16 space for each column and have 2 row.
  uint8_t lcdRegisterAddress = (0x40 * row) + col; // refer to device spec;
  
  uint8_t cursorMoveCommand = LCD_CMD_SET_CURSOR_ADDR + lcdRegisterAddress;
  _Lcd_writeLcdCmdData(lcd, cursorMoveCommand);
  
  for(int i=0; str[i]; i++){ // ★
    _Lcd_writeLcdCharData(lcd, str[i]);
  }
}

static void _Lcd_clearDisplay(lcd_t* lcd){
  _Lcd_writeLcdCmdData(lcd, LCD_8bit_DISPLAY_CLEAR);
}

// ⚠️ it must be executed one-time if same LCD device is used between services in app. refer to RESET FUNCTION part of Datasheet
static void _Lcd_preprocessLcdTurnOn(lcd_t* lcd){
  _delay_ms(15); // wait 15ms
  _Lcd_writeLcdCmdData(lcd, LCD_8bit_FUNCTION_SET); // FUNCTION SET
  _delay_ms(5); // wait 4.1ms
  _Lcd_writeLcdCmdData(lcd, LCD_8bit_FUNCTION_SET); // FUNCTION SET
  _delay_ms(1); // wait 100us
  _Lcd_writeLcdCmdData(lcd, LCD_8bit_FUNCTION_SET); // FUNCTION SET
  _Lcd_writeLcdCmdData(lcd, LCD_8bit_FUNCTION_SET); // FUNCTION SET
  _Lcd_writeLcdCmdData(lcd, LCD_8bit_DISPLAY_OFF);	// Display ON/OFF Control (OFF)
  _Lcd_writeLcdCmdData(lcd, LCD_8bit_DISPLAY_CLEAR);	// Display clear	// ?
  _Lcd_writeLcdCmdData(lcd, LCD_8bit_ENTRY_MODE_SET);	// Entry mode TODO:?? set  // ?
  _Lcd_writeLcdCmdData(lcd, LCD_8bit_DISPLAY_ON);	// Display ON/OFF Control (ON)
}


void Lcd_init(lcd_t* lcd, volatile uint8_t* dataBusDDR, volatile uint8_t* dataBusPort, volatile uint8_t* contrlDDR, volatile uint8_t* contrlPort, uint8_t controlRegisterSelectPinNum, uint8_t controlReadWritePinNum, uint8_t controlEnableSignalPinNum){
  lcd->dataBusDDR = dataBusDDR;
  lcd->dataBusPort = dataBusPort;
  lcd->contrlDDR = contrlDDR;
  lcd->contrlPort = contrlPort;
  //
  
  lcd->controlRegisterSelectPinNum = controlRegisterSelectPinNum;
  lcd->controlReadWritePinNum = controlReadWritePinNum;
  lcd->controlEnableSignalPinNum = controlEnableSignalPinNum;
  
  // refer to RESET FUNCTION of the data sheet
  gpio_initDataDirectionRegisterPins(contrlDDR, OUTPUT, 3, controlRegisterSelectPinNum, controlReadWritePinNum, controlEnableSignalPinNum);
  gpio_initDataDirectionRegister(dataBusDDR, OUTPUT);

  lcd->writeLcdStringToXy = _Lcd_writeLcdStringToXy;
  lcd->clearDisplay = _Lcd_clearDisplay;
  lcd->preprocessLcdTurnOn = _Lcd_preprocessLcdTurnOn;
  
  
  // ●
  if (!isLcdPreprocessBeforeTurnOn) {
    lcd->preprocessLcdTurnOn(lcd);
    isLcdPreprocessBeforeTurnOn = 1;
  }    
}

