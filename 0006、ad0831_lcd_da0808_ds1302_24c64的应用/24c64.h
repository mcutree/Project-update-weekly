#include <reg51.h>
#include <absacc.h>
#include <intrins.h>
#include "i2c.h"

#define uchar unsigned char
#define W_24C64 0xa0
#define R_24C64 0xa1

//******************24C64操作*********************//

void delay_8ms(void)
{
	uchar i;
	i = 1500;
	while(i--);
}

//写入24C64
void w_24c64_data(uchar addr_24c64_H,uchar addr_24c64_L,uchar data_w)
{
	I_start();
	if(I_send(W_24C64))
	{
		if(I_send(addr_24c64_H) && I_send(addr_24c64_L))
		{
				if(I_send(data_w))
				{
					I_stop();
				}
				else
				{
					I_stop();
				}
		}
		else
		{
			I_stop();
		}
	}
	else
	{
		I_stop();
	}
}	
//读24c64
void r_24c64_data(uchar addr_24c64_H,uchar addr_24c64_L,uchar *p_r)
{
	I_start();
	if(I_send(W_24C64))
	{
		if(I_send(addr_24c64_H) && I_send(addr_24c64_L))
		{
			I_start();
			if(I_send(R_24C64))
			{
				SDA = 1;
				*(p_r)=I_receive();
				I_clock();
				I_stop();
			}
			else
			{
				I_stop();
			}
		}
		else
		{
			I_stop();
		}
	}
	else
	{
		I_stop();
	}
}

//写入24c64序列
void w_24c64_serial(uchar addr_24c64_H,uchar addr_24c64_L,uchar *p_w)
{
	uchar i;
	I_start();
	if(I_send(W_24C64) && I_send(addr_24c64_H) && I_send(addr_24c64_L))
	{
		for(i=0;i<16;i++)
		{
			if(I_send(*(p_w+i)))
			{
				if(i==15)
				{
					I_stop();
					delay_8ms();
				}
			}
			else
			{
				I_stop();
			}
		}
	}
	else
	{
		I_stop();	
	}			
}

//读出24c64序列
void r_24c64_serial(uchar addr_24c64_H,uchar addr_24c64_L,uchar *p_r)
{
	uchar i;
	I_start();
	if(I_send(W_24C64) && I_send(addr_24c64_H) && I_send(addr_24c64_L))
	{
		I_start();
		if(I_send(R_24C64))
		{
			SDA = 1;
			for(i=0;i<16;i++)
			{
				*(p_r+i) = I_receive();
				if(i==15)
				{
					I_clock();
					I_stop();
				}
				else
				{
					I_Ack();
				}
			}
		}
		else
		{
			I_stop();
		}
	}
	else
	{
		I_stop();
	}
			
}

