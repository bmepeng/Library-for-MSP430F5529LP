
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
  char *string2 = string;//�洢str��ʼ��ַ
  char c;
  while((c = UART1_getchar())!='\r')//���յ�����ǰ��һֱ���ڽ���״̬,���յ������ַ�(�س�)ʱ����
  {
    if(c=='\b')//�˸�
    {
      if( (int)string2 < (int)string )//�ж�str��ǰ��ַ�Ǵ��ڳ�ʼ��ַ����������ʱ���յ����˸��ַ����ж�ά��Ч
      {
        string--;
      }
    }
    else 
    {
      *string++ = c;//���յ����ַ���Ϊ�˸�ʱ��Cд���ַ�����str++
    }
  }
  *string='\0';//���/0��ʾ�ַ�������
}


char UART1_getchar()
{
  while (!(UCA1IFG & UCRXIFG));//�ȴ������жϱ�־λ��1
  return UCA1RXBUF;
}


short UART1_GetIntNum()
{
  char str[18];
  char *string = str;
  unsigned short base     = 10;//���Ʊ�Ǳ���
  unsigned short minus    = 0;//�������λ�ı�Ǳ���
  short result   = 0;
  short lastIndex;    
  unsigned short i;
    
  UART1_GetString(string);
  //�����ж�
  if(string[0]=='-')//���յ����������ַ�����ʽ����
  {
    minus = 1;
    string++;
  }
  //16�����ж�
  if(string[0]=='0' && (string[1]=='x' || string[1]=='X'))
  {
    base    = 16;
    string += 2;
  }

  lastIndex = strlen(string) - 1;
  //�жϽ��յ��������Ƿ�Ϊ��    
  if(lastIndex<0)
  {
    return -1;
  }
  //16�����ж�
  if(string[lastIndex]=='h' || string[lastIndex]=='H' )
  {
    base = 16;
    string[lastIndex] = 0;//0����'/0',ȥ�����Ʊ�Ǻ󽫱��Ϊ��Ϊ���ֽ�β
    lastIndex--;
  }
  //ת������
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
