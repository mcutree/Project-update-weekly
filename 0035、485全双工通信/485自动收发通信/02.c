#include <reg51.h>
#include <absacc.h>
#define uchar unsigned char
#define uint  unsigned int

uchar idata buf[10];                      //接受收据
uchar idata buf1[3]={0x06,0x09,0x05};     //从机发送的数据
uchar data1,data2,data3;
uchar pf,i;
uchar flag,flag2;

sbit key1=P2^0;

/************延时程序************/
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
     SM2=1;                         //SM2=1，从机只处于接受地址状态
     key1=0;
     while(RI==0)
          {
            ;
          }
        data1=SBUF;               //接受地址与本机的地址比较
        RI=0;                
       if(data1!=0x04)
         {  
         flag2=3;                  //不是本机的地址
         }
    else {                         //地址正确
              key1=1;
              flag2=2;
              TB8=1;                //TB8=1是从机发送地址标志
              SM2=0;                //SM2=2是允许任何发送和接受数据
              SBUF=0x04;             //从机发送标志
              while(TI==0)
                   {
                     ;
                   }
              TI=0;
              pf=0;
              TB8=0;                 //TB8=0是从机以下通信的全是数据
              key1=0;
              while(RI==0)
                    {
                      ;
                    }
              data3=SBUF;             //从机接受主机状态
              RI=0;
              key1=1;
             if(data3==0x02)           //11111主机是接受状态
                   { TB8=0;
                    
                     SBUF=0x02;        //从机发送本机的状态
                     while(TI==0)
                       {
                         ;
                       }
                     TI=0;
                     for(i=0;i<=2;i++)            //从机发送数据
                          {  SBUF=buf1[i];
                             pf+=buf1[i];
                             while(TI==0)
                                  {
                                    ;
                                  }
                             TI=0;
                           }
                      SBUF=pf;                 //从机发送效验和
                      while(TI==0)
                            {
                              ;
                            }
                      TI=0;
                  }
             
               if(data3==0x01)                  //22222主机是发送状态
                   {  TB8=0;
                      key1=1;
                      SBUF=0x01;                //从机发送本机的状态
                      while(TI==0)
                       {
                         ;
                       }
                     TI=0;
                     key1=0;
                     for(i=0;i<=9;i++)
                        {                           //从机接受主机的数据
                         while(RI==0)
                              {
                               ;
                              }
                         buf[i]=SBUF;
                         pf+=buf[i];
                         RI=0;
                        }
                     while(RI==0)
                            {
                               ;                   //从机接受效验和
                            }
                     data2=SBUF;                  
                     RI=0;
                     key1=1;
                     if(data2==pf)                //从机接受的效验和与本机的效验和比较
                         {                //效验正确
                            TB8=0;
                            SBUF=0xcc;            //发送正确的标志
                            while(TI==0)  
                                 {
                                   ;
                                 } 
                            TI=0;
                         }
                  else{  
                         TB8=0;                    //效验错误
                         SBUF=0xdd;         //发送错误标志，请求主机重新发送数据
                         while(TI==0)
                               {
                                  ;
                                }
                          TI=0;
                       }
                }
             else                           //主机状态错误
                   {  key1=1;
                      flag2=3;
                      SBUF=0xac;             //发送错误标志
                      while(TI==0)
                        {
                         ;
                        }
                       TI=0;
                    }
       }
}

void display(void)
{ if(flag2==2)                   //从机显示标志
    {
         for(i=0;i<=9;i++)
            {
              P1=buf[i];
              delay(50);
             }
     }
}


void main(void)
{
    delay(500);
    init();
    while(1)
    {  
      receive();                //从机通信子程序
      display();                //从机显示子程序
    }
}