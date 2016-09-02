
#include <msp430f5529.h>
#include "uart.h"

void UART1_Init()
{
  UCA1CTL1 |= UCSSEL1;
  UCA1BR0 = 0x68;
  UCA1MCTL |= UCBRS0;
  P4SEL |= BIT4 + BIT5;
  UCA1CTL1 &= ~UCSWRST;
  UCA1IE |= UCTXIE + UCRXIE;
}


void UART1_printf(const char *fmt,...)
{
  va_list argptr;
  char string[65];
  va_start(argptr,fmt);
  vsprintf(string,fmt,argptr);
  UART1_SendString(string);
  va_end(argptr);
}


void UART1_SendString(char *ptr)
{
  while(*ptr)
  {
    UART1_SendByte(*ptr++);
  }
  return;
}


void UART1_SendByte(short sData)
{
    if(sData=='\n')
    {
        while ((UCA1IFG & UCTXIFG) == 0); 
        Delay(10);                 //because the slow response of hyper_terminal 
        UCA1TXBUF ='\r';
    }
    while ((UCA1IFG & UCTXIFG) == 0);
    Delay(10);
    UCA1TXBUF = sData;
    return;
}


void UART1_GetString(char *string)
{
  char *string2 = string;//存储str开始地址
  char c;
  while((c = UART1_getchar())!='\r')//接收到换行前将一直处于接收状态,接收到换行字符(回车)时结束
  {
    if(c=='\b')//退格
    {
      if( (int)string2 < (int)string )//判断str当前地址是大于初始地址，条件成立时接收到的退格字符才判断维有效
      {
        string--;
      }
    }
    else 
    {
      *string++ = c;//接收到的字符不为退格时将C写入字符串，str++
    }
  }
  *string='\0';//添加/0表示字符串结束
}


char UART1_getchar()
{
  while (!(UCA1IFG & UCRXIFG));//等待接收中断标志位置1
  return UCA1RXBUF;
}


short UART1_GetIntNum()
{
  char str[18];
  char *string = str;
  unsigned short base     = 10;//进制标记变量
  unsigned short minus    = 0;//代替符号位的标记变量
  short result   = 0;
  short lastIndex;    
  unsigned short i;
    
  UART1_GetString(string);
  //负数判断
  if(string[0]=='-')//接收的数字是以字符串形式发送
  {
    minus = 1;
    string++;
  }
  //16进制判断
  if(string[0]=='0' && (string[1]=='x' || string[1]=='X'))
  {
    base    = 16;
    string += 2;
  }

  lastIndex = strlen(string) - 1;
  //判断接收到的数据是否为空    
  if(lastIndex<0)
  {
    return -1;
  }
  //16进制判断
  if(string[lastIndex]=='h' || string[lastIndex]=='H' )
  {
    base = 16;
    string[lastIndex] = 0;//0即是'/0',去掉进制标记后将标记为设为数字结尾
    lastIndex--;
  }
  //转换部分
  if(base==10)
  {
    result = atoi(string);
    result = minus ? (-1*result):result;
  }
  else
  {
    for(i=0;i<=lastIndex;i++)
    {
      if(isalpha(string[i]))
      {
        if(isupper(string[i]))
        {
          result = (result<<4) + string[i] - 'A' + 10;
        }
        else
        {
          result = (result<<4) + string[i] - 'a' + 10;
        }
      }
      else
      {
        result = (result<<4) + string[i] - '0';
      }
    }
    result = minus ? (-1*result):result;
  }
  return result;
}


void Delay(short sTime)
{
  for(;sTime>0;sTime--)
  {
  }
  return;
}
