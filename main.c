#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
// ---------- ?? App must be run exclusively because of ISR function's redefinition.
#define FAN_MACHINE_ISR   // ¡Ü to prevent ISR redefinition
// #define CLOCK_MACHINE_ISR // ¡Ü to prevent ISR redefinition
// --------------------------------------------------


#ifdef CLOCK_MACHINE_ISR
#include "app/clockMachine/clockMachine.h"
// ?? Do not include LCD display in ISR. LCD;s enable-bit and disable-bit code include _delay_ms(1);
ISR(TIMER0_OVF_vect)
{
  FND_ISR_Process();
  TCNT0=130;
}

ISR(TIMER2_COMP_vect)
{
  stopwatch_update();
  timeClock_increaseMilisec();
}
#endif

#ifdef FAN_MACHINE_ISR
#include "app/fanMachine/fanMachinApp.h"
// ?? Do not include LCD display in ISR. LCD;s enable-bit and disable-bit code include _delay_ms(1);
//FILE OUTPUT_STDOUT = FDEV_SETUP_STREAM(uart0_transmit, NULL, _FDEV_SETUP_WRITE);
//stdout = &OUTPUT_STDOUT;
//uart0_sendString("\nDevice: ...\n");
//
ISR(TIMER0_OVF_vect)
{
  fanPresenter_displayFndISR();
  TCNT0=130;
}

ISR(TIMER2_COMP_vect)
{
  fanService_processTimerIsr();
}

ISR(USART0_RX_vect)
{
  fanService_receiveUartIsr();
}
#endif


int main(void)
{
  fanMachine_init(); // not ended..
  //initClockMachine();
  while (1)
  {
    fanMachine_run();
    ////runClockMachine();
  }
}

/* ?????? App Common Requirements
* Abstraction
- Be cautious when a struct have struct. If inner struct is local variable, it causes unknown result. use static qualifier or use as global variable to inner struct.


* Naming convention
- use PascalCase for struct type name and enum type name.
- make function name used as method ¡Ü "<struct or enum type name as Pascalcase>_<function name as Camelcase> like Hungarian notation in order to prevent conflicting name. C language does not have Namespace.
- make function name used as normal function or utility function "<module name as Camelcase>_<function name as Camelcase> in order to prevent conflicting name.
- prefix "_" for static functions.
- use Upper Snake Case for macros, constants, and enum values. otherwise, use CamelCase.



* To prevent conflicting name Redefinition
- Enum value name format: "<Enum variable prefix as Upper Snake Case>_<enum State as Upper Snake Case>.
e.g. ??? BUTTON_PRESSED_STATE_NONE


- Remove Floating
- Remove Blocking. make non-Blocking
- Remove Bouncing (Chattering). make Debouncing
- Add Interrupt
- Reduce using resource. some code may require hardcoding. e.g. fnd.c - displayDigits(). using pow (floating operation) occupy many resource.
- Data Driven Programming
- Not duplicate Header Guard
*/



/* Shortcut keys
* open Solution Explorer (+ search by file name)
Ctrl + Alt + L

* Go to Implementation
Alt + G
*/