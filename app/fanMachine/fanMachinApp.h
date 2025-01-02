#ifndef FANMACHINEAPP_H_
#define FANMACHINEAPP_H_

#define _countof(array) (sizeof(array) / sizeof(array[0])) // ⚠️ use only array is not pointer!!

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#include "model/fanModel.h"
#include "listener/fanListener.h"
#include "service/fanService.h"
#include "presenter/fanPresenter.h"
#include "../../driver/timer/timer.h"

void fanMachine_init();
void fanMachine_run();

#endif /* FANMACHINEAPP_H_ */


/*

Digital fan 만들기
* FanSpeed
- 풍량 조절: off, 미풍, 약풍, 강풍
// state: FanSpeedState = 0 ~ 3., getter, setter, setToNextMode  // 0 is off.
// listener: button 1
// service: FanSpeedState 에 따라 setFanSpeed() 세팅. % 로 적용하기 위해 OCR3a = ICR3 * dutyCycle /100  한다.
// presenter: None

- 모드: 자동, 수동 (UART, Button)
// state: ControlModeState: {FAN_OPERATION_MODE_AUTO, FAN_OPERATION_MODE_MANUAL}
// listener: button 2, uart   -> change State.
// service:
when Auto mode,
AutomaticModeClockTimer. 10초마다 서비스에서 미풍 ~ 강풍으로 변경. (i % 3)+1. CTC 모드에서 ISR에서 상태에 따라 활성화하기.
// ISP 에서 +1 millisecond 적용

// presenter: (%s, ControlMode)

- 조작방법
// event: Button, UART

* Timer: n분 후 fan off (3, 5,7 분)
// clockTimer_t fanOffClockTimer
- FND display
Timer 설정이 된 경우에만 시간 출력
// state: FanOffTimer {FAN_OFF_TIMER_NONE, FAN_OFF_TIMER_3_MINUTE, FAN_OFF_TIMER_5_MINUTE, FAN_OFF_TIMER_7_MINUTE, FAN_OFF_TIMER_PROCESSING}
// listener: button 3, uart   -> change State...
...?? 서비스에서 상태 바뀐 경우, FAN_OFF_TIMER_NONE 나 FAN_OFF_TIMER_PROCESSING 게 아니 경우, Timer 3 minute, FAN_OFF_TIMER_PROCESSING 로 설정.
// service: // ISP 에서 -1 millisecond 적용
// presenter: DisplayFormat: MMSS

- 조작방법
// event: Button, UART

* LCD
format:
- 1 line: 제품명
- 2 line: 풍량모드 / 타이머   // 0: 미설정. show fanOffClockTimer.second

* option
- Buzzer 사용: 동작/종료, 버튼 누를 시, 타이머 종료 시
- LED 사용
최대 9분. 초마다 GPIO.. 에 혼자 했던거 넣기.



=> Event:
button 1: 풍량 조절 (0 ~ 3; off, 미풍, 양풍, 강풍); enum State


// ... ??하드웨어와 직접 상호작용 하는 코드 -> driver
// 주변 장치 제어 코드는 드라이버를 이용하여 실제로 장치를 제어하는 고수준의 코드.. 이거 아니엇나..
*/
