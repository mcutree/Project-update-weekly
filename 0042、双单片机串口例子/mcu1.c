//两个单片机通讯，使用中断法


#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
#define key_port P1
#define dis_port P2

void main (void)
{
	uchar key_in=0xff;
	SCON=0x50; //MODER1,REN=1;
	TMOD=0x20; //TIMER1 MODER2;
	TH1=0xf3;  //bode=2400
	TL1=0xf3;
	ET1=1;
	TR1=1;

	EA=1;
	ES=1;
	while(1)
	{		
		if (key_in != key_port)
			{
				key_in = key_port;
				SBUF=key_in;
			}
	}
}

void get_disp (void) interrupt 4 using 0
{
	if (RI)			//如果是串口输入引起中断
			{
				dis_port = SBUF;
				RI=0;
			}
	 else TI=0;		//否则就是串口输出引起的中断
}
