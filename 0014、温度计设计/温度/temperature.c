#include "reg51.h"

char disp[11]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40};
char disp_dot[11]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,0xc0};

sbit DQ = P1^3;   //定义通信端口 

//晶振12MHz  
void delay_18B20(unsigned int i)
{
	while(i--);
}

//初始化函数
Init_DS18B20(void) 
{
	 unsigned char x=0;
	 DQ = 1;          //DQ复位
	 delay_18B20(8);  //稍做延时
	 DQ = 0;          //单片机将DQ拉低
	 delay_18B20(80); //精确延时 大于 480us
	 DQ = 1;          //拉高总线
	 delay_18B20(14);
	 x=DQ;            //稍做延时后 如果x=0则初始化成功 x=1则初始化失败
	 delay_18B20(20);
}


//读一个字节  
ReadOneChar(void)
{
	unsigned char i=0;
	unsigned char dat = 0;
	for (i=8;i>0;i--)
	 {
		  DQ = 0; // 给脉冲信号
		  dat>>=1;
		  DQ = 1; // 给脉冲信号
		  if(DQ)
		  dat|=0x80;
		  delay_18B20(4);
	 }
 	return(dat);
}

//写一个字节  
WriteOneChar(unsigned char dat)
{
 unsigned char i=0;
 for (i=8; i>0; i--)
 {
  DQ = 0;
  DQ = dat&0x01;
  delay_18B20(5);
  DQ = 1;
  dat>>=1;
 }
}

//读取温度
ReadTemperature(void)
{
	unsigned char a=0;
	unsigned char b=0;
	unsigned int  t=0;
	
	Init_DS18B20();
	WriteOneChar(0xCC); // 跳过读序号列号的操作
	WriteOneChar(0x44); // 启动温度转换
	delay_18B20(100);
	Init_DS18B20();
	WriteOneChar(0xCC); //跳过读序号列号的操作
	WriteOneChar(0xBE); //读取温度寄存器等（共可读9个寄存器） 前两个就是温度
	a=ReadOneChar();
	b=ReadOneChar();
		
	//传感器返回值除16得实际温度值
	//为了得到2位小数位，先乘100，再除16，考虑整型数据长度，
	//技巧处理后先乘25，再除4，除4用右移实现

	t = (b*256+a)*25;	
	return( t >> 2  );
}

main()
{
	unsigned int tmp;
	unsigned char counter;
	while(1)
	{
		//温度测量频率没有必要太高，太高反而影响数码显示
		//所以用计数器加以控制
		if(counter-- == 0)
		{
			tmp = ReadTemperature(); 			
			counter = 20;
		}

		P2 = 0xff;
		P0 = disp[tmp%10];
		P2 = 0xfb;
		delay_18B20(1000);
		P2 = 0xff;
		P0 = disp[tmp/10%10];
		P2 = 0xf7;
		delay_18B20(1000);
		P2 = 0xff;
		P0 = disp_dot[tmp/100%10];
		P2 = 0xef;
		delay_18B20(1000);
		P2 = 0xff;
		P0 = disp[tmp/1000%10];
		P2 = 0xdf;
		delay_18B20(1000);
	}
}