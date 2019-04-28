#include<reg52.h>

#define uchar unsigned char
#define uint unsigned int

sbit duan = P1^6; //段选
sbit wei = P1^7; //位选
sbit S1 = P3^0;	//开始修改参数键
sbit S2 = P3^6;	//增加键
sbit S3 = P3^7;	//减少键

uchar code aaa[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
uchar temp,out = 1,qq = 0,ww = 0,H,M,S,j1,j2,k1,k2,l1,l2;
uchar H1 = 0,M1 = 0,Sa = 0,j10,j20,k10,k20,l10,l20,SS = 0;
uint UT;
//无按键按下开始计数标志
uint num=0;


void TIM0_Init()
{
	TMOD = 0x01; 
	TH0 = (65536 - 50000)/256; //初值：2^16=65536  12M 50ms定时
	TL0 = (65536 - 50000)%256;
	EA=1;
	ET0 = 1; //中断打开，打开外部中断0和定时器0中断
	TR0=1;                     //打开定时器开关
}
void TIM1_Init(void)
{
         TMOD |= 0x10;
        TH1=(65536-50000)/256;
        TL1=(65536-50000)%256;
        EA=1;
        ET1=1;
        TR1=1;   
}




void delayMS(x) //延时函数，单位毫秒
{
	uint a , b;
	for(a = 0 ; a < x ; a++ )
	for(b = 0 ; b < 110 ; b++);
}


void play(uint h1 , uint h2 , uint m1 , uint m2 , uint s1 , uint s2) //时分秒的显示
{
	wei = 1; //时的十位
	P2 = 0x7f;
	wei = 0; 

	duan = 1;
	P0 = aaa[h1];
	duan = 0;
	delayMS(3);

	wei = 1; //时的个位
	P2 = 0xbf;
	wei = 0; 

	duan = 1;
	P0 = aaa[h2];
	duan = 0;	
	delayMS(3);

	wei = 1; //分的十位
	P2 = 0xdf;
	wei = 0; 

	duan = 1;
	P0 = aaa[m1];
	duan = 0;
	delayMS(3);

	wei = 1; //分的个位
	P2 = 0xef;
	wei = 0; 

	duan = 1;
	P0 = aaa[m2];
	duan = 0;
	delayMS(3);

	wei = 1; //秒的十位
	P2 = 0xf7;
	wei = 0; 

	duan = 1;
	P0 = aaa[s1];
	duan = 0;
	delayMS(3);

	wei = 1; //秒的个位
	P2 = 0xfb; 
	wei = 0; 

	duan = 1;
	P0 = aaa[s2];
	duan = 0;
	delayMS(3);		
}  

void stopfunc() //S1键函数开始修改参数
{
	if(S1 == 0)
	{
		while(!S1);
		qq++;
		out = 0; //暂停
		TR0 = 0;
		TR1=1;
		num=0;
	}		
}


void buttfunc() //S2键、S3键函数 调时
{
	
	if(qq == 1) //第一次按S1时，调秒
	{
		if(S2 == 0)
		{
			while(!S2);
			if(S < 59)
			{
				S++;
			}
			else
			{
				S = 0;	
			}
			delayMS(5);
			num==0;
		}
		if(S3 == 0)
		{
			while(!S3);
			if(S > 0)
			{					
				S--;
			}
			else
			{
				S = 59;
			}
			delayMS(5);
			num==0;
		}
			j1=H%10;
			j2=H/10;
			k1=M%10;
			k2=M/10;
			l1=S%10;
			l2=S/10;
			play(j2,j1,k2,k1,l2,l1);
	}
	if(qq == 2) //第二次按S1时，调分
	{
		if(S2 == 0)
		{
			while(!S2);
			if(M < 59)
			{
				M++;
			}
			else
			{
				M = 0;
			}
			num==0;
			delayMS(5);
		}
		if(S3 == 0)
		{
			while(!S3);
			if(M > 0)
			{					
				M--;
			}
			else
			{
				M = 59;
			}
			num==0;
			delayMS(5);
		}
			j1=H%10;
			j2=H/10;
			k1=M%10;
			k2=M/10;
			l1=S%10;
			l2=S/10;
			play(j2,j1,k2,k1,l2,l1);
	}
	if(qq == 3) //第三次按S1时，调时
	{
		if(S2 == 0)
		{
			while(!S2);
			if(H < 23)
			{
				H++;
			}
			else
			{
				H = 0;
			}
			num==0;
			delayMS(5);
		}
		if(S3 == 0)
		{
			while(!S3);
			if(H > 0)
			{					
				H--;
			}
			else
			{
				H = 23;
			}
			num==0;
			delayMS(5);

		}
			j1=H%10;
			j2=H/10;
			k1=M%10;
			k2=M/10;
			l1=S%10;
			l2=S/10;
			play(j2,j1,k2,k1,l2,l1);
	}
}






void main()
{
	TIM0_Init();
	TIM1_Init();
	while(1)
	{ 
		stopfunc();
		if(out == 1)
		{
			TR0 = 1;
			TR1=0;
			if(UT == 20) //1秒钟到了----20*50=1000ms
			{	
				UT = 0;
				S++;
				if(S == 60)
				{
					S=0;
					M++;
					if(M == 60)
					{
						M = 0;
						H++;
						if(H == 24) //24小时制
						{
							H = 0;
						}
					}
				}
			}
		
			j1=H%10;
			j2=H/10;
			k1=M%10;
			k2=M/10;
			l1=S%10;
			l2=S/10;
			play(j2,j1,k2,k1,l2,l1);
		
		}
		else
		{
			buttfunc();	
		}
	}
}

void TIME() interrupt 1
{
	TH0 = (65536 - 50000)/256; //初值：2^16=65536  12M 50ms定时
	TL0 = (65536 - 50000)%256;
	UT++;
}

void Timer1_isr(void) interrupt 3 using 1
{
	TH1 = (65536-50000)/256;//晶振12M 50ms 16bit 自动重载
 	TL1 = (65536-50000)%256;
	num++;
	if(num==60)
	{
	qq=0;
	out=1;
	num=0;
	}
}




		










 

