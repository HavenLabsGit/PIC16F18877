#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "pin_manager.h"
#include <stdint.h>

// Macros

#define RISING_EDGE 1
#define FALING_EDGE 0

// Interrupt enable bits
//
#define GIE INTCONbits.GIE // Global interrupt bit 7
#define PIE INTCONbits.PEIE // Peripheral interrupt bit 6
#define INT_EDGE INTCONbits.INTEDG // Select rising/falling edge bit 0

// PEI0 Regsiter

#define TMR0_IE PEI0bits.TMR0IE // Timer 0 overflow bit flag bit 5
#define IOC_IE PEI0bits.IOCIE // Interrupt on change bit 4
#define INTE PEI0bits.INTE // External interrupt flag bit 0

// PEI1 Regsiter

#define OSC_FAIL_IE PEI1bits.OSFIE // Oscillator fail bit 7
#define CLOCK_SWITCH_IE PEI1bits.CSWIE // Clock switch interrupt bit 6
#define ADC_THRES_IE PEI1bits.ADTIE // ADC threshold compare interrupt bit 1
#define ADC_IE PEI1bits.ADIE // ADC interrupt enable bit 0

// PEI2 Regsiter

#define ZCD_IE PEI2bits.ZCDIE // Zero Cross detection interrupt bit 6
#define COMP2_IE PEI2bits.C2IE // Comparator C2 interrupt bit 1
#define COMP1_IE PEI2bits.C1IE // Comparator C1 interrupt bit 0

// PEI3 Register

#define UART_RX_IE PEI3bits.RCIE // UART Receiver flag bit 5
#define UART_TX_IE PEI3bits.TXIE // UART Transmit flag bit 4
#define MMSP2_BUS_COL_IE PEI3bits.BCL2IE // MMSP2 bus collusion bit 3
#define SYNC2_SERIAL_COL_IE PEI3bits.SSP2IE // SSP bus collusion bit 2
#define MMSP1_BUS_COL_IE PEI3bits.BCL1IE // MMSP2 bus collusion bit 1
#define SYNC1_SERIAL_COL_IE PEI3bits.SSP1IE // SSP bus collusion bit 0

// PIE4 Register

#define TMR6_IE PEI4bits.TMR6IE // Timer 6 interrupt flag bit 5
#define TMR5_IE PEI4bits.TMR5IE // Timer 5 interrupt flag bit 4
#define TMR4_IE PEI4bits.TMR4IE // Timer 4 interrupt flag bit 3
#define TMR3_IE PEI4bits.TMR3IE // Timer 3 interrupt flag bit 2
#define TMR2_IE PEI4bits.TMR2IE // Timer 2 interrupt flag bit 1
#define TMR1_IE PEI4bits.TMR1IE // Timer 1 interrupt flag bit 0

//















#endif // INTERRUPTS_H_
