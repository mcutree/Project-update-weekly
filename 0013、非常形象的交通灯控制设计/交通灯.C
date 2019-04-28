/*****************************************************
       十字路口交通灯控制 C 程序

******************************************************/

#define	uchar	unsigned char
#define	uint	unsigned int
#include	<reg52.h>
/*****定义控制位**********************/
sbit    Time_Show_LED2=P2^5;//Time_Show_LED2控制位
sbit    Time_Show_LED1=P2^4;//Time_Show_LED1控制位
sbit	EW_LED2=P2^3;	//EW_LED2控制位
sbit	EW_LED1=P2^2;	//EW_LED1控制位
sbit	SN_LED2=P2^1;	//SN_LED2控制位
sbit	SN_LED1=P2^0;	//SN_LED1控制位
sbit    SN_Yellow=P1^6;//SN黄灯
sbit    EW_Yellow=P1^2;//EW黄灯
sbit    EW_Red=P1^3;//EW红灯
sbit    SN_Red=P1^7;//SN红灯
sbit    EW_ManGreen=P3^0;//EW人行道绿灯
sbit    SN_ManGreen=P3^1;//SN人行道绿灯
sbit    Special_LED=P2^6;//交通正常指示灯
sbit    Busy_LED=P2^7;//交通繁忙指示灯
sbit    Nomor_Button=P3^5;//交通正常按键
sbit    Busy_Btton=P3^6;//交通繁忙按键
sbit    Special_Btton=P3^7;//交通特殊按键  
sbit    Add_Button=P3^3;//时间加
sbit    Reduces_Button=P3^4;//时间减
bit     Flag_SN_Yellow; //SN黄灯标志位
bit     Flag_EW_Yellow;//EW黄灯标志位
char	Time_EW;//东西方向倒计时单元
char	Time_SN;//南北方向倒计时单元
uchar EW=60,SN=40,EWL=19,SNL=19; //程序初始化赋值，正常模式
uchar EW1=60,SN1=40,EWL1=19,SNL1=19;//用于存放修改值的变量
uchar code table[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};//1~~~~9段选码
uchar code S[8]={0X28,0X48,0X18,0X48,0X82,0X84,0X81,0X84};//交通信号灯控制代码
/**********************延时子程序************************/
void	Delay(uchar	 a)
	{
		uchar	i;
		i=a;
		while(i--){;}
	}
/*****************显示子函数**************************/
void	Display(void)
	{
		char h,l;
		h=Time_EW/10;
		l=Time_EW%10;
  	    P0=table[l];
		EW_LED2=1;
		Delay(2);
		EW_LED2=0;
	    P0=table[h];
		EW_LED1=1;
		Delay(2);
		EW_LED1=0;

		h=Time_SN/10;
		l=Time_SN%10;
		P0=table[l];
		SN_LED2=1;
		Delay(2);
		SN_LED2=0;
	    P0=table[h];
		SN_LED1=1;
		Delay(2);
		SN_LED1=0;
		

		h= EW1/10;
		l= EW1%10;
		P0=table[l];
		Time_Show_LED1=1;
		Delay(2);
        Time_Show_LED1=0;
		P0=table[h];
		Time_Show_LED2=1;
		Delay(2);
	    Time_Show_LED2=0;
} 
/**********************外部0中断服务程序************************/

void	EXINT0(void)interrupt 0 using 1
	{
		EX0=0; //关中断

if(Add_Button==0) //时间加
       { 
            EW1+=5;
            SN1+=5;
              if(EW1>=100)
			   {
			     EW1=99;
			     SN1=79;
               }
            }
if(Reduces_Button==0) //时间减
       {
            EW1-=5;
            SN1-=5;
            if(EW1<=40)
              { 
			     EW1=40;
                 SN1=20;
               }
				
		    } 

if(Nomor_Button==0)//测试按键是否按下，按下为正常状态
        {
            EW1=60;
            SN1=40;
			EWL1=19;
			SNL1=19;
			Busy_LED=0;//关繁忙信号灯
			Special_LED =0;//关特殊信号灯
            }
if(Busy_Btton==0) //测试按键是否按下，按下为繁忙状态
        {
		    EW1=45;
            SN1=30;
			EWL1=14;
			SNL1=14;
			Special_LED=0;//关特殊信号灯
			Busy_LED=1;//开繁忙信号灯
		
        }
if(Special_Btton==0)//测试按键是否按下，按下为特殊状态
        {
		    EW1=75;
            SN1=55;
			EWL1=19;
			SNL1=19;
			Busy_LED=0;//关繁忙信号灯
		    Special_LED =1;//开特殊信号灯
                  
	    }					
		EX0=1;//开中断
	}
