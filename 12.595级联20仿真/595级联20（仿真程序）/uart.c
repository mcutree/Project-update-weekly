#include "uart.h"

void Uart1Init(void)		//115200bps@22.1184MHz
{
	SCON = 0x50;		//8位数据，可变波特率
	AUXR |= 0x40;		//1T模式
	AUXR &= 0xFE;		//选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设定定时器1为16位自动重载
	TL1 = 0xD0;			//设定定时器初值
	TH1 = 0xFF;			//设定定时器初值
	ET1 = 0;				//禁止定时器1中断
	TR1 = 1;				//启动定时器1
	ES = 1; 				//使能串口1中断
}

void Uart2Init(void)		//115200bps@22.1184MHz
{
	S2CON = 0x50;		//8位数据，可变波特率
	AUXR |= 0x04;		//1T模式
	T2L = 0xD0;			//设定定时器初值
	T2H = 0xFF;			//设定定时器初值
	AUXR |= 0x10;		//启动定时器2
	IE2  |= 0x01;   //使能串口2中断
}

/*----------------------------
UART1 发送串口数据
-----------------------------*/
void UART1_SendData(u8 dat)
{
	ES=0;					//关串口中断
	SBUF=dat;			
	while(TI!=1);	//等待发送成功
	TI=0;					//清除发送中断标志
	ES=1;					//开串口中断
}
/*----------------------------
UART1 发送字符串
-----------------------------*/
void UART1_SendString(char *s)
{
	while(*s)//检测字符串结束符
	{
		UART1_SendData(*s++);//发送当前字符
	}
}

/*----------------------------
UART2 发送串口数据
-----------------------------*/
void UART2_SendData(u8 dat)
{
	IE2 &= ~0x01;					//关串口中断
	S2BUF=dat;			
	while((S2CON&S2TI)!=S2TI);	//等待发送成功
	S2CON &= ~S2TI;					//清除发送中断标志
	IE2 = 0x01;					//开串口中断
}
/*----------------------------
UART2 发送字符串
-----------------------------*/
void UART2_SendString(char *s)
{
	while(*s)//检测字符串结束符
	{
		UART2_SendData(*s++);//发送当前字符
	}
}

