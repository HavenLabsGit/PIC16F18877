#ifndef OSC_H_
#define OSC_H_

#include <stdint.h>

// Defines for NOSC bits (New Oscillator source request bits)

#define HFINTOSC 0b110
#define EXTOSC 0b111
#define LFINTOSC 0b101
#define EXTOSC_4PLL 0b010
#define HFINTOSC_2PLL 0b001

// Defines for NDIV bits

#define DIV_1 0b0000
#define DIV_2 0b0001
#define DIV_3 0b0010
#define DIV_4 0b0011
#define DIV_8 0b0100
#define DIV_16 0b0101
#define DIV_32 0b0110
#define DIV_64 0b0111
#define DIV_128 0b1000
#define DIV_256 0b1001

// Defines for frequency
#define _1MHZ 0b000
#define _2MHZ 0b001
#define _4MHZ 0b010
#define _8MHZ 0b011
#define _12MHZ 0b100
#define _16MHZ 0b101
#define _32MHZ 0b110

void SetOscillator(uint8_t NOSC, uint8_t NDIV);



#endif // OSC_H_
