
#include <at89x51.h>
#include "18b20.h"
#include "1302.h"
#include "12864.h"
#include "zifu.h"
uchar k,direction;
bit flag;
bit flag5=0;			   //flag5是外部中断1的标志位 flag1是步进标志
uchar p,dengji;               //定时次数 
bit flag1=0;
systemtime realtime;
bit first=1;				   //中断次数控制
void dingshi() interrupt 1  using 1  //定时程序.产生步进时间
{
   if(p--)
   {
    TL0=0;
	TH0=0xa0;
	flag1=0;
   }
   else
   {
     flag1=1;
	 TL0=0;
	 TH0=0x00;
	 p=20-(dengji>>1);
   }
 }
/*开始确认暂停键的判断*/
void zhongduan1() interrupt 2 using 2
{
   if(!flag5)
   {
     flag5=1;
   }
   else
   {
     flag5=0;
   }
}
void zhongduan() interrupt 0 using 0 
  {
    uchar i=0;
	if(first)	       //FIRST=1;打开方向按键判断标志
	{
	first=0;	    
	k=(P2>>6);	   
	k=k&0x03;				
	if(flag)
	  {
	    if(k==1)     direction=3;//左
	    if(k==2)	 direction=1;//右
   	  }
	  else
 	  {
	    if(k==0)	 direction=4;//上
	    if(k==3)	 direction=2;//下
   	  }
	}
  }
 /*显示四个小格的方块*/
