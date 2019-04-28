#include <reg51.h>
#include <absacc.h>
#define uchar unsigned char
#define uint  unsigned int

uchar idata buf[10];
uchar data1,data2,data3;
uchar pf,i;
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
    TH1=0xfd;
    TL1=0xfd;
    PCON=0x00;
    TR1=1;
    SCON=0Xd0;
} 

void receive(void)
{   
  
     
      SM2=1;
      key2=0;
      while(RI==0)
          {
            ;
          }
      data1=SBUF;
      RI=0;
      if(data1!=0x03)
          { 
            flag1=1;
          }
     else {
            flag1=2;
            TI=0;
            TB8=1;
            SM2=0;
            key2=1;
            SBUF=0x03;
            while(TI==0)
               {
                ;
               }
             TI=0;
             pf=0;
             TB8=0;
             key2=0;
             while(RI==0)
                 {
                   ;
                 }
              data3=SBUF;
              RI=0;
              if(data3!=0x01)
                {
                  flag1=1;
                }
              else{ key2=1;
                    SBUF=0x01;
                    while(TI==0)
                       {
                         ;
                       }
                     TI=0;
                     for(i=0;i<=9;i++)
                          {  key2=0;
                             while(RI==0)
                                  {
                                    ;
                                  }
                              buf[i]=SBUF;
                              pf+=buf[i];
                              RI=0;
                           }
                      key2=0;
                      while(RI==0)
                            {
                              ;
                            }
                     data2=SBUF;
                     RI=0;
                     if(data2==pf)
                             {  
                                TB8=0;
                               
                                SBUF=0xcc;
                                 key2=1;
                                while(TI==0)  
                                    {
                                      ;
                                    }
                                TI=0;
                              }
                     else{ 
                              TB8=0;
                              SBUF=0xdd;
                               key2=1;
                              while(TI==0)
                                 {
                                   ;
                                 }
                               TI=0;
                          }
                  }
           }
  }

void display(void)
{ if(flag1==2)
    {
         for(i=0;i<=9;i++)
            {
              P1=buf[i];
              delay(300);
             }
     }
}


void main(void)
{
    delay(500);
    init();
    while(1)
    {  
      receive();
      display();
    }
}