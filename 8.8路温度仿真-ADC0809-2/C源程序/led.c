#include<reg52.h>
#define uchar unsigned char 
#define uint unsigned int
#define ulong unsigned long
unsigned char code dispbitcode[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char dispbuf[4];
unsigned int i;
unsigned int j;
unsigned char getdata;
unsigned int temp,Num1,Num2,Num3;
unsigned int temp1;
unsigned char count;
unsigned char d,a,b,c,e,f,g;
//unsigned char tab_H[8]={100,100,100,100,100,100,100,100};
unsigned char tab_8[9]={0,0,0,0,0,0,0,0,0};

unsigned char wen_H[9]={100,100,100,100,100,100,100,100,100};
unsigned char wen_L[9]={60,60,60,60,60,60,60,60,60};

unsigned char tab_flag[9]={0,0,0,0,0,0,0,0,0};

sbit ST=P1^2;
sbit OE=P1^0;
sbit EOC=P1^1;
sbit CLK=P1^3;



sbit A5=P3^0;
sbit A1=P1^4;
sbit A2=P1^5;
sbit A3=P1^6;
sbit A4=P1^7;
sbit ADD_A=P3^1;
sbit ADD_B=P3^2;
sbit ADD_C=P3^3;
sbit K1=P3^4;
sbit K2=P3^5;
sbit K3=P3^6;
//sbit K4=P3^7;
sbit LED_R=P3^7;
bit flag0,flag1,flag2,flag3;


void TimeInitial();
void Delay(unsigned int i);//
void TimeInitial()
{  
  TMOD=0x10;
  TH1=(65536-200)/256;//定时时间为2us,亦即CLK周期为0.4us
  TL1=(65536-200)%256;
  EA=1;
  ET1=1;
  TR1=1;
 }

void Delay(unsigned int i)//延时函数
{
  unsigned int j;
  for(;i>0;i--)
  {
   for(j=0;j<125;j++)
  {;}
  }
}
void scan(uint data_ad)
{ 
  dispbuf[0]=data_ad%10;//百分位
  dispbuf[1]=data_ad/10%10;//十分位
  dispbuf[2]=data_ad/100%10;//个位
  dispbuf[3]=data_ad/1000;//十位   
} 
void Display()//

{ 
  P0=0xff;   
  if(b==1)
  P0=0xc7;
  else if(b==2)
  P0=0x89;
  A1=1;
  A2=0;
  A3=0;
  A4=0;
  A5=0;
  Delay(1);
  P0=0xff;
  if(b!=0&&flag1==1)
  P0=0xff;//百分位
  else
  {
  if(dispbuf[2]==0)
  P0=0xff;
  else
  P0=dispbitcode[dispbuf[2]];//个位
  }
  A1=0;
  A2=1;
  A3=0;
  A4=0;
  A5=0;
  Delay(1); 
  P0=0xff;
    if(b!=0&&flag1==1)
  P0=0xff;//百分位
  else
  P0=dispbitcode[dispbuf[1]];//十分位
  A1=0;
  A2=0;
  A3=1;
  A4=0;
  A5=0;
  Delay(1);
  P0=0xff;
    if(b!=0&&flag1==1)
  P0=0xff;//百分位
  else
  P0=dispbitcode[dispbuf[0]];//百分位
  A1=0;
  A2=0;
  A3=0;
  A4=1;
  A5=0;
  Delay(1);
  P0=0xff;
  if(b==0)
  {
  if(tab_flag[a]==0)
  		P0=dispbitcode[a];//百分位
  else
  {
	  if(flag1==1)
	  P0=0xff;//百分位
	  else
	  P0=dispbitcode[a];//百分位
  }
  
  
  }
  else
  P0=dispbitcode[a];
  
  
  A1=0;
  A2=0;
  A3=0;
  A4=0;
  A5=1;
  Delay(1);
}

void main()//主函数
{
 TimeInitial();
 a=1;
 ADD_A=0;
  ADD_B=0;
   ADD_C=0;
   //wen_H=100;
   //wen_L=60;
   LED_R=0;
 while(1)
 {
  ST=0;//关闭转换
  OE=0;//关闭输出
  ST=1;//开启转换
  ST=0;//关闭转换

  while(EOC==0);//判断是否转换结束:是则执行以下语句,否则等待
  OE=1;//开启数据输出允许
  getdata=P2;//将数据取走,存放在变量getdata中
  OE=0;//关闭输出
  temp=getdata/1.7;//电压值转换,5V作为参考电压,分成256份

  Display(); 
  if(K1==0)
  {
   	while(K1==0);
  	b++;
	if(b>2)
	b=0;
	Num2=0;
	if(b!=0)
	LED_R=1;

  }
    if(LED_R==0&&b!=0)
  {
   	while(LED_R==0);
  	a++;
	if(a>8)
	a=1;
	
  }
  /*
  if(K4==0&&flag0==1)
  {
   while(K4==0);
   a++;
   if(a>8)
   	a=1;
  }
  */
  if(b==1)
  scan(wen_L[a]);
  else if(b==2)
  scan(wen_H[a]);



  if(b==2&&K2==0)
  {
     while(K2==0);
  	 if( wen_H[a]<150)
	  wen_H[a]= wen_H[a]+10;
   }
   else if(b==1&&K2==0)
  {
     while(K2==0);
  	 if(wen_H[a]>wen_L[a]&&(wen_H[a]-wen_L[a]>10))
	 wen_L[a]=wen_L[a]+10;
   }
   else if(b==1&&K3==0)
  {
     while(K3==0);
  	 if(wen_L[a]>10)
	 wen_L[a]=wen_L[a]-10;
   }
  else if(b==2&&K3==0)
  {
     while(K3==0);
  	 
  	 if(wen_H[a]>wen_L[a]&&(wen_H[a]-wen_L[a]>10))
	 wen_H[a]=wen_H[a]-10;
   }
   if(b==0&&Num2>10000)
   {
   a++;
   if(a>8)
   a=1;
   Num2=0;
   
   }
   if(b==0)
   {
    scan(temp);
	tab_8[a]=temp;
   	if(a==1)
	{
	
	 ADD_A=0;
     ADD_B=0;
     ADD_C=0;	
	}
	else if(a==2)
	{
	 ADD_A=1;
     ADD_B=0;
     ADD_C=0;	
	}
		else if(a==3)
	{
	 ADD_A=0;
     ADD_B=1;
     ADD_C=0;	
	}
		else if(a==4)
	{
	 ADD_A=1;
     ADD_B=1;
     ADD_C=0;	
	}
		else if(a==5)
	{
	 ADD_A=0;
     ADD_B=0;
     ADD_C=1;	
	}
		else if(a==6)
	{
	 ADD_A=1;
     ADD_B=0;
     ADD_C=1;	
	}
		else if(a==7)
	{
	 ADD_A=0;
     ADD_B=1;
     ADD_C=1;	
	}
		else if(a==8)
	{
	 ADD_A=1;
     ADD_B=1;
     ADD_C=1;	
	}
   	 if(tab_8[a]<wen_L[a]||tab_8[a]>wen_H[a])
   	 {
	  
	  tab_flag[a] =1;
	 
	 }
	 else if(tab_8[a]>=wen_L[a]&&tab_8[a]<=wen_H[a])
	 tab_flag[a] =0;


   	 if(tab_flag[1]||tab_flag[2]||tab_flag[3]||tab_flag[4]||tab_flag[5]||tab_flag[6]||tab_flag[7]||tab_flag[8])
   	 flag2=1;
	 else if((tab_flag[1]==0&&tab_flag[2]==0&&tab_flag[3]==0&&tab_flag[4]==0&&tab_flag[5]==0&&tab_flag[6]==0&&tab_flag[7]==0&&tab_flag[8]==0))
   	 flag2=0;
   }
	if(flag2==0&&b==0)
	
	LED_R=0;

	



  
  
   
 }
}

void t1(void) interrupt 3 using 0//定时器中断服务函数;作用:产生CLK信号
 {
   TH1=(65536-200)/256;
   TL1=(65536-200)%256;
   CLK=~CLK;
   Num1++;
   if(Num1>2000)
   {
   		Num1=0;
		flag1=~flag1;   
   }
   
   if(b==0 )
   Num2++;

   if(b==0)
   {
   if(Num3<300)
	{
	 if(flag2==1)
	 LED_R=~LED_R;
	 }
	 else if(Num3<1000&&b==0)
	 LED_R=0;

	 if(Num3>1000)
	 Num3=0;
   }



 } 





/*

#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
//各数字的数码管段码（共阴）
uchar code DSY_CODE[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
sbit CLK=P1^3;		//时钟信号
sbit ST=P1^2;		//启动信号
sbit EOC=P1^1;		//转换结束信号
sbit OE=P1^0;		//输出使能
//延时
void DelayMS(uint ms)
{
	uchar i;
	while(ms--) for(i=0;i<120;i++);
}
//显示转换结果
void Display_Result(uchar d)
{
	P2=0x8F;		//第4个数码管显示个位数
	P0=DSY_CODE[d%100%10];
	//P0=0xc0;
	DelayMS(30);
	P2=0x4F;		//第3个数码管显示十位数
	P0=DSY_CODE[d%100/10];
	DelayMS(30);
	P2=0x2F;		//第2个数码管显示百位数
	P0=DSY_CODE[d/100];
	DelayMS(30);
}
//主程序
void main()
{
	TMOD=0x02;		//T1工作模式2
	TH0=0x14;		
	TL0=0x00;
	IE=0x82;
	TR0=1;
	//P1=0x3f;		//选择ADC0809的通道3（0111）（P1.4~P1.6）
	while(1)
	{
		ST=0;ST=1;ST=0;		//启动A/D转换
		while(EOC==0);		//等待转换完成
		OE=1;
		Display_Result(P3);
		OE=0;



	}
}
//T0定时器中断给ADC0808提供时钟信号
void Timer0_INT() interrupt 1
{
	CLK=~CLK;
}
*/