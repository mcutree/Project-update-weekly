#include <absacc.h>
#include <intrins.h>
#include <reg51.h>

#define uchar unsigned char

#define DS1302_SECOND	0x80
#define DS1302_MINUTE	0x82
#define DS1302_HOUR		0x84
#define DS1302_WEEK		0x8A
#define DS1302_DAY		0x86
#define DS1302_MONTH	0x88
#define DS1302_YEAR		0x8C

sbit  DS1302_CLK = P2^6;              //实时时钟时钟线引脚 
sbit  DS1302_IO  = P2^5;              //实时时钟数据线引脚 
sbit  DS1302_RST = P2^7;              //实时时钟复位线引脚

uchar read_1302(void)		//从1302中读取一个字节
{
	uchar i,data_1302;
	for(i=0;i<8;i++)
	{
		data_1302>>=1;
		if(DS1302_IO)
		{
			data_1302|=0x80;
		}
		DS1302_CLK=1;
		DS1302_CLK=0;
	}
	return (data_1302);
}

void write_1302(uchar data_1302)//向1302中写入一个字节
{
	uchar i;
	for(i=0;i<8;i++)
	{
		DS1302_IO=(bit)(data_1302&0x01);
		DS1302_CLK=1;
		DS1302_CLK=0;
		data_1302>>=1;
	}
}
//向1302的某一地址中写入一个字节的数据
void write_all_1302(uchar addr,uchar data_1302) 
{
	DS1302_RST = 0;
	DS1302_CLK = 0;
	DS1302_RST = 1;
	write_1302(addr);
	write_1302(data_1302);
	DS1302_CLK = 1;
	DS1302_RST = 0;
}
//从1302的某一地址中读取一个字节的数据
uchar read_all_1302(uchar addr)
{
	uchar data_1302;
	DS1302_RST = 0;
	DS1302_CLK = 0;
	DS1302_RST = 1;
	write_1302(addr|0x01);
	data_1302 = read_1302();
	DS1302_CLK = 1;
	DS1302_RST = 0;
	return (data_1302);
}

void DS1302_SetProtect(bit flag)        //是否写保护
{
	if(flag)
		write_all_1302(0x8E,0x10);
	else
		write_all_1302(0x8E,0x00);
}
//停止1302时钟
void stop_1302(void)
{
	uchar i;
	i = read_all_1302(DS1302_SECOND);
	i |= 0x80;
	write_all_1302(DS1302_SECOND,i);
}
//启动1302时钟
void start_1302(void)
{
	uchar i;
	i = read_all_1302(DS1302_SECOND);
	i &= 0x7f;
	write_all_1302(DS1302_SECOND,i);
}

//读出1302的时间序列
void read_serial(uchar *j)
{
	uchar i;
	DS1302_RST = 0;
	DS1302_CLK = 0;
	DS1302_RST = 1;
	write_1302(0xbf);//0xbf为连续读出的命令代码
	for(i=0;i<8;i++)
	{
		*(j+i) = read_1302();
		nop();
	}
	DS1302_CLK = 1;
	DS1302_RST = 0;
}
//写入1302的时间序列
void write_date_time(uchar *j)
{
	uchar i;
	DS1302_RST = 0;
	DS1302_CLK = 0;
	DS1302_RST = 1;
	write_1302(0xbe);//0xbe为连续写入的命令代码
	for(i=0;i<8;i++)
	{
		write_1302(*(j+i));
	}
	DS1302_CLK = 1;
	DS1302_RST = 0;
}

