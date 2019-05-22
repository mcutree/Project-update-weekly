#include<reg51.h>
#define INT8U   unsigned char
#define INT16U  unsigned int
#define uchar unsigned char 
#define uint unsigned int
#define ulong unsigned long

sbit ADCS=P3^0;
sbit ADRD=P3^1;
sbit ADWR=P3^2;
sbit OUT=P2^7;

sbit LED=P2^0;
#define  ad1_7  P0

bit flag;



unsigned int Num1=0,Num2=0,Num3=0,Num4=0;

uchar code table_dm[11]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};//共阳极数码管断码表
uchar code table_dd[10]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};//个位带小数点的共阳极数码管断码表断码表
uint Display_Buffer1[2]={0,0};
uint Display_Buffer2[2]={0,0};
uint Display_Buffer3[2]={0,0};
uint Display_Buffer4[2]={0,0};
uint a,b;
uchar e,n;

void int_mcu(void)//初始化单片机，通过串口通信?
{
EA=1;
ES=1;
TMOD=32;
SCON=80;
PCON=0;
TL1=0xfd;
TH1=0xfd;
TR1=1;

}


void delayms(uint xms)
{
	int i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}
void start_adc0804(void)
 {      
 		ADCS=0;                        
 		ADWR=0;
		delayms(1);
 		ADWR=1; 
		ADCS=1;        
		delayms(1); 
 }

read_ad()
{       
	 uchar ad_data;         
	 ad1_7=0xff;          
	 ADCS=0;                   
	 ADRD=0;                    
	 delayms(1);          
	 ad_data=ad1_7;         
	 ADRD=1;
	 ADCS=1;           
	 
	 return(ad_data);
}

void scan1(uint data_ad1)
{ 
	(uint)Display_Buffer1[0]=data_ad1/10;	
	(uint)Display_Buffer1[1]=data_ad1%10;   
}

void system_Ini()
{
     TMOD = 0x00; //选择模式0  13位计数 最大计数8192
	 TH0 = (8192 - 1000)/32;
	 TL0 = (8192 - 1000)%32	;
     IE = 0x8A;   //中断	
     TR0  = 1;    //开启T0定时器
}




void main(void)
{
	unsigned int t=0;
	system_Ini();
  	LED=1;	
	OUT=1;
	while(1)
	{
	  	  
			if(Num1>50)
			{
				Num1=0;
				start_adc0804(); 
				a= read_ad();
				if(a>127)
				{
				LED=0;
				OUT=0;
				}
				else
				{
				LED=1;
				OUT=1;
				}

			}
			 

			 
	 


	}


}

 void T0zd(void) interrupt 1      //3定时器1的中断号  1定时器0的中断号 0外部中断1 2外部中断2  4串口中断
{

	 
	 TH0 = (8192 - 1500)/32;
	 TL0 = (8192 - 1500)%32;  
	 Num1++; 
	 Num2++;
	 Num3++;

}