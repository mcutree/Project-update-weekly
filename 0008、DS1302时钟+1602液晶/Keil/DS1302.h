/**************************************************************************
  
                   		THE REAL TIMER DS1302 DRIVER LIB
  
             		COPYRIGHT (c)   2005 BY JJJ.
                       		--  ALL RIGHTS RESERVED  --
  
   File Name:       DS1302.h
   Author:          Jiang Jian Jun
   Created:         2003/7/21
   Modified:		NO
   Revision: 		1.0
  
***************************************************************************/
#ifndef _REAL_TIMER_DS1302_2003_7_21_
#define _REAL_TIMER_DS1302_2003_7_21_

sbit  DS1302_CLK = P1^6;              //实时时钟时钟线引脚 
sbit  DS1302_IO  = P1^7;              //实时时钟数据线引脚 
sbit  DS1302_RST = P1^5;              //实时时钟复位线引脚
sbit  ACC0 = ACC^0;
sbit  ACC7 = ACC^7;

typedef struct __SYSTEMTIME__
{
	unsigned char Second;
	unsigned char Minute;
	unsigned char Hour;
	unsigned char Week;
	unsigned char Day;
	unsigned char Month;
	unsigned char  Year;
	unsigned char DateString[9];
	unsigned char TimeString[9];
}SYSTEMTIME;	//定义的时间类型

#define AM(X)	X
#define PM(X)	(X+12)            	  // 转成24小时制
#define DS1302_SECOND	0x80
#define DS1302_MINUTE	0x82
#define DS1302_HOUR		0x84 
#define DS1302_WEEK		0x8A
#define DS1302_DAY		0x86
#define DS1302_MONTH	0x88
#define DS1302_YEAR		0x8C
#define DS1302_RAM(X)	(0xC0+(X)*2)   	//用于计算 DS1302_RAM 地址的宏 

void DS1302InputByte(unsigned char d) 	//实时时钟写入一字节(内部函数)
{ 
    unsigned char i;
    ACC = d;
    for(i=8; i>0; i--)
    {
        DS1302_IO = ACC0;           	//相当于汇编中的 RRC
        DS1302_CLK = 1;
        DS1302_CLK = 0;
        ACC = ACC >> 1; 
    } 
}

unsigned char DS1302OutputByte(void) 	//实时时钟读取一字节(内部函数)
{ 
    unsigned char i;
    for(i=8; i>0; i--)
    {
        ACC = ACC >>1;         			//相当于汇编中的 RRC 
        ACC7 = DS1302_IO;
        DS1302_CLK = 1;
        DS1302_CLK = 0;
    } 
    return(ACC); 
}

void Write1302(unsigned char ucAddr, unsigned char ucDa)	//ucAddr: DS1302地址, ucData: 要写的数据
{
    DS1302_RST = 0;
    DS1302_CLK = 0;
    DS1302_RST = 1;
    DS1302InputByte(ucAddr);       	// 地址，命令 
    DS1302InputByte(ucDa);       	// 写1Byte数据
    DS1302_CLK = 1;
    DS1302_RST = 0;
} 

unsigned char Read1302(unsigned char ucAddr)	//读取DS1302某地址的数据
{
    unsigned char ucData;
    DS1302_RST = 0;
    DS1302_CLK = 0;
    DS1302_RST = 1;
    DS1302InputByte(ucAddr|0x01);        // 地址，命令 
    ucData = DS1302OutputByte();         // 读1Byte数据
    DS1302_CLK = 1;
    DS1302_RST = 0;
    return(ucData);
}

void DS1302_SetProtect(bit flag)        //是否写保护
{
	if(flag)
		Write1302(0x8E,0x10);
	else
		Write1302(0x8E,0x00);
}

void DS1302_SetTime(unsigned char Address, unsigned char Value)        // 设置时间函数
{
	DS1302_SetProtect(0);
	Write1302(Address, ((Value/10)<<4 | (Value%10))); 
}

void DS1302_GetTime(SYSTEMTIME *Time)
{
	unsigned char ReadValue;
	ReadValue = Read1302(DS1302_SECOND);
	Time->Second = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);
	ReadValue = Read1302(DS1302_MINUTE);
	Time->Minute = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);
	ReadValue = Read1302(DS1302_HOUR);
	Time->Hour = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);
	ReadValue = Read1302(DS1302_DAY);
	Time->Day = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);	
	ReadValue = Read1302(DS1302_WEEK);
	Time->Week = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);
	ReadValue = Read1302(DS1302_MONTH);
	Time->Month = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);
	ReadValue = Read1302(DS1302_YEAR);
	Time->Year = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);	
}

void DateToStr(SYSTEMTIME *Time)
{
	Time->DateString[0] = Time->Year/10 + '0';
	Time->DateString[1] = Time->Year%10 + '0';
	Time->DateString[2] = '-';
	Time->DateString[3] = Time->Month/10 + '0';
	Time->DateString[4] = Time->Month%10 + '0';
	Time->DateString[5] = '-';
	Time->DateString[6] = Time->Day/10 + '0';
	Time->DateString[7] = Time->Day%10 + '0';
	Time->DateString[8] = '\0';
}

void TimeToStr(SYSTEMTIME *Time)
{
	Time->TimeString[0] = Time->Hour/10 + '0';
	Time->TimeString[1] = Time->Hour%10 + '0';
	Time->TimeString[2] = ':';
	Time->TimeString[3] = Time->Minute/10 + '0';
	Time->TimeString[4] = Time->Minute%10 + '0';
	Time->TimeString[5] = ':';
	Time->TimeString[6] = Time->Second/10 + '0';
	Time->TimeString[7] = Time->Second%10 + '0';
	Time->DateString[8] = '\0';
}

void Initial_DS1302(void)
{
	unsigned char Second=Read1302(DS1302_SECOND);
	if(Second&0x80)		  
		DS1302_SetTime(DS1302_SECOND,0);
}

/********************************************************************************
void BurstWrite1302(unsigned char *pWClock)	//往DS1302写入时钟数据(多字节方式)
{
    unsigned char i;
    Write1302(0x8e,0x00);         	// 控制命令,WP=0,写操作?
    DS1302_RST = 0;
    DS1302_CLK = 0;
    DS1302_RST = 1;
    DS1302InputByte(0xbe);        	// 0xbe:时钟多字节写命令
    for (i = 8; i>0; i--)     		//8Byte = 7Byte 时钟数据 + 1Byte 控制
    {
        DS1302InputByte(*pWClock); 	// 写1Byte数据
        pWClock++;
    }
    DS1302_CLK = 1;
    DS1302_RST = 0;
} 

void BurstRead1302(unsigned char *pRClock)	//读取DS1302时钟数据(时钟多字节方式)
{
    unsigned char i;
    DS1302_RST = 0;
    DS1302_CLK = 0;
    DS1302_RST = 1;
    DS1302InputByte(0xbf);             	// 0xbf:时钟多字节读命令 
    for (i=8; i>0; i--) 
    {
       *pRClock = DS1302OutputByte();   // 读1Byte数据 
       pRClock++;
    }
    DS1302_CLK = 1;
    DS1302_RST = 0;
}

void DS1302_TimeStop(bit flag)           // 是否将时钟停止
{
	unsigned char Data;
	Data=Read1302(DS1302_SECOND);
	DS1302_SetProtect(0);
	if(flag)
		Write1302(DS1302_SECOND, Data|0x80);
	else
		Write1302(DS1302_SECOND, Data&0x7F);
}
********************************************************************************/
#endif