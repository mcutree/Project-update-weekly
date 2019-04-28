#ifndef	_PWLOCK_H 		// 防止PWLock.h被重复引用

#define	_PWLOCK_H

#include <reg52.h>
#include <absacc.h>
#include <stdio.h>	
#include <math.h>

#define uchar unsigned char
#define uint unsigned int

uchar px;
uint a;
uint b;
uint c;                          //为0XFF
uint i;
uchar digbit;                    // 字位
uchar dy;				
uchar wordbuf[2];				// 字型码缓冲区
uchar count;					// 位计数
uchar pwbuf[2];					// 输入数字存储区
bit enterflag;					// 确认键按下与否标志
bit lh;
bit pwflag;						// 密码正确与否标志
bit showflag;					// 数码管显示与否标志

sbit P20=P2^0;
sbit P21=P2^1;

void display(void);				// 显示函数

#endif

//#include "PWLock.h"

/* 键消抖延时函数 */
void delay(void)
{
	uint i;
	for (i=4000;i>0;i--);
}


/* 键扫描函数 */
uchar keyscan(void)
{
	uchar scancode,tmpcode;
	P1 = 0xf0;			 					// 发全0行扫描码
	if ((P1&0xf0)!=0xf0)					// 若有键按下
	{
		delay();							// 延时去抖动
		if ((P1&0xf0)!=0xf0)				// 延时后再判断一次，去除抖动影响
		{  
			scancode = 0xfe;
			while((scancode&0x10)!=0)		// 逐行扫描
			{
				P1 = scancode;				// 输出行扫描码
				if ((P1&0xf0)!=0xf0)		// 本行有键按下
				{
					tmpcode = (P1&0xf0)|0x0f;

					/* 返回特征字节码，为1的位即对应于行和列 */
					return((~scancode)+(~tmpcode));
				}
				else scancode = (scancode<<1)|0x01;		// 行扫描码左移一位
			}
		}
	}
	return(0);								// 无键按下，返回值为0 	
}

/* 定时器0中断服务子程序，2ms定时动态扫描显示 */
void time0_int(void) interrupt 1 
{
	/* 重置2ms定时 */
	TH0 = -2000/256;
	TL0 = -2000%256;

         px++;                  //片选
	if (showflag==1)
		display();				// 调用显示函数
}


/* 根据共阴极字型编码表获取0~9，A~B字型代码 */
uchar getcode(uchar i)
{
	uchar p;
	switch (i)
	{
		case 0:	 p=0x3f;	break;			/* 0 */
		case 1:	 p=0x06;	break;			/* 1 */
		case 2:	 p=0x5B;	break;			/* 2 */
		case 3:	 p=0x4F;	break;			/* 3 */
		case 4:	 p=0x66;	break;			/* 4 */
		case 5:	 p=0x6D;	break;			/* 5 */
		case 6:	 p=0x7D;	break;			/* 6 */
		case 7:	 p=0x07;	break;			/* 7 */
		case 8:	 p=0x7F;	break;			/* 8 */
		case 9:	 p=0x67;	break;			/* 9 */
		default: 			break;
	}
	return(p);
}

void Display(void)   //LED数值显示
{ 
 switch (px%2)
  {
case 0:
        P20 = 1;P21 = 0; P0 = getcode(wordbuf[0]);break;
case 1:
        P21 = 1;P20 = 0; P0 = getcode(wordbuf[1]);break;
default:  return;
 }
}

