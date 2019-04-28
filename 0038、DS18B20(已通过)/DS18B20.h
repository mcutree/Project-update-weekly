#include <at89x51.h>//用AT89C51时就用这个头文件
//#include <reg52.h>//用华邦W78E58B时必须用这个头文件
sbit DQ = P3^4;			//定义DQ引脚为P3.4
/***********ds18b20延迟子函数（晶振12MHz ）*******/ 
/************DS18B20对时间要求很严,但只能长不能短
*************在11.0592M下也行,因为时间长些********/
void delay_18B20(unsigned int i)
{
	while(i--);
}

/**********ds18b20初始化函数**********************/

void Init_DS18B20(void) 
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

/***********ds18b20读一个字节**************/  

unsigned char ReadOneChar(void)
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

/*************ds18b20写一个字节****************/  

void WriteOneChar(unsigned char dat)
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

/**************读取ds18b20当前温度************/

unsigned char *ReadTemperature(char TH,char TL,unsigned char RS)
{	unsigned char tt[2];
	Init_DS18B20();
	WriteOneChar(0xCC);    	// 跳过读序号列号的操作
	WriteOneChar(0x4E); 	// //写入"写暂存器"命令,修改TH和TL和分辩率配置寄存器
							//先写TH,再写TL,最后写配置寄存器
	WriteOneChar(TH);		//写入想设定的温度报警上限
	WriteOneChar(TL);		//写入想设定的温度报警下限
	WriteOneChar(RS);		//写配置寄存器,格式为0 R1 R0 1,1 1 1 1
							//R1R0=00分辨率娄9位,R1R0=11分辨率为12位

	delay_18B20(80);       // this message is wery important
	Init_DS18B20();
	WriteOneChar(0xCC);    	// 跳过读序号列号的操作
	WriteOneChar(0x44); 	// 启动温度转换

	delay_18B20(80);       // this message is wery important
	Init_DS18B20();
	WriteOneChar(0xCC); 	//跳过读序号列号的操作
	WriteOneChar(0xBE); 	//读取温度寄存器等（共可读9个寄存器） 前两个就是温度
	delay_18B20(80);

	tt[0]=ReadOneChar();    	//读取温度值低位
	tt[1]=ReadOneChar();   		//读取温度值高位
	return(tt);
}