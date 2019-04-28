#include <absacc.h>
#include <intrins.h>
#include <reg51.h>

//#include "1302.h"
// LCD128*64 数据线
#define LCD12864DataPort P1
#define uchar unsigned char
#define uint unsigned char
// LCD128*64 I/O 信号管脚
sbit di = P2^0; // 数据\指令 选择
sbit rw = P2^2; // 读\写 选择
sbit en = P2^1; // 读\写使能
sbit cs1= P2^3; // 片选1,低有效(前64列)
sbit cs2= P2^4; // 片选2,低有效(后64列)

void nop(void)
{
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
}

//状态检查
void CheckState(void)
{
	uchar dat;
	dat = 0x00;
	di=0;
	rw=1;
/*	do
	{
		P1=0xff;
		en=1;
		dat=P1; 
		en=0;
		dat&=0x80; //仅当第7位为0时才可操作
	}while(dat);*/
}

//写显示数据
//dat:显示数据
void WriteByte(uchar dat)
{
	CheckState();
	di=1; 
	rw=0;
	LCD12864DataPort=dat;
	en=1; 
	en=0;
}
/*-----------------------------------------------------------------------------------------------------*/
//向LCD发送命令
//command :命令
SendCommandToLCD(uchar command)
{
	CheckState();
	rw=0;
	di=0;
	LCD12864DataPort=command;
	en=1;
	en=0;
}
/*----------------------------------------------------------------------------------------------------*/
//设定行地址(页)--X 0-7
void SetLine(uchar line)
{
	line &= 0x07; // 0<=line<=7
	line |= 0xb8; //1011 1xxx
	SendCommandToLCD(line);
}
//设定列地址--Y 0-63
void SetColumn(uchar column)
{
	column &= 0x3f; // 0=<column<=63
	column |= 0x40; //01xx xxxx
	SendCommandToLCD(column);
}
//设定显示开始行--XX
void SetStartLine(uchar startline) //0--63
{
	//startline &= 0x07;
	startline |= 0xc0; //1100 0000
	SendCommandToLCD(startline);
}
//开关显示
void SetOnOff(uchar onoff)
{
	onoff|=0x3e; //0011 111x
	SendCommandToLCD(onoff);
}
/*---------------------------------------------------------------------------------------------------*/
//选择屏幕
//screen: 0-全屏,1-左屏,2-右屏
void SelectScreen(uchar screen)
{ //北京显示器:负有效 cs1: 0--右; cs2: 0--左
	switch(screen)
	{ 
		case 0: 
			cs1=0;//全屏
			nop();
			cs2=0; 
			nop();
			break; 
		case 1: 
			cs1=1;//左屏
			nop();
			cs2=0;
			nop();
			break;
		case 2: 
			cs1=0;//右屏
			nop();
			cs2=1;
			nop();
			break;
		default:
			break;
	}
}
/*---------------------------------------------------------------------------------------------------*/
//清屏
//screen: 0-全屏,1-左屏,2-右
void ClearScreen(uchar screen)
{ 
	uchar i,j;
	SelectScreen(screen);
	for(i=0;i<8;i++)
	{ 
		SetLine(i);
		for(j=0;j<64;j++)
		{
			WriteByte(0x00);
		}
	}
}
/*--------------------------------------------------------------------------------------------------*/
//显示8*8点阵
//lin:行(0-7), column: 列(0-127)
//address : 字模区首地址
void Show8x8(uchar lin,uchar column,uchar *address)
{ 
	uchar i;
//	if(column>128) {return;}
	if(column<64)
	{
		SelectScreen(1); //如果列数<64则从第一屏上开始写
		SetLine(lin);
		SetColumn(column);
		for(i=0;i<8;i++)
		{
			if(column+i<64)
			{
				WriteByte(*(address+i));
			}
			else
			{
				SelectScreen(2);
				SetLine(lin);
				SetColumn(column-64+i);
				WriteByte(*(address+i));
			}
		}
	}
	else 
	{
		SelectScreen(2); //否则从第二屏上开始写
		column-=64; //防止越界
		SetLine(lin);
		SetColumn(column);
		for(i=0;i<8;i++)
		{
			if(column+i<64)
			{
				WriteByte(*(address+i));
			}
			else
			{
				SelectScreen(1);
				SetLine(lin);
				SetColumn(column-64+i);
				WriteByte(*(address+i));
			}
		}
	}
}

//显示数字8*16
void ShowNumber(uchar lin,uchar column,uchar num)
{
	uchar *address;
	address=&Numcode[num][0];
	Show8x8(lin,column,address);
   	Show8x8(lin+1,column,address+8);
}
//显示汉字16*16
void ShowChina(uchar lin,uchar column,uchar num)
{
	uchar *address;
//	if(lin>7 || column>127){return;}	
	address = &HZcode[num][0];
	Show8x8(lin,column,address);
   	Show8x8(lin,column+8,address+8);
   	Show8x8(lin+1,column,address+16);
   	Show8x8(lin+1,column+8,address+24);
}

void InitLCD(void) //初始化LCD
{ 
	uchar i=2000; //延时
	while(i--);
 	SetOnOff(1); //开显示
	ClearScreen(1);//清屏
	ClearScreen(2);
  	SetStartLine(0); //开始行:0
}
