#include <reg51.h>
#include <absacc.h>
#define TR 1
#define uchar unsigned char
#define uint  unsigned int

uchar idata buf[10]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};  //从机1发送的数据
uchar idata buf1[10]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x09}; //从机2发送的数据
uchar idata buf2[3];                                                      //接受从机的数据
uchar data1,data2,data3;
uchar pf,addr,TRR,count,count1;
uchar flag,flag1,flag2=3;
uchar i; 

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
    SCON=0xd0;
} 



void send(uchar addr,uchar TRR)
{ 
                       
        
      TB8=1;  
      key1=1;                     //TB8置1
      SBUF=addr;                   //发送从机的地址 
       while(TI==0) 
         {
           ;
         }
       TI=0;
       key1=0;
      while(RI==0)
       {
        ;
       }
        data1=SBUF;                //接受从机地址并检验
        RI=0; 
       if(data1!=addr)             //从机地址有错误
         {
          flag2=0;
           
         }      
     else{                        //从机地址正确--------是发送数据标志0X01 
           if(TRR==0x01)          
               { 
                 TB8=0;            //TB8置0
                 key1=1;
                 SBUF=TRR;
                 while(TI==0)
                  {
                    ;
                  }
                  TI=0;
                  key1=0;
                 while(RI==0)       //接受从机状态
                      {
                        ;
                      }
                 data3=SBUF;
                 RI=0;
                 if(data3!=TRR)     //从机没有就绪
                     {
                      flag2=0;
                     }
                 
                 else{              //从机就绪
                       pf=0;        //清效验位
                       key1=1;  
                       for(i=0;i<=9;i++)         //发送数据   
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
                         SBUF=pf;                //发送效验和
                         while(TI==0)
                              {
                                ;
                              }
                         TI=0;
                         key1=0;
                         while(RI==0)            //主机接受从机是否正确接受数据
                               {
                                ;
                               }
                         data2=SBUF;
                         RI=0;
                         if(data2==0xcc)         //如果正确结束数据通信
                            {
                             flag2=3;            //通信结束标志
                            }
                         else{
                             flag2=0;            //如果不正确重新通信------即重新通信标志
                             }
                       }
                   }
             if(TRR==0x02)
                 {               //是接受从机数据标志------即TRR=0X0
                    TB8=0;
                    key1=1; 
                    SBUF=TRR;                    //发送接受标志0X02
                    while(TI==0)
                        {
                          ;
                        }
                    TI=0;
                    key1=0;
                    while(RI==0)                 //接受从机的状态
                       {
                           ;
                        }
                     data3=SBUF;
                     RI=0;
                     if(data3!=TRR)              //从机没有就绪
                          {
                             flag2=0;
                          }
                   
                     else{ key1=0;                     //从机就绪---主机接受数据
                           pf=0;
                           for(i=0;i<=2;i++)
                            { 
                              while(RI==0)
                                 {
                                   ;
                                  }
                              buf2[i]=SBUF;        //接受从机发送的数据
                              pf+=buf2[i];
                              RI=0;
                            }
                           key1=0;
                           while(RI==0)            //接受从机的效验和
                                {
                                  ;
                                }
                            data2=SBUF;            
                            RI=0;
                            if(pf==data2)         //比较效验和
                              {
                                flag2=3;          //效验和正确标志
                              }
                            else{
                                  flag2=0;        //效验和错误标志
                                 
                                }
                         }
                  }  
             
         }
    
 }

void  display(void)
{
     if(flag2==3)                  //如果接受正确开始显示
       {
        for(i=0;i<=2;i++)
          {
            P0=buf2[i];
            delay(50);
          }
       }
}

void main(void)
{
    delay(500);
    init();
    count=2;
    count1=2;
    while(1)
    {  
      while(count!=0) 
      { 
        count--;
        send(0x03,0x01);               //主机---从机1交换数据子函数
        send(0x03,0x02); 
         display(); 
      } 
      
      while(count1!=0)
        { count1--;
          send(0x04,0x01);               //主机---从机1交换数据子函数
          send(0x04,0x02); 
          display(); 
          
        }
       if(count1==0)
       {
        count1=2;
        count=2;
       }
     
      
    }
}