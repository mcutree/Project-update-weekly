/*******************************************************************
                          智能温控器

问题描述：当温控开关打开时，若测得环境温度大于设定温度，则继电器吸合
		  ，启动压缩机工作；若测得环境温度小于设定温度，则继电器释放，
		  压缩机停止工作。
          该实验可以应用于对温度控制精度要求不是很高的场合，例如，粮仓，
		  电冰箱，空调，电饭锅等。如果配以通讯接口，可以做成多点温度检
          测监控系统。具有极强的扩展性。

作者：    yiwei  "shannxi university of technolog " 
日期：    2007.4.1在proteus上仿真成功；
          2007.4.3电路板焊接调试成功

参考资料：[1] 周兴华 编著 《单片机智能产品c语言设计实例祥解》
          [2]《电子制作》 2006.11
          [3] www.proteus.com

注意： 此文档为仿真程序，若要在试验板上验证，需要须改一下函数
        

void lcd_wait(void)
{
    DATAPORT=0xff;	     
	LCM_EN=1;
    LCM_RS=0;   			
    LCM_RW=1;   			
    _nop_();
    while(DATAPORT&BUSY)；
   	LCM_EN=0;
	
}

*******************************************************************/

#include<reg51.h>
#include<intrins.h>
#include <absacc.h>
#define uchar unsigned char
#define uint   unsigned int

#define BUSY  0x80                               //lcd忙检测标志
#define DATAPORT P0                              //定义P0口为LCD通讯端口
#define PLAYE_ADDR XBYTE[0XBFFF]                 //语音报警地址

sbit RED_ALARM=P1^0;           					 //红色指示灯
sbit WRITE_ALARM=P1^1;          				//白色指示灯
sbit GREEN_ALARM=P1^2;          				//绿色指示灯
sbit P1_4=P1^4;                				    //时钟调整
sbit P1_5=P1^5;                 				//时钟加
sbit P1_6=P1^6;                 				//时钟减

sbit DQ = P1^7;                 				//定义ds18b20通信端口 
sbit LCM_RS=P2^0;								//数据/命令端
sbit LCM_RW=P2^1;								//读/写选择端
sbit LCM_EN=P2^2;               				//LCD使能信号
sbit ad_busy=P3^2;              				//adc中断方式接口
sbit RECLED_EOC=P3^5;           				//ISD1420放音结束查询标志
sbit OUT=P3^7;

uchar ad_data;                  				//ad采样值存储						
uchar seconde=0;                				//定义并初始化时钟变量
uchar minite=0;
uchar hour=12;
uchar mstcnt=0;
uchar temp1,temp2,temp;         			    //温度显示变量
uchar t,set;
uchar K;
bit ON_OFF=0;
bit outflag;

uchar code str0[]={"---  :  :  ---  "};
uchar code str1[]={"SET:  C SA:  . C"};

void delay_LCM(uint);             											//LCD延时子程序
void initLCM( void);               											//LCD初始化子程序
void lcd_wait(void);              											//LCD检测忙子程序
void WriteCommandLCM(uchar WCLCM,uchar BusyC);                              //写指令到ICM子函数
void WriteDataLCM(uchar WDLCM);                                             //写数据到LCM子函数
void DisplayOneChar(uchar X,uchar Y,uchar DData);                           //显示指定坐标的一个字符子函数
void DisplayListChar(uchar X,uchar Y,uchar code *DData);                    //显示指定坐标的一串字符子函数
void init_timer0(void);               										//定时器初始化
void displayfun1(void);
void displayfun2(void);
void displayfun3(void);
void displayfun4(void);
void keyscan(void );                									    //键盘扫描子程序
void set_adj(void);
void inc_key(void);
void dec_key(void);
void delay_18B20(unsigned int i);
void Init_DS18B20(void) ;
uchar ReadOneChar(void);
void WriteOneChar(unsigned char dat);
void ReadTemperature(void);
void ad0809(void);
void playalarm(void); 


/*********延时K*1ms,12.000mhz**********/

void delay_LCM(uint k)
{
    uint i,j;
    for(i=0;i<k;i++)
    {
        for(j=0;j<60;j++)
        	{;}
    }
}   
/**********写指令到ICM子函数************/

void WriteCommandLCM(uchar WCLCM,uchar BusyC)
{
    if(BusyC)lcd_wait();
	DATAPORT=WCLCM;
    LCM_RS=0;                   // 选中指令寄存器
    LCM_RW=0;               	// 写模式	
    LCM_EN=1;    
	_nop_();   
	_nop_();
	_nop_(); 
    LCM_EN=0;  
}

