#include<AT89x51.h> 
#include"intrins.h"
#include"key.h"
#include"xsh.h"
#include"24c02.h"
#define ulong unsigned long
bit  BJCB=0;//报警标志					  
     XG=0,//修改密码标志位
     BJ=0,//报警标志位
     SJ=0;//锁键盘标志位
    // xg=0;//修改密码标志位
uchar PSWD0_0[16]={0};//密码输入缓存存储单元
//uchar code PSWD0_1[16]={1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};//用户初始密码存储单元
//uchar PSWD1_0[16]={0};//读出密码缓存存储单元
uchar PSWD1_1[16]={1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};////管理员初始密码存储单元
sbit OUT=P3^5;//输出端口
sbit L1=P0^2;//上电指示
sbit L2=P0^1;//开锁指示
sbit L3=P0^0;//报警指示
uint   mg=0,//密码个数
       KSC=0,//开锁次数
       BJC=0,//报警次数
	   TCNTY=0,//用户按键定时次数累加
	   TCNTG=0,//管理员输入密码定时次数
	   yhsh,//用户输入标志位
	   glsh,//管理员输标志位
	   shw;//密码输完标志位
void yhmimaxig();//密码修改程序
void glmimaxig();//管理员修改程序
void bjyin(ulong t)
{
 ulong c;
 uint n;
 for(c=0;c<t;c++)
{
 for(n=0;n<50;n++); //延时
 BEEP=~BEEP; //取反输出到喇叭的信号
}
}
 void delay_10ms(void)
{
	uint i = 1000;
	while(i--);
}
//////////////定时中断服务函数//////////////////////////////////////
 void timer0() interrupt 1 
{ 
 uint i;
 TH0=(65536-50000)/256; //对TH0 TL0赋值50MS定时
 TL0=(65536-50000)%256; //重装计数初值
 if(yhsh==1) 
 {
  TCNTY++;//用户定时计数
  if(shw==1)
 {
  TR0=0;
  TCNTY=0;
  }
  if(TCNTY==400)
  { 
   TR0=0;//关闭T0定时器
   TCNTY=0;
    mg=0;//密码个数清零
	L1=1;
	for(i=0;i<2;i++)//声光报警电路
	 {
		  L3=0;
		  bjyin(1000);
		  L3=1;
		  delay(1000);
	  } 
	  L1=0; 
     }
    } 
	else if(glsh==1)
	    {
		 TCNTG++;//管理员定时计数
         if(shw==1)
        {
           TR0=0;
           TCNTG=0;
         }
       if(TCNTG==400)
       { 
        TR0=0;//关闭T0定时器
        TCNTG=0;
        mg=0;//密码个数清零
		L1=1;
	     for(i=0;i<2;i++)//声光报警电路
	    {
		  L3=0;
		  bjyin(1000);
		  L3=1;
		  delay(1000);
		 }
		 L1=0; 
		}
		}   	
		}	     	 
	    
