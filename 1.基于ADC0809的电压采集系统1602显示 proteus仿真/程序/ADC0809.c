/***************************************
<基于ADC0809的电压采集系统>
采集最大误差0.01v；
采用单通道查询方式采集电压；

Lucky - D
售后QQ:810488037

2018/10/31
****************************************/

#include <reg52.h>
#include <intrins.h>

#define  DBPort P0    //LCD数据端口

sbit LcdRs = P2^5;//lcd控制端口；
sbit LcdRw = P2^6;
sbit LcdEn = P2^7;
sbit Lcdbf = P0^7; //LCD忙标志 Busy Flag


sbit CLK=P1^0;		//时钟信号
sbit ST=P1^3;		//启动信号
sbit EOC=P1^2;		//转换结束信号
sbit OE=P1^1;		//输出使能

unsigned char Voltage;
//-----------------------------------------------------
//-------------Lcd1602驱动程序-------------------------
//-----------------------------------------------------
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
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------

void display_vol(unsigned int dat, x, y)//电压显示；
{
		unsigned char i;
		unsigned char display[5] = {0};//0.0196	
		dat = 19.6 * dat; //将才回来的数字量转换为电压值扩大一千倍；
		display[0] 	= dat / 1000+'0';
		display[1]	= 0x2e;	//小数点的ascii码；
		display[2]	= dat % 1000 / 100+'0';
		display[3]	= dat % 1000 % 100 / 10+'0';
		display[4]  = dat %10+'0';
		GotoXY(x, y);
		for(i=0; i<5; i++)
		{
			LCD_Write(1, display[i]);
	    }
		LCD_Write(1, 'V');//显示单位；
}
//-------------------------------------------------------------------------------------------------


//主程序
void main()
{
	TMOD=0x02;		//T1工作模式2
	TH0=0x14;		
	TL0=0x00;
	IE=0x82;
	TR0=1;
	LCD_Initial();//LCD1602初始化；
	P1 = 0X0F;	  //选中通道0；
	while(1)
	{
		Print("Volt:", 3, 0);
		ST=0;ST=1;ST=0;		//启动A/D转换
		while(EOC==0);		//等待转换完成
		OE=1;
		Voltage = P3;
		display_vol(Voltage, 8, 0);//显示电压；
		OE=0;
		Print("#Detecting...#", 1, 1);//显示系统状态；
	}
}
//T0定时器中断给ADC0809提供时钟信号
void Timer0_INT() interrupt 1
{
	CLK=~CLK;
}
//分辨率0.0196；