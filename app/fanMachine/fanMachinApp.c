#include "fanMachinApp.h"


void fanMachine_init()
{
  initTimerCounter0Interrupt();
  initTimerCounter2Interrupt();
  //
  fanListener_init();
  fanService_init();
  fanPresenter_init();
}

void fanMachine_run()
{
  fanService_run();
}