void playbuf(uchar buff,char offsetx,char offsety)	  
{
  //i=(moxing+((dat&0xf0)|((dat&0x0f)<<2)));
  change1((((*(moxing+((buff&0xf0)+((buff&0x0f)<<2))))&0xf0)>>4)+offsetx,((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))))&0x0f)+offsety);
  change1((((*((moxing+((buff&0xf0)+((buff&0x0f)<<2))+1)))&0xf0)>>4)+offsetx,((*(((moxing+((buff&0xf0)|((buff&0x0f)<<2))))+1))&0x0f)+offsety);
  change1((((*(((moxing+((buff&0xf0)|((buff&0x0f)<<2))))+2))&0xf0)>>4)+offsetx,((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+2))&0x0f)+offsety);
  change1((((*(((moxing+((buff&0xf0)|((buff&0x0f)<<2))))+3))&0xf0)>>4)+offsetx,((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+3))&0x0f)+offsety);

}
/*判断方块停止向下运动*/
bit tingzhixia(uchar buff,char offsetx,char offsety)
{
   char x0,y0,x1,y1,x2,y2,x3,y3;
   bit tz=0;
   x0=(((*(moxing+((buff&0xf0)|((buff&0x0f)<<2))))&0xf0)>>4)+offsetx;
   x1=(((*((moxing+((buff&0xf0)|((buff&0x0f)<<2))+1)))&0xf0)>>4)+offsetx;
   x2=(((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+2))&0xf0)>>4)+offsetx;
   x3=(((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+3))&0xf0)>>4)+offsetx;
   y2=((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+2))&0x0f)+offsety;
   y3=((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+3))&0x0f)+offsety;
   y0=((*(moxing+((buff&0xf0)|((buff&0x0f)<<2))))&0x0f)+offsety;
   y1=((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+1))&0x0f)+offsety;
   
   if(readfk(x0+1,y0))
   {
      if(!((((x0+1)==x1)&&(y0==y1))|(((x0+1)==x2)&&(y0==y2))|(((x0+1)==x3)&&(y0==y3))))
	 { 
	  tz=1;
	  }
   }
    if(readfk(x1+1,y1))
   {
      if(!((((x1+1)==x0)&&(y1==y0))|(((x1+1)==x2)&&(y1==y2))|(((x1+1)==x3)&&(y1==y3))))
	 { 
	  tz=1;
	 }
   }
   if(readfk(x2+1,y2))
   {
      if(!((((x2+1)==x0)&&(y2==y0))|(((x2+1)==x1)&&(y2==y1))|(((x2+1)==x3)&&(y2==y3))))
	  {
	   tz=1;
	  }
   }
   if(readfk(x3+1,y3))
   {
      if(!((((x3+1)==x0)&&(y3==y0))|(((x3+1)==x1)&&(y3==y1))|(((x3+1)==x2)&&(y3==y2))))
	  {
	   tz=1;
	  }
   }
   return(tz);
}
/*判断一行是否可以消除*/
bit hangman(uchar x)
{
 uchar i;
 bit   man=1;
 for(i=0;i<15;i++)
 {
 	man=man&(readfk(x,i));
	if(!man)
	break;
 }
 return(man);
}
/*消除一行*/
void xiaohang(uchar x)
{
  uchar i,j;
  for(i=0;i<15;i++)
  {
    clear1(x,i);
  }
  for(i=1;i<=x;i++)
  {
   for(j=0;j<15;j++)
   {
     if(readfk(x-i,j))
	 {
	  change1(x-i+1,j);
	  clear1(x-i,j);
	 }
   }
  }
}
/*判断是否停止向右*/
bit tingzhiyou(uchar buff,char offsetx,char offsety)
{
   char x0,y0,x1,y1,x2,y2,x3,y3;
   bit tz=0;
   x0=(((*(moxing+((buff&0xf0)|((buff&0x0f)<<2))))&0xf0)>>4)+offsetx;
   x1=(((*((moxing+((buff&0xf0)|((buff&0x0f)<<2))+1)))&0xf0)>>4)+offsetx;
   x2=(((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+2))&0xf0)>>4)+offsetx;
   x3=(((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+3))&0xf0)>>4)+offsetx;
   y2=((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+2))&0x0f)+offsety;
   y3=((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+3))&0x0f)+offsety;
   y0=((*(moxing+((buff&0xf0)|((buff&0x0f)<<2))))&0x0f)+offsety;
   y1=((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+1))&0x0f)+offsety;
   if(readfk(x0,y0-1))
   {
      if(!(((x0==x1)&&((y0-1)==y1))|((x0==x2)&&((y0-1)==y2))|((x0==x3)&&((y0-1)==y3))))
	 { 
	   tz=1;
	  }
   }
   if(readfk(x1,y1-1))
     {
      if(!(((x1==x0)&&((y1-1)==y0))|((x1==x2)&&((y1-1)==y2))|((x1==x3)&&((y1-1)==y3))))
	 { 
	  tz=1;	   
	 }
 }
    if(readfk(x2,y2-1))
   {
      if(!(((x2==x0)&&((y2-1)==y0))|((x2==x1)&&((y2-1)==y1))|((x2==x3)&&((y2-1)==y3))))
	  {
	   tz=1;
	  }
   }
      if(readfk(x3,y3-1))
   {
      if(!(((x3==x0)&&((y3-1)==y0))|((x3==x1)&&((y3-1)==y1))|((x3==x2)&&((y3-1)==y2))))
	  {
	   tz=1;
	  }
   }
   return(tz);
}
/*判断是否停止向左*/
bit tingzhizuo(uchar buff,char offsetx,char offsety)
{
   char x0,y0,x1,y1,x2,y2,x3,y3;
   bit tz=0;
   x0=(((*(moxing+((buff&0xf0)|((buff&0x0f)<<2))))&0xf0)>>4)+offsetx;
   x1=(((*((moxing+((buff&0xf0)|((buff&0x0f)<<2))+1)))&0xf0)>>4)+offsetx;
   x2=(((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+2))&0xf0)>>4)+offsetx;
   x3=(((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+3))&0xf0)>>4)+offsetx;
   y2=((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+2))&0x0f)+offsety;
   y3=((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+3))&0x0f)+offsety;
   y0=((*(moxing+((buff&0xf0)|((buff&0x0f)<<2))))&0x0f)+offsety;
   y1=((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+1))&0x0f)+offsety;
   if(readfk(x0,y0+1))
   {
      if(!(((x0==x1)&&((y0+1)==y1))|((x0==x2)&&((y0+1)==y2))|((x0==x3)&&((y0+1)==y3))))
	 { 
	   tz=1;
	  }
   }
   if(readfk(x1,y1+1))
     {
      if(!(((x1==x0)&&((y1+1)==y0))|((x1==x2)&&((y1+1)==y2))|((x1==x3)&&((y1+1)==y3))))
	 { 
	  tz=1;	   
	 }
 }
    if(readfk(x2,y2+1))
   {
      if(!(((x2==x0)&&((y2+1)==y0))|((x2==x1)&&((y2+1)==y1))|((x2==x3)&&((y2+1)==y3))))
	  {
	   tz=1;
	  }
   }
      if(readfk(x3,y3+1))
   {
      if(!(((x3==x0)&&((y3+1)==y0))|((x3==x1)&&((y3+1)==y1))|((x3==x2)&&((y3+1)==y2))))
	  {
	   tz=1;
	  }
   }
   return(tz); 
}
/*清除一个方块*/
void clearbuf(uchar dat,char setx,char sety)
{
  uchar *i;
  i=(moxing+((dat&0xf0)|((dat&0x0f)<<2)));
  clear1(((((*i)&0xf0)>>4)+setx),(((*i)&0x0f)+sety));
  clear1(((((*(i+1))&0xf0)>>4)+setx),(((*(i+1))&0x0f)+sety));
  clear1(((((*(i+2))&0xf0)>>4)+setx),(((*(i+2))&0x0f)+sety));
  clear1(((((*(i+3))&0xf0)>>4)+setx),(((*(i+3))&0x0f)+sety));  
}
/*俄罗斯方块子程序*/
void fangkuai(void)
{
  uchar fenshu=0;
  char offsety,offsetx;
  char offsety_buff,offsetx_buff;
  uchar buff=0x10;		 
  bit ting=0;								
  uchar i;
  //flag5=1;
  TMOD=1;	  //定时器工作方式
  IT0=1;	  //边延有效
  IT1=1;
  EA=1;		  //开CPU中断
  ET0=1;	  //开定时器中断
  EX0=1;	  //开外部中断
  EX1=1;
  TL0=0x00;
  TH0=0x00;	  //定时器初值
  TR0=1;	  //启动定时器
  k=5;
  choose12864(2);
  clear12864();
  play16(0,0,0,els);
  play16(0,0,1,els+32);
  play16(0,0,2,els+64);
  play16(0,2,0,els+96);
  play16(0,2,1,els+128);
  play8(0,0,3,shu0);
  play8(0,1,3,shu0);
  vertical(1,60,30);
  vertical(1,60,127);
  for(i=0;i<98;i++)
  {
    dot(30+i,1);
	dot(30+i,62);
  }
  offsety=7;
  offsetx=-3;
  for(;;)
 {
   if(P3&0x04)
   first=1;
   if((k==0x02)&&((P3&0x04)==0x04))
   {
     offsety_buff=offsety;
	 ting=tingzhiyou(buff,offsetx,offsety);
	if(!ting)
	 {
	  if(((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+2))&0x0f)+offsety)
      offsety--;
	  clearbuf(buff,offsetx_buff,offsety_buff);
	  playbuf(buff,offsetx,offsety);
	  offsety_buff=offsety;
	  
    }
	  k=5;
   }
   if((k==0x01)&&((P3&0x04)==0x04))
   {

     offsety_buff=offsety;
	 ting=tingzhizuo(buff,offsetx,offsety);
	 if(!ting)
	{
 	 if(((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+3))&0x0f)+offsety<=13)
     offsety++;
	 k=5;
	 clearbuf(buff,offsetx_buff,offsety_buff);
	 playbuf(buff,offsetx,offsety);
	 offsety_buff=offsety;
	}
   }
   if((k==0x03)&&((P3&0x04)==0x04))
   {
     dengji=36;/////////////
	 k=5;
   }
   if((k==0x00)&&((P3&0x04)==0x04))
   {
      uchar i;
	  k=5;
	  i=buff;
	  buff++;
	  if((buff&0x0f)>=4)
	  buff=buff&0xf0;
	  
	  //change1(0,14);
      if(((*(((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+3))&0x0f)+offsety)>14)
       {
	     do
		  {
		  	offsety--;
		  }while((((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+3))&0x0f)+offsety)>14);
		 
	   }
	  if(((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+2))&0x0f)+offsety<0)
	  {
	    do
		{
		  offsety++;
		}while(((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+2))&0x0f)+offsety);
	  }
	  clearbuf(i,offsetx_buff,offsety_buff);
	  playbuf(buff,offsetx,offsety);
   }
   ting=tingzhixia(buff,offsetx,offsety);
   while(flag5);
   if(flag1)
   {
     offsetx_buff=offsetx;
	 offsety_buff=offsety;
     offsetx++;
	 clearbuf(buff,offsetx_buff,offsety_buff);
	 playbuf(buff,offsetx,offsety);
     offsetx_buff=offsetx;
	 flag1=0;
    }
   if((((((*((moxing+((buff&0xf0)+((buff&0x0f)<<2))+1)))&0xf0)>>4)+offsetx)>22)|ting)
   { 
    uchar i=0;
	if(hangman((((*((moxing+((buff&0xf0)+((buff&0x0f)<<2))+1)))&0xf0)>>4)+offsetx))
	{xiaohang((((*((moxing+((buff&0xf0)+((buff&0x0f)<<2))+1)))&0xf0)>>4)+offsetx);fenshu++;i++;}
   
	if((((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+2))&0xf0)>>4)+offsetx>=(((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+3))&0xf0)>>4)+offsetx)	 //x2>=x3
	{
	 if((((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+2))&0xf0)>>4)+offsetx<(((*((moxing+((buff&0xf0)|((buff&0x0f)<<2))+1)))&0xf0)>>4)+offsetx)	//x2<x1
	 {
	   if(hangman((((*((moxing+((buff&0xf0)+((buff&0x0f)<<2))+2)))&0xf0)>>4)+offsetx+i))
	   {xiaohang((((*((moxing+((buff&0xf0)+((buff&0x0f)<<2))+2)))&0xf0)>>4)+offsetx+i);fenshu++;i++;}
	 }
	 if((((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+3))&0xf0)>>4)+offsetx<(((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+2))&0xf0)>>4)+offsetx)	 //x3<x2
	  {
	   if(hangman((((*((moxing+((buff&0xf0)+((buff&0x0f)<<2))+3)))&0xf0)>>4)+offsetx+i))
	   {xiaohang((((*((moxing+((buff&0xf0)+((buff&0x0f)<<2))+3)))&0xf0)>>4)+offsetx+i);fenshu++;i++;}
	  }
	 if((((*(moxing+((buff&0xf0)|((buff&0x0f)<<2))))&0xf0)>>4)+offsetx<(((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+3))&0xf0)>>4)+offsetx)	 //x0<x3
	 {
	   if(hangman((((*(moxing+((buff&0xf0)+((buff&0x0f)<<2))))&0xf0)>>4)+offsetx+i))
	   {xiaohang((((*(moxing+((buff&0xf0)+((buff&0x0f)<<2))))&0xf0)>>4)+offsetx+i);fenshu++;i++;}
	 }
	}
	if((((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+2))&0xf0)>>4)+offsetx<(((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+3))&0xf0)>>4)+offsetx) //x2<x3
	{
	   if((((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+3))&0xf0)>>4)+offsetx<(((*((moxing+((buff&0xf0)|((buff&0x0f)<<2))+1)))&0xf0)>>4)+offsetx)
	   {
	     if(hangman((((*((moxing+((buff&0xf0)+((buff&0x0f)<<2))+3)))&0xf0)>>4)+offsetx+i))
	     {xiaohang((((*((moxing+((buff&0xf0)+((buff&0x0f)<<2))+3)))&0xf0)>>4)+offsetx+i);fenshu++;i++;}
	   }
	   if(hangman((((*((moxing+((buff&0xf0)+((buff&0x0f)<<2))+2)))&0xf0)>>4)+offsetx+i))
	   {xiaohang((((*((moxing+((buff&0xf0)+((buff&0x0f)<<2))+2)))&0xf0)>>4)+offsetx+i);fenshu++;i++;}
	   if((((*(moxing+((buff&0xf0)|((buff&0x0f)<<2))))&0xf0)>>4)+offsetx<(((*((moxing+((buff&0xf0)|((buff&0x0f)<<2)))+2))&0xf0)>>4)+offsetx)
	   {
	     if(hangman((((*(moxing+((buff&0xf0)+((buff&0x0f)<<2))))&0xf0)>>4)+offsetx+i))
	     {xiaohang((((*(moxing+((buff&0xf0)+((buff&0x0f)<<2))))&0xf0)>>4)+offsetx+i);fenshu++;i++;}
	   }
	}
	 
	play8(0,0,3,shu0+((fenshu/10)<<4));
	play8(0,1,3,shu0+((fenshu%10)<<4));
	dengji=fenshu/5;
	if(((((*(moxing+((buff&0xf0)+((buff&0x0f)<<2))))&0xf0)>>4)+offsetx)<1)
	{

	  delay1ms(450);
      delay1ms(450);
      choose12864(2);
      clear12864();
      play16(0,4,1,over);
      play16(0,6,1,over+32);
      play16(1,0,1,over+64);
      play16(1,2,1,over+96);
      delay1ms(450);
      delay1ms(450);
      break;
	}	
	buff=(((TL0%7)<<4)|(TH0%4));
	//buff=0x11;
    offsety=7;
    offsetx=-3;
	offsetx_buff=-9;
	offsety_buff=-9;
	} 
 } 
 
}					  


