#include <reg51.h>
#include <absacc.h>
#define uchar unsigned char
#define uint  unsigned int

uchar idata buf[10];                        //寄存主机数据
uchar idata buf1[3]={0x0f,0x0f,0x09};       //从机发送的数据   
uchar data1,data2,data3;
uchar pf,i;
uchar flag,flag1;

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
                          //从机数据通信
      key1=0; 
      SM2=1;              //SM2=1从机接受地址 
         
      while(RI==0)
          {
            ;
          }
      data1=SBUF;
      RI=0;
    
       if(data1==0x03) 
          {
            flag1=6;      //地址正确标志
            TI=0;
            key1=1;
            TB8=1;        
            SM2=0;        //TB8=1，SM2=0----表明以后通信的的都是数据
            SBUF=0x03;    //发送本机地址
            while(TI==0)
               {
                ;
               }
             TI=0;
             pf=0;
             TB8=0;
             key1=0;
             while(RI==0)    //从机接受从机状态标志
                 {
                   ;
                 }
              data3=SBUF;
              RI=0;
               if(data3==0x02)       //如果是主机接受数据状态
                   { key1=1;
                     SBUF=0x02;      //回发从机状态
                     while(TI==0)
                       {
                         ;
                       }
                     TI=0;
                     for(i=0;i<=2;i++)       
                          {  
                             SBUF=buf1[i];      //从机发送数据
                             pf+=buf1[i];
                             while(TI==0)
                                  {
                                    ;
                                  }
                             TI=0;
                           }
                      SBUF=pf;                //从机发送效验和
                      while(TI==0)
                            {
                              ;
                            }
                      TI=0;
                  }
             if(data3==0x01)                //如果是主机发送数据标志
                   { key1=1;
                     SBUF=0x01;             //回发从机状态
                     while(TI==0)
                       {
                         ;
                       }
                     TI=0;
                     key1=0;
                     for(i=0;i<=9;i++)        //从机接受数据
                          { 
                             while(RI==0)
                                  {
                                    ;
                                  }
                              buf[i]=SBUF;
                              pf+=buf[i];
                              RI=0;
                           }
                      while(RI==0)           //从机接受效验和
                            {
                              ;
                            }
                     data2=SBUF;
                     RI=0;                   //与本机的效验和进行比较
                     key1=1;
                     if(data2==pf)           //效验和正确
                             {               
                                SBUF=0xcc;      //发送从机正确接受标志
                                while(TI==0)  
                                    {
                                      ;
                                    }
                                TI=0;
                              }
                     else{                     //效验和错误
                              SBUF=0xdd;      //从机发送错误标志----请求主机重新发送数据
                              while(TI==0)
                                 {
                                   ;
                                 }
                               TI=0;
                          }
                     }
                  
                    
         
              else
                 {key1=1;                   //如果从机接受的既不是主机接受标志也不是主机发送标志，从机发送错误数据，从机请求主机重新发送数据
                  flag1=1;
                  SBUF=0xad;
                  while(TI==0)
                  {
                    ;
                  }
                 TI=0;
                }
           }
          
          
      else
          { 
            flag1=5;       //地址不正确
                           //************注意这里不回发任何数据**************
          }
  }

void display(void)
{ if(flag1==6)                       //从机显示标志
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
      receive();                 //通信子程序
      display();                 //显示子程序
    }     
}