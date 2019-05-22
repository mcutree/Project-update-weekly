#include "string.h"
#include "delay.h"
#include "uart.h"
#define MAIN_Fosc		22118400L	//定义主时钟
#define	RX1_Lenth		32			//串口接收缓冲长度
#define	BaudRate1		115200UL	//选择波特率


#define	Timer1_Reload	(65536UL -(MAIN_Fosc / 4 / BaudRate1))		//Timer 1 重装值， 对应300KHZ
#define	Timer2_Reload	(65536UL -(MAIN_Fosc / 4 / BaudRate1))		//Timer 2 重装值， 对应300KHZ

#include	"STC15Fxxxx.H"
#define uchar unsigned char
#define uint  unsigned int
#define ulong  unsigned long




//u8 Time_count=0;
bdata u8 Flag;//定时器标志位
sbit Timer0_start =Flag^0;	//定时器0延时启动计数器
sbit Uart2_Start  =Flag^1;	//串口2开始接收数据
sbit Uart2_End		=Flag^2;	//串口2接收数据结束

bit flag0=0;


sbit SDA1=P1^4;		//数据串入595引脚
sbit SCL1=P1^5;		//595的位移时钟引脚

sbit SCL11=P1^2;		//数据串入595引脚

sbit SCL2=P1^3;		//595的并出时钟引脚



sbit key=P1^7;		//595的并出时钟引脚



unsigned char code duan[]={	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
                     0x80,0x90,0x83,0xc6,0xa1,0x86,0x8e };//共阳数码管低电平点亮
unsigned char code wei[]={0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};//高电平位选
unsigned char Data1,Data2,Data3,Data4,Data5;
unsigned char cent[10]={0,0,0,0,0,0,0,0,0,0};
unsigned char cent1[10]={0,0,0,0,0,0,0,0,0,0};
unsigned char receive[2]={0,0};



/*************	本地函数声明	**************/
void GPIO_config(void); //端口初始化配置
void Timer0Init(void);  //定时器0初始化
void CLR_Buf2(void);    //清除串口2接收缓存
u8 Find(u8 *a);         //查找字符串
void Second_AT_Command(u8 *b,u8 *a,u8 wait_time); //发送AT指令函数
void Set_Pdu_Mode(void);//设置短信模式PDU
void Wait_CREG(void);   //查询等待模块注册成功
void Send_Pdu_Sms(void);//发送一条中文短信


void Delay(void)                       //延时函数
{
 unsigned char i,j;
 for(i=133;i>0;i--)
 for(j=6;j>0;j--);
}
/*********************************/
void W595_in(unsigned char Data)   //完成一个字节8位的输入
{
  unsigned char i;
  for(i=0;i<8;i++)
  {
   SCL1=0;			  //拉低位移时钟信号线
   SDA1=Data&0x80;	 //将最高位赋值给SDA1，即595数据串入引脚
   Data<<=1;		 //数据左移一位
   SCL1=1;			 //拉高位移时钟信号线 ，完成一位的存储
  }
}

void W595_in1(unsigned char Data1)   //完成一个字节8位的输入
{
  unsigned char i;
  for(i=0;i<8;i++)
  {
   SCL11=0;			  //拉低位移时钟信号线
   SDA1=Data1&0x80;	 //将最高位赋值给SDA1，即595数据串入引脚
   Data1<<=1;		 //数据左移一位
   SCL11=1;			 //拉高位移时钟信号线 ，完成一位的存储
  }
}
/*****************************/
void W595_out(void)      //完成并出数据功能
{
 SCL2=0;		  //拉低并出时钟信号线
 _nop_();
 SCL2=1;		  //拉高并出时钟信号线

}
/**************************/

void Disp(uchar *s)	
{
	unsigned char i;
	for(i=0;i<10;i++)
	W595_in(wei[s[9-i]]);
	W595_out();
	Delay();
}
void Disp1(uchar *w)	
{
	unsigned char i;
	for(i=0;i<10;i++)
	W595_in1(wei[w[9-i]]);
	W595_out();
	Delay();
}
void main(void)
{
	//GPIO_config();
	Timer0Init();


	EA=1;	//开总中断
	Data1=76;
	
	flag0=1;
	
	while(1)
	{
		unsigned char i;
		if(key==0&&flag0==0)
		{
		 	flag0=1;
			Data1++;	
			while(key==0);
		}

		//if(flag0==1&&receive[0]<=78)
		if(flag0==1&&Data1<=78)
		{  	
			
			ES=1;
			flag0=0;
			Data2=(Data1-1)/8;
			Data3=((Data1-1)%8+1);
	  		cent[Data2]=Data3;

			
			Disp(cent);
			receive[0]=0;
			for(i=0;i<10;i++)
			cent[i]=0;
		}
		else if(flag0==1&&Data1>78&&Data1<157)
		{  
			
			ES=1;
			flag0=0;

			Data2=(Data1-79)/8;
			Data3=((Data1-79)%8+1);
	  		cent1[Data2]=Data3;

			
			Disp1(cent1);
			receive[0]=0;
			for(i=0;i<10;i++)
			cent1[i]=0;
		}


		else if(flag0==1&&receive[0]>156)
		{
		 	ES=1;
			receive[0]=0;
			flag0=0;
		}

		
		
	}
	
}

/*******************************************************************************
* 函数名 : Uart1 
* 描述   : 串口1中断服务入口函数
* 输入   : 
* 输出   : 
* 返回   : 
* 注意   : 
*******************************************************************************/

void	GPIO_config(void)
{
		P3M1 &= 0XC3;  //配置P32~P35为推挽输出
		P3M0 |=	~0XC3;
	
}
void Timer0Init(void)		//20毫秒@22.1184MHz
{

	S1_8bit();				//8位数据
	S1_USE_P30P31();		//UART1 使用P30 P31口	默认


	AUXR &= ~(1<<4);	//Timer stop		波特率使用Timer2产生
	AUXR |= 0x01;		//S1 BRT Use Timer2;
	AUXR |=  (1<<2);	//Timer2 set as 1T mode
	TH2 = (u8)(Timer2_Reload >> 8);
	TL2 = (u8)Timer2_Reload;
	AUXR |=  (1<<4);	//Timer run enable

	REN = 1;	//允许接收
	ES  = 1;	//允许中断

	EA = 1;		//允许全局中断
	


}

void UART1_int (void) interrupt UART1_VECTOR
{
	
	if(RI==1)
	{
		static unsigned char count;//串口接收计数的变量
		receive[count]=SBUF;
		flag0=1;	
		RI=0;//手动清某个寄存器，大家都懂的
	 	ES  = 0;
	}
	if(TI)
	{
		TI = 0;
	}


}




