#ifndef __SHUMAGUAN__H
#define __SHUMAGUAN__H
#include "shumaguan.h"
#include "yanshims.h"
#define uchar unsigned char
#define uint unsigned int
uchar code tab[]={
	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff
};
uchar code wei[]={
	0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f
};
uchar  buf[]={
	10,10,10,10,10,10,10,10,
};
sbit dx=P2^0;
sbit px=P2^1;
void xianshi(uchar *buf)
{
	uchar i;
	for(i=0;i<8;i++)
	{
		px=0;
		dx=0;
		P0=~tab[*buf];
		dx=1;
		yanshi(1);
		dx=0;
		P0=wei[i];
		px=1;
		yanshi(1);
		P0=0xff;
		px=0;
		buf++;
	}
}
#endif