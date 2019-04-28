#include <absacc.h>
#include <intrins.h>
#include <reg51.h>

uchar date_buf[8];	//存储1032的数据
uchar b1,b2,b3,a;  	//从adc0831转换后的数字值，a为二进制数据，
					//b1、b2、b3为对应于百位，十位与个位的十进制数

void show_date(void)
{
	uchar i,j;
	j = 16;
	//year
	i = date_buf[6]>>4;
	i &= 0x0f;
	ShowNumber(4,16+j,i);
	i = date_buf[6] & 0x0f;
	ShowNumber(4,24+j,i);
	ShowChina(4,32+j,12);
	//month
	i = date_buf[4]>>4;
	i &= 0x01;
	ShowNumber(4,48+j,i);
	i = date_buf[4] & 0x0f;
	ShowNumber(4,56+j,i);
	ShowChina(4,64+j,13);
	//day
	i = date_buf[3]>>4;
 	i &= 0x03;
	ShowNumber(4,80+j,i);
	i = date_buf[3] & 0x0f;
	ShowNumber(4,88+j,i);
	ShowChina(4,96+j,14);
}

void show_time(void)
{
	uchar i,j;
	j = 32;
	//hour
	i = date_buf[2]>>4;
	i &= 0x03;
	ShowNumber(6,0+j,i);
	i = date_buf[2] & 0x0f;
	ShowNumber(6,8+j,i);
	ShowChina(6,16+j,15);
	//minute
	i = date_buf[1]>>4;
	i &= 0x07;
	ShowNumber(6,32+j,i);
	i = date_buf[1] & 0x0f;
	ShowNumber(6,40+j,i);
	ShowChina(6,48+j,16);
	//second
	i = date_buf[0]>>4;
 	i &= 0x07;
	ShowNumber(6,64+j,i);
	i = date_buf[0] & 0x0f;
	ShowNumber(6,72+j,i);
	ShowChina(6,80+j,17);
}

void show_hz(void)
{
	ShowChina(0,0,0);
	ShowChina(0,16,1);
	ShowChina(0,32,2);
	ShowChina(0,48,3);
	ShowChina(0,64,4);
	ShowChina(0,80,5);
	ShowChina(0,96,6);
	ShowChina(0,112,7);
	ShowChina(2,32,8);
	ShowChina(2,48,9);
	ShowChina(2,64,10);
	ShowChina(2,80,11);
}

void show_date_time(void)
{
	uchar *j;
	j = date_buf;
	read_serial(j);
	show_date();
	show_time();
}

void show_ad(void)
{
	ShowNumber(6,0,b1);
	ShowNumber(6,8,b2);
	ShowNumber(6,16,b3);
}