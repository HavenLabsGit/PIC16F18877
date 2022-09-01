#ifndef PWM_H_
#define PWM_H_

#include "pin_manager.h"
#include <xc.h>
/* Setup for PWM
 * 1. Disable the PWMx Pin retting TRIS bits
 * 2. Configure the PWM output polariy with PWMxPOL of PWMxCon
 * 3. Load PR2 register with PWM period value
 * 4. Load PWMxDCH register and bits 7:6 of PWMxDCL register from equation
 * 5. Clear TMR2IF of PIR1 register
 * 6. Enable Timer2 prescale by configuring T2CKPS1:0 of T2CON register
 * 7. Enable Timer2 by setting TMR2ON bit of T2CON
 * 8. Wait until TIMR2IF is set
 * 9. When set, clear associated TRIS bit to enable output driver
 *    Route the signal to desired pin by configuring RxyPPS register
 *    Enable PWMx Module by setting the PWMxEN bit of PWMxCON register */

/************* PWMxCON PWM CONTROL REGISTER ************************
 * PWMxEN bit 7. 1 is enable PWM 0 is disable
 * PWMxOUT bit 5. Outputlevel when bit is read
 * PWMxPOL bit 4. Output polarity select bit, 1 is active low 0 is active high
 *
 */

#define PWM6_ENABLE PWM6CONbits.PWM6EN
#define PWM6_POLARITY PWM6CONbits.PWM6POL
#define CLEAR_TRM2IF do {PIR4bits.TMR2IF = 0;} while(0)
#define PRESCALER_1 do {T2CONbits.OUTPS = 0x00;} while(0)
#define TIMER2_ON do {T2CONbits.ON = ENABLE;} while(0)
#define TRM2IF PIR4bits.TM2IF
#define SETPWM6_PPS do {PWM6OUTPPS = 0x0E; RA0PPS = 0x00;} while(0)
#define PWM7_ENABLE PWM6CONbits.PWM7EN
#define PWM7_POLARITY PWM6CONbits.PWM7POL
#define SETPWM7_PPS do {PWM7OUTPPS = 0x0F; RA1PPS = 0x01;} while(0)


 /*************** PWMxDCH PWM Duty Cycle High Bits *************************
 * PWMxDCH Duty cycle high bits 9:2 while PWMxDCL(bit 7:0) is low 1:0 (bit 7:6)
 * page 280 has more info
 *
 * */

void Init_PWM6(void);
void Init_PWM7(void);

#endif // PWM_H_
