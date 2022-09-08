/*RCJK I2C Drivers PIC16F18877*/

#ifndef I2C_DRIVERS_H_
#define I2C_DRIVERS_H_

#include <stdint.h>
#include "../in_progress/pin_manager.h"


//MACROS

#define ACKNOWLEDGE 0
#define NOT_ACKNOWLEDGE 1

#define CLOCK_400KHZ 0x09 
#define MASTER_MODE 0x08


#define SSP1
// I2C crap

#ifdef SSP1

#define SSP_SLEW_RATE SSP1STATbits.SMP
#define SSP_SMBUS_EN SSP1STATbits.CKE

#define SSP_CLOCK SSP1ADD
#define SSP_ENABLE SSP1CON1bits.SSPEN
#define SSP_MODE SSP1CON1bits.SSPM

// PPS Inputs
#define SDA_PPS_INPUT do{SSP1DATPPS = 0x14;} while(0) //RC4->MSSP1:SDA1; page 236
#define SCK_PPS_INPUT do{SSP1CLKPPS = 0x13;} while(0) //RC3->MSSP1:SCL1;
// PPS Outputs
#define SDA_PPS_OUTPUT do{RC4PPS = 0x15;} while(0) //RC4->MSSP1:SDA1;
#define SCK_PPS_OUTPUT do{RC3PPS = 0x14;} while(0) //RC3->MSSP1:SCL1; page 239
// Conditions
#define I2C_START_SEND do{SSP1CON2bits.SEN = 1;} while(0) // Sends start bit
#define I2C_START_BIT SSP1CON2bits.SEN // Access start bit
#define I2C_STOP_SEND do{SSP1CON2bits.PEN = 1;} while(0) // Sends stop bit
#define I2C_STOP_BIT SSP1CON2bits.PEN // Access stop bit
#define I2C_RESEND do{SSP1CON2bits.RSEN = 1;} while(0) // Sends reset bit
#define I2C_RESEND_BIT SSP1CON2bits.RSEN
#define I2C_DATA_BUFFER SSP1BUF // Access I2C data buffer
#define I2C_DATA_BIT SSP1STATbits.BF // Access buffer status
#define I2C_RECEIVE do{SSP1CON2bits.RCEN = 1;} while(0)
#define I2C_ACK_SEQ do{SSP1CON2bits.ACKEN = 1;} while(0)
#define I2C_ACK SSP1CON2bits.ACKDT
#define I2C_IDLE ((SSP1STAT == 0x04) || (SSP1CON2 == 0x1f))
// Interupt handling
#define I2C_CLEAR_IF PIR3bits.SSP1IF = 0
#define I2C_IF PIR3bits.SSP1IF
#define I2C_CLEAR_BUS_COL PIR3bits.BCL1IF = 0
#define I2C_BUS_COL PIR3bits.BCL1IF
// Alias for analog/digital ports
#define RC3_DIGITAL do{ANSC3 = 0;} while(0)
#define RC4_DIGITAL do{ANSC4 = 0;} while(0)



#endif

#ifdef SSP2

#define SSP_SLEW_RATE SSP2STATbits.SMP // 1 disable slew rate 0 enables might need for 400kHz
#define SSP_SMBUS_EN SSP2STATbits.CKE

#define SSP_CLOCK SSP2ADD
#define SSP_ENABLE SSP2CON1bits.SSPEN
#define SSP_MODE SSP2CON1bits.SSPM

#define SDA_PPS_INPUT do{SSP2DATPPS = 0x0A;} while(0) //RB1->MSSP2:SDA1; page 236
#define SCK_PPS_INPUT do{SSP2CLKPPS = 0x19;} while(0) //RB2->MSSP2:SCL1;

#define SDA_PPS_OUTPUT do{RB1PPS = 0x16;} while(0) //RB1->MSSP2:SCL1; page 239
#define SCK_PPS_OUTPUT do{RB2PPS = 0x17;} while(0) //RB2->MSSP2:SDA1;
// Conditions
#define I2C_START_SEND do{SSP2CON2bits.SEN = 1;} while(0) // Sends start bit
#define I2C_START_BIT SSP2CON2bits.SEN // Access start bit
#define I2C_STOP_SEND do{SSP2CON2bits.PEN = 1;} while(0) // Sends stop bit
#define I2C_STOP_BIT SSP2CON2bits.PEN // Access stop bit
#define I2C_RESEND do{SSP2CON2bits.RSEN = 1;} while(0) // Sends reset bit
#define I2C_RESEND_BIT SSP2CON2bits.RSEN
#define I2C_DATA_BUFFER SSP2BUF // Access I2C data buffer
#define I2C_DATA_BIT SSP2STATbits.BF // Access buffer status
#define I2C_RECEIVE do{SSP2CON2bits.RCEN = 1;} while(0)
#define I2C_ACK_SEQ do{SSP2CON2bits.ACKEN = 1;} while(0)
#define I2C_ACK SSP2CON2bit.ACKDT
#define I2C_IDLE ((SSP2STAT == 0x04) || (SSP2CON2 == 0x1f))
// Interupt handling
#define I2C_CLEAR_IF PIR3bits.SSP2IF = 0
#define I2C_IF PIR3bits.SSP2IF
#define I2C_CLEAR_BUS_COL PIR3bits.BCL2IF = 0
#define I2C_BUS_COL PIR3bits.BCL2IF

#endif


// ========================== How the signal works ========================= //
/*    SEN=1  SEN=0       ADDRESS                         R/W  ACK=0                 
 *      ____      __    __    __    __    __    __    __    
 * SDA |    |    |  |  |  |  |  |  |  |  |  |  |  |  |  |  
 *     |    |____|A7|__|A6|__|A5|__|A4|__|A3|__|A2|__|A1|__________
 
 
 */
/***************************************************************************
  ================= PRIVATE Function Prototypes ===========================
 ***************************************************************************/
static void Flag_Polling(void);
static void I2C_Idle_Check(void);

/***************************************************************************
  ================= PUBLIC Function Prototypes ============================
 ***************************************************************************/

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Restart(void);
void I2C_NotAck_Read(uint8_t *rx_data);
void I2C_Ack_Read(uint8_t *rx_data, uint8_t count);
void I2C_Write(uint8_t I2C_data);


#endif
