
/*
 * This is a UART Library.
 */

/*
 * WARNING!!!
 * If you're using the "lcd.h" and "lcd.c" downloaded in the same repository, check your pin configuration.
 */

//	       UART:P4.4   <--->  UCA1TXD
//	            P4.5   <--->  UCA1RXD

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//You cannot use any other function if UART is not initialized.
//Once it's initialized, you don't need initialize it again.
//If you don't need to send or receive data, you can modify the pin configuration yourself.
void UART1_Init();

//Used to send a variable string, I think it's very useful for most people.
//Sample:UART1_printf("%d test %s",1,"111");
//Result:1 test 111
void UART1_printf(const char *fmt,...);

//UART1_printf's auxiliary function.
//It can be used to send a constant string, and in this case it will be faster than UART1_printf.
//Sample:Uart1_SendString("111");
void UART1_SendString(char *ptr);

//UART1_SendString's auxiliary function.
//It can be used to send a constant char, and in this case it will be faster than UART1_SendString.
//Sample:UART1_SendByte('\n')
void UART1_SendByte(short sData);

//Used to receive string, end with carriage-return character(This can be modified by yourself).
//Sample:char char *str[18];
//       UART1_GetString(str);
void UART1_GetString(char *string);

//UART1_GetString's auxiliary function.
//It can be used to receive a char, and in this case it will be faster than UART1_GetString.
//Sample:c=UART1_getchar();
char UART1_getchar();

//Used to receive integer in string format,the number can be negative, decimal, hexadecimal.
//It's just a reference, most of the time it will not be used.
short UART1_GetIntNum();

//Delay function
void Delay(short sTime);
