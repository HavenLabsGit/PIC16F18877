/******************************************************************************

                                                                              
 The driver is for I2C mode only
                                                                                                                                                            
 Co - Continuation bit ~ set to zero transmission contains only data bytes ~
 D/C# - Data/Command Selection bit ~ Set to 0 defines data as command, set to 1
                                     defines following data byte as data ~
 ACK - Acknowledgment
 SA0 - Slave address bit
 R/W# - Read/Write Selection bit ~ 0 is write, 1 is read ~
 S - Start Condition 
 P - Stop Condition
  
   0 1 2 3 4 5 6   7       0  1   2 3 4 5 6 7
 S|1|1|1|1|0|0| |R/W#|ACK|Co|D/C#| | | | | | |ACK| | | | | | | | |ACK|P|
 slave address                    control byte    MSB ~ data byte ~ LSB
                                                         n >= 0 bytes
 |1|1|1|1|0|0|SA0|R/W#| ~ SSD1306 Slave Address
 SA0 - Provides 
 |Co|D/C|0|0|0|0|0|0|ACK| ~ Control byte 
  
*******************************************************************************/


// ============================ GDDRAM Structure =========================== //
/*            No row re-mapping and column re-mapping
 *
 *     PAGE0 (COM0-COM7)   |________PAGE 0_________|
 *     PAGE0 (COM8-COM15)  |________PAGE 1_________|
 *     PAGE0 (COM16-COM23) |________PAGE 2_________|
 *     PAGE0 (COM24-COM31) |________PAGE 3_________|
 *
 *     S S S S
 *     E E E E
 *     G G G G
 *     0 1.. 127
 *     _ _ _ _
 *    |_|_|_|_| LSB D[0]
 *    |_|_|_|_|
 *    |_|_|_|_|             <----- One Page
 *    |_|_|_|_|
 *    |_|_|_|_|
 *    |_|_|_|_|
 *    |_|_|_|_|
 *    |_|_|_|_| MSB D[7]
 *     */
#ifndef SSD1306_DRIVERS_H
#define SSD1306_DRIVERS_H


/***************************************************************************
 ================================ Includes =================================
 ***************************************************************************/
#include <stdint.h>
#include <stdbool.h>

/***************************************************************************
 =========================== Function Prototypes ===========================
***************************************************************************/

void SSD1306_Command(const uint8_t *array, uint8_t size_array);
void SSD1306_Data();
void SSD1306_Init(void);
void ClearDisplay(void);
uint8_t GotoXY(uint8_t row, uint8_t column);
void Draw_pixel(void);
void init_test(void);
void draw_test(void);
void horizontal_fill_screen(uint8_t value);
void Horz_Goto_XY(uint8_t start_column, uint8_t end_column, uint8_t start_row, uint8_t end_row );

/***************************************************************************
 ================================= Macros ==================================
 ***************************************************************************/
#define I2C_ADDRESS   0x78 // 0b111100 is 0x3C address followed by two 0 for SAO
                           // and write
#define COMMAND 0x00
#define DATA 0x40

/* Parameters of screen */
#define SSD1306_129_32
#define LCDWIDTH             128
#define LCDHEIGHT            32

/***************************************************************************
 =========================== Fundamental Commads ===========================
***************************************************************************/
#define SETCONTRAST          0x81
#define DISPLAYALLON_RESUME  0xA4
#define DISPLAYALLON         0xA5
#define NORMALDISPLAY        0xA6
#define INVERTDISPLAY        0xA7
#define DISPLAYOFF           0xAE
#define DISPLAYON            0xAF

/***************************************************************************
 =========================== Scrolling Commands ============================
***************************************************************************/
#define ACTIVATE_SCROLL                      0x2F
#define DEACTIVATE_SCROLL                    0x2E
#define SET_VERTICAL_SCROLL_AREA             0xA3
#define RIGHT_HORIZONTAL_SCROLL              0x26
#define LEFT_HORIZONTAL_SCROLL               0x27
#define VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  0x2A

