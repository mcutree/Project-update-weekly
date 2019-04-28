/**************************************************************************
  
                   		THE MAX7221 LED DRIVER LIB
  
             		COPYRIGHT (c)   2005 BY JJJ.
                       		--  ALL RIGHTS RESERVED  --
  
   File Name:       Max7221.h
   Author:          Jiang Jian Jun
   Created:         2005/9/19
   Modified:		NO
   Revision: 		1.0
  
***************************************************************************/
#ifndef _MAX7221_LED_DRIVER_2005_9_19_
#define _MAX7221_LED_DRIVER_2005_9_19_

#include <intrins.h>

sbit Max7221CS  = P3^1;
sbit Max7221DIN = P3^0;
sbit Max7221CLK = P3^2;

void WriteMax7221(unsigned char Address,unsigned char Data)
{
	unsigned char i;
	Max7221CS = 0;
	for (i=0;i<8;i++)
	{
		Max7221CLK = 0;
		Max7221DIN = (Address&(0x80>>i)) ? 1:0;
		_nop_();
		_nop_();
		Max7221CLK = 1;
		_nop_();
		_nop_();
	}
	for (i=0;i<8;i++)
	{
		Max7221CLK = 0;
		Max7221DIN = (Data&(0x80>>i)) ? 1:0;
		_nop_();
		_nop_();
		Max7221CLK = 1;
		_nop_();
		_nop_();
	}
	Max7221CS = 1;	
}

void InitialMax7221(void)
{
	WriteMax7221(0x0A,0x07);	//亮度地址0AH,0x00~0x0F,0x0F最亮
	WriteMax7221(0x0B,0x07);	//扫描LED个数地址0BH,0x00~0x07,最多扫描8个数码管
	WriteMax7221(0x0C,0x01);	//工作模式地址0x0C. 0x00:ShutDown;0x01:Normal
	WriteMax7221(0x09,0xFF);	//编码模式地址0x09. 0x00~0xFF:哪一位为1，哪一位就支持编码
}

void Max7221Display(unsigned char *buffer)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		WriteMax7221(i+1,*(buffer+i));
	}
}

#endif