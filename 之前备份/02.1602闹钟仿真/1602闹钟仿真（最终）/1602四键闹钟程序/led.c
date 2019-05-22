#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char

sbit LCD_RS=P2^6;  //复位端 液晶           
sbit LCD_RW=P2^5;	 //写数据端液晶
sbit LCD_EP=P2^7;	 //使能端液晶 

sbit key1=P2^0;//键盘1
sbit key2=P2^1;//键盘2
sbit key3=P2^2;//键盘3
sbit key4=P2^3;//键盘4
sbit Beep=P1^5;//蜂鸣器
uint num,Num1,Num2;

uchar shi_d,fen_d;
uchar shi_c=8;
uchar fen_c=0;

uchar shi_wei[2]={0,0};
uchar fen_wei[2]={0,0};
uchar shi_weid[2]={0,0};
uchar fen_weid[2]={0,0};
uchar shi_weic[2]={0,0};
uchar fen_weic[2]={0,0};
bit flag0;
bit flag1;
bit flag2;
bit flag3;


uchar a,b,c,d,e,aa;

uchar code table[]="  ";			  //设定开始显示的时间
uchar code table1[]="  ";

uchar miao=0;			
uchar fen=42;
uchar shi=8;

void delay(uint z)//延时
{
	uint x,y;
	for(x=z;x>0;x--)
	for(y=110;y>0;y--);
}
void di()
{
	Beep=1;
	delay(1000);
	Beep=0;	
}
void write_com(uchar com)//写指令函数液晶
{
	LCD_RS=0;
	LCD_RW=0;
	P0=com;
	delay(5);//E变为以有个时间
	LCD_EP=1;
	delay(5);//一个高脉冲
	LCD_EP=0;
	
}
void write_date(uchar date)//写数据函数液晶
{
	LCD_RS=1;
	LCD_RW=0;
	P0=date;
	delay(5);//E变为yi有个时间
	LCD_EP=1;
	delay(5);//一个高脉冲
	LCD_EP=0;
}
void init()//初始化函数
{
    TMOD=0x01;
    TH0=(65536-50000)/256;
    TL0=(65536-50000)%256;
    EA=1;
    ET0=1;
    TR0=1;
	LCD_EP=0;
	write_com(0x38);//显示模式
	write_com(0x0c);//打开显示，光标不开，不闪烁
	write_com(0x01);//清屏
	write_com(0x80);//数据指针初始化
}

