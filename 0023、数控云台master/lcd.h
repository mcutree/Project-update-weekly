/*
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
*/
#include "circlecode.h"
#include "HZcode.h" 
#include "DegreePoint.h"
#define EN 2
#define DI 3
#define RW 4
#define CS1 4
#define CS2 5    
void SinPout(uchar tmp)  
{ 
	/*   
uchar i;
for (i=0;i<8;i++)
{ 
     
      if (tmp&0x80)
      {
       
         
          PORTD|=Bit(IN164);  
         
          }
       else            
       {
          PORTD&=~Bit(IN164);  
         
          } 
      PORTD&=~Bit(CLK164);    
       
       PORTD|=Bit(CLK164);      
       
      tmp=tmp<<1;
} 
*/
if (tmp&0x01)
		PORTC|=Bit(0);
	else
		PORTC&=~Bit(0);	
	if (tmp&0x02)
		PORTC|=Bit(1);
	else
		PORTC&=~Bit(1);
	if (tmp&0x04)
		PORTD|=Bit(2);
	else
		PORTD&=~Bit(2);
	if (tmp&0x08)
		PORTD|=Bit(3);
	else
		PORTD&=~Bit(3);
	if (tmp&0x10)
		PORTD|=Bit(4);
	else
		PORTD&=~Bit(4);	
	if (tmp&0x20)
		PORTD|=Bit(5);
	else
		PORTD&=~Bit(5);
	if (tmp&0x40)
		PORTD|=Bit(6);
	else
		PORTD&=~Bit(6);
	if (tmp&0x80)
		PORTD|=Bit(7);
	else
		PORTD&=~Bit(7);
}
 
void nop(void)
{
	//_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	uchar i;
	for (i=0;i<20;i++) 
	{
	#asm("NOP") ;
	}
}

//状态检查
void CheckState(void)
{
	uchar dat;
	dat = 0x00;
	//di=0;
       //	#asm("CBI PORTB,DI")
       PORTB&=~Bit(DI);
	//rw=1;
       //	#asm("SBI PORTB,RW")
       PORTB|=Bit(RW);
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
	//di=1; 
	//rw=0;
	//#asm("SBI PORTB,DI")
	//#asm("CBI PORTB,RW")
      	PORTB|=Bit(DI);
       	PORTB&=~Bit(RW);
       //	LCD12864DataPort=dat;
       SinPout(dat);
	//en=1; 
	//en=0;
	//#asm("SBI PORTB,EN")
	//#asm("CBI PORTB,EN")
     	PORTB|=Bit(EN);
     	PORTB&=~Bit(EN);
       //	LCD12864DataPort=0;
}
/*-----------------------------------------------------------------------------------------------------*/
//向LCD发送命令
//command :命令
SendCommandToLCD(uchar command)
{
      	CheckState();
	//rw=0;
	//di=0;
	//#asm("CBI PORTB,RW")
	//#asm("CBI PORTB,DI")   
	PORTB&=~Bit(RW);   

	PORTB&=~Bit(DI);
        SinPout(command);
       //	LCD12864DataPort=command;
	//en=1;
	//en=0;
	//#asm("SBI PORTB,EN")
	//#asm("CBI PORTB,EN")
	PORTB|=Bit(EN);

	PORTB&=~Bit(EN);

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
			//cs1=0;//全屏
			//#asm("CBI PORTB,CS1")
			PORTC&=~Bit(CS1);
			nop();
			//cs2=0; 
			//#asm("CBI PORTB,CS2")
			PORTC&=~Bit(CS2);
			nop();
			break; 
		case 1: 
			//cs1=1;//左屏
			//#asm("SBI PORTB,CS1")
			PORTC|=Bit(CS1);
			nop();
			//cs2=0;
			//#asm("CBI PORTB,CS2")
			PORTC&=~Bit(CS2);
			nop();
			break;
		case 2: 
			//cs1=0;//右屏
			//#asm("CBI PORTB,CS1")
			PORTC&=~Bit(CS1);
			nop();
			//cs2=1;
			//#asm("SBI PORTB,CS2")
			PORTC|=Bit(CS2);
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

void Show8x8(uchar lin,uchar column,uchar num,uchar add)
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
				WriteByte(HZcode[num][add+i]);
				
			}
			else
			{
				SelectScreen(2);
				SetLine(lin);
				SetColumn(column-64+i);
				WriteByte(HZcode[num][add+i]);
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
				WriteByte(HZcode[num][add+i]);
			}
			else
			{
				SelectScreen(1);
				SetLine(lin);
				SetColumn(column-64+i);
				WriteByte(HZcode[num][add+i]);
			}
		}
	}
}

void Show_Circle(void)
{
	uchar i;
	uchar lin,column;
	
	column=8;
	for (lin=0;lin<6;lin++)
	{
	       	SelectScreen(1); //如果列数<64则从第一屏上开始写
	      	SetLine(lin);    
	        SetColumn(column);
		for(i=0;i<48;i++)
		{
		       	WriteByte(CirCode[lin][i]);
		      //	nop();
		}
	}
	
}
void Show_HalfCircle(void)
{
	uchar i;
	uchar lin,column;
	
	column=25;
	for (lin=0;lin<6;lin++)
	{
	        SelectScreen(2); //如果列数<64则从第一屏上开始写
	      	SetLine(lin);
	     	SetColumn(column);
		for(i=24;i<48;i++)
		{
			WriteByte(CirCode[lin][i]);
		}
	}
}
void PaintDegree(uchar deg,uchar bScreen)
{
	uchar lin,column,i;
	column=16;
//	bit dgflag[16];
	SetLine(0);
	if (bScreen) {SelectScreen(2);column=10;}
	else
		SelectScreen(1);
	for (lin=0;lin<4;lin++)
	{
		SetLine(lin+1);
		SetColumn(column);
		for(i=0;i<33;i++)
		{
			WriteByte(DegreeCode[deg][lin*33+i]);
		}
			
	}
	
}


//显示汉字16*16
void ShowChinese(uchar lin,uchar column,uchar num)
{
        //uchar *address;
//	if(lin>7 || column>127){return;}	
       	//address = &HZcode[num][0];
       	Show8x8(lin,column,num,0);
       	Show8x8(lin,column+8,num,8);
     	Show8x8(lin+1,column,num,16);
     	Show8x8(lin+1,column+8,num,24); 
     
}

void InitLCD(void) //初始化LCD
{ 
	int i=2000; //延时
	while(i--);
 	SetOnOff(1); //开显示
	//ClearScreen(1);//清屏
	//ClearScreen(2);
	ClearScreen(0);
       //	SetStartLine(0); //开始行:0
}
void Show_Preset(void)
{
	ShowChinese(6,20,0);//预
	ShowChinese(6,34,1);//设
	
}

void Show_Slow(void)
{
ShowChinese(6,86,3);//慢
}
void Show_Quick(void)
{
ShowChinese(6,86,2);//快
}