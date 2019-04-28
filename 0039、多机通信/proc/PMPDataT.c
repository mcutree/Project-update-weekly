/*****************************************/
/* Copyright (c) 2005, 通信工程学院      */
/* All rights reserved.                  */
/* 作    者：戴 佳						 */
/*****************************************/

#include "PMPDataT.h"

/* 延时t毫秒 */
void delay(uint t)
{
	uint i;
	while(t--)
	{
		/* 对于11.0592M时钟，约延时1ms */
		for (i=0;i<125;i++)
		{}
	}
} 
uchar keyscan(void)
{
	uchar scancode,tmpcode;
	P1 = 0xf0;			 					// 发全0行扫描码
	if ((P1&0xf0)!=0xf0)					// 若有键按下
	{
		delay(10);							// 延时去抖动
		if ((P1&0xf0)!=0xf0)				// 延时后再判断一次，去除抖动影响
		{
			scancode = 0xfe;
			while((scancode&0x10)!=0)		// 逐行扫描
			{
				P1 = scancode;				// 输出行扫描码
				if ((P1&0xf0)!=0xf0)		// 本行有键按下
				{
					tmpcode = (P1&0xf0)|0x0f;

					/* 返回特征字节码，为1的位即对应于行和列 */
					return((~scancode)+(~tmpcode));
				}
				else scancode = (scancode<<1)|0x01;		// 行扫描码左移一位
			}
		}
	}
	return(0);								// 无键按下，返回值为0 	
}

/* 发送数据函数 */
void senddata(uchar buf)
{

	/* 发送数据 */
		TI = 0;
		TB8 = 0;				// 发送数据帧
		SBUF =buf;	
		while(!TI);
		TI = 0;
}

/* 串口初始化函数 */
void init_serial()
{
	TMOD = 0x20;				// 定时器T1使用工作方式2
	TH1 = 250;
	TL1 = 250;
	TR1 = 1;					// 开始计时
	PCON = 0x80;				// SMOD = 1
	SCON = 0xd0;				// 工作方式，9位数据位，波特率9600kbit/s，允许接收 
}
void Getkey()
{
    switch(get_key)
   		{
      		case 0x11:						// 1行1列，数字0
			      key=0xc0;
				  break;
			case 0x21:						// 1行2列，数字1
                 key=0xf9;
				break;			
			case 0x41:						// 1行3列，数字2
				key=0xa4;
				break;
     		case 0x81:						// 1行4列，数字3
				key=0xb0;
				break;
			case 0x12:						// 2行1列，数字4
                key=0x99;
				break;
			case 0x22:						// 2行2列，数字5
				  key=0x92;
				break;
			case 0x42:						// 2行3列，数字6
				   key=0x82;
				break;
			case 0x82:						// 2行4列，数字7
				   key=0xf8;
				break;
			case 0x14:						// 3行1列，数字8
				   key=0x80;
				   break;
			case 0x24:						// 3行2列，数字9
				 key=0x90;
				break;
			case 0x44:						// 3行3列，10
				  key=0x88;
				break;
			case 0x84:						// 3行4列，11
				 key=0x83;
				break;
			case 0x18:						// 4行1列，12
				 key=0xc6;
				break;
			case 0x28:						// 4行2列，13
				 key=0xa1;
				break;
			case 0x48:						// 4行3列，14
				 key=0x86;
				break;
			case 0x88:						// 3行4列，15
				 key=0x8e;
				break;
			default:break;
		}


}
/* 主程序 */
void main()
{ 
	uchar i = 0;
	key=0xc0; 
	while(1)
    {
	 	 get_key = keyscan();				// 调用键盘扫描函数 
	     Getkey();
		 buf=key;

    	/* 通过P0口读要访问的从机地址 */
	  P0 = 0xff;
	  addr = P0&0x0f;
	  init_serial();				// 串口初始化 

	  EA = 1;						// 关闭所有中断
	
	     	TI = 0;
		    TB8 = 1;				// 发送地址帧	
		    SBUF = addr;
		    while(!TI);
		    TI = 0;
		 senddata(buf);			// 发送数据
	 
	} 
	
}