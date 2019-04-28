#include <absacc.h>
#include <intrins.h>
#include <reg51.h>
#include "24c64.h"
#include "lcd_show.h"

sbit key_1 = P0^7;
sbit key_2 = P0^6;
sbit key_3 = P0^5;
sbit key_4 = P0^4;

void key_delay(uchar i)
{
	while(i--);
}

void key_1_f(void)
{
	w_24c64_data(0x00,0x00,a);
}
void key_2_f(void)
{
	uchar *p_c4;
	uchar c1,c2,c3,c4;
	p_c4 = &c4;
	r_24c64_data(0x00,0x00,p_c4);
	c1 = c4/100;
	c2 = (c4%100)/10;
	c3 = (c4%100)%10;
	ShowNumber(4,0,c1);
	ShowNumber(4,8,c2);
	ShowNumber(4,16,c3);
}
void key_3_f(void)
{

}

void judge_key(void)
{
	if((!key_1) || (!key_2) || (!key_3))
	{
		key_delay(2000);
		if(!key_1)
		{
			while(!key_1)
			{
				key_delay(1000);
			}
			key_1_f();
		}
		else if(!key_2)
		{
			while(!key_2)
			{
				key_delay(1000);
			}
			key_2_f();
		}
		else if(!key_3)
		{
			while(!key_3)
			{
				key_delay(1000);
			}
			key_3_f();
		}
		else
		{
		}
	}
}