void main()				   
{
	
	
	
	
	
	//Beep=0;
	init();



	
	write_com(0x80);
	write_date('O');
	write_com(0x80+0x01);
	write_date('F');
	write_com(0x80+0x02);
	write_date('F');
	

	TR0=1;
	
    while(1)
	{
		if(a==0)							 //正常运行时间
		{
			write_com(0x80+0x46);
			for(num=0;num<2;num++)
			{ write_date(0x30+shi_wei[num]);
			  delay(5);
			}
		
			write_com(0x80+0x49);
			for(num=0;num<2;num++)
			{ write_date(0x30+fen_wei[num]);
			  delay(5);
			}
			if(Num1<10&&flag0==0)
			{
				write_com(0x80+0x48);
				write_date(':');
				flag0=1;
			}
			else if(Num1>9&&flag0==1)
			{
				write_com(0x80+0x48);
				write_date(' ');
				flag0=0;
			}
	    }
		else if(a==1)								  //设置现在时间
		{	
			write_com(0x80);
			write_date(' ');
			write_com(0x80+0x01);
			write_date(' ');
			write_com(0x80+0x02);
			write_date(' ');
			write_com(0x80+0x48);

			write_date(':');
			if(Num1<10&&flag0==0)
			{
				write_com(0x80+0x46);
				for(num=0;num<2;num++)
				{ 
					write_date(0x30+shi_weid[num]);
					delay(5);
				}
				 		
				write_com(0x80+0x49);
				for(num=0;num<2;num++)
				{ 
					write_date(0x30+fen_weid[num]);
					delay(5);
				}
				flag0=1;
			}
			else if(Num1>9&&flag0==1)
			{
			  	write_com(0x80+0x46);	 
				for(num=0;num<2;num++)
				{ 
					write_date(table[num]);
					delay(5);
				}
				write_com(0x80+0x49);	 
				for(num=0;num<2;num++)
				{ 
					write_date(table[num]);
					delay(5);
				}
				flag0=0;

				write_com(0x80+0x48);
				write_date(':');
			} 		
		}
		else if(a==3)										//显示闹钟设置的时间
		{
		
				write_com(0x80+0x48);
				write_date(':');
		 		write_com(0x80+0x46);
				for(num=0;num<2;num++)
				{ 
					write_date(0x30+shi_weic[num]);
					delay(5);
				}
				 		
				write_com(0x80+0x49);
				for(num=0;num<2;num++)
				{ 
					write_date(0x30+fen_weic[num]);
					delay(5);
				}
		
		}



		else if(a==2)												 //设置闹钟的时间
		{	
			write_com(0x80+0x48);
			write_date(':');
			if(Num1<10&&flag0==0)
			{
				write_com(0x80+0x46);
				for(num=0;num<2;num++)
				{ 
					write_date(0x30+shi_weic[num]);
					delay(5);
				}
				 		
				write_com(0x80+0x49);
				for(num=0;num<2;num++)
				{ 
					write_date(0x30+fen_weic[num]);
					delay(5);
				}
				flag0=1;
			}
			else if(Num1>9&&flag0==1)
			{
			  	write_com(0x80+0x46);	 
				for(num=0;num<2;num++)
				{ 
					write_date(table[num]);
					delay(5);
				}
				write_com(0x80+0x49);	 
				for(num=0;num<2;num++)
				{ 
					write_date(table[num]);
					delay(5);
				}
				flag0=0;

				
			} 		
		}




	   	if(a==0&&key1==0)
		{
			while(key1==0)
			{
			 	if(Num1<10&&flag0==0)
				{
					write_com(0x80+0x48);
					write_date(':');
					flag0=1;
				}
				else if(Num1>9&&flag0==1)
				{
					write_com(0x80+0x48);
					write_date(' ');
					flag0=0;
				}			
			}
			a=1;
			shi_d=shi;
			fen_d=fen;	
		}



		if(a==0&&key2==0)
		{
			while(key2==0)
			{
			 	if(Num1<10&&flag0==0)
				{
					write_com(0x80+0x48);
					write_date(':');
					flag0=1;
				}
				else if(Num1>9&&flag0==1)
				{
					write_com(0x80+0x48);
					write_date(' ');
					flag0=0;
				}			
			}
			a=3;
			//shi_c=shi;
			//fen_c=fen;	
		}

		if(a==3&&key3==0)
		{
			while(key3==0);
			
			a=2;
			
		}





		if(a==1&&key1==0)
		{
			while(key1==0)
			{
			 	if(Num1<10&&flag0==0)
				{
					write_com(0x80+0x46);
					for(num=0;num<2;num++)
					{ 
						write_date(0x30+shi_weid[num]);
						delay(5);
					}
					 		
					write_com(0x80+0x49);
					for(num=0;num<2;num++)
					{ 
						write_date(0x30+fen_weid[num]);
						delay(5);
					}
					flag0=1;
				}
				else if(Num1>9&&flag0==1)
				{
				  	write_com(0x80+0x46);	 
					for(num=0;num<2;num++)
					{ 
						write_date(table[num]);
						delay(5);
					}
					write_com(0x80+0x49);	 
					for(num=0;num<2;num++)
					{ 
						write_date(table[num]);
						delay(5);
					}
					flag0=0;
	
					//write_com(0x80+0x48);
					//write_date(':');
				} 			
			}
			shi_d++;
			if(shi_d>24)
			shi_d=0;
		}

		if(a==1&&key2==0)
		{
			while(key2==0)
			{
			 	if(Num1<10&&flag0==0)
				{
					write_com(0x80+0x46);
					for(num=0;num<2;num++)
					{ 
						write_date(0x30+shi_weid[num]);
						delay(5);
					}
					 		
					write_com(0x80+0x49);
					for(num=0;num<2;num++)
					{ 
						write_date(0x30+fen_weid[num]);
						delay(5);
					}
					flag0=1;
				}
				else if(Num1>9&&flag0==1)
				{
				  	write_com(0x80+0x46);	 
					for(num=0;num<2;num++)
					{ 
						write_date(table[num]);
						delay(5);
					}
					write_com(0x80+0x49);	 
					for(num=0;num<2;num++)
					{ 
						write_date(table[num]);
						delay(5);
					}
					flag0=0;
	
					//write_com(0x80+0x48);
					//write_date(':');
				} 			
			}
			fen_d++;
			if(fen_d>59)
			fen_d=0;
		}
		if(a==1&&key3==0)
		{
			while(key3==0)
			{
			 	if(Num1<10&&flag0==0)
				{
					write_com(0x80+0x46);
					for(num=0;num<2;num++)
					{ 
						write_date(0x30+shi_weid[num]);
						delay(5);
					}
					 		
					write_com(0x80+0x49);
					for(num=0;num<2;num++)
					{ 
						write_date(0x30+fen_weid[num]);
						delay(5);
					}
					flag0=1;
				}
				else if(Num1>9&&flag0==1)
				{
				  	write_com(0x80+0x46);	 
					for(num=0;num<2;num++)
					{ 
						write_date(table[num]);
						delay(5);
					}
					write_com(0x80+0x49);	 
					for(num=0;num<2;num++)
					{ 
						write_date(table[num]);
						delay(5);
					}
					flag0=0;
	
					//write_com(0x80+0x48);
					//write_date(':');
				} 			
			}
			a=0;
			if(flag1==1)
			{
				write_com(0x80);
				write_date('O');
				write_com(0x80+0x01);
				write_date('N');
				write_com(0x80+0x02);
				write_date(' '); 			
			}
			else
			{
				write_com(0x80);
				write_date('O');
				write_com(0x80+0x01);
				write_date('F');
				write_com(0x80+0x02);
				write_date('F');
			}

			miao=0;
			shi=shi_d;
			fen=fen_d;
		}





		if(a==2&&key1==0)
		{
			while(key1==0)
			{
			 	if(Num1<10&&flag0==0)
				{
					write_com(0x80+0x46);
					for(num=0;num<2;num++)
					{ 
						write_date(0x30+shi_weic[num]);
						delay(5);
					}
					 		
					write_com(0x80+0x49);
					for(num=0;num<2;num++)
					{ 
						write_date(0x30+fen_weic[num]);
						delay(5);
					}
					flag0=1;
				}
				else if(Num1>9&&flag0==1)
				{
				  	write_com(0x80+0x46);	 
					for(num=0;num<2;num++)
					{ 
						write_date(table[num]);
						delay(5);
					}
					write_com(0x80+0x49);	 
					for(num=0;num<2;num++)
					{ 
						write_date(table[num]);
						delay(5);
					}
					flag0=0;
	
					//write_com(0x80+0x48);
					//write_date(':');
				} 			
			}
			shi_c++;
			if(shi_c>24)
			shi_c=0;
		}

		if(a==2&&key2==0)
		{
			while(key2==0)
			{
			 	if(Num1<10&&flag0==0)
				{
					write_com(0x80+0x46);
					for(num=0;num<2;num++)
					{ 
						write_date(0x30+shi_weic[num]);
						delay(5);
					}
					 		
					write_com(0x80+0x49);
					for(num=0;num<2;num++)
					{ 
						write_date(0x30+fen_weic[num]);
						delay(5);
					}
					flag0=1;
				}
				else if(Num1>9&&flag0==1)
				{
				  	write_com(0x80+0x46);	 
					for(num=0;num<2;num++)
					{ 
						write_date(table[num]);
						delay(5);
					}
					write_com(0x80+0x49);	 
					for(num=0;num<2;num++)
					{ 
						write_date(table[num]);
						delay(5);
					}
					flag0=0;
	
					//write_com(0x80+0x48);
					//write_date(':');
				} 			
			}
			fen_c++;
			if(fen_c>59)
			fen_c=0;
		}


		if(a==2&&key3==0)
		{
			while(key3==0)
			{
			 	if(Num1<10&&flag0==0)
				{
					write_com(0x80+0x46);
					for(num=0;num<2;num++)
					{ 
						write_date(0x30+shi_weic[num]);
						delay(5);
					}
					 		
					write_com(0x80+0x49);
					for(num=0;num<2;num++)
					{ 
						write_date(0x30+fen_weic[num]);
						delay(5);
					}
					flag0=1;
				}
				else if(Num1>9&&flag0==1)
				{
				  	write_com(0x80+0x46);	 
					for(num=0;num<2;num++)
					{ 
						write_date(table[num]);
						delay(5);
					}
					write_com(0x80+0x49);	 
					for(num=0;num<2;num++)
					{ 
						write_date(table[num]);
						delay(5);
					}
					flag0=0;
	
					//write_com(0x80+0x48);
					//write_date(':');
				} 			
			}
			a=0;
			
		
		}





		if(a==0&&key4==0)
		{
		 	while(key4==0)
			{
			 	if(Num1<10&&flag0==0)
				{
					write_com(0x80+0x48);
					write_date(':');
					flag0=1;
				}
				else if(Num1>9&&flag0==1)
				{
					write_com(0x80+0x48);
					write_date(' ');
					flag0=0;
				}			
			} 
			flag1=~flag1;
			if(flag1==1)
			{
				write_com(0x80);
				write_date('O');
				write_com(0x80+0x01);
				write_date('N');
				write_com(0x80+0x02);
				write_date(' '); 
				
				aa=0;
				c=3;			
			}
			else
			{
				write_com(0x80);
				write_date('O');
				write_com(0x80+0x01);
				write_date('F');
				write_com(0x80+0x02);
				write_date('F');
				aa=0;
				c=1;
			}	
		}

		if(shi_c==shi&&fen_c==fen&&miao==0&&a==0&&flag1==1)
		{
		 	aa=0;
			c=180;//三分钟闹铃
			flag3=1;

		}
		if(flag3==1&&key4==0)
		{
		 	flag3=0;
			Beep=0;
			flag2=0;
			
			aa=0;
			c=0;
		}


	}
} 							
void time() interrupt 1 //中断函数
{
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;//进入中断装初值

	if(flag2==1)
	Beep=~Beep;
	else
	Beep=0;
	aa++;
	if(c)
	{
		if(aa<6)
		flag2=1;
		else if(aa<20)
		flag2=0;
		else
		{
		 	c--;
			aa=0;
		}
	
	
	}
	else
	{
		aa=0;
		
	}

	Num1++;
	if(Num1>19)
	{
		Num1=0;
		miao++;
		if(miao>59)
		{
		 	miao=0;
			fen++;
			if(fen>59)
			{
			 	fen=0;
				shi++;
				if(shi>24)
				shi=0;
			}


		}
	
	
	}



	shi_wei[0]=shi/10;
	shi_wei[1]=shi%10;
	fen_wei[0]=fen/10;
	fen_wei[1]=fen%10;

	shi_weid[0]=shi_d/10;
	shi_weid[1]=shi_d%10;
	fen_weid[0]=fen_d/10;
	fen_weid[1]=fen_d%10;

	shi_weic[0]=shi_c/10;
	shi_weic[1]=shi_c%10;
	fen_weic[0]=fen_c/10;
	fen_weic[1]=fen_c%10;

}
		
		
