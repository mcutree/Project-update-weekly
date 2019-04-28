#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
	
sbit duan = P2^6;
sbit wei  = P2^7;
sbit key  = P3^2;
sbit LED1 = P2^0;
sbit LED2 = P2^1;
sbit LED3 = P2^2;
sbit LED4 = P2^3;

uchar stu_flag = 1,dat = 0;

//学号数组
uchar stu1_ID[8]={1,6,0,3,2,1,0,6};
uchar stu2_ID[8]={1,6,0,3,2,1,0,7};
uchar stu3_ID[8]={1,6,0,3,2,1,1,7};

//数码管0-f数组
uchar table_duan[16]={
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x67,0x77,0x7c,
	0x39,0x5e,0x79,0x71
};

//数码管位选数组（选择哪个数码管）
uchar table_wei[8]={
	0xfe,0xfd,0xfb,0xf7,
	0xef,0xdf,0xbf,0x7f,
};

void delay(uint z);		//延时函数
void LED_Flash(uchar ch);	//选择LED闪烁

void main()
{
	uchar i = 0;
	SCON= 0x50;	//设定串口工作方式0101 0000
	PCON= 0x00;
	TMOD= 0x21;
	TL1 = 0xF3;	//波特率2400 = 12M/12/32/（256-初值0xf3(即243)）
	TH1 = 0xF3;
	TR1 = 1;
	TH0 = (65536-10000)/256;	//定时10ms=12/12M*10000
	TL0 = (65536-10000)%256;	
	TR0 = 1;	//启动定时器0
	ET0 = 1;
	EX0 = 1;
	EA = 1;
	ES = 1;
	while(1)
	{
		if(stu_flag == 1)			//学号标志位选择
		{
			for(i = 0;i < 8;i++)	//八位数码管循环显示
			{			
				wei=1;				//数码管位选
				P0=table_wei[i];
				wei=0;
				P0=0xff;			//消影
				duan=1;
				P0=table_duan[stu1_ID[i]];	//数码管段选
				duan=0;
				P0=0xff;
				delay(2);
			}
		}
		
		if(stu_flag == 2)
		{
			for(i = 0;i < 8;i++)
			{			
				wei=1;
				P0=table_wei[i];
				wei=0;
				P0=0xff;
				duan=1;
				P0=table_duan[stu2_ID[i]];
				duan=0;
				P0=0xff;
				delay(2);
			}
		}
		
		if(stu_flag == 3)
		{
			for(i = 0;i < 8;i++)
			{			
				wei=1;
				P0=table_wei[i];
				wei=0;
				P0=0xff;
				duan=1;
				P0=table_duan[stu3_ID[i]];
				duan=0;
				P0=0xff;
				delay(2);
			}
		}
	}
}

void key_int(void) interrupt 0		//按键中断
{
	if(key == 0)
	{
		delay(10);			//延时
		if(key == 0)
		{
			stu_flag++;		//切换模式			
			if(stu_flag > 3)	//只留三种模式
				stu_flag = 1;
			LED_Flash(stu_flag);
		}
	}
}

void time0_isr() interrupt 1	 //10ms 进入一次
{
	static char c;
	TH0 = (65536-10000)/256;	//定时10ms
	TL0 = (65536-10000)%256;	
	c++;
	if(c > 50)
	{
		LED4 = !LED4;	//LED闪烁
		c=0;
	}
}

void usart_receive(void) interrupt 4 	//串口服务函数                     
{        
	if(RI == 1) 
	{    
		RI = 0;        
		dat=SBUF;
		switch(dat)		//切换模式
		{
			case '1':stu_flag = 1;LED_Flash(stu_flag);break;
			case '2':stu_flag = 2;LED_Flash(stu_flag);break;
			case '3':stu_flag = 3;LED_Flash(stu_flag);break;
			default :			  break;
		}
    }  
    else  
	{          
		TI = 0;         
    }                                                           
}

void LED_Flash(uchar ch)
{
	if(ch == 1)
	{
		LED1 = 0;
		delay(500);
		LED1 = 1;
	}
	
	if(ch == 2)
	{
		LED2 = 0;
		delay(500);
		LED2 = 1;
	}
	
	if(ch == 3)
	{
		LED3 = 0;
		delay(500);
		LED3 = 1;
	}
}

void delay(uint z)
{
	uint i,j;
	for(i=z;i>0;i--)
		for(j=110;j>0;j--);
}
	