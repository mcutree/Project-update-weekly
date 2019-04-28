#include <reg51.h>
#include <absacc.h>
#define TR 1
#define uchar unsigned char
#define uint  unsigned int

uchar idata buf[10]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};
uchar idata buf1[10]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x09};
uchar data1,data2,data3;
uchar pf,addr,TRR;
uchar flag,flag1,flag2=3;

sbit key1=P1^0;
sbit key2=P1^1;
sbit key3=P2^0;
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
    SCON=0xd0;
} 


void keyscan(void)
{
   if(key1==0) 
    {
      delay(50);
        if(key1==0)
          {
            while(key1==0)
              {
               ;
              }
           flag2=0;
           TRR=0x01;
           addr=0x03;
          }
    } 
   if(key2==0) 
    {
      delay(50);
        if(key2==0)
          {
            while(key2==0)
              {
               ;
              }
           flag2=1;
           TRR=0x01;
           addr=0x04;
         }
    } 
}

void send(void)
{ uchar i; 

  if(flag2==0)
    { 
      TB8=1; 
      key3=1;
      SBUF=addr;
       while(TI==0)
         {
           ;
         }
       TI=0;
       key3=0;
      while(RI==0)
       {
        ;
       }
        data1=SBUF;
        RI=0;
       if(data1!=addr)
         {
          flag2=0;
           
         }
     else{ 
             TB8=0;
             key3=1;
             SBUF=TRR;
             while(TI==0)
             {
                ;
             }
             TI=0;
             key3=0;
             while(RI==0)
             {
                ;
             }
             data3=SBUF;
             RI=0;
             if(data3!=TRR)
               {
                flag2=0;
               }
             else{
                     pf=0;
                     key3=1;
                    for(i=0;i<=9;i++)
                      {
                        TB8=0;
                        SBUF=buf[i];
                        pf+=buf[i];
                        
                        while(TI==0)
                             {
                               ;
                             }
                        TI=0;
                       } 
                     TB8=0;
                     SBUF=pf;
                     while(TI==0)
                            {
                              ;
                            }
                     TI=0;
                     key3=0;
                     while(RI==0)
                            {
                              ;
                            }
                     data2=SBUF;
                     RI=0;
                     if(data2==0xcc)
                          {
                            flag2=3;
                          }
                     else{
                            flag2=0;
                         }
                  }
           }
      }
 }


void send1(void)
{ uchar i; 
  if(flag2==1)
    { 
      TB8=1; 
      SBUF=addr;
       while(TI==0)
         {
           ;
         }
       TI=0;
      while(RI==0)
       {
        ;
       }
        data1=SBUF;
        RI=0;
       if(data1!=addr)
         {
          flag2=1;
           
         }
       else{
             TB8=0;
             SBUF=TRR;
             while(TI==0)
             {
                ;
             }
             TI=0;
             while(RI==0)
             {
                ;
             }
             data3=SBUF;
             RI=0;
             if(data3!=TRR)
                {
                 flag2=1;
                }
            else
                {  
                   pf=0;
                   for(i=0;i<=9;i++)
                      {  
                        TB8=0;
                        SBUF=buf1[i];
                        pf+=buf1[i];
                        while(TI==0)
                             {
                               ;
                             }
                        TI=0;
                      }
                    TB8=0;
                    SBUF=pf;
                    while(TI==0)
                       {
                        ;
                       }
                    TI=0;
                    while(RI==0)
                        {
                         ;
                        }
                    data2=SBUF;
                    RI=0;
                    if(data2==0xcc)
                        {
                          flag2=3;
                        }
                    else{
                          flag2=1;
                        }
              
               }
            }
      }
 }
void main(void)
{
    delay(500);
    init();
    while(1)
    {
        send();
        send1();
        keyscan();
      
    }
}