/**********写数据到LCM子函数************/

void WriteDataLCM(uchar WDLCM)
{ 
    lcd_wait( );            //检测忙信号    
	DATAPORT=WDLCM;
    LCM_RS=1;               // 选中数据寄存器
    LCM_RW=0;           	// 写模式
    LCM_EN=1;
    _nop_();
	_nop_();
	_nop_();
    LCM_EN=0;
}

/***********lcm内部等待函数*************/

void lcd_wait(void)
{
    DATAPORT=0xff;	     
	LCM_EN=1;
    LCM_RS=0;   			
    LCM_RW=1;   			
    _nop_();
    while(DATAPORT&BUSY)
	{  LCM_EN=0;
	   _nop_();
	   _nop_();
	   LCM_EN=1;
	   _nop_();
	   _nop_();
	   }
   	LCM_EN=0;
	
}

/**********LCM初始化子函数***********/

void initLCM( )
{   
	DATAPORT=0;	
	delay_LCM(15);
	WriteCommandLCM(0x38,0);    //三次显示模式设置，不检测忙信号
    delay_LCM(5); 
    WriteCommandLCM(0x38,0);
    delay_LCM(5); 
    WriteCommandLCM(0x38,0);
    delay_LCM(5); 

    WriteCommandLCM(0x38,1);    //8bit数据传送，2行显示，5*7字型，检测忙信号
    WriteCommandLCM(0x08,1);    //关闭显示，检测忙信号
    WriteCommandLCM(0x01,1);    //清屏，检测忙信号
    WriteCommandLCM(0x06,1);    //显示光标右移设置，检测忙信号
    WriteCommandLCM(0x0c,1);    //显示屏打开，光标不显示，不闪烁，检测忙信号
}

/****************显示指定坐标的一个字符子函数*************/

void DisplayOneChar(uchar X,uchar Y,uchar DData)
{
    Y&=1;
    X&=15;
    if(Y)X|=0x40;               //若y为1（显示第二行），地址码+0X40
    X|=0x80;                    //指令码为地址码+0X80
    WriteCommandLCM(X,0);
    WriteDataLCM(DData);
}

/***********显示指定坐标的一串字符子函数***********/

void DisplayListChar(uchar X,uchar Y,uchar code *DData)
{
    uchar ListLength=0;
    Y&=0x01;
    X&=0x0f;
    while(X<16)
    {
        DisplayOneChar(X,Y,DData[ListLength]);
        ListLength++;
        X++;
    }
}

/***********ds18b20延迟子函数（晶振12MHz ）*******/ 

void delay_18B20(unsigned int i)
{
	while(i--);
}

/**********ds18b20初始化函数**********************/

void Init_DS18B20(void) 
{
	 unsigned char x=0;
	 DQ = 1;          //DQ复位
	 delay_18B20(8);  //稍做延时
	 DQ = 0;          //单片机将DQ拉低
	 delay_18B20(80); //精确延时 大于 480us
	 DQ = 1;          //拉高总线
	 delay_18B20(14);
	 x=DQ;            //稍做延时后 如果x=0则初始化成功 x=1则初始化失败
	 delay_18B20(20);
}

/***********ds18b20读一个字节**************/  

unsigned char ReadOneChar(void)
{
	uchar i=0;
	uchar dat = 0;
	for (i=8;i>0;i--)
	 {
		  DQ = 0; // 给脉冲信号
		  dat>>=1;
		  DQ = 1; // 给脉冲信号
		  if(DQ)
		  dat|=0x80;
		  delay_18B20(4);
	 }
 	return(dat);
}

/*************ds18b20写一个字节****************/  

void WriteOneChar(uchar dat)
{
 	unsigned char i=0;
 	for (i=8; i>0; i--)
 	{
  		DQ = 0;
 		DQ = dat&0x01;
    	delay_18B20(5);
 		DQ = 1;
    	dat>>=1;
 }
}

/**************读取ds18b20当前温度************/

void ReadTemperature(void)
{
	unsigned char a=0;
	unsigned char b=0;
	unsigned char t=0;

	Init_DS18B20();
	WriteOneChar(0xCC);    	// 跳过读序号列号的操作
	WriteOneChar(0x44); 	// 启动温度转换

	delay_18B20(100);       // this message is wery important

	Init_DS18B20();
	WriteOneChar(0xCC); 	//跳过读序号列号的操作
	WriteOneChar(0xBE); 	//读取温度寄存器等（共可读9个寄存器） 前两个就是温度

	delay_18B20(100);

	a=ReadOneChar();    	//读取温度值低位
	b=ReadOneChar();   		//读取温度值高位
	temp1=b<<4;
	temp1+=(a&0xf0)>>4;
	temp2=a&0x0f;

   temp=((b*256+a)>>4);    //当前采集温度值除16得实际温度值


}

