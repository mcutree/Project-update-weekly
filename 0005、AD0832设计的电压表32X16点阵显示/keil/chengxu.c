#include <intrins.h>
#include <reg52.h>
#include <stdio.h>

#define ulong unsigned long
#define uint unsigned int
#define uchar unsigned char
uchar k,i,j;
float l;
sbit sw=P3^0;      //159选通开关
sbit ADCS =P3^1;  //ADC0832 chip seclect
sbit ADDI =P3^3;  //ADC0832 k in
sbit ADDO =P3^3;  //ADC0832 k out
sbit ADCLK =P3^2;  //ADC0832 clock signal

uchar dsw[20];  //存放sprintf转换字符
uchar idata value[149]; //点阵字符储存
uchar code table[]={    //字符查表
0x00,0x00,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*".",0*/

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0xE0,0x0F,0x10,0x10,0x08,0x20,0x08,0x20,0x10,0x10,0xE0,0x0F,0x00,0x00,/*"0",1*/

0x00,0x00,0x10,0x20,0x10,0x20,0xF8,0x3F,0x00,0x20,0x00,0x20,0x00,0x00,0x00,0x00,/*"1",2*/

0x00,0x00,0x70,0x30,0x08,0x28,0x08,0x24,0x08,0x22,0x88,0x21,0x70,0x30,0x00,0x00,/*"2",3*/

0x00,0x00,0x30,0x18,0x08,0x20,0x88,0x20,0x88,0x20,0x48,0x11,0x30,0x0E,0x00,0x00,/*"3",4*/

0x00,0x00,0x00,0x07,0xC0,0x04,0x20,0x24,0x10,0x24,0xF8,0x3F,0x00,0x24,0x00,0x00,/*"4",5*/

0x00,0x00,0xF8,0x19,0x08,0x21,0x88,0x20,0x88,0x20,0x08,0x11,0x08,0x0E,0x00,0x00,/*"5",6*/

0x00,0x00,0xE0,0x0F,0x10,0x11,0x88,0x20,0x88,0x20,0x18,0x11,0x00,0x0E,0x00,0x00,/*"6",7*/

0x00,0x00,0x38,0x00,0x08,0x00,0x08,0x3F,0xC8,0x00,0x38,0x00,0x08,0x00,0x00,0x00,/*"7",8*/

0x00,0x00,0x70,0x1C,0x88,0x22,0x08,0x21,0x08,0x21,0x88,0x22,0x70,0x1C,0x00,0x00,/*"8",9*/

0x00,0x00,0xE0,0x00,0x10,0x31,0x08,0x22,0x08,0x22,0x10,0x11,0xE0,0x0F,0x00,0x00,/*"9",10*/

0x08,0x00,0x78,0x00,0x88,0x07,0x00,0x38,0x00,0x0E,0xC8,0x01,0x38,0x00,0x08,0x00,/*"V",11*/
};


void delay(int c)     //延时，C不能小于5
    {
    int i,j;
    for(i=0;i<c;i++)
        for(j=0;j<10;j++)
            ;
     }
/************
读ADC0832函数
************/

//采集并返回
unsigned int Adc0832(unsigned char channel)     //AD转换，返回结果
{
    uchar i=0;
    uchar j;
    uint dat=0;
    uchar ndat=0;

    if(channel==0)channel=2;
    if(channel==1)channel=3;
    ADDI=1;
    _nop_();
    _nop_();
    ADCS=0;//拉低CS端
    _nop_();
    _nop_();
    ADCLK=1;//拉高CLK端
    _nop_();
    _nop_();
    ADCLK=0;//拉低CLK端,形成下降沿1
    _nop_();
    _nop_();
    ADCLK=1;//拉高CLK端
    ADDI=channel&0x1;
    _nop_();
    _nop_();
    ADCLK=0;//拉低CLK端,形成下降沿2
    _nop_();
    _nop_();
    ADCLK=1;//拉高CLK端
    ADDI=(channel>>1)&0x1;
    _nop_();
    _nop_();
    ADCLK=0;//拉低CLK端,形成下降沿3
    ADDI=1;//控制命令结束 
    _nop_();
    _nop_();
    dat=0;
    for(i=0;i<8;i++)
    {
        dat|=ADDO;//收数据
        ADCLK=1;
        _nop_();
        _nop_();
        ADCLK=0;//形成一次时钟脉冲
        _nop_();
        _nop_();
        dat<<=1;
        if(i==7)dat|=ADDO;
    }  
    for(i=0;i<8;i++)
    {
        j=0;
        j=j|ADDO;//收数据
        ADCLK=1;
        _nop_();
        _nop_();
        ADCLK=0;//形成一次时钟脉冲
        _nop_();
        _nop_();
        j=j<<7;
        ndat=ndat|j;
        if(i<7)ndat>>=1;
    }
    ADCS=1;//拉低CS端
    ADCLK=0;//拉低CLK端
    ADDO=1;//拉高数据端,回到初始状态
    dat<<=8;
    dat|=ndat;
    return(dat);            //return ad k
}
/*************************************************
            点阵字符采集函数
**************************************************/

void tra(uchar *p)    //数组dsp[]里面的字符查询后，再储储存到另一个显示数组value[]
{ for(i=0;i<5;i++)
  {
      if(i<4)        //i=2时查的是句号，其他3个是电压值
      {
        for(j=0;j<16;j++)
        { 
          value[(i+1)*16+j]=table[(*p-0x2e)*16+j];
        }
       }
      else
      {  for(j=0;j<16;j++)      //电压符号V
          value[(i+1)*16+j]=table[12*16+j];
      }
      
      p++;
  }
  for(i=0;i<16;i++)           //前16个和后21个消隐作用，不显示
  value[i]=0;
  for(i=128;i<149;i++)
  value[i]=0;
}


void main()
    {

    unsigned int b=0,i,j;
    unsigned char a;



    while(1)
    {
    k=Adc0832(0);   //AD转换结果
    l=k/255.0*5.0;
    sprintf(dsw,"%2.3f",l);  //电压值转换成字符方式储存，不明白的人上百度查一下sprintf函数的运用就清楚的，俺也是查的
    tra(dsw);
    j=0;
    if(a>2) //移动间隔时间；越大移动越慢
        {
        a=0;
        b+=2;
        if(b>=85)  //显示到最后一个字，回头显示
            {
            b=0;
            }   
        }
     sw=1;   //显示字符，顺序是从左扫到右，有16列，数据电平是从左1到左16，由低到高
     for(i=0;i<16;i++)  //sw是154选通开关。
        {
        P1=i;
        P0=value[j+b];
        P2=value[j+b+1];
        delay(5);
        P0=0x00;
        P2=0x00;
        j+=2;
        }
     sw=0;
     for(i=0;i<16;i++)
        {
        P1=i;
        P0=value[j+b];
        P2=value[j+b+1];
        delay(5);
        P0=0x00;
        P2=0x00;
        j+=2;
        }
        a++;
     
    }
}

