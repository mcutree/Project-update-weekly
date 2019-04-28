#include "absacc.h"
#include"ds1302.h"
#include <reg51.h>	   //此文件中定义了51的一些特殊功能寄存器
#include<intrins.h>	   //头文件
#define INT8U   unsigned char  //宏定义
#define INT16U  unsigned int
#define uchar unsigned char 
#define uint unsigned int
#define ulong unsigned long

#define COM8155 XBYTE[0x7ff8]
#define PA8155 XBYTE[0x7ff9]
#define PB8155 XBYTE[0x7FFA]
#define PC8155 XBYTE[0x7ffB]

sbit D0=P0^0;				//定义IO端口
sbit D1=P0^1; 
sbit D2=P0^2;
sbit D3=P0^3; 
sbit D4=P0^7; 
sbit LED_NBZ=P3^0; 
sbit LED_NBG=P3^1;
sbit LED_NBY=P3^2; 
sbit LED_NBR=P3^3;

sbit LED_DXZ=P3^4; 
sbit LED_DXG=P3^5;
sbit LED_DXY=P3^6; 
sbit LED_DXR=P3^7;
sbit key1=P0^4;
sbit key2=P0^5;
sbit key3=P0^6;
sbit key4=P2^3;

unsigned int LedNumVal;			//定义变量
unsigned int Num,Num2,Num3,Num4;
uchar cent,jishu;
uchar cent_2;
uchar cent_shi;
uchar jishi;
uchar jishilaba;
unsigned int nub;
uchar data1,data2,data3,data4;

bit flag2=0;				  //定义标志
bit flag3=0;
bit flag4=0;
bit flag5=0;
bit flag6=0;
bit flag7=0;
bit flag8=0;
bit flag_sound=0;

uchar code table_dm[11]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};//共阳极数码管断码表	
uchar code table_dd[10]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};//个位带小数点的共阳极数码管断码表断码表



uint Display_Buffer[2]={0,0};			//定义数组
uint Display_Buffer2[2]={0,0};
uint ge,bai,n,k,p,q,abc,aaa,m,bbb,ccc,ddd;

uchar temp,flag,outcomeH,outcomeL,i;  //定义




void delayms(uint xms)			  //延时子程序
{
	uint h,j;
	for(h=xms;h>0;h--)
		for(j=110;j>0;j--);
}




void scan(uint data_ad)			  //分解倒计时时间子程序
{   

	(uint)Display_Buffer[0]=data_ad/10;	
	(uint)Display_Buffer[1]=data_ad%10;

   
}
void scan2(uint data_ad2)		   //分解倒计时时间子程序
{   

	(uint)Display_Buffer2[0]=data_ad2/10;	
	(uint)Display_Buffer2[1]=data_ad2%10;

   
}


void system_Ini()					  //系统初始化
{
     TMOD = 0x01; //选择模式0  13位计数 最大计数8192
	 TH0 = (8192 - 500)/32;
	 TL0 = (8192 - 500)%32	;
     IE = 0x8A;   //中断	
     TR0  = 1;    //开启T0定时器


}