/* 显示函数 */
/*void display(void)
{
	uchar i;
	switch (digbit)
	{
		case 1:		i=0;	break;
		case 2:		i=1;	break;
		default: 	break;
	}

	P2 = 0x0;						// 关闭显示
//	P20=0;
//	P21=0;
	P0 = getcode(wordbuf[i]);		// 送字型码
	P2=digbit;                    	// 送字位码
	digbit=1;
	if(digbit==1)
    {	
    digbit=2;
	P20 = 1;				
	P21 = 0;
    }
	digbit=2;
	P21 = 1;
	P20 = 0;
	if (digbit<0x02)				// 共2位
		digbit = digbit*2;			// 左移一位
	else
	    digbit = 0x01;
}
*/
/* 主程序 */
void main()
{
	uchar j,key;
    uint temp;

	P20 = 1;
	P21 = 1;							// 关闭数码管显示
	
	TMOD = 0x11;						// T0，T1工作方式1

	/* 2ms 定时设置 */
	TH0 = -2000/256;
	TL0 = 2000%256;
	
	/* 启动计数器0，关闭计数器1 */
	TR0 = 1;
	ET0 = 1;
	TR1 = 0;
	ET1 = 1;
	EA = 1;

	count = 0;						// 初始计数器设为0
	enterflag = 0;					// 没有按下确认键
	lh = 0;
	pwflag = 0;						// 标志先置为0
	
	digbit = 0x01;					// 从第一位数码管开始动态扫描

	/* 刚加电时，bu显示*/
	for (j=0;j<2;j++)
		wordbuf[j] = 17;

	showflag = 1;					// 打开数码管显	

  	while(1)

    {
		key = keyscan();					// 调用键盘扫描函数
        switch(key)
   		{
      		case 0x11:						// 1行1列，数字1
				if (count<2)
				{
					wordbuf[count] = 1;	// 对应位上显示“1”
					pwbuf[count] = 1;
					if(count==0)
                    {a=1;
                    }
					if(count==1)
                    {b=1;
                    }
					count++;
					
				}
				break;
			case 0x21:						// 1行2列，数字3
				if (count<2)
				{
					wordbuf[count] = 2;	// 对应位上显示“2"
					pwbuf[count] = 2;
					if(count==0)
                    {a=2;
                    }	
					if(count==1)
                    {b=2;
                    }
					count++;
				}
				break;			
			case 0x41:						// 1行3列，数字3
				if (count<2)
				{
					wordbuf[count] = 3;	// 对应位上显示“3"
					pwbuf[count] = 3;
					if(count==0)
                    {a=3;
                    }
					if(count==1)
                    {b=3;
                    }
					count++;
				}
				break;
    
			case 0x12:						// 2行1列，数字4
				if (count<2)
				{
					wordbuf[count] = 4;	// 对应位上显示“4"
					pwbuf[count] = 4;
					if(count==0)
                    {a=4;
                    }	
					if(count==1)
                    {b=4;
                    }
					count++;
				}
				break;
			case 0x22:						// 2行2列，数字5
				if (count<2)
				{
					wordbuf[count] = 5;	// 对应位上显示“5"
					pwbuf[count] = 5;
					if(count==0)
                    {a=5;
                    }
					if(count==1)
                    {b=5;
                    }
					count++;
				}
				break;
			case 0x42:						// 2行3列，数字6
				if (count<2)
				{
					wordbuf[count] = 6;	// 对应位上显示“6"
					pwbuf[count] = 6;
			    	if(count==0)
                    {a=6;
                    }	
					if(count==1)
                    {b=6;
                    }
					count++;
				}
				break;
	
			case 0x14:						// 3行1列，数字7
				if (count<2)
				{
					wordbuf[count] = 7;	// 对应位上显示“7"
					pwbuf[count] = 7;
					if(count==0)
                    {a=7;
                    }
					if(count==1)
                    {b=7;
                    }
					count++;
				}
				break;
			case 0x24:						// 3行2列，数字8
				if (count<2)
				{
					wordbuf[count] = 8;	// 对应位上显示“8"
					pwbuf[count] = 8;
					if(count==0)
                    {a=8;
                    }
					if(count==1)
                    {b=8;
                    }
					count++;
				}
				break;
			case 0x44:						// 3行3列，数字9
				if (count<2)
				{
					wordbuf[count] = 9;	// 对应位上显示“9"
					pwbuf[count] = 9;
					if(count==0)
                    {a=9;
                    }	
					if(count==1)
                    {b=9;
                    }
					count++;
				}
				break;	
		
			 case 0x18:						// 4行1列，数字*
				count = 0;
				P3=0;
				px=0;					// 显示清零
				for (j=0;j<2;j++)
				{
					wordbuf[j] = 17;			// 数码管不显示
					pwbuf[j] = 0;		// 用FFFFFF清除已经输入的密码
				}
				break;	
			case 0x28:              	// 4行2列，数字0
				if (count<2)
				{
					wordbuf[count] = 0;	// 对应位上显示“0"
					pwbuf[count] = 0;
					if(count==0)
                    {a=0;
                    
                    }	
					if(count==1)
                    {b=0;
                    }
					count++;
				}
				break;
			case 0x48:						// 4行3列，数字#
				 enterflag = 1;				// 确认键按下	
				 if (count==2) 				// 只有输入2个数后按确认键才有效输出
			    	pwflag = 1;      
				break;
		
			default:break;
		}

		if (enterflag==1)					// 如果按下确认键
		{
			enterflag = 0; 					// 标志位置回0
			count = 0;                      // 计数器清零
			c=0xff/6;						
			if (pwflag==1)			
            {
             P3=a*c+b*c/10+12*c/100;
             temp=a*c+b*c/10+12*c/100;
               if(temp>=0xff)
               {
                  P3=0xff;
               }
            }
            				
		}
	}    
}
