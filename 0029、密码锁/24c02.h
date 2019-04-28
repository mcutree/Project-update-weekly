#ifndef _24c02_h
#define _24c02_h
#include<AT89x51.h> 
#define WriteDeviceAddress 0xa0
#define ReadDeviceAddress 0xa1
sbit SDA=P1^5;//I2C数据端
sbit SCL=P1^6;//I2C时钟端
///////////////////////24C0224C08读写驱动程序///////////////////////

void DelayMs(unsigned int number) 
{
unsigned char temp;
for(;number>=1;number--) 
{
  for(temp=112;temp>=1;temp--) ;
}
}
void i2cStart(void)
{
  SDA=1;
  SCL=1;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  SDA=0;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  SCL=0;
}
void i2cStop(void)
{
  SDA=0;
  SCL=1;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  SDA=1;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_(); 
}
void i2cAck(void)
{
  SDA=0;
  SCL=1;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  SDA=1;
  SCL=0;
}
void i2cNoAck(void)
{
  SDA=1;
  SCL=1;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  SDA=0;
  SCL=0;
}
void i2cWrite8Bit(unsigned char input)
{
  unsigned char temp;
  for(temp=8;temp!=0;temp--)
  {
    SDA=(bit)(input&0x80);
    SCL=1;
_nop_();
    _nop_();
    _nop_();
_nop_();
    _nop_();
SCL=0;
input=input<<1;
  }
  DelayMs(20);
}
unsigned char i2cRead8Bit(void)
{
  unsigned char temp,rbyte=0;
  for(temp=8;temp!=0;temp--)
  {
    SCL=1;
_nop_();
    _nop_();
    _nop_();
rbyte=rbyte<<1;
rbyte=rbyte|((unsigned char)(SDA));
SCL=0;
  }
  return(rbyte);
}

void i2cWrite24LC16B(unsigned char wdata,unsigned char RomAddress)
{
  i2cStart();
  i2cWrite8Bit(WriteDeviceAddress);
  i2cAck();
  i2cWrite8Bit(RomAddress);
  i2cAck();
  i2cWrite8Bit(wdata);
  i2cAck();
  i2cStop();
  DelayMs(20);
}
//写入多个字节到24c02中
//传入参数：地址、待写入的数据的首地址、数据长度
bit i2cWrite24c02_page(uchar RomAddress,uchar *WRdata,uchar length) 
{	
  uint i;
  i2cStart();
  i2cWrite8Bit(WriteDeviceAddress);
  i2cAck();
  i2cWrite8Bit(RomAddress);
  i2cAck();
  for(i=0;i<length;i++)
  {
    i2cWrite8Bit(*WRdata);
   	i2cAck();
	WRdata++;
   }	
	i2cStop();
   DelayMs(20);
   return(1);
} 
 
unsigned char i2cRead24LC16B(unsigned char RomAddress)
{
  unsigned char x;
  i2cStart();
  i2cWrite8Bit(WriteDeviceAddress);
  i2cAck();
  i2cWrite8Bit(RomAddress);
  i2cAck();
  i2cStart();
  i2cWrite8Bit(ReadDeviceAddress);
  i2cAck();
  _nop_();
  _nop_();
  _nop_();
  x=0;
  x=i2cRead8Bit();
  i2cNoAck();
  i2cStop();
  return(x);
}
//从24c02中读出多个字节
bit Read_page24c02(uchar RomAddress,uchar p[],uint n) 
{   uint i;
	i2cStart();
  i2cWrite8Bit(WriteDeviceAddress);
  i2cAck();
  i2cWrite8Bit(RomAddress);
  i2cAck();
  i2cStart();
  i2cWrite8Bit(ReadDeviceAddress);
  i2cAck();
  _nop_();
  _nop_();
  _nop_();
   for(i=0;i<n-1;i++)
  {
   
   p[i]=i2cRead8Bit();
   i2cAck();
   }
   p[n-1]=i2cRead8Bit();
   i2cNoAck();
   i2cStop();
   return(1);
   }
 #endif