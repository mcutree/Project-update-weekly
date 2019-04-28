//程序是在AtmanAvr上调试通过的
/*
#ifndef _J_H_
#define _J_H_
#ifndef __AVR_ATmega8__
#define __AVR_ATmega8__
#endif
#define __MCU_CLOCK_FREQUENCY__ _8.0000_MHz
#include <io.h>
#include <wdt.h>
#include <sleep.h>
#include <Interrupt.h>
#include <sig-avr.h>
#include <inttypes.h>
#define uchar unsigned char
#define uint  unsigned int
#endif
*/  
#include "circlecode.h"
#include "degreepoint.h" 
#include "HZcode.h"
#define cs 5
#define si 6
#define scl 7
#define CorD 4
void lcm_out(char a);
void wr_com(uchar a);
void wr_date(uchar a);
void InitLCD(void);
//PORTD.2-->片选
//PORTD.3-->数据
//PORTD.4-->时钟


void nop(void)
{
	//_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	uchar i;
	for (i=0;i<20;i++) 
	{
	#asm("NOP") ;
	}
}
void delay(uchar i)
{
	uchar j;
	for (j=0;j<i;j++)
	nop();
}
void writelcd0(uchar i)
{
	uchar j;
	for (j=0;j<i;j++)
		wr_date(0);
}
/*
int main(void)
{
    io_init();
    lcm_init();
    //第一行80，第二行90，第三行88，第四行98
    //第一行显示
    wr_com(0x80);
    wr_date('o');
    wr_date('k');
    while(1)
    {
    
    }
}
*/
/*****************************************
液晶发送子程序（串行）
输入数据：要发送的8位数据
输出：无
作者：文志刚
修改时间：2004-08-11
*****************************************/
void lcm_out(char a)	//scl上升沿数据有效
{
    char i,d;
    for(i=0;i<8;i++)
    {
        PORTD&=~Bit(scl);
        d=a&0x80;
        if(d)
            PORTD|=Bit(si);
        else
            PORTD&=~Bit(si);
        a<<=1;
        PORTD|=Bit(scl);
    }
}
/*****************************************
液晶写控制字程序
输入数据：要写入的8位数据
输出：无
作者：文志刚
修改时间：2004-08-11
*****************************************/
void wr_com(uchar a)
{
   /* 
    uchar s;
    s=a&0xf0;
    
    lcm_out(0xf8);
    lcm_out(s);
    s=a&0x0f;
    s<<=4;
    */
    lcm_out(a);
     PORTD&=~Bit(CorD);
}
/*****************************************
液晶写数据字程序
输入数据：要写入的8位数据
输出：无
作者：文志刚
修改时间：2004-08-11
*****************************************/
void wr_date(uchar a)
{
    /*
    uchar s;
    s=a&0xf0;
    
   
    lcm_out(0xfa);
    lcm_out(s);
    s=a&0x0f;
    s<<=4;
    */
    lcm_out(a);
    PORTD|=Bit(CorD);
}                                            
void writehz(uchar i)
{
	uchar col;
		if (i==0)
	{
	wr_com(0x40);	//开始行  
	wr_com(0x11);	//开始列
	wr_com(0xB6);	//开始page  
//	writelcd0(16);  
    	for (col=0;col<16;col++) 
       		wr_date(HZcode[0][col]); 
       		wr_com(0x40);	//开始行  
	wr_com(0x11);	//开始列
	wr_com(0xB7);	//开始page  
	for (col=16;col<32;col++) 
       		wr_date(HZcode[0][col]); 
       }
}    
void paintLdegree(uchar i)
{
      	uchar j,col;
      	for (j=0;j<4;j++)
      	{
      	wr_com(0x40);	//开始行  
	wr_com(0x11);	//开始列
	wr_com(0xB1+j);	//开始page  
	for (col=0;col<33;col++) 
 		wr_date(DegreeCode[i][col+j*33]); 
 	}
		
}
void paintRdegree(uchar i)
{
	uchar j,col;
      	for (j=0;j<4;j++)
      	{
      	wr_com(0x40);	//开始行  
	wr_com(0x14);	//开始列
	wr_com(0xB1+j);	//开始page 
        writelcd0(24);	 
	for (col=16;col<33;col++) 
 		wr_date(DegreeCode[i][col+j*33]); 
 	}
}
/*****************************************
液晶初始化程序
输入数据：无
输出：无
作者：文志刚
修改时间：2004-08-11
*****************************************/   
void InitLCD(void)
{
    uchar col,line,page;
    PORTD&=~Bit(cs);;//片选
    wr_com(0xE2);	//复位
    wr_com(0xA3);	//设置偏压比
    wr_com(0x23);	//设置rb/ra比
    wr_com(0x2F);	//选择内部电源操作模式
    wr_com(0x81);	//设置可编程电压调整模式
    wr_com(0x27);	//设置电压编程寄存器
    wr_com(0xA1);	//adc选择(a0:normal a1:左-右翻转）
    wr_com(0xA6);	//显示模式(0xa6正显 0xa7反显）
    wr_com(0xA4);	//设置全显（0xa4正常显 0xa5全显黑
    wr_com(0xC0);	//输出方向选择（0xc0 normal 0xc8上下翻转）
    wr_com(0xAF);	//显示开关0xaf:开0xae 关
   
    for (page=0;page<6;page++)
    { 
    wr_com(0x40);	//开始行  
    wr_com(0x10);	//开始列
    wr_com(0xB0+page);	//开始page
    writelcd0(8); 
    for (col=0;col<48;col++)  
	wr_date(CirCode[page][col]); 
    writelcd0(32);
    for (col=24;col<48;col++)  
	wr_date(CirCode[page][col]);
    writelcd0(24);
    }  
    /* 
    for (page=6;page<8;page++)
    {
    	wr_com(0x40);	//开始行  
    	wr_com(0x10);	//开始列
    	wr_com(0xB0+page);	//开始page
    	writelcd0(132);
    } 
    writehz(0);
    */
   // /* 
    for (page=6;page<8;page++)
    {
    uchar tmp;
    tmp=(page-6)*16;
    wr_com(0x40);	//开始行  
    wr_com(0x10);	//开始列
    wr_com(0xB0+page);	//开始page
    writelcd0(16);  
    for (col=0;col<16;col++) 
       wr_date(HZcode[0][col+tmp]);
    for (col=0;col<16;col++) 
       wr_date(HZcode[1][col+tmp]); 
    writelcd0(36); 
    for (col=0;col<16;col++) 
       wr_date(HZcode[2][col+tmp]);
    writelcd0(32); 
    } 
    paintLdegree(1);
    paintRdegree(2);
}   
