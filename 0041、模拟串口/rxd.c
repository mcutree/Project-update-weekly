#include <reg51.h>

//初始化串行口
void csh()
	{
		SM0=0;
		SM1=1;
		REN=1;
		TI=0;
		RI=0;
		PCON=0;
		TH1=0xFD;
		TL1=0XFD;
		TMOD=0X20;
		EA=1;
		ET1=0;
		ES=1;
		TR1=1;
	}

void main()
	{
		csh();
		while(1)
		{;}
}

void intrr() interrupt 4
	{
		char temp;
		temp=SBUF;
		P1=temp;
        RI=0;
	}