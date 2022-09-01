#include "pin_manager.h"


void pin_initialize(){
/* LATx registers ~ output latch */
    LATE = 0x00;
    LATD = 0x00;
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    /* TRISx registers ~ data direction*/
    TRISE = 0x07;
    TRISA = 0x02;
    TRISB = 0xFF;
    TRISC = 0xBF;
    TRISD = 0xFF;

    /* ANSELx registers ~ Analog select */

    ANSELD = 0xFF;
    ANSELC = 0xE7;
    ANSELB = 0xE9;
    ANSELE = 0x07;
    ANSELA = 0x00;

    /* PORTx registers ~ read the level of the pins */
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0X00;
    PORTD = 0x00;
    // Pin mapping





}
