#ifndef UART_H_
#define UART_H_

#define _countof(array) (sizeof(array) / sizeof(array[0]))
#define QUEUE_COUNT 4
#define QUEUE_CHAR_LENGTH 100
#define UART_CHANNEL_1 UART0
#define UART_CHANNEL_2 UART1

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

typedef enum {
  UART_CHANNEL_1,
  UART_CHANNEL_2
} UartChannel ; // TODO: initialize method for UART_CHANNEL_2

typedef struct _uart {
  // It is implemented as Circular Queue.
  volatile uint8_t* dataChannel; // USART Data Register
  volatile uint16_t rear;
  volatile uint16_t front;
  volatile uint16_t charIndex;
  volatile uint8_t rxBuffer[QUEUE_COUNT][QUEUE_CHAR_LENGTH];
  
  ////// TODO Dynamic allocation of rx_bufffrom queue_count, queue_char_length.
  

  void (*enqueue)(struct _uart* self, uint8_t data);
  volatile uint8_t* (*dequeue)(struct _uart* self);
  uint8_t (*isFull)(struct _uart* self);
  uint8_t (*isEmpty)(struct _uart* self);
  
  uint8_t (*getRxData)(struct _uart* self);

} uart_t;


void Uart_init(uart_t* uart, UartChannel uartChannel);


#endif /* UART_H_ */


/*
===== ⚠️ Caution ⚠️ =====
When upload, ISP/UART switch must be in ISP mode.
When communicate UART, UART port must be opened firstly before you set ISP/UART switch  to UART mode.
===================

How to use
  🛍️ e.g.
  ISR(USART0_RX_vect)
  {
    fanService_processUart0Isr();
  }
  void fanService_run()
  {
    if (!uart.isEmpty(&uart)){
      volatile uint8_t* rxString = uart.dequeue(&uart); // pop
      printf("%s\n", rxString);
    }
  }




|	I2C			    |		UART		  |		SPI
-----------------------------------------------------------------
used Pin			      | SCL, SDA		|	TxD, RxD		| MOSI, MISO, SS, CLK
use Clock?			    | O				    |	O				    | X
unit of Bit Rate	  | Bps			    | Baud Rate		| Bps
number of Relation	| 1 : N			  | 1 : 1				| 1 : N
Communication		    | Half-duplex	| Full-duplex	| Full-duplex

Serial Peripheral Interface (SPI) ; https://en.wikipedia.org/wiki/Serial_Peripheral_Interface
[Pinout]
MOSI	Master Out Slave In
MISO	Master In Slave Out
SCLK	Serial Clock
CS		Chip Select (one or more)


Universal Asynchronous Receiver-Transmitter (UART) ; https://en.wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter
✅ Does a UART connection require shared ground? ; https://raspberrypi.stackexchange.com/questions/133811/does-a-uart-connection-require-shared-ground


specification: USART 170
...  Supports Serial Frames with 5, 6, 7, 8, or 9 Data Bits and 1 or 2 Stop Bits
Figure 79. USART Block Diagram
UBRR: USART Baud Rate Register (UBRR)
UDRE: USART Data Register Empty (UDRE) and Transmit Complete (TXC).
... (RXD1/IIT2) PD2
... (TXD1/INT3) PD3

* Frame Format 175
📝 default is High in IDLE.
USART Control and Status Register A – UCSRnA
• Bit 6 – TXCn: USART Transmit Complete
• Bit 7 – RXCn: USART Receive Complete
USARTn Control and Status Register B – UCSRnB
• Bit 7 – RXCIEn: RX Complete Interrupt Enable
• Bit 6 – TXCIEn: TX Complete Interrupt Enable
USART Baud Rate Registers – UBRRnL and UBRRnH
Table 74. Equations for Calculating Baud Rate Register Setting

193 p..
... Table 85. Examples of UBRR Settings for Commonly Used Oscillator Frequencies

Receive Compete Flag and Interrupt..
https://en.wikipedia.org/wiki/Parity_bit

USART (Universal Synchronus Receiver Transmit)    vs.   UART (Universal Asynchronous Receiver Transmit)
1. Promise Baud Rate, the number of (Data bit, Stop bit, Parity bit)
default value:
- Data bit:   8 bit
- Stop bit:   1 bit
- Parity bit: None
// x2 mode, Baud Rate 9600 ???
USART Control and Status Register A – UCSRnA
USARTn Control and Status Register B – UCSRnB
// Bit 0 – TXB8n: Transmit Data Bit 8
// Bit 1 – RXB8n: Receive Data Bit 8

*/