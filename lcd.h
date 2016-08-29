/*
 *READ THIS TO DECIDE IF THIS FILE IS HELPFUL TO YOU
 *The LCD model is JLX12864G-00091. I used the LCD module in AY-MSE KIT. If your
 *module is different from mine, you should modify the pin configuration first.
 *Of course it's better to check the pin configuration first under any
 *circumstances. Even though your LCD model is different from mine, this file
 *can also be a reference as long as your LCD's protocol is SPI.
 */

/*
 *READ THIS TO DECIDE WHAT SHOULD YOU MODIFY
 *The pin configuration has been mentioned above. There is only Number's font 
 *and int display function in this file, it can be your reference if it's not
 *enough to you. Write your own font lattice library and display function to
 *meet your own requirements. The delay function's parameter is decided on
 *the condition that the frequence of MCLK is 8MHz and, caculate your own parameter
 *or increase the parameter when the LCD cannot run fine.
 */

//	       LCD:P6.0   <--->  SCK
//	           P6.3   <--->  SDA
//	           P3.3   <--->  CS
//	           P1.2   <--->  CD
//	           P6.6   <--->  RES

#include <stdint.h>

#define LCD_SCK_H P6OUT |= BIT0
#define LCD_SCK_L P6OUT &= ~BIT0
#define LCD_SDA_H P6OUT |= BIT3
#define LCD_SDA_L P6OUT &= ~BIT3
#define LCD_CS_H P3OUT |= BIT3
#define LCD_CS_L P3OUT &= ~BIT3
#define LCD_CD_H P1OUT |= BIT2
#define LCD_CD_L P1OUT &= ~BIT2
#define LCD_RES_H P6OUT |= BIT6
#define LCD_RES_L P6OUT &= ~BIT6

//You cannot use any other function if the LCD module is not initialized.
//Once it's initialized, you don't need initialize it again.
void LCD_Init();

//Display a int on LCD,start displaying on x page(You can understand it as row,
//one row is usually consist of two pages, have a try and you will understand
//it) y column. Because max unsigned int on most platform is 65535, I used a
//while statement to make sure the number displayed on LCD occupies 5 column,
//you can modify it in "lcd.c" file by your own requirement.
void LCD_Disp_uint(uint8_t x,uint8_t y,unsigned int num);


//MOST OF THE TIME, YOU DON'T NEED THE FUNCTIONS BELOW, BUT DON'T DELETE THEM.

//Clear the screen.
void LCD_Clear();

//Locate where to display.
void LCD_Address(uint8_t page,uint8_t column);

//Send data to LCD as a command.
void LCD_Command(uint8_t data);

//Send data to LCD as a data to display.
void LCD_Data(uint8_t data);

//Send data to LCD, the voltage on pin CD will decide it's a command or a data.
void LCD_Byte(uint8_t data);

//Delay about i*400 MCLK cycle.
void LCD_Delay(uint8_t i);
