#include "lcd1602.h"

void delay(unsigned int t)	 //延时
{    
	while(t--);
}

void  LCD_Wait(void)	//读忙状态
{								   
	LcdRs=0;
	LcdRw=1;
	LcdEn=1;delay(10);LcdEn=0;	//下降沿	
	while(Lcdbf)
	{
	  LcdEn=0;LcdEn=1;	 //仿真才需要此语句,实际硬件中不需要
	}			
} 

void LCD_Write(bit style, unsigned char input)	 //写数据1/命令0
{
	LcdRs=style;
	LcdRw=0;		
	DBPort=input;	
	LcdEn=1;delay(10);LcdEn=0;			
	LCD_Wait();	
}

void GotoXY(unsigned char x, unsigned char y)  //移动光标到指定位置
{
	if(y==0)	LCD_Write(0,0x80|x);
	if(y==1)    LCD_Write(0,0xc0|x);
}

void LCD_Initial(void)			  //初始化LCD
{
	LCD_Write(0,0x38);  		 //8位数据端口,2行显示,5*7点阵
	delay(300);
	delay(300);
	LCD_Write(0,0x0c);           //显示模式
	LCD_Write(0,0x01);           //清屏
	LCD_Write(0,0x06);           //输入模式
}



void Print(unsigned char *str, unsigned char x, unsigned char y)	 //指定坐标输出字符串
{
	unsigned char i=0, temp=0;
	while(*str)  
	{
		if(i==0 && temp==0)
		{
			GotoXY(x+i, y);
			temp = 1;
		}
		if(temp == 1)
		{
			GotoXY(x+i, y);
			LCD_Write(1,*str++);
			i++;
		}
	}
}

void display_int(unsigned int dat, unsigned char x, unsigned char y, unsigned char num_size)
{
		unsigned char i;
		unsigned char display[5] = {0};
		display[0] 	= dat / 10000;
		display[1]	= dat % 10000 / 1000;
		display[2]	= dat % 10000 % 1000 / 100;
		display[3]	= dat % 10000 % 1000 % 100 / 10;
		display[4]	= dat % 10000 % 1000 % 100 % 10;
		GotoXY(x, y);
		for(i=5-num_size; i<5; i++)
		{
			LCD_Write(1, display[i]+'0');
		}
}

