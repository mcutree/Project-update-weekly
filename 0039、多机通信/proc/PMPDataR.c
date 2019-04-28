
#include "PMPDataR.h"

unsigned char zu[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8d};
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

/* 发送数据函数 */
uchar recvdata()
{

	/* 接收数据 */
		while(!RI);
		if (RB8==1)
			return 0xee;		// 若接收的为地址帧，则返回0xee
		buf = SBUF;	
		RI = 0;	
	return 0;					// 返回0
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

/* 主程序 */
void main()
{ 
	uchar i = 0;
	uchar tmp = 0xff;
	P1= 0xff;
	addr = P1&0x0f;				// 获取本机地址
	P23 = 1;					// 发光管不亮
	
	init_serial();				// 串口初始化 

	EA = 1;						// 关闭所有中断
	
	/* 进入设备应答 */
	while(1)
	{
		SM2 = 1;				// 只接收地址帧
		
		/* 如果接收到的地址帧不是本机地址，则继续等待 */
		while (tmp!=addr)
		{
			RI = 0;
			while(!RI)
			tmp = SBUF;
			RI = 0;
		}	
		SM2 = 0;				// 允许接收数据

		/* 数据接收 */
       tmp = recvdata();
	   //if(buf!=0x00)
	    
		if (tmp==0x00)	
		{		 
	   	     P0=buf;
			/* 绿灯亮，持续500ms，表示接收数据成功 */
			P23 = 0;			
			delay(30);
			P23 = 1;
			
		}	    
		// 如果接收数据时发现地址帧，则重新开始整个接收过程
	}
}