#ifndef __TOUPIAO__H
#define __TOUPIAO__H
#define uchar unsigned char
#define uint unsigned int
#include "yanshims.h"
#include "toupiao.h"
sbit k0=P1^0;
sbit k1=P1^1;
sbit k2=P1^2;
sbit k3=P1^3;
sbit k4=P1^4;
sbit k5=P1^5;
sbit k6=P1^6;
sbit k7=P1^7;
sbit zongk=P2^2;
uchar miao=30;
uchar kongzhi=0;
uchar piaoshu=0;
uchar l0,l1,l2,l3,l4,l5,l6,l7;

void fuzhi()
{
	buf[7]=miao%10;
	buf[6]=miao/10%10;
	buf[4]=piaoshu%10;
	buf[1]=8-buf[4];
}
void qingling()
{
	l0=l1=l2=l3=l4=l5=l6=l7=0;
	piaoshu=0;
	miao=30;
}
void panduan()
{
	if(k0==0&l0==0)
	{
		l0=1;
		piaoshu++;
	}
	if(k1==0&l1==0)
	{
		l1=1;
		piaoshu++;
	}
	if(k2==0&l2==0)
	{
		l2=1;
		piaoshu++;
	}
	if(k3==0&l3==0)
	{
		l3=1;
		piaoshu++;
	}
	if(k4==0&l4==0)
	{
		l4=1;
		piaoshu++;
	}
	if(k5==0&l5==0)
	{
		l5=1;
		piaoshu++;
	}
	if(k6==0&l6==0)
	{
		l6=1;
		piaoshu++;
	}
	if(k7==0&l7==0)
	{
		l7=1;
		piaoshu++;
	}
}
#endif