#include "timer.h"

//// Settings - Interrupt
// Interrupt Service Routine (ISR) is located in a App directory or main.c.

void initTimerCounter0Interrupt() // 1ms overflow Interrupt , FND Display
{
	TCCR0 |= ((1<<CS02) | ( 0<<CS01) | (1<<CS00));	// 128 PreScaler
	TIMSK |= (1<<TOIE0);							// TIMSK Timer/Counter0 overflow Interrupt Enable
	TCNT0 = 130;
	
	sei(); // (Set Enable Interrupts) set global interrupt enable
}

void initTimerCounter2Interrupt()
{
	// Timer/Counter 2 1/64 1ms period interrupt, CTC mode
	// 1/64 PreScaler
	TCCR2 |= ((0<<CS22) | (1<<CS21) | (1<<CS20));
	TIMSK |= (1<<OCIE2);
	// CTC mode
	TCCR2 |= ((1<<WGM21) | (0<<WGM20));
	OCR2 = 250-1;	// Output Compare Register
	
	sei(); // (Set Enable Interrupts) set global interrupt enable
}

	
  
////TODO

//// Settings - Interrupt
// Interrupt Service Routine (ISR) is located in main.c file.

//static void setGlobalInterrupt(){
  //sei(); // (Set Enable Interrupts) set global interrupt enable
//}
//
//// "Timer/Counter Interrupt Mask Register – TIMSK"
//static void setTIMSK(uint8_t timerCounterNum){
  //switch (timerCounterNum){
    //case 0: // and if Normal mode
    //TIMSK |= (1<<TOIE0); // Timer/Counter0 Overflow Interrupt Enable.
    //TCNT0 = 130; // 255 - 125. 1/( 125000) * 125  = 0.001. to occur
    //break;
    //case 2: // and if CTC mode
    //TCCR2 |= (0<<CS22 | 1 << CS21 | 1<< CS20);
    //TIMSK |= (1<<OCIE2); // enable
    //break;
  //}
  //
//}
//
//static void setPrescaler(uint8_t timerCounterNum){
  //switch (timerCounterNum){
    //case 0: // and if Normal mode
    //TCCR0 |= ((1<<CS02) | ( 0<<CS01) | (1<<CS00));	// Timer Counter Control Register. 128 prescaler
    //break;
    //case 2: // and if CTC mode
    //TCCR2 |= (1<<WGM21) | (0<<WGM20);	// 64 prescaler
    //OCR2 = 250-1; // ???? // Output Compare Register
    //break;
  //}
//}
//
//static void setTimerCounterInterrupt(uint8_t timerCounterNum){
  ////// Requirements
  //setPrescaler(timerCounterNum);
  //setTIMSK(timerCounterNum);
  //setGlobalInterrupt();
//}
//
//void initTimer(uint8_t timerCounterNum){
  //setTimerCounterInterrupt(timerCounterNum);
//}
//
