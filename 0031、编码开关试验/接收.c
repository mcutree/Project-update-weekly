#include <AT89X52.h>

#define JINGZHEN 24
#define TIME0TH ((65536-50*JINGZHEN/12)&0xff00)>>8 // 50us
#define TIME0TL ((65536-50*JINGZHEN/12)&0xff)
#define TIME1TH ((65536-3000*JINGZHEN/12)&0xff00)>>8   
#define TIME1TL ((65536-3000*JINGZHEN/12)&0xff)


sbit CodingsWitch_A1=P1^0;
sbit CodingsWitch_B1=P1^1;
sbit CodingsWitch_A2=P1^2;
sbit CodingsWitch_B2=P1^3;
sbit CodingsWitch_A3=P1^4;
sbit CodingsWitch_B3=P1^5;
sbit CodingsWitch_A4=P1^6;
sbit CodingsWitch_B4=P1^7;

void CodingsWitchPolling1(); 
void CodingsWitchPolling2(); 
void CodingsWitchPolling3(); 
void CodingsWitchPolling4(); 

code char num[10]={0x03,0x9f,0x25,0x0d,0x99,0x49,0x41,0x1f,0x01,0x09,};

 unsigned char dat[4];
void timer1int (void)  interrupt 1  using 0{	 //定时器0
	EA=0;
	TH0 = TIME0TH;  
	TL0 = TIME0TL;
	CodingsWitchPolling1();
	CodingsWitchPolling2();
	CodingsWitchPolling3();
	CodingsWitchPolling4();
	EA=1;
}
main()
{
 unsigned char i,c,b;
 unsigned int a;
 P1=0xff;
 P3=0;
 TH0 = TIME0TH;
 TL0 = TIME0TL;
 TMOD  |= 0x11;
 ET0=1;
 ET1=1;
 TR1=0;
 TR0=1;
 EA=1;
 dat[0]=dat[1]=dat[2]=dat[3]=23;
 while(1)
 {
 	b=0x80;
	
	for(i=0;i<8;i++)
	{
		P2=b;
		if((i%2)==0)c=dat[i/2]%10;else c=dat[i/2]/10;
		P0=~num[c];
		for(a=0;a<10;a++) ;
		b>>=1;P0=0;
		//if(i==7) for(a=0;a<10000;a++) ;
	}
 }
}

void CodingsWitchPolling1()// 
{ 
   static char st;         //定义了一个变量用来储蓄以前是否出现了两个引脚都为高电平的状态 
   if(CodingsWitch_A1&&CodingsWitch_B1) 
   {st = 1;}      // 
   if(CodingsWitch_A1==0&&CodingsWitch_B1==0) 
   {st = 2;}      // 
   if(st)               //如果st为1执行下面的步骤 
   { 
      if(CodingsWitch_A1!=CodingsWitch_B1)      //如果当前编码开关的两个引脚都为底电平执行下面的步骤 
      { 
         if(CodingsWitch_A1)      //为高说明编码开关在向加大的方向转 
         { 
            if(dat[0]>0&&st==1)dat[0]--;      // 
            if(dat[0]<64&&st==2)dat[0]++;      // 
            st = 0;       
			return;
         } 
         if(CodingsWitch_B1)      //为高说明编码开关在向减小的方向转 
         { 
			if(dat[0]<64&&st==1)dat[0]++;
			if(dat[0]>0&&st==2)dat[0]--;
            st = 0; 
			return;
         } 
      } 
   } 
} 
 

void CodingsWitchPolling2()// 
{ 
   static char st;         //定义了一个变量用来储蓄以前是否出现了两个引脚都为高电平的状态 
   if(CodingsWitch_A2&&CodingsWitch_B2) 
   {st = 1;}      // 
   if(CodingsWitch_A2==0&&CodingsWitch_B2==0) 
   {st = 2;}      // 
   if(st)               //如果st为1执行下面的步骤 
   { 
      if(CodingsWitch_A2!=CodingsWitch_B2)      //如果当前编码开关的两个引脚都为底电平执行下面的步骤 
      { 
         if(CodingsWitch_A2)      //为高说明编码开关在向加大的方向转 
         { 
            if(dat[1]>0&&st==1)dat[1]--;      // 
            if(dat[1]<64&&st==2)dat[1]++;      // 
            st = 0;       
			return;
         } 
         if(CodingsWitch_B2)      //为高说明编码开关在向减小的方向转 
         { 
			if(dat[1]<64&&st==1)dat[1]++;
			if(dat[1]>0&&st==2)dat[1]--;
            st = 0; 
			return;
         } 
      } 
   } 
} 
void CodingsWitchPolling3()// 
{ 
   static char st;         //定义了一个变量用来储蓄以前是否出现了两个引脚都为高电平的状态 
   if(CodingsWitch_A3&&CodingsWitch_B3) 
   {st = 1;}      // 
   if(CodingsWitch_A3==0&&CodingsWitch_B3==0) 
   {st = 2;}      // 
   if(st)               //如果st为1执行下面的步骤 
   { 
      if(CodingsWitch_A3!=CodingsWitch_B3)      //如果当前编码开关的两个引脚都为底电平执行下面的步骤 
      { 
         if(CodingsWitch_A3)      //为高说明编码开关在向加大的方向转 
         { 
            if(dat[2]>0&&st==1)dat[2]--;      // 
            if(dat[2]<64&&st==2)dat[2]++;      // 
            st = 0;       
			return;
         } 
         if(CodingsWitch_B3)      //为高说明编码开关在向减小的方向转 
         { 
			if(dat[2]<64&&st==1)dat[2]++;
			if(dat[2]>0&&st==2)dat[2]--;
            st = 0; 
			return;
         } 
      } 
   } 
} 
void CodingsWitchPolling4()// 
{ 
   static char st;         //定义了一个变量用来储蓄以前是否出现了两个引脚都为高电平的状态 
   if(CodingsWitch_A4&&CodingsWitch_B4) 
   {st = 1;}      // 
   if(CodingsWitch_A4==0&&CodingsWitch_B4==0) 
   {st = 2;}      // 
   if(st)               //如果st为1执行下面的步骤 
   { 
      if(CodingsWitch_A4!=CodingsWitch_B4)      //如果当前编码开关的两个引脚都为底电平执行下面的步骤 
      { 
         if(CodingsWitch_A4)      //为高说明编码开关在向加大的方向转 
         { 
            if(dat[3]>0&&st==1)dat[3]--;      // 
            if(dat[3]<64&&st==2)dat[3]++;      // 
            st = 0;       
			return;
         } 
         if(CodingsWitch_B4)      //为高说明编码开关在向减小的方向转 
         { 
			if(dat[3]<64&&st==1)dat[3]++;
			if(dat[3]>0&&st==2)dat[3]--;
            st = 0; 
			return;
         } 
      } 
   } 
} 
