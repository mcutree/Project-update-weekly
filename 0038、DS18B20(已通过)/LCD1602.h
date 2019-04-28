#include <at89x51.h>//用AT89C51时就用这个头文件
//#include <reg52.h>//用华邦W78E58B时必须用这个头文件
#include <intrins.h>
//注意那个LCD_Wait()函数,它是判"忙"标志的,在实际硬件要把注掉的那种打开
//Port Definitions**********************************************************
sbit LcdRs		= P2^0;
sbit LcdRw		= P2^1;
sbit LcdEn  	= P2^2;
sfr  DBPort 	= 0x80;		//P0=0x80,P1=0x90,P2=0xA0,P3=0xB0.数据端口

//内部等待函数**************************************************************************
unsigned char LCD_Wait(void)
{
	LcdRs=0;
	LcdRw=1;	_nop_();
	LcdEn=1;	_nop_();
	//while(DBPort&0x80);//在用Proteus仿真时，注意用屏蔽此语句，在调用GotoXY()时，会进入死循环，
						 //可能在写该控制字时，该模块没有返回写入完备命令，即DBPort&0x80==0x80
						 //实际硬件时打开此语句
	LcdEn=0;
	return DBPort;		
}
//向LCD写入命令或数据************************************************************
#define LCD_COMMAND			0      // Command
#define LCD_DATA			1      // Data
#define LCD_CLEAR_SCREEN	0x01      // 清屏
#define LCD_HOMING  		0x02      // 光标返回原点
void LCD_Write(bit style, unsigned char input)
{
	LcdEn=0;
	LcdRs=style;
	LcdRw=0;		_nop_();
	DBPort=input;	_nop_();//注意顺序
	LcdEn=1;		_nop_();//注意顺序
	LcdEn=0;		_nop_();
	LCD_Wait();	
}

//设置显示模式************************************************************
#define LCD_SHOW			0x04    //显示开
#define LCD_HIDE			0x00    //显示关	  

#define LCD_CURSOR			0x02 	//显示光标
#define LCD_NO_CURSOR		0x00    //无光标		     

#define LCD_FLASH			0x01    //光标闪动
#define LCD_NO_FLASH		0x00    //光标不闪动

void LCD_SetDisplay(unsigned char DisplayMode)
{
	LCD_Write(LCD_COMMAND, 0x08|DisplayMode);	
}

//设置输入模式************************************************************
#define LCD_AC_UP			0x02
#define LCD_AC_DOWN			0x00      // default

#define LCD_MOVE			0x01      // 画面可平移
#define LCD_NO_MOVE			0x00      //default

void LCD_SetInput(unsigned char InputMode)
{
	LCD_Write(LCD_COMMAND, 0x04|InputMode);
}


//初始化LCD************************************************************
void LCD_Initial()
{
	LcdEn=0;
	LCD_Write(LCD_COMMAND,0x38);           //8位数据端口,2行显示,5*7点阵
	LCD_Write(LCD_COMMAND,0x38);
	LCD_SetDisplay(LCD_SHOW|LCD_NO_CURSOR);    //开启显示, 无光标
	LCD_Write(LCD_COMMAND,LCD_CLEAR_SCREEN);   //清屏
	LCD_SetInput(LCD_AC_UP|LCD_NO_MOVE);       //AC递增, 画面不动
}

//************************************************************************
void GotoXY(unsigned char x, unsigned char y)
{
	if(y==0)
		LCD_Write(LCD_COMMAND,0x80|x);
	if(y==1)
		LCD_Write(LCD_COMMAND,0x80|(x-0x40));
}

void Print(unsigned char *str)
{
	while(*str!='\0')
	{
		LCD_Write(LCD_DATA,*str);
		str++;
	}
}

void LCD_Print(unsigned char x, unsigned char y, unsigned char *str)
{
  GotoXY(x,y);
  Print(str);
}

