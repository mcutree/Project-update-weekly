#include <reg51.h>	//51寄存器文件
#include <intrins.h>
	
typedef unsigned char BYTE;	//用BYTE代替unsigned char 
typedef bit BOOL;  // 用BOOL代替bit 

sbit LCD_RS = P2^6;  //寄存器选择（RS＝0，命令寄存器；RS＝1，数据寄存器）            
sbit LCD_RW = P2^5;	 //读写端（RW＝1，读；RW＝0，写）
sbit LCD_EP = P2^7;	 //使能端
sbit ST=P3^0;   //A/D启动转换信号
sbit OE=P3^1;   //数据输出允许信号
sbit EOC=P3^2;  //A/D转换结束信号
sbit CLK=P3^3;  //时钟脉冲  
sbit LED=P3^4;
sbit MOTOR=P3^5;
int z,x,c,v,AD0809, date;	//定义数据类型

/****************延时函数************************/	
	void delay(int ms)
	{                    //延时子程序
	int i;
	while(ms--)
	{
	  for(i = 0; i< 250; i++)
	  {
	   _nop_();	  //空执行
	   _nop_();
	   _nop_();
	   _nop_();
	  }
	}
	}

/****************查忙函数************************/		
	BOOL lcd_bz()
	{                         
	BOOL result;
	LCD_RS = 0;
	LCD_RW = 1;
	LCD_EP = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	result = (BOOL)(P0 & 0x80);	 //检测P0最高位是否为1
	LCD_EP = 0;
	return result;//返回查忙结果
	}

/****************写命令函数************************/	
	void lcd_wcmd(BYTE cmd)
	{                          // 写入指令数据到LCD
	while(lcd_bz());
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_EP = 0;
	_nop_();
	_nop_(); 
	P0 = cmd; //将8位指令通过P0口传给1602
	_nop_();
	_nop_(); //用于产生一个脉冲宽度
	_nop_();
	_nop_();
	LCD_EP = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	LCD_EP = 0;  
	}
	
	void lcd_pos(BYTE pos)
	{                          //设定显示位置
	lcd_wcmd(pos | 0x80);
	}

/****************写数据函数************************/	
	void lcd_wdat(BYTE dat) 
	{                   //写入字符显示数据到LCD
	while(lcd_bz());
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_EP = 0;
	P0 = dat;  //将8位数据通过P0口传给1602
	_nop_();
	_nop_();   //用于产生一个脉冲宽度
	_nop_();
	_nop_();
	LCD_EP = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	LCD_EP = 0; 
	}
	
	void lcd_init()
	{                   //LCD初始化设定
	lcd_wcmd(0x38);     //16*2显示，5*7点阵，8位数据
	delay(1);
	lcd_wcmd(0x0c);     //显示开，关光标
	delay(1);
	lcd_wcmd(0x06);     //移动光标
	delay(1);
	lcd_wcmd(0x01);     //清除LCD的显示内容
	delay(1);
	}

	void Print(unsigned char RH)
	{
	     lcd_pos(0);
		lcd_wdat('R');delay(1);
		lcd_wdat('H');delay(1);
		lcd_wdat(':');delay(1);
		lcd_wdat('0'+RH/10);delay(1);
		lcd_wdat('0'+RH%10);delay(1);
		lcd_wdat('%');delay(1);

		
	}
/****************主函数************************/	
	main()
	{
	    BYTE i;
		lcd_init();// 初始化LCD
		TMOD=0X01;			  //定时器中断0
		CLK=0;				  //脉冲信号初始值为0
		TH0=(65536-2)/256;	  //定时时间高八位初值
		TL0=(65536-2)%256;	  //定时时间低八位初值
		EA=1;				  //开CPU中断
		ET0=1;				  //开T/C0中断
		TR0=1;
	    
	    delay(10);
	
	    while(1)
		{
	ST=0;				//使采集信号为低
	ST=1;				//开始数据转换
	ST=0;				//停止数据转换
	while(!EOC);		//等待数据转换完毕
	OE=1;				//允许数据输出信号
	AD0809=P1;		    //读取数据
	OE=0;				//关闭数据输出允许信号
	if(AD0809>=251)		//电压显示不能超过5V
	AD0809=249;
	date=AD0809/2.5;		//数码管显示的数据值，其中20为采集数据的毫安值
	if(date<40)
	{LED=1;MOTOR=0;}
	else 
	{LED=0;MOTOR=1;}
	Print(date);			//数码管显示函数
	delay(30);
		}			
	}
	 
void timer0( ) interrupt 1 //定时器0工作方式1
{

TH0=(65536-2)/256;	  //重装计数初值
TL0=(65536-2)%256;	  //重装计数初值
CLK=!CLK;			  //取反
}	 
