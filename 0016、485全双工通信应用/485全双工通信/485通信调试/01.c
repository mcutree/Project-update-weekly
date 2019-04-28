#include <reg51.h>
#include <absacc.h>
#define uchar unsigned char
#define uint  unsigned int

//uchar idata buf[10]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};
uchar data1,data2;
uchar pf;
uchar flag,flag1;

sbit key1=P1^0;
sbit key2=P2^0;
/************—” ±≥Ã–Ú************/
void delay(uchar k)
    {
        uchar j;
        while((k--)!=0)           
        	{
                for(j=0;j<125;j++)
                	{;}
        	}
    }

void init(void)
{
    TMOD=0x20;
    TH1=0xe8;
    TL1=0xe8;
    PCON=0x00;
    TR1=1;
    SCON=0X50;
} 

void receive(void)
{      key2=0;
       while(RI==0)
          {
            ;
          }
        data1=SBUF;
        RI=0;
       
}


void main(void)
{
    delay(500);
    init();
    while(1)
    {
      receive();
      P1=data1;
    }
}