/**********************T0中断服务程序*******************/
	void timer0(void)interrupt 1 using 1
{
	static uchar count;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	count++;
	
	if(count==10)
	{
	  if(Flag_SN_Yellow==1) //测试南北黄灯标志位
	  {SN_Yellow=~SN_Yellow;}
	  if(Flag_EW_Yellow==1)  //测试东西黄灯标志位
	  {EW_Yellow=~EW_Yellow;} 
	}
	if(count==20)
	{
	Time_EW--;
	Time_SN--;
	if(Flag_SN_Yellow==1)//测试南北黄灯标志位
	    {SN_Yellow=~SN_Yellow;}
	if(Flag_EW_Yellow==1)//测试东西黄灯标志位
	    {EW_Yellow=~EW_Yellow;}
	count=0;
	}
	
}
/*********************主程序开始**********************/
void	main(void)

{ 
	Busy_LED=0;
	Special_LED=0;
	IT0=1;	//INT0负跳变触发	
    TMOD=0x01;//定时器工作于方式1
	TH0=(65536-50000)/256;//定时器赋初值
	TL0=(65536-50000)%256;
	EA=1; //CPU开中断总允许
	ET0=1;//开定时中断
	EX0=1;//开外部INTO中断
    TR0=1;//启动定时

     while(1)

{				/*******S0状态**********/
				EW_ManGreen=0;	//EW人行道禁止
	            SN_ManGreen=1;//SN人行道通行
                Flag_EW_Yellow=0;	   //EW关黄灯显示信号
				Time_EW=EW;	
				Time_SN=SN;		
				while(Time_SN>=5)
			    {P1=S[0];	 //SN通行，EW红灯
		         Display();}
				/*******S1状态**********/
			    P1=0x00;
				while(Time_SN>=0)
			   {Flag_SN_Yellow=1;	 //SN开黄灯信号位
			    EW_Red=1;      //SN黄灯亮，等待左拐信号，EW红灯
			 
			     Display();
				}
				/*******S2状态**********/
			    Flag_SN_Yellow=0; //SN关黄灯显示信号
				Time_SN=SNL;
				while(Time_SN>=5)
				{P1=S[2];//SN左拐绿灯亮，EW红灯
				 Display();}

			  /*******S3状态**********/
				P1=0x00;
				while(Time_SN>=0)
			   {Flag_SN_Yellow=1;	//SN开黄灯信号位
			    EW_Red=1;      //SN黄灯亮,等待停止信号，EW红灯
			   	
			    Display();}


			   /***********赋值**********/
				EW=EW1;
				SN=SN1;
				EWL=EWL1;
				SNL=SNL1;


				/*******S4状态**********/
				EW_ManGreen=~EW_ManGreen;//EW人行道通行
	            SN_ManGreen=~SN_ManGreen;//SN人行道禁止
				Flag_SN_Yellow=0;  //SN关黄灯显示信号
				Time_EW=SN;
				Time_SN=EW;
			    while(Time_EW>=5)
			    {P1=S[4];	 //EW通行，SN红灯
				 Display();}
				/*******S5状态**********/
				P1=0X00;
				while(Time_EW>=0)
			   {Flag_EW_Yellow=1;//EW开黄灯信号位
			    SN_Red=1;//EW黄灯亮，等待左拐信号，SN红灯	
			    Display();}
				/*******S6状态**********/
				Flag_EW_Yellow=0;	    //EW关黄灯显示信号
				Time_EW=EWL;
				while(Time_EW>=5)
				{P1=S[6];//EW左拐绿灯亮，SN红灯
				 Display();}

				/*******S7状态**********/
				P1=0X00;
				while(Time_EW>=0)
			   {Flag_EW_Yellow=1; //EN开黄灯信号位
			    SN_Red=1;//EW黄灯亮，等待停止信号，SN红灯	
			    Display();}
			
			   	 /***********赋值**********/
			    EW=EW1;
				SN=SN1;
				EWL=EWL1;
				SNL=SNL1;
			}

	}