/***************液晶显示子函数1正常显示*****************/

void displayfun1(void)
{	
	WriteCommandLCM(0x0c,1);   					 //显示屏打开，光标不显示，不闪烁，检测忙信号	
	DisplayListChar(0,0,str0);	
	DisplayListChar(0,1,str1);	
											    	  
	DisplayOneChar(3,0,hour/10+0x30);		    //液晶上显示小时
	DisplayOneChar(4,0,hour%10+0x30);

	DisplayOneChar(6,0,minite/10+0x30);			//液晶上显示分
	DisplayOneChar(7,0,minite%10+0x30);
	
	DisplayOneChar(9,0,seconde/10+0x30);	    //液晶上显示秒
	DisplayOneChar(10,0,seconde%10+0x30);

	DisplayOneChar(4,1,K/10+0x30);			    //液晶上显示设定的温度
	DisplayOneChar(5,1,K%10+0x30);
 
   	DisplayOneChar(11,1,temp1/10+0x30);         //液晶上显示测得的温度  
	DisplayOneChar(12,1,temp1%10+0x30);
	DisplayOneChar(14,1,temp2/10+0x30);

	if(ON_OFF==0)						      //若温控标志为0
	{
		DisplayOneChar(14,0,0x4f);			   // 液晶上显示不控温的标志
		DisplayOneChar(15,0,0x46);
	}
	else
	{
		DisplayOneChar(14,0,0x4f);			   // 液晶上显示控温的标志
		DisplayOneChar(15,0,0x4e);
		if(outflag==1)
		    DisplayOneChar(0,0,0x7c);			   
	    else
			DisplayOneChar(0,0,0xef);
	}

	
}
/************液晶显示子函数2***************/

void displayfun2(void)
{
	WriteCommandLCM(0x0c,1);                     //显示屏打开，光标不显示，不闪烁，检测忙信号	
	DisplayListChar(0,0,str0);	
	DisplayListChar(0,1,str1);	
		
	DisplayOneChar(6,0,minite/10+0x30);
	DisplayOneChar(7,0,minite%10+0x30);
	
	DisplayOneChar(9,0,seconde/10+0x30);
	DisplayOneChar(10,0,seconde%10+0x30);

	DisplayOneChar(4,1,K/10+0x30);			   
	DisplayOneChar(5,1,K%10+0x30);
 
   	DisplayOneChar(11,1,temp1/10+0x30);         
	DisplayOneChar(12,1,temp1%10+0x30);
	DisplayOneChar(14,1,temp2/10+0x30);

   	WriteCommandLCM(0x0f,1);   					 //显示屏打开，光标显示，闪烁，检测忙信号	
    DisplayOneChar(3,0,hour/10+0x30);
	DisplayOneChar(4,0,hour%10+0x30);
}

/**************液晶显示子函数3*****************/

void displayfun3(void)
{
	WriteCommandLCM(0x0c,1);    				//显示屏打开，光标不显示，不闪烁，检测忙信号	
	DisplayListChar(0,0,str0);	
	DisplayListChar(0,1,str1);	
	
	DisplayOneChar(3,0,hour/10+0x30);
	DisplayOneChar(4,0,hour%10+0x30); 

	DisplayOneChar(9,0,seconde/10+0x30);
	DisplayOneChar(10,0,seconde%10+0x30);

	DisplayOneChar(4,1,K/10+0x30);			   
	DisplayOneChar(5,1,K%10+0x30);

   	DisplayOneChar(11,1,temp1/10+0x30);         
	DisplayOneChar(12,1,temp1%10+0x30);
	DisplayOneChar(14,1,temp2/10+0x30);

   
	WriteCommandLCM(0x0f,1);   					 //显示屏打开，光标显示，闪烁，检测忙信号
	DisplayOneChar(6,0,minite/10+0x30);
	DisplayOneChar(7,0,minite%10+0x30);

}

/**************液晶显示子函数4 *****************/

