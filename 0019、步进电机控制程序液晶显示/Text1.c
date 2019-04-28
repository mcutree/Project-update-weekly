#include <reg51.h>
#define uchar unsigned char 
sbit P1_0=P1^0;sbit P1_1=P1^1;sbit P1_2=P1^2;sbit P1_3=P1^3;
sbit P1_4=P1^4;sbit P1_5=P1^5;sbit P1_6=P1^6;sbit P1_7=P1^7;
uchar RRR,flg,KKK; //RRR用于调速控制；flg=0正转；flg=1反转; flg=2不转；KKK为P1的状态寄存
uchar loop[2][4]={{0x0c,0x06,0x03,0x09},{0x09,0x03,0x06,0x0c}};
void loop1(void);
void loop2(void);
void step(void);

main()
{
uchar i,j;
TMOD=0x10;
TL1=0xe0;
TH1=0xb1;
IE=0;
while(1)
{
  if(KKK!=P1)           //当P1的值发生变化，触发采集信号
    loop1();
  if(flg!=2)            
  {
   for(i=0;i<=3;i++)
    {
     P0=loop[flg][i];
     for(j=0;j<=RRR;j++)
	 {step();}
	}
  }
}
}

void step(void)        //产生20MS的单位步时间
{
TF1=0;
TR1=1;
while(TF1==0);
TR1=0;
TL1=0xe0;
TH1=0xb1;
}

void loop1(void)                 //采集顺时针或逆时针信号，P1.6=1，顺时针，P1.7=1，逆时针
{
KKK=P1;                          //暂存P1的状态       
if(P1_6==1)
 {flg=0;loop2();}
else if(P1_7==1)
 {flg=1;loop2();}
else
 flg=2;
}
void loop2(void)
{
  if(P1_0==1)
  RRR=5;

 else if(P1_1==1)
  RRR=8;

 else if(P1_2==1)
  RRR=11;

 else if(P1_3==1)
  RRR=14;

 else if(P1_4==1)
  RRR=17;

 else if(P1_5==1)
  RRR=20;
}










