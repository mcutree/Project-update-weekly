#include <at89x51.h>//用AT89C51时就用这个头文件
//#include <reg52.h>//用华邦W78E58B时必须用这个头文件
#include <absacc.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <DS18B20.h>
#include "LCD1602.h"			////液晶显示头文件
//sbit DQ = P3^4;					//定义DQ引脚为P3.4
unsigned char t[2],*pt;				//用来存放温度值,测温程序就是通过这个数组与主函数通信的
unsigned char  TempBuffer1[9]={0x2b,0x31,0x32,0x32,0x2e,0x30,0x30,0x43,'\0'};
								//显示实时温度,上电时显示+125.00C
unsigned char  TempBuffer0[17]={0x54,0x48,0x3a,0x2b,0x31,0x32,0x35,0x20,
								0x54,0x4c,0x3a,0x2b,0x31,0x32,0x34,0x43,'\0'};
								//显示温度上下限,上电时显示TH:+125 TL:+124C							
unsigned char code dotcode[4]={0,25,50,75};
/***因显示分辨率为0.25,但小数运算比较麻烦,故采用查表的方法*******
再将表值分离出十位和个位后送到十分位和百分位********************/


void covert0( unsigned char TH, unsigned char TL)	//将温度上下限转换为LCD显示的数据
{ 
   if(TH>0x7F)                    //判断正负,如果为负温,将其转化为其绝对值
   {
    TempBuffer0[3]=0x2d;	     //0x2d为"-"的ASCII码
	TH=~TH;
	TH++;
   }
   else TempBuffer0[3]=0x2b;	//0x2B为"+"的ASCII码

   if(TL>0x7f)
   {
   TempBuffer0[11]=0x2d;	     //0x2d为"-"的ASCII码
   TL=~TL+1;
   }
   else TempBuffer0[11]=0x2b;	//0x2B为"+"的ASCII码

  TempBuffer0[4]=TH/100+0x30;		             //分离出TH的百十个位
  if( TempBuffer0[4]==0x30) TempBuffer0[4]=0xfe; //百位数消隐
  TempBuffer0[5]=(TH%100)/10+0x30;				//分离出十位
  TempBuffer0[6]=(TH%100)%10+0x30;	 			//分离出个位
  TempBuffer0[12]=TL/100+0x30;		             //分离出TL的百十个位
  if( TempBuffer0[12]==0x30) TempBuffer0[12]=0xfe; //百位数消隐
  TempBuffer0[13]=(TL%100)/10+0x30;				//分离出十位
  TempBuffer0[14]=(TL%100)%10+0x30;	 			//分离出个位
}


void covert1(void)	//将温度转换为LCD显示的数据
{
   unsigned char x=0x00,y=0x00;
   t[0]=*pt;
   pt++;
   t[1]=*pt;
   if(t[1]>0x07)                    //判断正负温度
   {
    TempBuffer1[0]=0x2d;	     //0x2d为"-"的ASCII码
	t[1]=~t[1];			 /*下面几句把负数的补码*/
	t[0]=~t[0]; 		 /* 换算成绝对值*********/
	x=t[0]+1;				 /***********************/
	t[0]=x;					 /***********************/
	if(x>255)                /**********************/
	t[1]++;				 /*********************/
   }
   else TempBuffer1[0]=0x2b;	//0xfe为变"+"的ASCII码
  t[1]<<=4;		//将高字节左移4位
  t[1]=t[1]&0x70;		//取出高字节的3个有效数字位
  x=t[0];					//将t[0]暂存到X,因为取小数部分还要用到它
  x>>=4;					//右移4位
  x=x&0x0f;					//和前面两句就是取出t[0]的高四位	
  t[1]=t[1]|x;			//将高低字节的有效值的整数部分拼成一个字节
  TempBuffer1[1]=t[1]/100+0x30;		             //+0x30 为变 0~9 ASCII码
   if( TempBuffer1[1]==0x30) TempBuffer1[1]=0xfe; //百位数消隐
  TempBuffer1[2]=(t[1]%100)/10+0x30;				//分离出十位
  TempBuffer1[3]=(t[1]%100)%10+0x30;	 			//分离出个位
  t[0]=t[0]&0x0c;							//取有效的两位小数
  t[0]>>=2;									//左移两位,以便查表
  x=t[0];										
  y=dotcode[x];									//查表换算成实际的小数
  TempBuffer1[5]=y/10+0x30;							//分离出十分位
  TempBuffer1[6]=y%10+0x30;							//分离出百分位
}			

void delay(unsigned char i)
{
	while(i--);
}

main()
{
 unsigned char TH=110,TL=-20;    					//下一步扩展时可能通过这两个变量,调节上下限
       									 //测温函数返回这个数组的头地址
 while(1)
 {	
    pt=ReadTemperature(TH,TL,0x3f);		 //上限温度-22,下限-24,分辨率10位,也就是0.25C
										 //读取温度,温度值存放在一个两个字节的数组中,
	delay(100); 
	covert1();
	covert0(TH,TL);
	LCD_Initial();							//第一个参数列号,第二个为行号,为0表示第一行
											//为1表示第二行,第三个参数为显示数据的首地址
	LCD_Print(0,0,TempBuffer0);	
	LCD_Print(0,1,TempBuffer1); 				
 }
}
  



