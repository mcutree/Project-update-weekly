#include <reg52.h>//头文件
#include "yanshims.h"
#define uint unsigned int//宏定义
#define uchar unsigned char
sbit k=P3^0;//总控制按键接P3.0端口
sbit g1=P3^4;
sbit g2=P3^5;
uchar code tab[]={
0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90
};
uchar buf[]={
	1,0
};
uchar miao=10;
void fuzhi()
{
	buf[0]=miao/10%10;
	buf[1]=miao%10;
}
void kai(a)
{
	switch(a)
	{
		case 0:g1=g2=0;break;
		case 1:g1=1;g2=0;break;
		case 2:g1=0;g2=1;break;
		default:break;
	}
}
void xianshi()
{
	kai(1);
	P0=tab[buf[0]];
	yanshi(1);
	kai(2);
	P0=tab[buf[1]];
	yanshi(1);
	kai(0);
}
mian()
{
	while(1)
	{
	xianshi();
	}
}
