#include "Presenter.h"

static lcd_t lcd;
static fnd_t fnd;

void initStopwatchPresenter()
{
	Lcd_init(&lcd, &LCD_DATA_BUS_DDR, &LCD_DATA_BUS_PORT, &LCD_CONTROL_DDR, &LCD_CONTROL_PORT, LCD_RS, LCD_RW, LCD_E);
  
	static uint8_t fndDigitPinNumArr[4] = {FND_DIGIT_4_PIN, FND_DIGIT_3_PIN, FND_DIGIT_2_PIN, FND_DIGIT_1_PIN};
	Fnd_init(&fnd, &FND_SEGMENT_DDR, &FND_DIGIT_DDR, &FND_SEGMENT_PORT, &FND_DIGIT_PORT, _countof(fndDigitPinNumArr), fndDigitPinNumArr);
}


void displayStopWatchData(uint8_t hour, uint8_t min, uint8_t sec, uint16_t milisec)
{
  // ??? Always run...
	static uint16_t prevMilisec = 0xff;
	
	if(milisec/10 == prevMilisec){
		prevMilisec = milisec/10;
		return;
	}
	
	uint16_t stopWatchData;

	stopWatchData = (min%10*1000)+(sec*10)+(milisec/100%10);
	//FND_setFndData(stopWatchData);
	fnd.setFndNum(&fnd, stopWatchData);
	
	char buff[30];
	
	sprintf(buff,"Stop Watch");
  lcd.writeLcdStringToXy(&lcd, buff, 0, 3);
	sprintf(buff,"%02d:%02d:%02d:%02d", hour, min, sec, milisec/10);
  lcd.writeLcdStringToXy(&lcd, buff, 1, 3);
}

void displayTimeClockData(uint8_t hour, uint8_t min, uint8_t sec, uint16_t milisec)
{
	static uint16_t prevMilisec = 0xff;
	
	if(milisec/10 == prevMilisec){
		prevMilisec = milisec/10;
		return;
	}	
	
	uint16_t timeClockData = 0;
	uint8_t timeClockDispStateData;
	timeClockDispStateData = Model_getTimeClockDispStateData();
	
	switch(timeClockDispStateData)
	{
		case HOUR_MIN :
		timeClockData = hour*100+min;
    fnd.setFndNum(&fnd, timeClockData);
		//FND_setFndData(timeClockData);
		break;
		case SEC_MIL :
		timeClockData = sec*100+milisec/10;
		//FND_setFndData(timeClockData);
    fnd.setFndNum(&fnd, timeClockData);
		break;
	}	
	char buff[30];
	
	sprintf(buff,"Time Clock");
  lcd.writeLcdStringToXy(&lcd, buff, 0, 3);
	sprintf(buff,"%02d:%02d:%02d:%02d", hour, min, sec, milisec/10);
	lcd.writeLcdStringToXy(&lcd, buff, 1, 3);
	
	if(milisec/10 < 50)
	{
		//FND_colonOn();
    fnd.setFndColonFlag(&fnd, 1);
  }
	else
	{
		//FND_colonOff();
    fnd.setFndColonFlag(&fnd, 0);
	}
	
	
}


void FND_ISR_Process()
{
  fnd.displayFnd(&fnd);
}