void main()
{  
   uint i;
   TMOD=0x01;  //定时器工作在方式1
   ET0=1; 
   EA=1;
   TH0=(65536-50000)/256; //对TH0 TL0赋值
   TL0=(65536-50000)%256; //使定时器0.05秒中断一次
  //Read_page24c02(0x00,PSWD1_1,16);//向24c02里读用户初始密码
   //i2cWrite24LC16B(0,0X20);
 /////////////第一次向24c02里写入初始管理员密码、用户密码、开锁次数/////////////////////
   for(i=0;i<16;i++)	//用一次写一个向24c02里写
  {
   i2cWrite24LC16B(PSWD1_1[i],i);
   delay_10ms;  
  } 
   for(i=0;i<16;i++)	//用一次写一个向24c02里写
  {
   i2cWrite24LC16B(PSWD1_1[i],0x10+i);
   delay_10ms;  
  }  //proteus仿真时用，烧程序时，第一次用，第二次不用。
  KSC=i2cRead24LC16B(0X20);
 loop:  L1=0;//上电红灯亮
		L2=1;//开锁成功后绿灯亮
		L3=1;//输错时黄灯亮报警
		OUT=0;//开信号关闭
       display_0(KSC);//开锁前显示
            
///////////密码输入/////////////////
 if(SJ==0)//锁键盘标志位为0
 { 
  do
   {
    flag=0;//键盘标志位
    key();
	if(flag==1&&num==12) //判断是否为管理员功能键按下
	{
	 goto gl;
   	}
   	if(flag==1&&num<=9)
	 {
	  PSWD0_0[mg]=num;
	  mg++;//密码个数
	 }
	 if(flag==1&&num==14&&mg>=1)//输入错误删除
	 {
	   mg=mg-1;
	   } 
	 if(mg==1) //有密码键按下开定时器限时
	 {
	  TR0=1;
	  yhsh=1; 
	  }
   }	
   while(num!=15);
   if(mg!=16)
   {
    for(i=mg;i<16;i++)
	{
	 PSWD0_0[i]=0;
	}
   }   
/////////////////密码比较电路////////////////////////////
 if(flag==1&&num==15)  
 { flag=0;
   yhsh=0;
   shw=1;
   num=0;
  for(i=0;i<16;i++)	//从24c02里读出16个密码
  {
    PSWD1_1[i]=i2cRead24LC16B(i);
    delay_10ms;  
  }
  for(i=0;i<16;i++)
 {
   if(PSWD1_1[i]!=PSWD0_0[i])
   {
     BJCB=1;
     break;
	}
   else
   BJCB=0;	
   
  }
 }
   if(BJCB!=0)
       { 
	     BJC++; 
		 if(BJC!=3)   	
	    {
		 BJCB=0; //第一次和第二次报警
	     delay(500);
		 mg=0;//密码个数清零
		 L1=1;
		 for(i=0;i<3;i++)//声光报警电路
		 {
		  L3=0;
		  display_3();
		  bjyin(1000);
		  L3=1;
		  delay(1000);
		  }
		 goto loop;	 
		}
	  else if(BJC==3)
	    {
		 BJC=0;
	     BJCB=0;
	     display_5();//三次输入密码失败,自锁
	     SJ=1;//锁键盘标志位
	     mg=0;//密码个数清零
		 L1=1;
		 for(i=0;i<2;i++)//声光报警电路
		 {
		  L3=0;
		  bjyin(1000);
		  L3=1;
		  delay(1000);
		  }
	     goto loop;
		} 
		}     	  
	   else 
	   if(BJCB==0)
	  {
	   KSC++;
	   display_1(KSC);
	   i2cWrite24LC16B(KSC,0X20);
	   if(KSC==100)
	   {
	    SJ=1; 
		 }
	   L2=0;
	   L1=1;
	   OUT=1;
	   mg=0;//密码个数清零
 loop1:do	   //键盘扫描等待功能键按下
	   {
	    flag=0;
	    key();
		if(flag)
	   {	
	     flag=0;
	    switch(num)
	   {   
	    case 13:	   
	        {
			  display_2();
             do
            {
             flag=0;//键盘标志位
             key();
        	if(flag==1&&num<=9)
	       {
	         PSWD0_0[mg]=num;
	         mg++;//密码个数
	        }
	       if(flag==1&&num==14&&mg>=1)//输入错误删除
	      {
	       mg=mg-1;
	      }
	      if(mg==16)
	     {
	       do	   //键盘扫描等待功能键按下
	     {
	       flag=0;
	       key();
	     }
	    while(num!=15);
	   } 
       }	
       while(num!=15);
      if(mg!=16&&num==15)
     {
      for(i=mg;i<16;i++)
	 {
	   PSWD0_0[i]=0;
	  }
	 }
	if(flag==1&&num==15)
   { 
     flag=0;	
	 mg=0;
   for(i=0;i<16;i++)	//用一次写一个向24c02里写
  {
   i2cWrite24LC16B(PSWD0_0[i],i);
   delay_10ms;  
  } 
  display_1(KSC);
   do	   //键盘扫描等待功能键按下
   {
	 flag=0;
	 key();
	}
	while(num!=11); //按下返回键，锁锁返回 
	{
      goto loop;
	}
    }
	};break;
		
   case 11: {
		       goto loop;
				  //break;           
		    }
		    }
			}
			}
	  while(flag!=0);//如果设置密码键按下
	  goto loop1;
 // i2cWrite24c02_page(0x00,PSWD1_1,mg);
   } 
   }
 else
    { 
	 do
    {
    flag=0;
    key();
	}
	while(num!=12);//判断是否为管理员功能键按下	  
  gl:do//管理员输入密码
     { 
     flag=0;
     key();
   	 if(flag==1&&num<=9)
	 {
	  PSWD0_0[mg]=num;
	  mg++;//密码个数
	 }
	 if(flag==1&&num==14&&mg>=1)//删除键按下
	 {
	   mg=mg-1;
	 } 
	 if(mg==1)
	  {
	   TR0=1;
	  }//开定时器TO限5秒开锁
      }	
   while(num!=15);
   if(mg!=16&&num==15)
   {
    for(i=mg;i<16;i++)
	{
	 PSWD0_0[i]=0;
	}
   }
  //////////管理员密码比较///////////////////////
 //Read_page24c02(0x10,PSWD0_1,16)
for(i=0;i<16;i++)	//从24c02里读出16个密码
{
    PSWD1_1[i]=i2cRead24LC16B((0x10+i));
    delay_10ms;  
}	
if(flag==1&&num==15)  
{  flag=0;
   shw=1;
   num=0;
  for(i=0;i<mg;i++)
 {
   if(PSWD1_1[i]!=PSWD0_0[i])
   { BJCB=1;
     break;
	}
   else	
   BJCB=0;
   }
   }
   if(BJCB!=0)
       { 
	     BJC++; 
		 if(BJC!=3)   	
	    { 
		 BJCB=0; //第一次和第二次报警
	     
		 mg=0;//密码个数清零
		 L1=1;
		 for(i=0;i<2;i++)//声光报警电路
		 {
		  L3=0;
		  display_3();
		  bjyin(1000);
		  L3=1;
		  delay(1000);
		  }
		 display_1(KSC);
		 goto loop;	 
		}
	  else
	    {
		 BJCB=0;
	     display_5();//三次输入密码失败,自锁
	     mg=0;//密码个数清零
		 delay(10000);
		 display_1(KSC);
	     goto loop; 
		}     	
	   }   
	   else 
	  { 
	   SJ=0;
	   display_4();//管理员开锁显示
       mg=0;
	   L2=0;
	   L1=1;
	   L3=0;//密码个数清零
	   do	   //键盘扫描等待功能键按下
	   {
	    flag=0;
	    key();
	   }
	   while(flag==0); //如果设置密码键按下
	   if(flag==1&&num==13)
	   {
	     flag=0;
	     display_2();
             do
            {
             flag=0;//键盘标志位
             key();
        	if(flag==1&&num<=9)
	       {
	         PSWD0_0[mg]=num;
	         mg++;//密码个数
	        }
	       if(flag==1&&num==14&&mg>=1)//输入错误删除
	     {
	       mg=mg-1;
	      }
	      if(mg==16)
	     {
	       do	   //键盘扫描等待功能键按下
	     {
	       flag=0;
	       key();
	     }
	    while(num!=15);
	   } 
       }	
       while(num!=15);
      if(mg!=16&&num==15)
     {
      for(i=mg;i<16;i++)
	 {
	   PSWD0_0[i]=0;
	  }
	 }
	if(flag==1&&num==15)
   { 
     flag=0;	
	 mg=0;
   for(i=0;i<16;i++)	//用一次写一个向24c02里写
  {
   i2cWrite24LC16B(PSWD0_0[i],(0x10+i));
   delay_10ms;  
  } 
  display_4();
   do	   //键盘扫描等待功能键按下
   {
	 flag=0;
	 key();
	}
	while(num!=11); //按下返回键，锁锁返回 
	{
      goto loop;
	}
    }
	   }
	   if(flag==1&&num==10)
	   {
	    KSC=0;
		i2cWrite24LC16B(KSC,0X20);
		display_1(KSC);
	    do	   //键盘扫描等待功能键按下
	   {
	    flag=0;
	    key();
	   }
	   while(num!=11);//按下返回键，锁锁返回 
	    goto loop; 
       }
	   if(flag==1&&num==11)//按下返回键，锁锁返回 
	   {
	    goto loop;
		}
       }
	   }
	   }