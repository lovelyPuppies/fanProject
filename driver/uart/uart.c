#include "uart.h"

static void _Uart_enqueue(uart_t* uart, uint8_t data){
  if ((data == '\n') || (uart->charIndex == QUEUE_CHAR_LENGTH)){
    uart->rxBuffer[uart->rear][uart->charIndex] = '\0';
    uart->charIndex = 0;
    uart->rear = (uart->rear+1) % QUEUE_COUNT;
   }
   else {
    uart->rxBuffer[uart->rear][uart->charIndex] = data;
    (uart->charIndex)++;
  }
  
  // pro-process
}

static volatile uint8_t* _Uart_dequeue(uart_t* uart){
  volatile uint8_t* rxString = uart->rxBuffer[uart->front];
  uart->front = (uart->front + 1) % QUEUE_COUNT;
  return rxString;
}

static uint8_t _Uart_isQueueFull(uart_t* uart){
  return (uart->rear + 1) % QUEUE_COUNT == uart->front % QUEUE_COUNT;
}
static uint8_t _Uart_isQueueEmpty(uart_t* uart){
  return uart->rear == uart->front;
}

static uint8_t _Uart_getRxData(uart_t* uart){
    return *(uart->dataChannel);
      
}
// ● It must be run once before communiation.

void Uart_initUartRegisterChannel1(){
  sei();
  
  UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
  //  Bit 1 – U2Xn: Double the USART Transmission Speed
  UCSR0A |= (1<<U2X0);
  UBRR0L = 207;  // set Baud Rate 4800 for F_osc = 16MHz.
  UCSR0B |= 1<<RXCIE0;  // Bit 7 – RXCIEn: RX Complete Interrupt Enable
}

void Uart_init(uart_t* uart, UartChannel uartChannel){
  uart->front = 0;
  uart->rear = 0;
  uart->charIndex = 0;

  for (size_t i=0; i< QUEUE_COUNT; i++){
    memset((void*)uart->rxBuffer[i], '\0', QUEUE_CHAR_LENGTH);
  }
  
  switch (uartChannel){
    case UART_CHANNEL_1:
      uart->dataChannel = &UDR0;  // USART Data Register
      Uart_initUartRegisterChannel1();
    break;
    case UART_CHANNEL_2: break; // TODO
  }
  
  
  uart->enqueue = _Uart_enqueue;
  uart->dequeue = _Uart_dequeue;
  uart->isFull = _Uart_isQueueFull;
  uart->isEmpty = _Uart_isQueueEmpty;
  
  uart->getRxData = _Uart_getRxData;
  }
  
  

  /*

  //uart0_sendString("Receive Data: ");
  //uart0_sendString((char*) uart0_readRxBuff());
 
 //
 //void uart0_transmit( unsigned char data )
 //{
   // Wait for empty transmit buffer 
   //// Bit 5 – UDREn: USART Data Register Empty
   //while ( !( UCSR0A & (1<<UDRE0)))   ;    // when UDRE0 is 1 (emtpy), put data
   // Put data into buffer, sends the data 
   //UDR0 = data;
 //}
 //// Data Reception – The USART Receiver
 //// Receiving Frames with 5 to 8 Data Bits
 //unsigned char uart0_receive( void )
 //{
   /// Wait for data to be received 
   //while ( !(UCSR0A & (1<<RXC0)) )
   //;
   // Get and return received data from buffer 
   //return UDR0;
 //}
 //unsigned char uart0_receiveAvailableData( void )
 //{
   // Wait for data to be received 
   //if ( !(UCSR0A & (1<<RXC0)) )
   //return 0;
   //
   // Get and return received data from buffer 
   //return 1;
 //}
//
 //void uart0_sendString (char*str)
 //{
   //for (int i = 0; str[i]; i++){
     //uart0_transmit(str[i]);
   //}
 //}
//
 //void uart0_disableRxFlag(){
   //uart0RxFlag = 0;
 //}
 //void uart0_enableRxFlag(){
   //uart0RxFlag = 1;
 //}
//
 //uint8_t uart0_getRxFlag(){
   //return uart0RxFlag;
 //}
//
 //uint8_t* uart0_readRxBuff(){
   //return uart0Rxbuff;
 //} 
  //
  */