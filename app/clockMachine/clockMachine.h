#ifndef CLOCKMACHINE_H_
#define CLOCKMACHINE_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Listener/Listener.h"
#include "Service/Service_StopWatch.h"
#include "Service/Service_TimeClock.h"
#include "Presenter/Presenter.h"
#include "Model/Model_StopWatchState.h"
#include "Model/Model_timeClockDispState.h"
#include "Model/Model_TimeModeState.h"
#include "../../driver/timer/timer.h"


void initClockMachine();
void runClockMachine();


#endif /* CLOCKMACHINE_H_ */




/*
===== Consideration =====
- share ClockMachineAppState between StopWatch, Clock.
  ✋ use extern variable: extern enum ClockMachineAppState clockMachineAppState;
- share same LCD hardware between StopWatch, Clock.
  but LCD reset function must be run only one-time before first turn-on.
  ✋ use extern variable: extern uint8_t isLcdPreprocessdBeforeTurnOn;
- share Timer/Counter Interrupt Registers between StopWatch, Clock.
  ✋ use extern variable: extern uint8_t isTimerInterruptInitialized;

- share same (Button, LED) between StopWatch, Clock.
  but each struct is in each file, Two states not Interfere themselves.

- ★ Optimize ISR. complete operation must be run in main loop. not ISR. otherwise whenever interrupt occurs, ISR may be not processed until next Interrupt. 
    - ISR(TIMER0_OVF_vect): only display FND, LCD. format operation must be written in main loop. not ISR.
    - ISR(TIMER2_COMP_vect): only do +1 millisecond to timer operation.
===== Requirements =====

ISR(TIMER0_OVF_vect): use TCNT0 = 130 (255 - 125);

*/


/*
.. 다른사람이 한 것:	

속도가 너무 느림.. 테스트해봐야 할 것..
- sei() 2번 호출이 영향을 주는가? X 
- 전역변수 많이 상ㅇ하는 문제?
	캐시 효율성 저하: 전역 변수가 많이 사용되면, 프로세서의 캐시 성능에 영향을 줄 수 있습니다. 전역 변수는 메모리 상의 임의 위치에 존재할 수 있으므로, 캐시 미스(cache miss)가 발생할 가능성이 높아질 수 있습니다. 이는 메모리 접근 속도를 저하시킬 수 있습니다.
접근성 떄문인가? 포인터.. struct Timer -> +1
fnd -> +1

*/