/***************************************************************************
 ========================= Address Setting Commads =========================
***************************************************************************/
#define MEMORYMODE           0x20
#define COLUMNADDR           0x21
#define PAGEADDR             0x22
#define SETLOWCOLUMN         0x00
#define SETHIGHCOLUMN        0x10

/***************************************************************************
 ========================== Harware Configuration ==========================
***************************************************************************/
#define SETCOMPINS           0xDA
#define SETDISPLAYOFFSET     0xD3      // 0xD3 Sets display RAM start line 0 - 63 with 0b00000
                                       // Example to move COM 16 to COM 0, 0b10000 || 0x10

#define SETSTARTLINE         0x40     //Sets display RAM start line register from 0-63
                                   // opcode is 0x40 to 0x7F which looks like 0b01XXXXX test
#define COMSCANCOM0          0xC0   //Scan from COM0 to COM[N-1] where N is multuplixed ratio
#define COMSCANCOM_N         0xC8 // Scan from COM[N-1] to COM0 where N is multuplixed ratio
#define SEGREMAP             0xA1 // column address 127 is mapped to SEG0
#define SEGREMAP_RESET       0xA0 // column address 0 is mapped to SEG0
#define SETMULTIPLEX         0xA8 // set MUX ratio N+1, N=A[5:0] 16MUX to 64MUX

/***************************************************************************
 =========================== Timing & Driving ============================
***************************************************************************/
#define SETVCOMDESELECT      0xDB    // VCOMH deselect level 0x00~0.65xVCC, 0x10~0.77xVCC, 0x30~0.83xVCC
#define SETDISPLAYCLOCKDIV   0xD5     // 0xD5 Display Clock Divide Ratio A[3:0] divide ration is 1 to 16.
                                     // Oscillator frequency A[7:4] defualt value is 1000b.
#define SETPRECHARGE         0xD9  // Phase 1 A[3:0] up to 15DCLK / Phase 2 A[7:4] up to 15DCLK
#define CHARGEPUMP           0x8D  // 0x8D A[2]=0b disbale charge pump A[2]=1b enable charge pump opcode 010X00b
#define CHARGEPUMP_EN        0x14 // Enable charge pump
#define EXTERNALVCC          0x01
#define SWITCHCAPVCC         0x02

/* Global Variables */
uint8_t _vccstate, *x_pos, *y_pos;

const uint8_t horz_init[]={

   COMMAND,
      DISPLAYOFF,
      SETDISPLAYCLOCKDIV,
      0x90,             // 400kHz FOSC, divide by 1
      SETMULTIPLEX,
      0x1F,     // Sets MUX to 31 for 128x32 OLED. This means PAGE0 to PAGE3
                           // PAGE0 (COM0-COM7)
                           // PAGE1 (COM8-COM15)
                           // PAGE2 (COM16-COM23)
                           // PAGE3 (COM24-COM31)
      SETDISPLAYOFFSET,
      0x00, //offset is COM0
      SETSTARTLINE,
      CHARGEPUMP,
      CHARGEPUMP_EN,
      SEGREMAP_RESET,
      SETCOMPINS,
      COMSCANCOM0,
      SETCONTRAST,
      0x7F, // Reset contrast
      SETPRECHARGE,
      0xF1, // TODO need more info
      DISPLAYALLON_RESUME,
      NORMALDISPLAY,
      MEMORYMODE,
      0x00, // Horizontal mode
      DISPLAYON,

};

/* Array that has instructions to set area to entire screen, only vertical or horizontal addressing */

const uint8_t entire_screen[]={

COLUMNADDR,
0x00,
0x7F,
PAGEADDR,
0x00,
0x03,


};


bool wrap = true;

