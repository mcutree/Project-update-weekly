#include<reg51.h>
#include<absacc.h>
#define  dac0832 XBYTE[0X7fff]
unsigned char code shu[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
float s;
sbit ALE=P3^0;
sbit START=P3^1;
sbit EOC=P3^2;
sbit OE=P3^3;
sbit SHCP=P2^0;
sbit DS=P2^1;
sbit STCP=P2^2;
sbit P11=P3^5;
sbit P12=P3^7;
sbit clk=P2^6;
unsigned char j,k,m,n,i,a;
unsigned int b;
void delay(unsigned char t)
{  while(t--); 
   }
void display()
{ 
  
  j=0x01;
  for(i=0;i<8;i++)
  { if((shu[m]&j)==0)
       { DS=0;}
     else {DS=1;}
    SHCP=1;
    SHCP=0;
      j<<=1;
    }	
	P12=0;
    P11=1;

   
   	
   

    STCP=0;
    STCP=1;
    delay(200);
   j=0x01;
    for(i=0;i<8;i++)
     { if((shu[n]&j)==0)
       { DS=0;}
   else {DS=1;}
     SHCP=1;
   SHCP=0;
     j<<=1;
    } 
   	P11=0;
    P12=1;
  
    
	
      STCP=0;
   STCP=1;
   delay(200);
     }
  

void main()
{
 P2=0X87;
TMOD=0X20;
TH1=0X06;
TL1=0X06;
EA=1;
ET1=1;
TR1=1;

 while(1)
 {
   ALE=1;
   ALE=0;
   START=1;
   START=0;
   while(EOC==0);
   OE=1;
   k=P1;
   a=P1;
   b=a*6;
   m=b/1000;
   n=b%1000/100;
   
   dac0832=k;
  
 display();
 
   }
   }
   void  time() interrupt 3
  {
     clk=!clk;
    }



 
