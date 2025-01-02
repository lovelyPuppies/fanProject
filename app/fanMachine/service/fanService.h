#ifndef FANSERVICE_H_
#define FANSERVICE_H_



#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "../model/fanModel.h"
#include "../listener/fanListener.h"
#include "../presenter/fanPresenter.h"
#include "../../../utility/clockTimer.h"
#include "../../../driver/uart/uart.h"
#include "../../../peripheral/motor/motor.h"
#include "../../../peripheral/buzzer/buzzer.h"

void fanService_processTimerIsr();
void fanService_receiveUartIsr();

void fanService_init();
void fanService_run();

#endif /* FANSERVICE_H_ */