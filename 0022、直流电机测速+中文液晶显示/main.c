#include <showfun.h>
#include <stdio.h>

extern char fnLCMInit(); // LCM 初始化
extern void at(unsigned char x,unsigned char y);/*设定文本x,y值*/
extern void cls();	 // 清屏
extern void charout(unsigned char *str); //ASCII(8*8) 显示函数
extern void fnSetPos(unsigned char urow, unsigned char  ucol);	// 设置当前地址
extern uchar dprintf(uchar x,uchar y,char *fmt);// ASCII(8*16) 及 汉字(16*16) 显示函数
extern uchar fnPR12(uchar uCmd); // 写无参数的指令
extern uchar fnPR13(uchar uData); // 写数据
extern unsigned int Adc0832(unsigned char channel);
extern void Line( unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, bit Mode);
extern void Pixel(unsigned char PointX,unsigned char PointY, bit Mode);



uchar dsp[10]={0,0,0,0,0,0,0,0,0,0,};
char abc[3]={0,0,0,};
uchar key=0;
uint a=100;
uchar n=5;
uchar count=1; 
uint k1=0;

uchar GeyKey();
void delay(uchar i);
void control();


main()
{  
     
 	fnLCMInit();
	fnSetPos(0,0);
	dprintf(0,0,"直流电机加-减速及测速系统");
	dprintf(0,12,"键盘+:步长加速");
	dprintf(0,24,"键盘-:步长减速");
	dprintf(0,36,"键盘=:顺时针转");
	dprintf(0,48,"键盘on/c:逆时针转");
     
     dprintf(0,72,"方向:");
  	 dprintf(0,84,"转速:");  
    
	 P1_1=0;
     TMOD=0x15;
	 TH1=0x3c;
	 TL1=0xb0;
     TH0=0x00;
	 TL0=0x00;
	 ET0=1;
	 ET1=1;
	 TR0=1;
	 TR1=1;
    
    while(1)
	{  key=GeyKey();
      switch(key)
       {   case '1': {          a=10;
	                            //sprintf(abc,"%3.2f",a/255.0);
		                        dprintf(0,96,"  5    r/min");   
                                //dprintf(0,96,abc);  
                                dprintf(60,96,"r/min");
	                            break;      }
	       case '2': {          a=25;dprintf(0,96,"  25    r/min");    break;      }
		   case '3': {          a=40; dprintf(0,96," 40    r/min");   break;      }
		   case '4': {          a=55; dprintf(0,96," 60    r/min");   break;      }
		   case '5': {          a=70; dprintf(0,96," 80    r/min");   break;      }
		   case '6': {          a=90; dprintf(0,96,"100    r/min");   break;      }
		   case '7': {          a=110; dprintf(0,96,"120    r/min");   break;      }
		   case '8': {          a=130; dprintf(0,96,"135    r/min");   break;      }
		   case '9': {          a=150; dprintf(0,96,"150    r/min");   break;      }
	       case '+': {          dprintf(0,72,"方向: 顺时针");
	                            control();
								break;
						}
           case '-': {         P1_0=0;
		                        dprintf(0,72,"方向: 逆时针");
		                         control();
		                        break;
					}
           case '=': {P1_0=1;dprintf(0,72,"方向: 顺时针");break;}
           case 'c': {P1_0=0;dprintf(0,72,"方向: 逆时针");break;}
           case '/': {dprintf(0,72,"方向: 顺时针");
	                            control();}
		   default:  break;
        }
    }
}


uchar GeyKey()
{
 	P1_4=0;
 	P1_5=1;
 	P1_6=1;
 	P1_7=1;
	P3_0=1;
	P3_1=1;
	P3_2=1;
    P3_3=1;
	_nop_();_nop_();
	if(!P3_0)return '7';
 	if(!P3_1)return '8';
 	if(!P3_2)return '9';
    if(!P3_3)return '/';
 	P1_4=1;
 	P1_5=0;
 	P1_6=1;
 	P1_7=1;
	_nop_();_nop_();
	if(!P3_0)return '4';
 	if(!P3_1)return '5';
 	if(!P3_2)return '6';
    if(!P3_3)return '*';

 	P1_4=1;
 	P1_5=1;
 	P1_6=0;
 	P1_7=1;
	_nop_();_nop_();
	if(!P3_0)return '1';
 	if(!P3_1)return '2';
 	if(!P3_2)return '3';
    if(!P3_3)return '-';


 	P1_4=1;
 	P1_5=1;
 	P1_6=1;
 	P1_7=0;
	_nop_();_nop_();
	if(!P3_0)return 'c';
 	if(!P3_1)return '0';
 	if(!P3_2)return '=';
    if(!P3_3)return '+';

	return 0;
}


void delay(uchar i)
{  uchar j,k;
    for(;i>0;i--)
    for(j=15;j>0;j--)
    for(k=11;k>0;k--);
}
	
	
	
void time()interrupt 3 
{    
     TR1=0;
     count++;
     k1+=TL0;
	 if(count==51)
	 {     
	      sprintf(dsp,"%3d",k1);
		  dprintf(0,108,dsp);   
          dprintf(60,108,"r/min");   
		  count=1;
          k1=0;
      }
	  TH1=0x3c;
	  TL1=0xb0;
	  TH0=0x00;
	  TL0=0x00;
	  TR1=1;

}

void control()
{                            
       EA=1;
	   while(1)
	   {    if(a>=150) 
               a=150;
			if(a<=10) 
			    a=10;
			 P1_1=0; 
			 delay(160-a);
			 P1_1=1;
			 delay(a);
			 key=GeyKey();
			 if(key=='-') a-=n;
			 else 
			   if(key=='+') a+=n;
			 else 
			   if(key=='=')
			   {  P1_0=1;
				   dprintf(0,72,"方向: 顺时针");
			 }
			 else 
			 if(key=='c') 
			 {  P1_0=0;
			   dprintf(0,72,"方向: 逆时针");
			 }
			 else  
			  if(key=='*')
			  {   P1_1=0;
			      break;
			  }
			  else
			 if(key!=0)
			   break;
			 }
		 EA=0;
}


