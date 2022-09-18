/***************************************************************************
 ================================ Includes =================================
 ***************************************************************************/


#include <stdint.h>
#include <stdint.h>
#include <stdbool.h>
#include "../libs/i2c_drivers.h"
#include "SSD1306_drivers.h"



/* Name: SSD1306_Command()
 * Parameter: none
 * Return: Nothing
 * Description: Sets the Co and D/C# for write command mode to SSD1306.
 *              Then start I2C, writes addres to device, issues command mode then send the data
 *              which is the parameter. After stops I2C communication.
 */

void SSD1306_Command(const uint8_t *array, uint8_t size_array){

    I2C_Start();    // Start bit
    I2C_Write(I2C_ADDRESS); // Write address
    I2C_Write(COMMAND); // Write command mode

    for(int i = 0; i < size_array; i++){
      I2C_Write(array[i]);

    }
    I2C_Stop();

}


/* Name: SSD1306_Data())
 * Parameter: uint8_t
 * Return: Nothing
 * Description: Takes one uint8_t into function. Sets the Co and D/C# for write data mode to SSD1306.
 *              Then start I2C, writes addres to device, issues command mode then send the data
 *              which is the parameter. After stops I2C communication.
 */

void SSD1306_Data(){

    I2C_Start();    // Start bit
    I2C_Write(I2C_ADDRESS); // Write address
    I2C_Write(DATA); // Write command mode

}
/* Name: SSD1306_Init()
 * Parameter: void
 * Return: nothing
 * Description: This is the initalization sequence for the SSD1306. Will exectue all the following
 *              to get OLED into a ready state.
 */

void SSD1306_Init(void){

  SSD1306_Command(horz_init, sizeof(horz_init));
}


/* Name: horizontal_clear_screen
 * Parameter: uint8_t
 * Return: nothing
 * Description: Function to clear entire screen. Issues the commands followed by a for loop to
 *              clear each pixel.
 */

void horizontal_fill_screen(uint8_t value){

  SSD1306_Command(entire_screen, sizeof(entire_screen));

  SSD1306_Data();

  for( uint8_t i = 0, j = 0; j < 5; j++ ){
    for(; i < 127; i++){
        I2C_Write(value);
    }
    i = 0;
  }

 I2C_Stop();

}

/* Name: GotoXY()
 * Parameter: uint8_t, uint8_t
 * Return: nothing
 * Description: Function goes to X coordinate and Y coordinate using PAGE Memory Mode. Takes intergers which is broken out into two nibbles.
 *              The upper nibble needs 0x10 added per datasheet.
 */


void Horz_Goto_XY(uint8_t start_column, uint8_t end_column, uint8_t start_row, uint8_t end_row) {

  uint8_t goto_xy[6] = {

  COLUMNADDR,
  0x00,
  0x00,
  PAGEADDR,
  0x00,
  0x03,
};

  goto_xy[1] = start_column;
  goto_xy[2] = end_column;
  goto_xy[4] = start_row;
  goto_xy[5] = end_row;

  SSD1306_Command(goto_xy, 6);

}


void draw_test(){
/*  I2C_Write(I2C_ADDRESS);
  I2C_Write(0x00);
  I2C_Write(COLUMNADDR);
  I2C_Write(0x0A);
  I2C_Write(0x7F);
  I2C_Write(PAGEADDR);
  I2C_Write(0x02);
  I2C_Write(0x01);
  I2C_Stop();
*/
  I2C_Start();
  I2C_Write(I2C_ADDRESS);
  I2C_Write(0x40);

  I2C_Write(0x7F);
  I2C_Write(0x08);
  I2C_Write(0x08);
  I2C_Write(0x08);
  I2C_Write(0x7F);
  
  I2C_Write(0x00);
  I2C_Write(0x00);
  I2C_Write(0x00);
  I2C_Write(0x00);
  I2C_Write(0x00);
  
  I2C_Write(0x7F);
  I2C_Write(0x49);
  I2C_Write(0x49);
  I2C_Write(0x49);
  I2C_Write(0x41);

  I2C_Write(0x00);
  I2C_Write(0x00);
  I2C_Write(0x00);
  I2C_Write(0x00);
  I2C_Write(0x00);
  
  I2C_Write(0x7F);
  I2C_Write(0x40);
  I2C_Write(0x40);
  I2C_Write(0x40);
  I2C_Write(0x40);

  I2C_Write(0x00);
  I2C_Write(0x00);
  I2C_Write(0x00);
  I2C_Write(0x00);
  I2C_Write(0x00);

  I2C_Write(0x7F);
  I2C_Write(0x40);
  I2C_Write(0x40);
  I2C_Write(0x40);
  I2C_Write(0x40);

  I2C_Write(0x00);
  I2C_Write(0x00);
  I2C_Write(0x00);
  I2C_Write(0x00);
  I2C_Write(0x00);
    
  I2C_Write(0x3E);
  I2C_Write(0x41);
  I2C_Write(0x41);
  I2C_Write(0x41);
  I2C_Write(0x3E);

  

 

  I2C_Stop();

}

uint8_t GotoXY(uint8_t row, uint8_t column){


// ============================ Page Addressing =========================== //
// Example from data sheet: Want to write PAGE2 Column 3
// Write 0xB2 (PAGE2)
// Write lower start aka lower nibble 0x03
// Write upper start aka upper nibble 0x10
// In binary it looks like this 1 0000 0011
// Basically for the upper start, the upper nibble is ignored
// My own example Column 96
// Lower nibble = 0x06
// Upper nibble = 0x19
// Binary looks like 1 1001 0110
// ====================================================================== //
//
  uint8_t byte;
  uint8_t lower_nibble =(column & 0x0F);  // Takes column AND with 0x0F to only get lower nibble
  uint8_t upper_nibble = (column & 0xF0); // Takes colum AND with 0xF0 to only get upper nibble
  uint8_t upper_final = ((upper_nibble >>= 4) + 0x10); // Bitshift right 4 to only have upper nibble then add 0x10
  byte = upper_nibble + lower_nibble;
  x_pos = &byte;
  y_pos = &row;

  I2C_Write(0xB0 + row); // Start PAGE Address
  I2C_Write(0x00 + lower_nibble); //Start lower nibble address
  I2C_Write(0x00 + upper_final); //Start upper nibble address
  I2C_Stop();

}
