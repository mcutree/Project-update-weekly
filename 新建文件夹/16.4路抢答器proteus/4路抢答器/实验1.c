#include <reg52.h>//头文件
#define uint unsigned int//宏定义
#define uchar unsigned char
sbit k=P3^0;//总控制按键接P3.0端口
sbit qingling=P3^1;//总控制按键接P3.0端口
sbit g1=P3^2;
sbit g2=P3^3;
sbit feng=P3^7;
uchar fangui;
uchar com=0;
uchar miao=10;
uchar miaoshi=0;
uchar qdb;
uchar code tab[]={//数码管的数码 一维数组
	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0xbf
};
uchar buf[]={
	0,0
};
uchar xuanshou=10;//选手号  初值为什么也不现显示
void yanshi(uint x)//毫秒延时函数
{
	uchar i;
	while(x--)
		for(i=0;i<123;i++);
}
void fuzhi()
{
	buf[0]=miao/10%10;
	buf[1]=miao%10;
}
void xuanshouhaofuzhi()
{
	buf[0]=xuanshou/10%10;
	buf[1]=xuanshou%10;
}
void xianshi()//显示函数
{
	g1=1;
	g2=0;
	P0=tab[buf[0]];
	yanshi(1);
	g1=0;
	P0=0xff;
	g2=1;
	P0=tab[buf[1]];
	yanshi(1);
	g2=0;
}
void qingchu()//清楚子函数
{
	xuanshou=10;//选手号为10，数码管不显示
	P1=0xff;//所有的指示灯灭
	miao=0;
	qdb=0;
}
void sss()interrupt 3
{
	TH1=(65536-50000)/256;//50ms中断依一次
	TL1=(65536-50000)%256;
	if(qdb==1)
	{
		miaoshi++;
		if(miaoshi==20&miao>0&com==0)
		{
			miaoshi=0;
			miao--;
		}
		if(com==1)
			xuanshouhaofuzhi();
		else
			fuzhi();
	}
	xianshi();//数码管显示程序放在中断里为了防止数码管闪烁
}
void xs()interrupt 1//定时器中断0
{
	uchar i;
	TH0=(65536-5000)/256;//50ms中断依一次
	TL0=(65536-5000)%256;
	if(fangui==1)
	{
		i++;
		feng=!feng;
		if(i==100)
		{
			i=0;
			fangui=0;
		}
	}
}
void main()
{
	TMOD=0x11;//设置中断方式为T0 16为计时器中断
	TH0=(65536-5000)/256;//赋初始值50ms中断一次
	TL0=(65536-5000)%256;
	TH1=(65536-50000)/256;//赋初始值50ms中断一次
	TL1=(65536-50000)%256;
	EA=1; //开总允许位
	ET0=1;//允许T0中断
	ET1=1;
	TR1=1;
	TR0=1;//打开T0，开始计时
	while(1)//死循环
	{
LL:
		if((P2&0x0f)!=0x0f)
			fangui=1;
		if(!k)//如果总按键按下
		{
			yanshi(50);//延时100ms消抖
			if(!k)//如果总按键还按下
			{
				miao=10;
				miaoshi=0;
				qdb=1;
				while(!k);//当总按键松开继续执行
				while(1)//死循环
				{
					if(!qingling&com==1)//
					{
L1:
						qingchu();//清除一切数据
						fuzhi();
						com=0;//清除抢答痕迹
						goto LL;
					}
					if(miao==0)
					{
						com=1;
						goto L1;
					}
					if(com==0&miao>0)//如果开始抢答并且没人抢答完成
					{
						switch(P2)//判断P2端口
						{
							case 0xfe:xuanshou=1;com=1;break;//1号选手抢答成功
							case 0xfd:xuanshou=2;com=1;break;//2号选手抢答成功
							case 0xfb:xuanshou=3;com=1;break;//3号选手抢答成功
							case 0xf7:xuanshou=4;com=1;break;//4号选手抢答成功
							default: xuanshou=11;break;//如果抢答前就有多人按下自己的键则无效
						}
					}
					if(com==1)//如果抢答完成
					{
						switch(xuanshou)//判断选手号
						{
							case 1:P1=0xfe;break;//1号选手选手则1号灯亮
							case 2:P1=0xfd;break;//2号选手选手则1号灯亮
							case 3:P1=0xfb;break;//3号选手选手则1号灯亮
							case 4:P1=0xf7;break;//4号选手选手则1号灯亮
							default: break;//都不是则无变化
						}
					}
				}
			}
		}
	}
}