void displayfun4(void)
{
	WriteCommandLCM(0x0c,1);    				//显示屏打开，光标不显示，不闪烁，检测忙信号	
	DisplayListChar(0,0,str0);	
	DisplayListChar(0,1,str1);	
	
	DisplayOneChar(3,0,hour/10+0x30);
	DisplayOneChar(4,0,hour%10+0x30); 

	DisplayOneChar(6,0,minite/10+0x30);
	DisplayOneChar(7,0,minite%10+0x30);

	DisplayOneChar(9,0,seconde/10+0x30);
	DisplayOneChar(10,0,seconde%10+0x30);

	
   	DisplayOneChar(11,1,temp1/10+0x30);         
	DisplayOneChar(12,1,temp1%10+0x30);
	DisplayOneChar(14,1,temp2/10+0x30);

   
	WriteCommandLCM(0x0f,1);   					 //显示屏打开，光标显示，闪烁，检测忙信号
	DisplayOneChar(4,1,K/10+0x30);			   
	DisplayOneChar(5,1,K%10+0x30);

}

/**************键盘扫描子函数******************/

void keyscan(void)
{
	uchar xx;                                           //局部变量
	P1=0xff;
	if(P1!=0xff)
	  {
	    delay_LCM(50);

		if(P1!=0xff)
		  {	
			xx=P1;
			switch(xx)					               // 根据按键状态，调用不同的子函数
			{
				case 0xfe:set_adj();       break;               
				case 0xfd:inc_key();       break;               
				case 0xfb:dec_key();       break;               
				case 0xf7:ON_OFF=!ON_OFF;  break;
				default:break;
			}
		  }
		
	  }
  
}

/**************设定工作模式子函数****************/

void set_adj(void)
{
	delay_LCM(100);
	set++;
    if(set>=4)set=0;
		
}

/****************按键加法子函数******************/

void inc_key(void)
{
	delay_LCM(100);
		
	switch(set)
	{
		case 0:if(P1==0xf7)ON_OFF=!ON_OFF;       break;
		case 1:hour++;   if(hour>=23)hour=23;    break;
		case 2:minite++; if(minite>=59)minite=59;break;
		case 3:K++;if(K>=99)K=99;				 break; 
		default:break;
	}
		
}

/****************按键减法子函数*****************/

void dec_key(void)
{
	delay_LCM(100);
	
	switch(set)
	{
	   	case 0:if(P1==0xf7)ON_OFF=!ON_OFF;    break;
		case 1:hour--;  if(hour<=0)hour=0;    break;
		case 2:minite--;if(minite<=0)minite=0;break;
		case 3:K--;if(K<=1)K=1;				  break; 
		default:break;
	}
		
}

/***************定时器t0初始化*******************/

void init_timer0(void)
{
	 TMOD=0x01;                                  //time0为定时器，方式1
     TH0=0x3c;                                   //预置计数初值
     TL0=0xb0;
     EA=1;   								
     ET0=1;          											
     TR0=1;          		
}

/***********定时器t0中断子函数**************/

void timer0(void) interrupt 1 using 0          //定时器0方式1，50ms中断一次
{
     TH0=0x3c;
     TL0=0xb0;
     mstcnt++;
     if(mstcnt>=20 )  {seconde++; mstcnt=0; }
	 if(seconde>=60)  {minite++;  seconde=0;}
	 if(minite>=60 )  {hour++;    minite=0; }
	 if(hour>=24   )  {hour=0;}
	 keyscan( );                               //按键扫描
}

/***********the main funtion*************/
    
void main(void)
{ 

    P1=0xff;                                   				//初始化p1口，全设为1       
	delay_LCM(500);	                                        //延时500ms启动
	initLCM( );                               				//LCD初始化
	init_timer0( );	                           				//时钟定时器0初始化	
    Init_DS18B20( ) ;                          				//DS18B20初始化
	DisplayListChar(0,0,str0);	
	DisplayListChar(0,1,str1);  
                     	
    while (1)
    {   
       	keyscan();                                            //按键扫描		
	    ReadTemperature();                                    //温度采集
	    switch(set)                                           //LCD根据工作模式显示
		{
			case 0:displayfun1();delay_LCM(1000);break;       //正常工作显示
			case 1:displayfun2();delay_LCM(1000);break;       //调整时显示
			case 2:displayfun3();delay_LCM(1000);break;       //调整分显示
			case 3:displayfun4();delay_LCM(1000);break; 	  //温度设定
			default:break;
		} 	
		keyscan( );  	                                     //相当于延时
		if(ON_OFF==1)      								     //若温控标志位1， 控制LAMP动作
		{
			if(temp1>=K+1){outflag=1;OUT=0;}
			if(temp1<K)
			{ 
				delay_LCM(1000);
				if(temp1<K){outflag=0;OUT=1;}		        //
			}
		}
		else{outflag=0;OUT=1;}
    }
	
}


