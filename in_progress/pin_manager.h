#ifndef PIN_MANAGER_H_
#define PIN_MANAGER_H_

#include <xc.h>

// Macros

#define INPUT   1
#define OUTPUT  0

#define ENABLE 1
#define DISABLE 0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

/* ~=~=~=~=~=~=~=~=~=~=~=~=~ Specifications Pull Up ~=~=~=~=~=~=~=~=~=~=~=~=~
 * Weak Pull-up Current Min Typ  Max
 *                      25  120  200 uA
 * ~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

#define OPEN_DRAIN 1
#define PUSH_PULL 0

#define LIMITED_SLEW 1
#define MAXIMUM_SLEW 0

/* ~=~=~=~=~=~=~=~=~=~ Specifications Input Threshold ~=~=~=~=~=~=~=~=~=~=~
 * NOTE: Changing the threshold should be done while peripheral modules are
 * disabled.
 * ~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/

#define ST_INPUT 1
#define TTL_INPUT 0


/* ~=~=~=~=~=~=~=~=~=~ Port Aliases ~=~=~=~=~=~=~=~=~=~= */

#define PORTA0 PORTAbits.RA0
#define PORTA1 PORTAbits.RA1
#define PORTA2 PORTAbits.RA2
#define PORTA3 PORTAbits.RA3
#define PORTA4 PORTAbits.RA4
#define PORTA5 PORTAbits.RA5
#define PORTA6 PORTAbits.RA6
#define PORTA7 PORTAbits.RA7

#define PORTB0 PORTBbits.RB0
#define PORTB1 PORTBbits.RB1
#define PORTB2 PORTBbits.RB2
#define PORTB3 PORTBbits.RB3
#define PORTB4 PORTBbits.RB4
#define PORTB5 PORTBbits.RB5
#define PORTB6 PORTBbits.RB6
#define PORTB7 PORTBbits.RB7

#define PORTC0 PORTCbits.RC0
#define PORTC1 PORTCbits.RC1
#define PORTC2 PORTCbits.RC2
#define PORTC3 PORTCbits.RC3
#define PORTC4 PORTCbits.RC4
#define PORTC5 PORTCbits.RC5
#define PORTC6 PORTCbits.RC6
#define PORTC7 PORTCbits.RC7

#define PORTD0 PORTDbits.RD0
#define PORTD1 PORTDbits.RD1
#define PORTD2 PORTDbits.RD2
#define PORTD3 PORTDbits.RD3
#define PORTD4 PORTDbits.RD4
#define PORTD5 PORTDbits.RD5
#define PORTD6 PORTDbits.RD6
#define PORTD7 PORTDbits.RD7



// Set PWM RC! aliases
/* #define PWM_C1_TRIS 	TRISCbits.TRISC1 */
/* #define PWM_C1_LAT 	LATCbits.LATC1 */
/* #define PWM_C1_PORT 	PORTCbits.RC1 */
/* #define PWM_C1_WPU 	WPUCbits.WPUC1 */
/* #define PWM_C1_OD 		ODCONCbits.ODC1 */


// Function prototypes
void pin_initalize();



#endif // PIN_MANAGER_H_
