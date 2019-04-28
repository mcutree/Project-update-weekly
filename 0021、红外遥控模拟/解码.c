#include "At89x51.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define JINGZHEN 48
#define TIME0TH ((65536-100*JINGZHEN/12)&0xff00)>>8   //time0,100us,红外遥控
#define TIME0TL ((65536-100*JINGZHEN/12)&0xff)
#define TIME1TH ((65536-5000*JINGZHEN/12)&0xff00)>>8   
#define TIME1TL ((65536-5000*JINGZHEN/12)&0xff)
#define uchar unsigned char
#define uint  unsigned int

code uchar  BitMsk[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,};

uint IrCount=0,Show=0,Cont=0;
uchar IRDATBUF[32],s[20];
uchar IrDat[5]={0,0,0,0,0};
uchar IrStart=0,IrDatCount=0;
extern void initLCM( void);               											//LCD初始化子程序
extern void DisplayListChar(uchar X,uchar Y, unsigned char *DData);                    //显示指定坐标的一串字符子函数

void timer1int (void)  interrupt 3  using 3{	 //定时器1
EA=0;
TH1 = TIME1TH;  
TL1 = TIME1TL;
Cont++;
if(Cont>10)Show=1;
EA=1;
}
void timer0int (void)  interrupt 1  using 1{	 //定时器0
	uchar i,a,b,c,d;
	EA=0;
	TH0 = TIME0TH;  
	TL0 = TIME0TL;
	if(IrCount>500)IrCount=0;
	if(IrCount>300&&IrStart>0){IrStart=0;IrDatCount=0;IrDat[0]=IrDat[1]=IrDat[2]=IrDat[3]=0;IrCount=0;}
	if(IrStart==2)
	{
		IrStart=3;
		for(i=0;i<IrDatCount;i++)
		{
			if(i<32)
			{
				a=i/8;

				b=IRDATBUF[i];
				c=IrDat[a];
				d=BitMsk[i%8];
				if(b>5&&b<14)c|=d;
				if(b>16&&b<25)c&=~d;
				IrDat[a]=c;
			}
		}
		if(IrDat[2]!=~IrDat[3])
		{
		 IrStart=0;IrDatCount=0;IrDat[0]=IrDat[1]=IrDat[2]=IrDat[3]=0;IrCount=0;
		 
		}
		EA=1;
		return;
	}
	IrCount++; 
	EA=1;
}
void int0() interrupt 0  using 0  {
	EA=0;
	if(IrStart==0)
	{
	  IrStart=1;IrCount=0;TH0 = TIME0TH;TL0 = TIME0TL;
	  IrDatCount=0;EA=1;
	  return;
	}
	if(IrStart==1)
	{
	 if(IrDatCount>0&&IrDatCount<33)
	 	IRDATBUF[IrDatCount-1]=IrCount;
	 if(IrDatCount>31)
	 	{IrStart=2;TH0 = TIME0TH;TL0 = TIME0TL;EA=1;return;}
	 if(IrCount>114&&IrCount<133&&IrDatCount==0)
	 	{IrDatCount=1;}else if(IrDatCount>0)IrDatCount++;
	}			
	IrCount=0;TH0 = TIME0TH;TL0 = TIME0TL;
	EA=1;
}

main()
{
	uchar *a,n;
	TMOD  |= 0x011;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	ET0=1;
	TR0=1;				
	ET1=1;
	TR1=1;				
	IT0 = 1;				//下降沿
	EX0 = 1;
	initLCM();
	EA=1;
	for(;;)
	{

		if(Show==1)
		{
			Show=0;
			Cont=0;
			DisplayListChar(0,1,"Please keys");
			a="";
			switch (IrDat[3])
			{
		      case 0x12://ON/C
			  	  a="ON/C";
				  break;
		      case 0x0b://±
			  	  a="+/-";
				  break;
		      case 0x1a://+
			  	  a="+";
				  break;
		      case 0x1e://-
			  	  a="-";
				  break;
		      case 0x0e://÷
			  	  a="/";
				  break;
		      case 0x1d://MRC
			  	  a="MRC";
				  break;
		
		      case 0x1f://M-
			  	  a="M-";
				  break;
		      case 0x1b://M+
			  	  a="M+";
				  break;
		      case 0x00://0
			  	  if(IrDat[2]==0xff)a="0";
				  break;
		      case 0x01://1
			  	  a="1";
				  break;
		      case 0x02://2
			  	  a="2";
				  break;
		
		      case 0x03://3
			  	  a="3";
				  break;
		      case 0x04://4
			  	  a="4";
				  break;
		      case 0x05://5
			  	  a="5";
				  break;
		      case 0x06://6
			  	  a="6";
				  break;
		      case 0x07://7
			  	  a="7";
				  break;
		      case 0x08://8
			  	  a="8";
				  break;
		
		      case 0x09://9
			  	  a="9";
				  break;
		      case 0x2A://%
			  	  a="%";
				  break;
		      case 0x2B://X
			  	  a="X";
				  break;
		      case 0x2C://.
			  	  a=".";
				  break;
		      case 0x2D://=
			  	  a="=";
				  break;
		      case 0x2E://□
			  	  a=" ";
				  break;

			}
			n=strlen(a);
			if(n>0)sprintf(s,"Key is [%s]",a);else sprintf(s,"Not Key         ",a);
			DisplayListChar(0,0,s);
		}
	}
}