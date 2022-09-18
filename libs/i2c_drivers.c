
#include <stdint.h>
#include "i2c_drivers.h"
#include "pic16f18877.h"


/***************************************************************************
 ============================ Public Functions =============================
 ***************************************************************************/

/* Name: I2C_INIT
 * Parameter: void
 * Return: nothing
 * Description: Function initializes the ucontroller for I2C communication
 */


void I2C_Init(void){
    
    RC3_DIGITAL;
    RC4_DIGITAL;
    SSP_SLEW_RATE = 0;
    SSP_SMBUS_EN = DISABLE;
    SSP_CLOCK = CLOCK_400KHZ; /* Sets I2C clock to 400kHz */
    SSP_ENABLE = ENABLE; /* Enables the SDA and SCL pins as source */
    SSP_MODE = MASTER_MODE; /* I2C Master Mode clock = Fosc / (4 * (SSP1ADD +1)) */
    SDA_PPS_INPUT;
    SCK_PPS_INPUT;
    SDA_PPS_OUTPUT;
    SCK_PPS_OUTPUT;
}

/* Name: I2C_Start
 * Parameter: void
 * Return: nothing
 * Description: Function issues a start condition. Start condition is the transition of SDA
 * from a high to low state while SCL is high */


void I2C_Start(void){

    I2C_Idle_Check();
    I2C_START_SEND;
    while(I2C_START_BIT == HIGH);
    //Flag_Polling();

}

/* Name: I2C_Stop
 * Parameter: void
 * Return: nothing
 * Description: Function issues a stop condition. Stop condition is the transition of SDA
 * from a low to high state while SCL is high */

void I2C_Stop(void){

    I2C_Idle_Check();
    I2C_STOP_SEND;
    //Flag_Polling();


}
/* Name: I2C_Restart
 * Parameter: void
 * Return: nothing
 * Description: Function issues a reset. Reset is valid any time a stop is valid. Master can
 *  issue reset which has same effect on the slave that a start would in resetting
 *  all slave logic. */

void I2C_Restart(void){

    I2C_Idle_Check();
    I2C_RESEND;
}


/* Name: I2C_Write
 * Parameter: uint8_t
 * Return: nothing
 * Description: Function writes the data. Load slave address first to SSPxBUF. MMSP will shift
 *  notACK to ACKSTAT CON2 register. Then you can load 8 bits of data. notACK is
 * shifted again. */

void I2C_Write(uint8_t I2C_data){

    I2C_Idle_Check();
    I2C_DATA_BUFFER = I2C_data;
    while(I2C_DATA_BIT == HIGH);
    //Flag_Polling();


    }


/* Name: I2C_NotAck_Read
 * Parameter: uint8_t
 * Return: nothing
 * Description: Function reads the data I2C. Load slave address to SSPxBUF. MMSP will shift
 *  notACK to ACKSTAT CON2 register. Set the RCEN bit of CON2. After 8th edge,
 * SSPxIF and BF are set.  Master sets ACK in ACKDT bit of CON2 and initiates the
 * ACK be setting ACKEN bit. */

void I2C_NotAck_Read(uint8_t *rx_data){


    I2C_RECEIVE;
    while(I2C_DATA_BIT == LOW);
    //Flag_Polling();
    *rx_data = I2C_DATA_BUFFER;
    I2C_Idle_Check();
    I2C_ACK_SEQ;
    I2C_ACK = NOT_ACKNOWLEDGE;
   //Flag_Polling();

}


/* Name: I2C_Ack_Read
 * Parameter: uint8_t
 * Return: nothing
 * Description: Reads the data I2C and acknowledges. Load slave address to SSPxBUF. MMSP will shift
 * ACK to ACKSTAT CON2 register. Set the RCEN bit of CON2. After 8th edge,
 * SSPxIF and BF are set.  Master sets ACK in ACKDT bit of CON2 and initiates the
 * ACK be setting ACKEN bit. */

void I2C_Ack_Read(uint8_t *rx_data, uint8_t count){


    I2C_RECEIVE;
    while(I2C_DATA_BIT == 0);
    //Flag_Polling();
    *rx_data = I2C_DATA_BUFFER;
    I2C_Idle_Check();
    I2C_ACK_SEQ;
    I2C_ACK = ACKNOWLEDGE;
    //Flag_Polling();


}


/***************************************************************************
  =========================== Private Functions ===========================
 ***************************************************************************/



/* Name: I2C_Idle_Check
 * Parameter: void
 * Return: nothing
 * Description: Function checks to see if I2C is idle or transmitting*/

static void I2C_Idle_Check(void){

    while(I2C_IDLE);

}

/* Name: SPxIF_flag_polling
 * Parameter: void
 * Return: nothing
 * Description: Clears the interrupt flag */


static void Flag_Polling(void){

    while(!I2C_IF){

    }
    I2C_CLEAR_IF;
}
