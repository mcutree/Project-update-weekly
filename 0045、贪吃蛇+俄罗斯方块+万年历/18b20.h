#ifndef _DS18B20_H__
#define _DS18B20_H__
#define uchar unsigned char
#define uint unsigned int	   //宏定义
uchar flagg=0;
sbit DQ=P3^4;
uchar temp[3];
void delayfor(uchar i)
{
  for(i;i>0;i--);
}
void delay11us(uint k)
{
  while(k--);
}
/**ds18b20**/
void ds18b20_init(void)
{
   EA=0;
   DQ=1;
   delayfor(8);
   DQ=0;
   delayfor(70);  
   DQ=1;
   delayfor(25);
   EA=1;
 }
/**ds18b20读一个字节**/
uchar ds18b20_readchar(void)
{
  	uchar i=0;
	uchar dat = 0;
	EA=0;
	for(i=8;i>0;i--)
	 {
		  DQ = 0; // 给脉冲信号
		  dat>>=1;
		  DQ = 1; // 给脉冲信号
		  if(DQ)
		  dat|=0x80;
		  
		  delay11us(10);
		 
	 }
	  EA=1;
 	return(dat);
}
/**ds18b20写一个字节**/
ds18b20_writechar(uchar dat)
{
 uchar i=0;
 EA=0;
 for (i=8; i>0; i--)
  {
    DQ = 0;
    DQ = dat&0x01;
	
    delay11us(10);

    DQ = 1;
    dat>>=1;
  }
 EA=1;
}
/**读出温度**/
uint readtemperature(void)
{
	uchar a=0;
	uchar b=0;
	uint  t=0;
	ds18b20_init();
	ds18b20_writechar(0xCC); // 跳过读序号列号的操作
	ds18b20_writechar(0x44); // 启动温度转换
	delay11us(100);
	ds18b20_init();
	ds18b20_writechar(0xCC); //跳过读序号列号的操作
	ds18b20_writechar(0xBE); //读取温度寄存器等（共可读9个寄存器） 前两个就是温度
	a=ds18b20_readchar();
	b=ds18b20_readchar();
	if((b*256+a)>63488)	
	  {
			  t=~(b*256+a)+1; t=t*25;flagg=1;//取反加1
	   }  
	else
	  { 
			 t = (b*256+a)*25;flagg=0;
	  }	
	return(t>>2);
 }
 /**温度数值处理**/
 void gettemperature(void)
 {
    static uint te=0xffff;
   	uint realtemp;
	realtemp=readtemperature();
	if(te!=realtemp)
	{
	temp[0]=realtemp/1000;
	temp[1]=(realtemp/100)%10;
	temp[2]=(realtemp/10)%10;
	te=realtemp;
	}
 }
  #endif
