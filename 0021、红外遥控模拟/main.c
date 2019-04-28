#include <AT89X51.h> 

static bit OP;        //红外发射管的亮灭
static unsigned int count;       //延时计数器
static unsigned int endcount; //终止延时计数
static unsigned char Flag;      //红外发送标志
char iraddr1;  //十六位地址的第一个字节
char iraddr2;  //十六位地址的第二个字节

void SendIRdata(char p_irdata);
void delay();
char getkey()
{
	  P1=0xfe;P3_6=P3_7=1;P3_3=1;
	  if(!P1_4)return 1;   //ON
	  if(!P1_5)return 2;   //7
	  if(!P1_6)return 3;   //8
	  if(!P1_7)return 4;   //9
	  if(!P3_6)return 5;   //X
	  if(!P3_7)return 6;   //÷
	  P1=0xfd;
	  if(!P1_4)return 11; //+-
	  if(!P1_5)return 12; //4
	  if(!P1_6)return 13; //5
	  if(!P1_7)return 14; //6
	  if(!P3_6)return 15; //-
	  if(!P3_7)return 16; //MRC
	  P1=0xfb;
	  if(!P1_4)return 21; //%
	  if(!P1_5)return 22; //1
	  if(!P1_6)return 23; //2
	  if(!P1_7)return 24; //3
	  if(!P3_6)return 25; //+
	  if(!P3_7)return 26; //M-
	  P1=0xf7;
	  if(!P1_4)return 31; //□
	  if(!P1_5)return 32; //0
	  if(!P1_6)return 33; //.
	  if(!P1_7)return 34; //=
	  if(!P3_6)return 35; //+
	  if(!P3_7)return 36; //M+

	  P1=0xfF;P3_3=0;
	  if(!P1_4)return 41; //
	  if(!P1_5)return 42; //
	  if(!P1_6)return 43; //
	  if(!P1_7)return 44; //
	  if(!P3_6)return 45; //
	  if(!P3_7)return 46; //
	  return 0;
}

void main(void) 
{
  char key;
  count = 0;
  Flag = 0;
  OP = 0;
  P3_4 = 1;
  EA = 1; //允许CPU中断 
  TMOD = 0x11; //设定时器0和1为16位模式1 
  ET0 = 1; //定时器0中断允许 

  P1=0xff;
  TH0 = 0xFF; 
  TL0 = 0xE6; //设定时值0为38K 也就是每隔26us中断一次  
  TR0 = 1;//开始计数

  iraddr1=0xff;
  iraddr2=0xff;


  do{
	  key=getkey();
      if(key==1)SendIRdata(0x12);//set
      if(key==11)SendIRdata(0x0b);//exit
      if(key==25||key==35)SendIRdata(0x1a);//+
      if(key==15)SendIRdata(0x1e);//-
      if(key==6)SendIRdata(0x0e);//↑ ÷
      if(key==16)SendIRdata(0x1d);//↓ MRC

      if(key==26)SendIRdata(0x1f);//← M-
      if(key==36)SendIRdata(0x1b);//→ M+
      if(key==32)SendIRdata(0x00);//0
      if(key==22)SendIRdata(0x01);//1
      if(key==23)SendIRdata(0x02);//2

      if(key==24)SendIRdata(0x03);//3
      if(key==12)SendIRdata(0x04);//4
      if(key==13)SendIRdata(0x05);//5
      if(key==14)SendIRdata(0x06);//6
      if(key==2)SendIRdata(0x07);//7
      if(key==3)SendIRdata(0x08);//8

      if(key==4)SendIRdata(0x09);//9
      if(key==21)SendIRdata(0x2A);//%
      if(key==5)SendIRdata(0x2B);//X
      if(key==33)SendIRdata(0x2C);//.
      if(key==34)SendIRdata(0x2D);//=
      if(key==31)SendIRdata(0x2E);//□

      if(key==41)SendIRdata(0x2F);//
      if(key==42)SendIRdata(0x30);//
      if(key==43)SendIRdata(0x31);//
      if(key==44)SendIRdata(0x32);//
      if(key==45)SendIRdata(0x33);//
      if(key==46)SendIRdata(0x34);//
  }while(1);
} 
//定时器0中断处理 
void timeint(void) interrupt 1 
{ 
  TH0=0xFF; 
  TL0=0xE6; //设定时值为38K 也就是每隔26us中断一次
  count++;

} 


void SendIRdata(char p_irdata)
{
  int i;
  char irdata=p_irdata;

  //发送9ms的起始码
  endcount=223;
  Flag=1;
  count=0;
  P3_4=0;
  do{}while(count<endcount);

  //发送4.5ms的结果码
  endcount=117;
  Flag=0;
  count=0;
  P3_4=1;
  do{}while(count<endcount);

  //发送十六位地址的前八位
  irdata=iraddr1;
  for(i=0;i<8;i++)
  {

     //先发送0.56ms的38KHZ红外波（即编码中0.56ms的低电平）
     endcount=10;
     Flag=1;
     count=0;
	 P3_4=0;
     do{}while(count<endcount);

    //停止发送红外信号（即编码中的高电平）
     if(irdata-(irdata/2)*2)  //判断二进制数个位为1还是0
     {
       endcount=15;  //1为宽的高电平
     }
    else
     {
     endcount=41;   //0为窄的高电平
     }
    Flag=0;
    count=0;
	P3_4=1;
    do{}while(count<endcount);

    irdata=irdata>>1;
  }

  //发送十六位地址的后八位
  irdata=iraddr2;
  for(i=0;i<8;i++)
  {
     endcount=10;
     Flag=1;
     count=0;
	 P3_4=0;
     do{}while(count<endcount);

     if(irdata-(irdata/2)*2)
     {
        endcount=15;
     }
     else
     {
       endcount=41;
     }
     Flag=0;
     count=0;
	 P3_4=1;
     do{}while(count<endcount);

     irdata=irdata>>1;
  }

  //发送八位数据
  irdata=~p_irdata;
  for(i=0;i<8;i++)
  {
     endcount=10;
     Flag=1;
     count=0;
	 P3_4=0;
     do{}while(count<endcount);

     if(irdata-(irdata/2)*2)
     {
         endcount=15;
     }
     else
     {
       endcount=41;
     }
     Flag=0;
     count=0;
	 P3_4=1;
     do{}while(count<endcount);

     irdata=irdata>>1;
  }

  //发送八位数据的反码
  irdata=p_irdata;
  for(i=0;i<8;i++)
  {
     endcount=10;
     Flag=1;
     count=0;
	 P3_4=0;
     do{}while(count<endcount);

     if(irdata-(irdata/2)*2)
     {
         endcount=15;
     }
     else
     {
       endcount=41;
     }
     Flag=0;
     count=0;
	 P3_4=1;
     do{}while(count<endcount);

     irdata=irdata>>1;
  }

  endcount=10;
  Flag=1;
  count=0;
  P3_4=0;
 do{}while(count<endcount);
  P3_4=1;
  Flag=0;
}

void delay()
{
  int i,j;
  for(i=0;i<400;i++)
  {
    for(j=0;j<100;j++)
    {
    }
  }
}


