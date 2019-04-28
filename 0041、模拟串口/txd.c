#include <AT89X51.H>
#define uchar unsigned char
#define RXD P1_0
#define TXD P1_1

//计数器初始化
void S2INI(void)
{
    TMOD |=0x02;                //计数器0，方式2
    TH0=0xA0;                    //预值为256-96=140，十六进制A0
    TL0=TH0;        
    TR0=1;                        //开始计数
    TF0=0;
}

//查询计数器溢出标志位
void WaitTF0( void )
{
    while(!TF0);
    TF0=0;
}

void WByte(uchar input)
{
    //发送启始位
    uchar i=8;
    TR0=1;
    TXD=(bit)0;
    WaitTF0();
    //发送8位数据位
    while(i--)
    {
        TXD=(bit)(input&0x01);     //先传低位
        WaitTF0();
        input=input>>1;
    }
    //发送校验位(无)
    //发送结束位
    TXD=(bit)1;
    WaitTF0();
    TR0=0;
}    
void delay()
{
 uchar i,j,k;
 for(i=100;i>0;i--)
 for(j=20;j>0;j--)
 for(k=248;k>0;k--);
}
void main(void)
{
 S2INI();
 while(1)
 {
   WByte(0x7f);
   delay();
   WByte(0xff);
	delay();
 }
}