// ============================== Fonts ============================== //
/* Example font:
 *     0x3E, 0x41, 0x41, 0x51, 0x73
 *     00111110 01000001 01000001 01010001 01110011
 *
 *     _ _ _ _ _
 *    |_|#|#|#|#| LSB D[0]
 *    |#|_|_|_|#|
 *    |#|_|_|_|_|
 *    |#|_|_|_|_|
 *    |#|_|_|#|#|
 *    |#|_|_|_|#|
 *    |_|#|#|#|#|
 *    |_|_|_|_|_| MSB D[7]
*/

const char Font[] = {
0x00, 0x00, 0x00, 0x00, 0x00, // sp 32d
0x00, 0x00, 0x2f, 0x00, 0x00, // ! 33d
0x00, 0x07, 0x00, 0x07, 0x00, // " 34d
0x14, 0x7f, 0x14, 0x7f, 0x14, // # 35d
0x24, 0x2a, 0x7f, 0x2a, 0x12, // $ 36d
0x23, 0x13, 0x08, 0x64, 0x62, // % 37d
0x36, 0x49, 0x55, 0x22, 0x50, // & 38d
0x00, 0x05, 0x03, 0x00, 0x00, // ' 39d
0x00, 0x1c, 0x22, 0x41, 0x00, // ( 40d
0x00, 0x41, 0x22, 0x1c, 0x00, // ) 41d
0x14, 0x08, 0x3E, 0x08, 0x14, // * 42d
0x08, 0x08, 0x3E, 0x08, 0x08, // + 43d
0x00, 0x00, 0xA0, 0x60, 0x00, // , 44d
0x08, 0x08, 0x08, 0x08, 0x08, // - 45d
0x00, 0x60, 0x60, 0x00, 0x00, // . 46d
0x20, 0x10, 0x08, 0x04, 0x02, // / 47d
0x3E, 0x51, 0x49, 0x45, 0x3E, // 0 48d
0x00, 0x42, 0x7F, 0x40, 0x00, // 1 49d
0x42, 0x61, 0x51, 0x49, 0x46, // 2 50d
0x21, 0x41, 0x45, 0x4B, 0x31, // 3 51d
0x18, 0x14, 0x12, 0x7F, 0x10, // 4 52d
0x27, 0x45, 0x45, 0x45, 0x39, // 5 53d
0x3C, 0x4A, 0x49, 0x49, 0x30, // 6 54d
0x01, 0x71, 0x09, 0x05, 0x03, // 7 55d
0x36, 0x49, 0x49, 0x49, 0x36, // 8 56d
0x06, 0x49, 0x49, 0x29, 0x1E, // 9 57d
0x00, 0x36, 0x36, 0x00, 0x00, // : 58d
0x00, 0x56, 0x36, 0x00, 0x00, // ; 59d
0x08, 0x14, 0x22, 0x41, 0x00, // < 60d
0x14, 0x14, 0x14, 0x14, 0x14, // = 61d
0x00, 0x41, 0x22, 0x14, 0x08, // > 62d
0x02, 0x01, 0x51, 0x09, 0x06, // ? 63d
0x32, 0x49, 0x59, 0x51, 0x3E, // @ 64d
0x7C, 0x12, 0x11, 0x12, 0x7C, // A 65d
0x7F, 0x49, 0x49, 0x49, 0x36, // B 66d
0x3E, 0x41, 0x41, 0x41, 0x22, // C 67d
0x7F, 0x41, 0x41, 0x22, 0x1C, // D 68d
0x7F, 0x49, 0x49, 0x49, 0x41, // E 69d
0x7F, 0x09, 0x09, 0x09, 0x01, // F 70d
0x3E, 0x41, 0x49, 0x49, 0x7A, // G 71d
0x7F, 0x08, 0x08, 0x08, 0x7F, // H 72d
0x00, 0x41, 0x7F, 0x41, 0x00, // I 73d
0x20, 0x40, 0x41, 0x3F, 0x01, // J 74d
0x7F, 0x08, 0x14, 0x22, 0x41, // K 75d
0x7F, 0x40, 0x40, 0x40, 0x40, // L 76d
0x7F, 0x02, 0x0C, 0x02, 0x7F, // M 77d
0x7F, 0x04, 0x08, 0x10, 0x7F, // N 78d
0x3E, 0x41, 0x41, 0x41, 0x3E, // O 79d
0x7F, 0x09, 0x09, 0x09, 0x06, // P 80d
0x3E, 0x41, 0x51, 0x21, 0x5E, // Q 81d
0x7F, 0x09, 0x19, 0x29, 0x46, // R 82d
0x46, 0x49, 0x49, 0x49, 0x31, // S 83d
0x01, 0x01, 0x7F, 0x01, 0x01, // T 84d
0x3F, 0x40, 0x40, 0x40, 0x3F, // U 85d
0x1F, 0x20, 0x40, 0x20, 0x1F, // V 86d
0x3F, 0x40, 0x38, 0x40, 0x3F, // W 87d
0x63, 0x14, 0x08, 0x14, 0x63, // X 88d
0x07, 0x08, 0x70, 0x08, 0x07, // Y 89d
0x61, 0x51, 0x49, 0x45, 0x43, // Z 90d
0x00, 0x7F, 0x41, 0x41, 0x00, // [ 91d
0x55, 0x2A, 0x55, 0x2A, 0x55, // 55
0x00, 0x41, 0x41, 0x7F, 0x00, // ] 93d
0x04, 0x02, 0x01, 0x02, 0x04, // ^ 94d
0x40, 0x40, 0x40, 0x40, 0x40, // _ 95d
0x00, 0x01, 0x02, 0x04, 0x00, // ' 96d
0x20, 0x54, 0x54, 0x54, 0x78, // a 97d
0x7F, 0x48, 0x44, 0x44, 0x38, // b 98d
0x38, 0x44, 0x44, 0x44, 0x20, // c 99d
0x38, 0x44, 0x44, 0x48, 0x7F, // d 100d
0x38, 0x54, 0x54, 0x54, 0x18, // e 101d
0x08, 0x7E, 0x09, 0x01, 0x02, // f 102d
0x18, 0xA4, 0xA4, 0xA4, 0x7C, // g 103d
0x7F, 0x08, 0x04, 0x04, 0x78, // h 104d
0x00, 0x44, 0x7D, 0x40, 0x00, // i 105d
0x40, 0x80, 0x84, 0x7D, 0x00, // j 106d
0x7F, 0x10, 0x28, 0x44, 0x00, // k 107d
0x00, 0x41, 0x7F, 0x40, 0x00, // l 108d
0x7C, 0x04, 0x18, 0x04, 0x78, // m 109d
0x7C, 0x08, 0x04, 0x04, 0x78, // n 110d
0x38, 0x44, 0x44, 0x44, 0x38, // o 111d
0xFC, 0x24, 0x24, 0x24, 0x18, // p 112d
0x18, 0x24, 0x24, 0x18, 0xFC, // q 113d
0x7C, 0x08, 0x04, 0x04, 0x08, // r 114d
0x48, 0x54, 0x54, 0x54, 0x20, // s 115d
0x04, 0x3F, 0x44, 0x40, 0x20, // t 116d
0x3C, 0x40, 0x40, 0x20, 0x7C, // u 117d
0x1C, 0x20, 0x40, 0x20, 0x1C, // v 118d
0x3C, 0x40, 0x30, 0x40, 0x3C, // w 119d
0x44, 0x28, 0x10, 0x28, 0x44, // x 120d
0x1C, 0xA0, 0xA0, 0xA0, 0x7C, // y 121d
0x44, 0x64, 0x54, 0x4C, 0x44, // z 122d
0x00, 0x08, 0x77, 0x00, 0x00, // { 123d
0x00, 0x7F, 0x00, 0x00, 0x00, // | 124d
0x00, 0x77, 0x08, 0x00, 0x00, // } 125d
0x10, 0x08, 0x10, 0x08, 0x00, // ~ 126d
                              };


#endif
