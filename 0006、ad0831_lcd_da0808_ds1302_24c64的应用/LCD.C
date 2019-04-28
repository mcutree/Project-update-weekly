#include <absacc.h>
#include <intrins.h>
#include <reg51.h>
#include "HZcode.h"
#include "LCD.h"
#include "1302.h"
#include "key.h"
#include "adc0831.h"

uchar time0_count; 	//time0计数器

//time0初始化
void time0_init(void)
{
	EA = 1;
	ET0 = 1;
	TMOD = 0x01;
	PT0 = 1;
	TH0 = 0x3C;
	TL0 = 0xB0;
	TR0 = 1;
}

void main(void)
{
	
	I_init();
	InitLCD();
	time0_init();
	show_hz();
	show_date_time();
	while(1)
	{
		judge_key();
	}
		
}
void time0_interrupt(void)interrupt 1
{
	TH0 = 0x3c;
	TL0 = 0xb0;
	time0_count++;
	if(time0_count==20)
	{
		time0_count=0;
		show_date_time();
 		a = readadc();
		b1 = a/100;
		b2 = (a%100)/10;
		b3 = (a%100)%10;
		show_ad();
		P3 = a;   //进行数模转换
	}
}
