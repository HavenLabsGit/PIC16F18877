#include "pwm.h"


void Init_PWM6(){

    TRISAbits.TRISA0 = DISABLE;
    PWM6_POLARITY = HIGH;
    PR2 = 0x4F;
    CLEAR_TRM2IF;
    PRESCALER_1;
    TIMER2_ON;
    while (TRM2IF == LOW);
    TRISAbits.TRISA0 = OUTPUT;
    SETPWM6_PPS;
    PWM6_ENABLE;



}


void Init_PWM7(){

    TRISAbits.TRISA1 = DISABLE;
    PWM7_POLARITY = LOW;
    PR2 = 0x4F;
    CLEAR_TRM2IF;
    PRESCALER_1;
    TIMER2_ON;
    while (TRM2IF == LOW);
    TRISAbits.TRISA1  = OUTPUT;
    SETPWM7_PPS;
    PWM7_ENABLE;



}
