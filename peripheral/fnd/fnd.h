#ifndef FND_H_
#define FND_H_
#define _countof(array) (sizeof(array) / sizeof(array[0])) // ⚠️ use only array is not pointer!!

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../driver/gpio/gpio.h"
#include "../../utility/bitmask.h"

// Flexible Numeric Display

// 📝 digitPortPins must be initialized in ascending order from high digit to low digit in order to use my fnd.h functions. and DIGIT_PORT_PINS_SIZE is 4.
typedef struct _fnd {
  volatile uint8_t* segmentDDR;
  volatile uint8_t* digitDDR;

  volatile uint8_t* segmentPort;
  volatile uint8_t* digitPort;
  size_t digitPortPinNumArrLength;
  uint8_t* digitPortPinNumArr; // array
  uint8_t max_digit_state;
  
  uint16_t value; // 4-digit value to display
  
  uint8_t digitState; // variable used to display One number. Max value is DIGIT_PORT_PINS_SIZE-1.
  
  uint8_t colonFlag;
  
  // struct Function Pointer as self
  void (*setFndNum)(struct _fnd* self, uint16_t value);
  void (*setFndColonFlag)(struct _fnd* self, uint8_t value);
  void (*displayFnd)(struct _fnd* self);
  void (*turnOff)(struct _fnd* self);
} fnd_t;

void Fnd_init(fnd_t* fnd, volatile uint8_t* segmentDDR, volatile uint8_t* digitDDR, volatile uint8_t* segmentPort, volatile uint8_t* digitPort, size_t digitPortPinNumArrLength, uint8_t* digitPortPinNumArr);

#endif /* FND_H_ */

/* Flexible Numeric Display (FND)
===== Device Specification =====
- Common-Cathode type
*/