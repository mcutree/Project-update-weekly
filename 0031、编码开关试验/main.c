//proteus∑¬’Ê¬€Ã≥£∫proteus.5d6d.com

#include <AT89X52.h>

#define JINGZHEN 24
#define TIME0TH ((65536-100*JINGZHEN/12)&0xff00)>>8   //time0,100us,∫ÏÕ‚“£øÿ
#define TIME0TL ((65536-100*JINGZHEN/12)&0xff)

main()
{
 char a,b,c,d;
 a=b=c=d=0;
 P3=0;
 TH0 = TIME0TH;
 TL0 = TIME0TL;
 TMOD  |= 0x11;
 ET0    = 1;
 TR0    = 1;
 EA=1;
while(1)
 {
 P1=0xff;
 if(P1_0==0)
 {
 	if(a==0)
	{
	a=1;
	P3_0=1;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	P3_1=1;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	}
	else
	{
	a=0;
	P3_0=0;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	P3_1=0;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	}
	while(P1_0==0);
 }
 if(P1_1==0)
 {
 	if(a==0)
	{
	a=1;
	P3_1=1;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	P3_0=1;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	}
	else
	{a=0;
	P3_1=0;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	P3_0=0;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	}
	while(P1_1==0);
 }
 
 if(P1_2==0)
 {
 	if(b==0)
	{
	b=1;
	P3_2=1;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	P3_3=1;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	}
	else
	{b=0;
	P3_2=0;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	P3_3=0;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	}
 	while(P1_2==0);
}
 if(P1_3==0)
 {
 	if(b==0)
	{
	b=1;
	P3_3=1;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	P3_2=1;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	}
	else
	{
	b=0;
	P3_3=0;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	P3_2=0;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	}
 	while(P1_3==0);
 }
  if(P1_4==0)
 {
 	if(c==0)
	{c=1;
	P3_4=1;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	P3_5=1;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	}
	else
	{c=0;
	P3_4=0;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	P3_5=0;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	}
 	while(P1_4==0);
 }
 if(P1_5==0)
 {
 	if(c==0)
	{c=1;
	P3_5=1;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	P3_4=1;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	}
	else
	{c=0;
	P3_5=0;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	P3_4=0;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	}
 	while(P1_5==0);
 }		   
if(P1_6==0)
 {
 	if(d==0)
	{d=1;
	P3_6=1;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	P3_7=1;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	}else
	{d=0;
	P3_6=0;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	P3_7=0;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	}
 	while(P1_6==0);
 }	
 if(P1_7==0)
 {
 	if(d==0)
	{d=1;
	P3_7=1;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	P3_6=1;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	}
	else
	{d=0;
	P3_7=0;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	P3_6=0;
	TH0 = TIME0TH;
	TL0 = TIME0TL;
	TF0=0;
	while(TF0==0);
	TF0=0;
	}
  	while(P1_7==0);
}
 }
}