#ifndef _key_h
#define _key_h
#include<AT89x51.h> 
#define uchar unsigned char 
#define uint unsigned int
bit flag=0;//按键按下标志位
sbit BEEP=P3^7;//蜂鸣器端口
delay(int z)//延时1ms
 { int x,y;
   for (x=z;x>0;x--)
   for (y=140;y>0;y--); 
 }
uchar num;//按键返回值
////////按键音程序////////////////// 
void yin()
 { 
  int c,n;
  if(flag==1)
  {	
   for(c=0;c<80;c++)
  { 
   for(n=0;n<50;n++); //延时
   BEEP=~BEEP; //取反输出到喇叭的信号
   }
   }
 }   
////////////键盘程序///////////////////
int key()
{ 	uchar temp;
    P2=0X7f;
    temp=P2&0x0f;
	if(temp!=0x0f)
	 {
	  delay(5); 
	  if(temp!=0x0f)
	  {temp=P2;
	   switch(temp)
	    {   case 0x77:num=0;
		    break;
			case 0x7b:num=1;
		    break;
	    	case 0x7d:num=2;
		    break;
			case 0x7e:num=3;
		    break; 
		}
       do{			   //等待按键抬起
		 	 temp=P2;
			 temp=temp&0x0f;
		 }	 
		  while(temp!=0x0f);
	    flag=1;
		yin();
		 } 
		 }
   	P2=0Xbf;	 
    temp=P2&0x0f;
	if(temp!=0x0f)
	 {delay(5);
	  if(temp!=0x0f)
	  {temp=P2;
	   switch(temp)
	    {   case 0xb7:num=4;
		    break;
			case 0xbb:num=5;
		    break;
	    	case 0xbd:num=6;
		    break;
			case 0xbe:num=7;
		    break; 
		}
       do{
		 	 temp=P2;
			 temp=temp&0x0f;
		 }	 
		  while(temp!=0x0f);
	    flag=1;
		yin();
	   }
	 }
	P2=0Xdf;
    temp=P2&0x0f;
	if(temp!=0x0f)
	 {delay(5);
	  if(temp!=0x0f)
	  {temp=P2;
	   switch(temp)
	    {   case 0xd7:num=8;
		    break;
			case 0xdb:num=9;
		    break;
	    	case 0xdd:num=10;
		    break;
			case 0xde:num=11;
		    break; 
		}
       do{
		 	 temp=P2;
			 temp=temp&0x0f;
		 }	 
		  while(temp!=0x0f);
		flag=1;
		yin();
	   }
	 }
	P2=0Xef;
    temp=P2&0x0f;
	if(temp!=0x0f)
	 {delay(5);
	  if(temp!=0x0f)
	  {temp=P2;
	   switch(temp)
	    {   case 0xe7:num=12;
		    break;
			case 0xeb:num=13;
		    break;
	    	case 0xed:num=14;
		    break;
			case 0xee:num=15;
		    break; 
		}
       do{
		 	 temp=P2;
			 temp=temp&0x0f;
		 }	 
		  while(temp!=0x0f);
		flag=1;
		yin();
	   } 
	 }
	 return(num);
 }
#endif