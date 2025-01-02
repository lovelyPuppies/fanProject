/*
 * bitmask.h
 *
 * Created: 2024-07-30 오전 11:24:06
 *  Author: iot04
 */ 


#ifndef BITMASK_H_
#define BITMASK_H_

#include <stddef.h>
#include <stdint.h>

uint8_t clearSpecificBit(uint8_t data, uint8_t bitPosition);
uint8_t bitmask_or(uint8_t ddr, const uint8_t *positions, size_t size);
uint8_t pullup_bitmask_input(uint8_t pin, const uint8_t *positions, size_t size);




#endif /* BITMASK_H_ */