main()
{ 

		   system_Ini();		  //系统初始化
		   Ds1302Init();
			P0=0xff;
		   flag3=0;
		  data1=30;				  //赋予初始值
		  data2=5;					
		  data3=10;
		  data4=45;


		  m=data1;	
		  p=data4;
		  cent_2=3;


	   while(1)			//大循环
	{  

		Ds1302ReadTime();


		scan(m);		//拆解数据 //m
		scan2(p);

	  if(LedNumVal>250)	//1秒数据处理
	  {
	   LedNumVal=0;
	   if(m==1)
	   {
	   cent++;
	   
	  if(cent>3)
	  cent=0;
	   if(cent==0)
	   m=data1;
	   if(cent==1)
	   m=data2;
	   if(cent==2)
	   m=data3;
	   if(cent==3)
	   m=data4;	  
	   }
	   else
	   m--; 

	   if(p==1)
	   {
	   cent_2++;
	   if(cent_2>3)
	    cent_2=0;
	   if(cent_2==0)
	   p=data1;
	   if(cent_2==1)
	   p=data2;
	   if(cent_2==2)
	   p=data3;
	   if(cent_2==3)
	   p=data4;	  
	   }
	   else
	   p--;
	  
	  }
	   if(flag2==0)		  //正常状态下，指示灯状态
	  {
	  if(cent==0)
	  {
		LED_NBZ=0; 
		LED_NBG=1;
		LED_NBY=0; 
		LED_NBR=0;  
	  
	  }
	  	  if(cent==1)
	  {
		LED_NBZ=0; 
		LED_NBG=0;
		LED_NBY=1; 
		LED_NBR=0;  
	  
	  }
	  	  if(cent==2)
	  {
		LED_NBZ=1; 
		LED_NBG=0;
		LED_NBY=0; 
		LED_NBR=0;  
	  
	  }
	  	  if(cent==3)
	  {
		LED_NBZ=0; 
		LED_NBG=0;
		LED_NBY=0; 
		LED_NBR=1;  
	  
	  }

	if(cent_2==0)
	  {
		LED_DXZ=0; 
		LED_DXG=1;
		LED_DXY=0; 
		LED_DXR=0;  
	  
	  }
	  	  if(cent_2==1)
	  {
		LED_DXZ=0; 
		LED_DXG=0;
		LED_DXY=1; 
		LED_DXR=0;  
	  
	  }
	  	  if(cent_2==2)
	  {
		LED_DXZ=1; 
		LED_DXG=0;
		LED_DXY=0; 
		LED_DXR=0;  
	  
	  }
	  	  if(cent_2==3)
	  {
		LED_DXZ=0; 
		LED_DXG=0;
		LED_DXY=0; 
		LED_DXR=1;  
	  
	  }
	  }
	   else			   //禁行状态下，指示灯状态
	  {
	   	LED_NBZ=0; 
		LED_NBG=0;
		LED_NBY=0; 
		LED_NBR=1; 
	  	LED_DXZ=0; 
		LED_DXG=0;
		LED_DXY=0; 
		LED_DXR=1; 
	  
	  }
	 	  if(key3==0)				//K1，禁行/解除按键处理
	  {
	  
	  		while(key3==0);
	  		flag2=~flag2;
	
		  LedNumVal=901;
		  m=1;
		  p=1;
		  cent=3;
		  cent_2=2; 
	  	D4=~D4;
	  }


	  

	if(key1==0&&flag2==0)
	{
	 	while(key1==0);
		flag3=0;
		if(flag3==0)
	{
		if(shi>7&&shi<12)
		{
			data1=15;				  //赋予初始值
			data2=5;					
			data3=10;
			data4=30;		
		}
		else if(shi>11&&shi<19)
		{
			data1=30;				  //赋予初始值
			data2=5;					
			data3=10;
			data4=45;
		}
		else if(shi<8||shi>18)
		{
			data1=45;				  //赋予初始值
			data2=5;					
			data3=10;
			data4=60;
		}	
	}
	
		  
		  m=data1;	
		  p=data4;
		  cent=0;
		  cent_2=3;

	}
		if(key2==0&&flag2==0)
	{
	 	while(key2==0);
		flag3=1;
		if(flag3==1)
	{
		if(shi>7&&shi<12)
		{
			data1=30;				  //赋予初始值
			data2=5;					
			data3=10;
			data4=45;		
		}
		else if(shi>11&&shi<19)
		{
			data1=15;				  //赋予初始值
			data2=5;					
			data3=10;
			data4=30;
		}
		else if(shi<8||shi>18)
		{
			data1=45;				  //赋予初始值
			data2=5;					
			data3=10;
			data4=60;
		}	
	}
	
		  
		  m=data1;	
		  p=data4;
		  cent=0;
		  cent_2=3;

	}











	if(flag3==0)
	{
		if(shi>7&&shi<12)
		{
			data1=15;				  //赋予初始值
			data2=5;					
			data3=10;
			data4=30;		
		}
		else if(shi>11&&shi<19)
		{
			data1=30;				  //赋予初始值
			data2=5;					
			data3=10;
			data4=45;
		}
		else if(shi<8||shi>18)
		{
			data1=45;				  //赋予初始值
			data2=5;					
			data3=10;
			data4=60;
		}	
	}
	else
	{
		if(flag3==1)
		{
			if(shi>7&&shi<12)
			{
				data1=30;				  //赋予初始值
				data2=5;					
				data3=10;
				data4=45;		
			}
			else if(shi>11&&shi<19)
			{
				data1=15;				  //赋予初始值
				data2=5;					
				data3=10;
				data4=30;
			}
			else if(shi<8||shi>18)
			{
				data1=45;				  //赋予初始值
				data2=5;					
				data3=10;
				data4=60;
			}	
		}	
	}

	  /*
	  	  if(key3==0)
	  {
	  while(key3==0);
	   data1=45;
		data2=5;
		 data3=10;
		  data4=60;	
		  LedNumVal=901;
		  m=1;
		  p=1;
		  cent=3;
		  cent_2=2; 
	  
	  }
	  */





  	   
	 
    }
}

 void T0zd(void) interrupt 1      //3定时器1的中断号  1定时器0的中断号 0外部中断1 2外部中断2  4串口中断
{

	 
	 TH0 = (8192 - 500)/32;
	 TL0 = (8192 - 500)%32;    
	 if(flag2==0)		 //正常状态下，1秒计数器
	 LedNumVal++; 
	 Num++;	
	 Num2++; 
	 Num3++;
	 Num4++;
	 if(Num2>1)				  //东西方向数码管动态扫描
	 {
	 Num2=0;
	 n++;
	 	D0=1;
		D1=1;
		D2=1;
		D3=1;
	 if(n>3)
	 n=0;
	 if(n==0||n==1)
	  P1=table_dm[Display_Buffer2[n]];
	  else 
	  P1=table_dm[Display_Buffer[n-2]];
	  if(n==0)
	   {
	    D0=0;
		D1=1;
		D2=1;
		D3=1;	   
	   }
	   	else if(n==1)
	   {
	    D0=1;
		D1=0;
		D2=1;
		D3=1;	   
	   }
	   	   	else if(n==2)
	   {
	    D0=1;
		D1=1;
		D2=0;
		D3=1;	   
	   }
	   	   	else if(n==3)
	   {
	    D0=1;
		D1=1;
		D2=1;
		D3=0;	   
	   }
	 
	 }
	   /*
	 	 if(Num3>20)	    //南北方向数码管动态扫描
	 {
	 Num3=0;
	 k++;
	 	D2=1;
		D3=1;
	 if(k>1)
	 k=0;
	  P2=table_dm[Display_Buffer[k]];
	  if(k==0)
	   {
	    D2=0;
		D3=1;	   
	   }
	   	if(k==1)
	   {
	    D2=1;
		D3=0;	   
	   }
	 
	 }
	 */


	 
}
	 