/*万年历子程序*/					  
void wannianli(void)
{
  uchar i;
  uchar count1=0;
  k=0;
  choose12864(2);
  init12864();
  clear12864();
  play8(0,0,0,shu2);		 //屏，列，页，地址
  play8(0,1,0,shu0);
  play16(0,4,0,nian);
  play16(1,0,0,yue);
  play16(1,4,0,ri);
  play16(0,2,1,shi);
  play16(0,6,1,fen);
  play16(1,2,1,miao);
  
  play16(1,0,2,xing);
  play16(1,2,2,qi);
  vertical(3,63,127);
  vertical(3,63,126);
  vertical(3,63,122);
  vertical(3,63,121);
   for(i=0;i<7;i++)
  {
    dot(121+i,3);
	dot(121+i,63);
  }
  for(i=0;i<12;i++)
  {
    dot(123,8+5*i);
  }
  for(i=0;i<7;i++)
  {
    if(i<4)
	{
	  play16(0,i<<1,3,yanyu+(i<<5));
	}
	if(i>=4)
	{
	  play16(1,(i-4)<<1,3,yanyu+(i<<5));
	}
  }
  init_ds1302();
  init_time();
  flag5=0;
  do
  {
     if(P3&0x04)
     first=1;
     init_ds1302();
     gettime(&realtime);
	 play8(0,2,0,(shu0+(datastring[0]<<4)));
	 play8(0,3,0,(shu0+(datastring[1]<<4)));
	 play8(0,6,0,(shu0+(datastring[2]<<4)));
	 play8(0,7,0,(shu0+(datastring[3]<<4)));
	 play8(1,2,0,(shu0+(datastring[4]<<4)));
	 play8(1,3,0,(shu0+(datastring[5]<<4)));
	 play8(0,0,1,(shu0+(datastring[6]<<4)));
	 play8(0,1,1,(shu0+(datastring[7]<<4)));
	 play8(0,4,1,(shu0+(datastring[8]<<4)));
	 play8(0,5,1,(shu0+(datastring[9]<<4)));
	 play8(1,0,1,(shu0+(datastring[10]<<4)));
	 play8(1,1,1,(shu0+(datastring[11]<<4)));
	 play16(1,4,2,(yi+((datastring[12]-2)<<5)));
	 gettemperature();
	 if(flagg)
	 {
	   play8(0,0,2,fu);
	   play8(1,6,3,fu);
	 }
	 else
	  {
	    clear8(6,4,0);
		play8(1,6,3,zheng);
	  }
	 play8(0,4+flagg,2,dian);
     play8(0,5+flagg,2,C);
	 play8(0,0+flagg,2,(shu0+(temp[0]<<4)));
	 play8(0,1+flagg,2,(shu0+(temp[1]<<4)));
	 play8(0,2+flagg,2,xiao);
	 play8(0,3+flagg,2,(shu0+(temp[2]<<4)));
	 play();
	 dot(124,3);
	 if((k==0x02)&&((P3&0x04)==0x04))
	 {
	   count1++;
	   if(count1==7)
	   count1=0;
	   switch (count1)
	   {
	     case 0:
		        {
                  play16(1,0,2,xing);
                  play16(1,2,2,qi);
				  k=0;break;
				}
	  
	     case 1:
		        {
				  play16_fb(0,4,0);			
				  k=0; break;
				}
		case 2:
		        {
                  play16(0,4,0,nian);
                  play16_fb(1,0,0);
				  k=0;break;				  
				}
	    case 3:
		        {
				  play16(1,0,0,yue);
                  play16_fb(1,4,0); 
				  k=0;break;
				}  
		case 4:
		        {
				  play16(1,4,0,ri);
                  play16_fb(0,2,1);
				  k=0;break;
				}
		case 5:
		        {
				  play16(0,2,1,shi);
                  play16_fb(0,6,1);
				  k=0;break;
				}
		case 6:
		        {
				   play16(0,6,1,fen);
				   play16_fb(1,0,2);
                   play16_fb(1,2,2);
				   k=0;break;
				}
		default:k=0;break;
	   }
	 }
	 if((k==0x03)&&((P3&0x04)==0x04))
	 {
	   switch(count1)
	   {
	     case 1:
		         {
				   setjia(ds1302_year);k=0;break;
				 }
		 case 2:
				 {
				   setjia(ds1302_month);k=0;break;
				 }
		 case 3:
				 {
				   setjia(ds1302_day);k=0;break;
				 }
	   	 case 4:
				 {
				   setjia(ds1302_hour);k=0;break;
				 }
		 case 5:
				 {
				   setjia(ds1302_minute);k=0;break;
				 }
		 case 6:
				 {
				  setjia(ds1302_week);k=0;break;
				 }
	   }
	 }
	 if((k==0x01)&&((P3&0x04)==0x04))
	 {
	   switch(count1)
	   {
	     case 1:
		         {
				   setjian(ds1302_year);k=0;break;
				 }
		 case 2:
				 {
				   setjian(ds1302_month);k=0;break;
				 }
		 case 3:
				 {
				   setjian(ds1302_day);k=0;break;
				 }
	   	 case 4:
				 {
				   setjian(ds1302_hour);k=0;break;
				 }
		 case 5:
				 {
				   setjian(ds1302_minute);k=0;break;
				 }
		 case 6:
				 {
				   setjian(ds1302_week);k=0;break;
				 }
	   }
	}
  }	while(!flag5);
}
/*贪吃蛇子程序*/
void tanchishe(void)													   
{	   
  uchar xdata length[102]={0,8,1,8};	 //存放蛇身的数组;
  uchar food[2]={12,8};
  uchar i,x,y;
  bit flag2,flag3,flag4;
  TMOD=1;	  //定时器工作方式
  IT0=1;	  //边延有效
  IT1=1;
  EA=1;		  //开CPU中断
  ET0=1;	  //开定时器中断
  EX0=1;	  //开外部中断
  EX1=1;
  TL0=0x00;
  TH0=0x00;	  //定时器初值
  TR0=1;	  //启动定时器

  dengji=2;
  p=20;
  direction=1;
  flag5=0;
  
  choose12864(2);
  clear12864();	
  vertical(1,61,30);
  vertical(1,61,127);
  for(i=0;i<98;i++)
  {
    dot(30+i,1);
	dot(30+i,62);
  }
  play16(0,0,0,tan);
  play16(0,0,1,chi);
  play16(0,0,2,she);
  change(length,(length+1));
  change((length+2),(length+3));
  change(food,food+1);
  for(;;)
  {
    do
   {
    first=1;
    while(flag5|!flag1);
    x=*(length);                               
    y=*(length+1);
    switch(direction)			   //右
	{
	  case 1:
	    {
	      for(i=0;i<dengji-1;i++)
	       {
	         *(length+(i<<1))=*(length+(i<<1)+2);
		     *(length+(i<<1)+1)=*(length+(i<<1)+3);
	       }
	       (*(length+(dengji<<1)-2))++;
		   flag=0;
		   break;
	      }
	   	case 2:					  //下
		 {
	      for(i=0;i<dengji-1;i++)
	       {
	         *(length+(i<<1))=*(length+(i<<1)+2);
		     *(length+(i<<1)+1)=*(length+(i<<1)+3);
	       }
		    (*(length+(dengji<<1)-1))++;
			flag=1;
			break;
		  }
		case 3:					//左
		 {
	       for(i=0;i<dengji-1;i++)
	       {
	         *(length+(i<<1))=*(length+(i<<1)+2);
		     *(length+(i<<1)+1)=*(length+(i<<1)+3);
	       }
	       (*(length+(dengji<<1)-2))--;
		   flag=0;
		   break;
		 }
		case 4:
		 {			//上
		 for(i=0;i<dengji-1;i++)
	       {
	         *(length+(i<<1))=*(length+(i<<1)+2);
		     *(length+(i<<1)+1)=*(length+(i<<1)+3);
	       }
		    (*(length+(dengji<<1)-1))--;
			flag=1;
			break;
		 }
	 }
	 flag4=((*(length+(dengji<<1)-2))==food[0])&&((*(length+(dengji<<1)-1))==food[1]);
	 if(flag4)	//
	 {
		for(i=dengji;i>0;i--)
		{
		  *(length+(i<<1))=*(length+(i<<1)-2);
		  *(length+(i<<1)+1)=*(length+(i<<1)-1);
		}
		*length=x;
		*(length+1)=y;
		dengji++;
		do
		{
		  flag3=0;
		  food[0]=TL0%24;
	      food[1]=TL0%15;
		  for(i=0;i<dengji-1;i++)	 //食物是否在蛇身身上
		  {
		    if((*(length+(i<<1)))==food[0]&&((*(length+(i<<1)+1))==food[1]))
			{
			  flag3=1;
			  break;
			 }
		  }
		}while(flag3);
		change(food,food+1); 
	 }
     flag2=1;	  //蛇头没有遇到蛇身
	 for(i=0;i<dengji-1;i++)
        {
		   if(*(length+(i<<1))==*(length+(dengji<<1)-2)&&(*(length+(i<<1)+1)==*(length+(dengji<<1)-1)))
		   {
		     flag2=0;
			 break;
			}
		}
	  flag2=flag2&&*(length+(dengji<<1)-2)>=0&&*(length+(dengji<<1)-2)<24;//蛇头是否出边界
	  flag2=flag2&&*(length+(dengji<<1)-1)>=0&&*(length+(dengji<<1)-1)<15;
	  if(flag2)
	   {
	    clear(&x,&y); 
		
	    
	     {
	       change(length+(dengji<<1)-2,length+(dengji<<1)-1);
	     }
		 if(flag4)
		 {
		   change(&x,&y);
		  }
	    flag1=0;
	    play8(0,0,3,shu0+((dengji/10)<<4));
	    play8(0,1,3,shu0+(((dengji)%10)<<4));
	   }
   }
   while(flag2);
   delay1ms(450);
   delay1ms(450);
   choose12864(2);
   clear12864();
   play16(0,4,1,over);
   play16(0,6,1,over+32);
   play16(1,0,1,over+64);
   play16(1,2,1,over+96);
   delay1ms(450);
   delay1ms(450);
   break;
  }
}
//////////////////////////////
main(void)
{
 uchar i;
 uchar count=0;
 P2=0xff;
  EA=1;		  //开CPU中断
  //ET0=1;	  //开定时器中断
  EX0=1;	  //开外部中断
  EX1=1;
 choose12864(2);
 init12864();
 clear12864();
 ////////////////////
 play16(0,4,0,tan);
 play16(0,6,0,chi);
 play16(1,0,0,she);
 ///////////////////
 play16(0,4,1,els);
 play16(0,6,1,els+32);
 for(i=0;i<3;i++)
 {
   play16(1,i<<1,1,(els+64+(i<<5)));
 }
 //////////////////

 play16(0,4,2,wnl);
 play16(0,6,2,wnl+32);
 play16(1,0,2,wnl+64);
 
 //////////////////
 for(;;)
  {
    if((k==0x03)&&((P3&0x04)==0x04))
   {
	count++;
	k=0;
	if(count==4)
	count=1;
	switch(count)
	{
	  case 1:
	         {
			    play16(0,4,2,wnl);
                play16(0,6,2,wnl+32);
                play16(1,0,2,wnl+64);
				play16_fb(0,4,0);
                play16_fb(0,6,0);
                play16_fb(1,0,0);
			 };break;
	  case 2: {
	  		   	 play16(0,4,0,tan);
                 play16(0,6,0,chi);
                 play16(1,0,0,she);
				 play16_fb(0,4,1);
                 play16_fb(0,6,1);
                 for(i=0;i<3;i++)
                 {
                   play16_fb(1,i<<1,1);
                  }
 	           };break;
	  case 3:
	          {
	            
				 play16(0,4,1,els);
                 play16(0,6,1,els+32);
                 for(i=0;i<3;i++)
                 {
                   play16(1,i<<1,1,(els+64+(i<<5)));
                 } 
				 play16_fb(0,4,2);
                 play16_fb(0,6,2);
                 play16_fb(1,0,2); 
	          };break;
	default:break;
	}
  }
  if(P3&0x04)
  first=1;
  if(flag5)
  {
    switch(count)
	{
	  case 1:flag5=0;tanchishe();count=0;flag5=0;k=0;break;
	  case 2:flag5=0;fangkuai();count=0;flag5=0; k=0;break;
	  case 3:flag5=0;wannianli();count=0;flag5=0;k=0;break;
	  default:count=0;k=3;flag5=0;break;
	}
	 choose12864(2);
     init12864();
     clear12864();
 ////////////////////
     play16(0,4,0,tan);
     play16(0,6,0,chi);
     play16(1,0,0,she);
 ///////////////////
     play16(0,4,1,els);
     play16(0,6,1,els+32);
     for(i=0;i<3;i++)
     {
       play16(1,i<<1,1,(els+64+(i<<5)));
     }
 //////////////////

     play16(0,4,2,wnl);
     play16(0,6,2,wnl+32);
     play16(1,0,2,wnl+64);
 //////////////////
  }
 }

}