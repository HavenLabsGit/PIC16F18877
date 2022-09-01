#include "thermo.h"
#include "i2c_drivers.h"
#include <stdint.h>
#include <stdio.h>

/***************************************************************************
 ============================= Device Information ==========================
 ***************************************************************************/
/* 12 bit ADC
 * temperature resolution 0.625 C
 * Update rate 80mS
 * conversion time of one-shot 27mS
 * 
 */


/***************************************************************************
 ============================== Communications =============================
 ***************************************************************************/
/*
** To read from device there are 4 operations. Write address, write pointer, read address
** and finally read.

SCL  1                                               9
_    __    __    __    __    __    __    __    __    __
 |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
 |__|  |__|  |__|  |__|  |__|  |__|  |__|  |__|  |__|  |

SDA Write Address MSB <- FRAME 1
    ___               ___                       _
   / 1 \    0    0   / 1 \   A2    A1    A0   R/W    ACK /
__/     \___________/     \_____________________________/


SCL  1                                               9
_    __    __    __    __    __    __    __    __    __
 |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
 |__|  |__|  |__|  |__|  |__|  |__|  |__|  |__|  |__|  |

SDA Write Pointer MSB <- ACK by DEVICE FRAME 2

                                  ____  ____  ____
\    0     0     0     0     0   / P2 \/ P1 \/ P0 \  ACK / STOP by Master
 \______________________________/_____/\____/\_____\____/

SCL  1                                               9
_    __    __    __    __    __    __    __    __    __
 |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
 |__|  |__|  |__|  |__|  |__|  |__|  |__|  |__|  |__|  |

SDA Read Address MSB <- ACK by DEVICE FRAME 3
    ___               ___                      ___
   / 1 \    0    0   / 1 \   A2    A1    A0   /R/W\  ACK  /
__/     \___________/     \__________________/     \_____/

SCL  1                                               9
_    __    __    __    __    __    __    __    __    __
 |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
 |__|  |__|  |__|  |__|  |__|  |__|  |__|  |__|  |__|  |

SDA  MSB <- ACK by MASTER  FRAME 4
_    __    __    __    __    __    __    __    __
 |  |D7|  |D6|  |D5|  |D4|  |D3|  |D2|  |D1|  |D0|  ACK /
 |__|  |__|  |__|  |__|  |__|  |__|  |__|  |__|  |_____/

SCL  1                                               9
_    __    __    __    __    __    __    __    __    __
 |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
 |__|  |__|  |__|  |__|  |__|  |__|  |__|  |__|  |__|  |

SDA  MSB <- ACK by MASTER  FRAME 5
_    __    __    __    __    __    __    __    __
 |  |D7|  |D6|  |D5|  |D4|  |D3|  |D2|  |D1|  |D0|  ACK / STOP by Master
 |__|  |__|  |__|  |__|  |__|  |__|  |__|  |__|  |_____/

*/


/***************** Global Variables ****************/
float celsius;
uint8_t data1, data2;
uint16_t digital_temp;

/*int main (){

uint8_t coninue = 0x01;
uint8_t tm = 0x00;
uint8_t pol = 0x04;
uint8_t fq = 0x00;
uint8_t os = 0x20;

uint16_t value = (OS + FQ6);
printf( "%X", value );
uint16_t value2 = value <<8;
printf( "\n%X\n", value2 );

} */

float Read_temp(){

    SSP1_I2C_Start();
    SSP1_I2C_Write(WRITE_ADDR);
    SSP1_I2C_Write(TEMP_READ);
    SSP1_I2C_Stop();
    SSP1_I2C_Start();
    SSP1_I2C_Write(READ_ADDR);
    SSP1_I2C_Ack_Read(&data1, 1);
    SSP1_I2C_Ack_Read(&data2, 1);
    SSP1_I2C_Stop();

    digital_temp = ((data1 << 4) | (data2 >> 4));
    celsius = digital_temp;
    celsius = (celsius * CONV_CONST);
    float faren = ((celsius * F_MULTIPLY) + F_ADD);
    return faren;

}
float Read_high(){

   SSP1_I2C_Start();
   SSP1_I2C_Write(WRITE_ADDR);
   SSP1_I2C_Write(TEMP_HIGH);
   SSP1_I2C_Stop();
   SSP1_I2C_Start();
   SSP1_I2C_Write(READ_ADDR);
   SSP1_I2C_Ack_Read(&data1, 1);
   SSP1_I2C_Ack_Read(&data2, 1);
   SSP1_I2C_Stop();
   digital_temp = ((data1 << 4) | (data2 >> 4));
   celsius = digital_temp;
   celsius = (celsius * CONV_CONST);
   float faren = ((celsius * F_MULTIPLY) + F_ADD);
   return faren;

}
float Read_low(){

    SSP1_I2C_Start();
    SSP1_I2C_Write(WRITE_ADDR);
    SSP1_I2C_Write(TEMP_LOW);
    SSP1_I2C_Stop();
    SSP1_I2C_Start();
    SSP1_I2C_Write(READ_ADDR);
    SSP1_I2C_Ack_Read(&data1, 1);
    SSP1_I2C_Ack_Read(&data2, 1);
    SSP1_I2C_Stop();
    digital_temp = ((data1 << 4) | (data2 >> 4));
    celsius = digital_temp;
    celsius = (celsius * CONV_CONST);
    float faren = ((celsius * F_MULTIPLY) + F_ADD);
    return faren;

}

void High_limit(uint16_t limit){

   uint8_t hbyte = limit >> 8;
   uint8_t lbyte = (uint8_t)limit;
   SSP1_I2C_Start();
   SSP1_I2C_Write(WRITE_ADDR);
   SSP1_I2C_Write(TEMP_HIGH);
   SSP1_I2C_Write(hbyte);
   SSP1_I2C_Write(lbyte);
   SSP1_I2C_Stop();

}

void Low_limit(uint16_t limit){

   uint8_t hbyte = limit >> 8;
   uint8_t lbyte = (uint8_t)limit;
   SSP1_I2C_Start();
   SSP1_I2C_Write(WRITE_ADDR);
   SSP1_I2C_Write(TEMP_LOW);
   SSP1_I2C_Write(hbyte);
   SSP1_I2C_Write(lbyte);
   SSP1_I2C_Stop();

}

void Config_temp(uint8_t one_shot, uint8_t Fault_count, uint8_t Pol,
                 uint8_t Alert_control, uint8_t Shutdown){

    uint8_t config = (one_shot + Fault_count + Pol + Alert_control + Shutdown);
    SSP1_I2C_Start();
    SSP1_I2C_Write(WRITE_ADDR);
    SSP1_I2C_Write(TEMP_CONFIG);
    SSP1_I2C_Write(config);
    SSP1_I2C_Write(0x00);
    SSP1_I2C_Stop();



}
