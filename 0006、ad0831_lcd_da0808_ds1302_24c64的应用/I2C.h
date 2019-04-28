#include <reg51.h>
#include <intrins.h>

#define HIGH 1
#define LOW 0
#define FALSE 0
#define TRUE ~FALSE
#define uchar unsigned char

sbit SCL = P0^4;
sbit SDA = P0^3;

//延时函数
void delay(void)
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}

//提供I2C总线工作时序中的起始位
void I_start(void)
{
	SDA = HIGH;
	delay();
	SCL = HIGH;
	delay();
	SDA = LOW;//当SCL为高时，SDA的一个下降沿作为起始位
	delay();
	SCL = LOW;
	delay();
}
//提供I2C总线工作时序中的停止位
void I_stop(void)
{
	SDA = LOW;
	delay();
	SCL = HIGH;
	delay();
	SDA = HIGH;//当SCL为高时，SDA的一个上升沿作为停止位
	delay();
	SCL = LOW;
	delay();
}
//I2C总线初始化
void I_init(void)
{
	SCL = LOW;
	I_stop();
}
//提供I2C总线的时钟信号，并返回时钟电平为高期间SDA信号线上状态
bit I_clock(void)
{
	bit sample;
	SCL = HIGH;
	delay();
	sample = SDA;
	SCL = LOW;
	delay();
	return (sample);
}
//向I2C总线发送8位数据，并请求一个应答信号ACK。如果收到ACK应答，则返回1，否则返回0。
bit I_send(uchar I_data)
{
	register uchar i;
	/*发送8位数据*/
	for(i=0;i<8;i++)
	{
		SDA = (bit)(I_data & 0x80);
		I_data <<= 1;
		I_clock();
	}
	/*请求应答信号ACK*/
	SDA = HIGH;
	delay();
	return(~I_clock());
}
//从I2C总线上接收8位数据信号，并将接收到的8位数据作为一个字节返回，不回送应答信号。
//主函数在调用本函数之前应保证SDA信号线处于浮置状态，SDA＝1.
uchar I_receive(void)
{
	uchar I_data = 0;
	register uchar i;
	for(i=0;i<8;i++)
	{
		I_data*=2;
		if(I_clock())I_data++;
	}
	return (I_data);
}
//向I2C总线发送一个应答信号ACK，一般用于连续数据读取时
void I_Ack(void)
{
	SDA = LOW;
	I_clock();
	SDA = HIGH;
}

