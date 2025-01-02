#include "Listener.h"

button_t btnRunStop, btnControlMode, btnSwitch, btnFND;

uint8_t stopWatchState;

void initListener()
{
  Button_init(&btnRunStop,&DDRA, &PINA,0);
  Button_init(&btnControlMode,&DDRA, &PINA,1);
  Button_init(&btnSwitch,&DDRA, &PINA,2);
  Button_init(&btnFND,&DDRA, &PINA,3);
}



void Listener_eventCheck()
{
  uint8_t timeModeState = getClockMachineModeStateData();
  
  switch(timeModeState)
  {
    case TIMECLOCK :
    checkClockEvent();
    if(Button_getPressedState(&btnSwitch)==BUTTON_PRESSED_STATE_RELEASED)
    {
      timeModeState = STOPWATCH;
      setClockMachineModeStateData(timeModeState);
    }
    break;
    case STOPWATCH :
    checkStopwatchEvent();
    if(Button_getPressedState(&btnSwitch)==BUTTON_PRESSED_STATE_RELEASED)
    {
      timeModeState = TIMECLOCK;
      setClockMachineModeStateData(timeModeState);
    }
    break;
    
  }
}


void checkStopwatchEvent()
{
  uint8_t stopWatchState;
  stopWatchState = getStopwatchStateData();
  
  switch(stopWatchState)
  {
    case STOP :
    if(Button_getPressedState(&btnRunStop)==BUTTON_PRESSED_STATE_RELEASED)
    {
      stopWatchState = RUN;
      Model_setStopWatchStateData(stopWatchState);
    }
    else if(Button_getPressedState(&btnControlMode)==BUTTON_PRESSED_STATE_RELEASED)
    {
      stopWatchState = RESET;
      Model_setStopWatchStateData(stopWatchState);
    }
    break;
    case RUN :
    if(Button_getPressedState(&btnRunStop)==BUTTON_PRESSED_STATE_RELEASED)
    {
      stopWatchState=STOP;
      Model_setStopWatchStateData(stopWatchState);
    }
    break;
    case RESET :
    {
      stopWatchState=STOP;
      Model_setStopWatchStateData(stopWatchState);
    }
    break;
  }
}

void checkClockEvent()
{
  uint8_t timeClockDisplayStateData;
  
  timeClockDisplayStateData = Model_getTimeClockDispStateData();
  
  switch (timeClockDisplayStateData)
  {
    case HOUR_MIN :
    if(Button_getPressedState(&btnFND)==BUTTON_PRESSED_STATE_RELEASED)
    {
      timeClockDisplayStateData = SEC_MIL;
      Model_setTimeClockDispStateData(timeClockDisplayStateData);
    }
    break;
    case SEC_MIL :
    if(Button_getPressedState(&btnFND)==BUTTON_PRESSED_STATE_RELEASED)
    {
      timeClockDisplayStateData = HOUR_MIN;
      Model_setTimeClockDispStateData(timeClockDisplayStateData);
    }
    break;
  }
  
}