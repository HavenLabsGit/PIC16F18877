/***************************************************************************
 ================================ Includes =================================
 ***************************************************************************/


#include <stdint.h>
#include <stdbool.h>
#include "../libs/i2c_drivers.h"
#include "SSD1306_drivers.h"



/* Name: SSD1306_Command()
 * Parameter: uint8_t
 * Return: Nothing
 * Description: Takes one uint8_t into function. Sets the Co and D/C# for write command mode to SSD1306.
 *              Then start I2C, writes addres to device, issues command mode then send the data
 *              which is the parameter. After stops I2C communication.
 */

void SSD1306_Command(uint8_t data){

    uint8_t control = 0x00; // Co = 0 D/C# = 0 sending command

    I2C_Start();    // Start bit
    I2C_Write(I2C_ADDRESS); // Write address
    I2C_Write(control); // Write command mode
    I2C_Write(data); // Command
    I2C_Stop();     // Stop Bit

}


/* Name: SSD1306_Data())
 * Parameter: uint8_t
 * Return: Nothing
 * Description: Takes one uint8_t into function. Sets the Co and D/C# for write data mode to SSD1306.
 *              Then start I2C, writes addres to device, issues command mode then send the data
 *              which is the parameter. After stops I2C communication.
 */

void SSD1306_Data(uint8_t data){

    uint8_t control = 0x40; // Co = 0 D/C# = 1 sending data

    I2C_Start();    // Start bit
    I2C_Write(I2C_ADDRESS); // Write address
    I2C_Write(control); // Write command mode
    I2C_Write(data); // Command
    I2C_Stop();     // Stop Bit

}
/* Name: SSD1306_Init()
 * Parameter: void
 * Return: nothing
 * Description: This is the initalization sequence for the SSD1306. Will exectue all the following
 *              to get OLED into a ready state.
 */

void SSD1306_Init(void){
    SSD1306_Command(DISPLAYOFF);     // 0xAE
    SSD1306_Command(SETMULTIPLEX);  // 0xA8
    SSD1306_Command(0x1F);     // Sets MUX to 31 for 128x32 OLED. This means PAGE0 to PAGE3
                           // PAGE0 (COM0-COM7)
                           // PAGE1 (COM8-COM15)
                           // PAGE2 (COM16-COM23)
                           // PAGE3 (COM24-COM31)
    SSD1306_Command(SETDISPLAYOFFSET);     // 0xD3 Sets display RAM start line 0 - 63 with 0b00000
                                       // Example to move COM 16 to COM 0, 0b10000 || 0x10
    SSD1306_Command(0x00); //Offset is COM0
    SSD1306_Command(MEMORYMODE); // Set addressing mode 00b Horizontal ~ 01b Vertical ~ 10 Page adressing
    SSD1306_Command(0x02);              // Set for page addressing
                                    // steps: Set the page start address with command 0xB0 to 0xB7
                                    // Set the lower start column address of pointer with command 0x00 to 0x0F LOWER NIBBLE
                                    // Set the upper start column address of pointer by command 0x10 to 0x1F UPPER NIBBLE
    SSD1306_Command(SETSTARTLINE);     //Sets display RAM start line register from 0-63
                                   // opcode is 0x40 to 0x7F which looks like 0b01XXXXX test
    SSD1306_Command(SEGREMAP);     // 0xA0 Wll map SEG0 (RESET) to either column address 0 (0xA0) or column address 127 (0xA1)
    SSD1306_Command(COMSCANCOM0);  // 0xC0 normal mode scan from COM0 to COM[N-1]
    SSD1306_Command(SETCOMPINS);  // 0xDA referenced page 44 in datasheet. opcode is 0b00XX0010. A[4]=0b sequential com pin configuration ~ A[4]=1b alernative come pin
                              // A[5]=0b Disable COM left/right remap ~ A[5]=1b Enable COM left/right remap
    SSD1306_Command(0x22);        // A[4]=0 A[5]=1
    SSD1306_Command(SETCONTRAST); // 0x81 double byte command, select 1 out of 256. 0x7F resets
    SSD1306_Command(0x7F);        // reset contrast
    SSD1306_Command(DISPLAYALLON); // 0xA5 Entire display ON output ignores the RAM content
    SSD1306_Command(NORMALDISPLAY); // 0xA6 for normal or 0xA7 for reverse. In normal, RAM data of 1 indicates an "ON" pixel while reverse a 0 indicates an "OFF" pixel
    SSD1306_Command(SETDISPLAYCLOCKDIV); // 0xD5 Display Clock Divide Ratio A[3:0] divide ration is 1 to 16.
                                     // Oscillator frequency A[7:4] defualt value is 1000b.
    SSD1306_Command(0x80);        // dafualt value ~380kHz
    SSD1306_Command(CHARGEPUMP); // 0x8D A[2]=0b disbale charge pump A[2]=1b enable charge pump opcode 010X00b
    SSD1306_Command(0x14);        //enable charge pump
    SSD1306_Command(INVERTDISPLAY);
    SSD1306_Command(DISPLAYON);   //Display ON normal mode


}

/* Name: ClearDisplay()
 * Parameter: void
 * Return: nothing
 * Description: Function will clear display by looping through iterations. I may need to come back and use function GotTOXY for page addressing
 *              I will know if function only erases PAGE0.
 */

void ClearDisplay(){

    SSD1306_Command(COLUMNADDR); // set start column
    SSD1306_Command(0);          // set SEG0
    SSD1306_Command(PAGEADDR);   // Set start row and end row 3bits A[2:0] range 0-7d B[2:0] 0-7d
    SSD1306_Command(0);          // PAGE0
    SSD1306_Command(3);          // End at PAGE3 for 32 row OLED

    I2C_Start();          // Start bit
    I2C_Write(I2C_ADDRESS);   // write address of device
    I2C_Write(SETSTARTLINE);  // 0x40 Set display RAM start line register. Opcode 01xxxxxx range 0x40 ~ 7F.

    for(uint16_t i = 0; i < LCDHEIGHT * (LCDWIDTH / 8); i++) // assign i as unisgned 16 and if it is less then (128 * (32/8)) = 512; Divide 32
                                                             // by 8 since when you write to a column on a PAGE it writes a byte. So PAGE 0 Column 0
                                                             // will write 0x00 to SEG0
        I2C_Write(0x00); // write 0 to clear display
    I2C_Stop(); // Sopt bit

}

/* Name: GotoXY()
 * Parameter: uint8_t, uint8_t
 * Return: nothing
 * Description: Function goes to X coordinate and Y coordinate using PAGE Memory Mode. Takes intergers which is broken out into two nibbles.
 *              The upper nibble needs 0x10 added per datasheet.
 */


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

  SSD1306_Command(0xB0 + row); // Start PAGE Address
  SSD1306_Command(0x00 + lower_nibble); //Start lower nibble address
  SSD1306_Command(0x00 + upper_final); //Start upper nibble address


}

void Draw_pixel(void){

  SSD1306_Command(COLUMNADDR); // Set start and stop column address two bytes
  SSD1306_Command(*x_pos);      // Send the start which is x_pos from GOtoXY
  SSD1306_Command(*x_pos + 5); // Send the stop which is x_pos + 5. One character takes 5 columns

  SSD1306_Command(PAGEADDR);
  SSD1306_Command(*y_pos);
  SSD1306_Command(*y_pos);

  SSD1306_Data(0x74); // Write character to screen
  }

