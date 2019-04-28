#include "d:\c51\reg51.h"
#include "d:\c51\intrins.h"


sbit LCM_RS=P3^0;
sbit LCM_RW=P3^1;
sbit LCM_EN=P3^7;

#define BUSY  		0x80              //常量定义
#define DATAPORT 	P1
#define uchar 		unsigned char
#define uint   		unsigned int
#define L			50

uchar str0[16],str1[16],count;
uint speed;
unsigned long time;

void ddelay(uint);
void lcd_wait(void);
void display();
void initLCM();
void WriteCommandLCM(uchar WCLCM,uchar BusyC);
void STR();
void account();


/*********延时K*1ms,12.000mhz**********/

void int0_isr(void) interrupt 0         /*遥控使用外部中断0,接P3.2口*/
{
    unsigned int temp;
	time=count;
    TR0=0;
	temp=TH0;
	temp=((temp << 8) | TL0);
    TH0=0x3c;
    TL0=0xaf;
	count=0;
    TR0=1;
	time=time*50000+temp;
}

void time0_isr(void) interrupt 1        /*遥控使用定时计数器1 */
{
   TH0 =0x3c;
   TL0 =0xaf;
   count++;
}

void main(void)
{
   	TMOD=0x01;                       /*TMOD T0选用方式1(16位定时) */
    IP|=0x01;                           /*INT0 中断优先*/
    TCON|=0x11;                         /*TCON  EX0下降沿触发,启动T0*/
    IE|=0x83;  
    TH0=0x3c;
    TL0=0xaf;
  
	initLCM();
   	WriteCommandLCM(0x01,1);		    //清显示屏
	for(;;)
	{
		account();
		display();
	}
}

void account()
{
	unsigned long a; 
	if (time!=0)
	{
		a=L*360000000/time;
	}
	speed=a;
}



void STR()
{
	str0[0]='S';
	str0[1]='p';
	str0[2]='e';
    str0[3]='e';
	str0[4]='d';
	str0[5]=' ';	
	str0[6]=(speed%100000)/10000+0x30;
	str0[7]=(speed%10000)/1000+0x30;
	str0[8]=(speed%1000)/100+0x30;
	str0[9]='.';
	str0[10]=(speed%100)/10+0x30;
	str0[11]=speed%10+0x30;
	str0[12]='k';
	str0[13]='m';
	str0[14]='/';
	str0[15]='h';
}

void ddelay(uint k)
{
    uint i,j;
    for(i=0;i<k;i++)
    {
        for(j=0;j<60;j++)
        	{;}
    }
}
/**********写指令到LCD子函数************/

void WriteCommandLCM(uchar WCLCM,uchar BusyC)
{
    if(BusyC)lcd_wait();
	DATAPORT=WCLCM;
    LCM_RS=0;                   /* 选中指令寄存器*/
    LCM_RW=0;               	// 写模式
    LCM_EN=1;
	_nop_();
	_nop_();
	_nop_();
    LCM_EN=0;

}

/**********写数据到LCD子函数************/

void WriteDataLCM(uchar WDLCM)
{
    lcd_wait( );            //检测忙信号
	DATAPORT=WDLCM;
    LCM_RS=1;               /* 选中数据寄存器  */
    LCM_RW=0;           	// 写模式
    LCM_EN=1;
    _nop_();
	_nop_();
	_nop_();
    LCM_EN=0;
}

/***********lcd内部等待函数*************/

void lcd_wait(void)
{
    DATAPORT=0xff;	     //读LCD前若单片机输出低电平,而读出LCD为高电平,则冲突,Proteus仿真会有显示逻辑黄色
	LCM_EN=1;
    LCM_RS=0;
    LCM_RW=1;
    _nop_();
    _nop_();
	_nop_();
    while(DATAPORT&BUSY)
	{  LCM_EN=0;
	   _nop_();
	   _nop_();
	   LCM_EN=1;
	   _nop_();
	   _nop_();
	}
   	LCM_EN=0;

}

/**********LCD初始化子函数***********/
void initLCM( )
{
	DATAPORT=0;
	ddelay(15);
	WriteCommandLCM(0x38,0);    //三次显示模式设置，不检测忙信号
    ddelay(5);
    WriteCommandLCM(0x38,0);
    ddelay(5);
    WriteCommandLCM(0x38,0);
    ddelay(5);

    WriteCommandLCM(0x38,1);    //8bit数据传送，2行显示，5*7字型，检测忙信号
    WriteCommandLCM(0x08,1);    //关闭显示，检测忙信号
    WriteCommandLCM(0x01,1);    //清屏，检测忙信号
    WriteCommandLCM(0x06,1);    //显示光标右移设置，检测忙信号
    WriteCommandLCM(0x0c,1);    //显示屏打开，光标不显示，不闪烁，检测忙信号
}

/****显示指定坐标的一个字符子函数****/

void DisplayOneChar(uchar X,uchar Y,uchar DData)
{
    Y&=1;
    X&=15;
    if(Y)X|=0x40;               //若y为1（显示第二行），地址码+0X40
    X|=0x80;                    //指令码为地址码+0X80
    WriteCommandLCM(X,0);
    WriteDataLCM(DData);
}

/*******显示指定坐标的一串字符子函数*****/

void DisplayListChar(uchar X,uchar Y,uchar *DData)
{
    uchar ListLength=0;
    Y&=0x01;
    X&=0x0f;
    while(X<16)
    {
        DisplayOneChar(X,Y,DData[ListLength]);
        ListLength++;
        X++;
    }
}


void display()
{

	STR(); 
	DisplayListChar(0,0,str0);
   	DisplayListChar(0,1,str1);
}
