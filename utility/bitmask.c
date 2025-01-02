#include "bitmask.h"

uint8_t clearSpecificBit(uint8_t data, uint8_t bitPosition){
	return data & ~(1 << bitPosition);
}

// 🛍️ e.g. BUTTON_DDR = pullup_bitmask_input(BUTTON_DDR, button_ddra_positions, _countof(button_ddra_positions));
uint8_t bitmask_or(uint8_t ddr, const uint8_t *positions, size_t size) {
	uint8_t mask = 0;
	for (size_t i = 0; i < size; ++i) {
		mask |= (1 << positions[i]);
	}
	return ddr | mask;
}
// 🛍️ e.g. LED_DDR = bitmask_or(LED_DDR, led_ddrd_positions, _countof(led_ddrd_positions));
// ⚠️ If hardware is no problem and not set LED DDR, led light is dark or weak.
uint8_t pullup_bitmask_input(uint8_t pin, const uint8_t *positions, size_t size) {
	uint8_t mask = 0;
	for (size_t i = 0; i < size; ++i) {
		mask |= (1 << positions[i]);
	}
	return pin & ~mask;
}
