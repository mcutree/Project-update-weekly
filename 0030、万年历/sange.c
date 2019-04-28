#include<reg51.h>
#include<absacc.h>
#define uchar unsigned char 
#define uint  unsigned int
#define ture  1
#define fault 0

sbit SET=P1^7;

void  delay(uchar  k) ;
uchar monthday(uchar a,uchar b);
void display()	;

uchar code dayofmonth[]={31,28,31,30,31,30,31,31,30,31,30,31};
uchar code scan[]={0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,
                    0xe8,0xe9,0xea,0xeb,0xec,0xed,0xee,0xef,
					0xf8,0xf9,0xfa,0xfb,0xfc,0xfd};
					//扫描的译码信号
uchar i;
uchar code table[]={0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0xA7,0xFF,0xEF,0xC0};
uchar  buffer[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uchar  shuju=0;
uchar  state=0;
uchar  qxiang;

typedef  struct  
         {
		 uchar year[2];
		 uchar month;
		 uchar day;
		 uchar week;
		 }date;
typedef  struct  
        {
	    uchar hour;
		uchar minute;
		uchar second;
		}time;
uchar  count=0;
date today={{9,20},4,20,1};
time now={11,8,10};
void main()
{
TMOD=0x01;
TL0=(65536-1000)%256;
TH0=(65536-1000)/256;
IE=0x82;	  //EA=1;ET0=1总中断允许和定时器中断允许
TCON=0x10;	  //定时器启动计数
while(1)
    {
	 P1=0xff;

	 shuju=P1&0xff;
	 qxiang=shuju&0x80;
		switch(qxiang)
	    {
		 case(0x80):switch(shuju)
			      {
				 case(0xfe) :			   //秒调整
		            {
					 EA=1;
					 EX0=1;           //IE=0x83;			//EA=1;ET0=1;EX0=0总中断允许，定时器中断允许，外中断允许
					 IT0=1;           //TCON=0x11;			//TR0=1;IT0=1;定时器启动,外中断为负边沿触发
			         }break;
	           	 case(0xfd)	:			 //分调整
		            {
					 EA=1;
					 EX0=1;                  // IE=0x83;
					 IT0=1;                    //TCON=0x11;
			         }break;
	           	 case(0xfb) :			//时调整
		            {
					EA=1;
					 EX0=1;
					 IT0=1;
					
			         }break;
                 case(0xf7) :			   //星期调整
		            {
					EA=1;
					 EX0=1;
					 IT0=1;
			      
			         }break;
                 case(0xef) :					//日调整
	 	            {
					EA=1;
					 EX0=1;
					 IT0=1;
				
			         }break;
                 case(0xdf):				 //月调整
	 	            {
					EA=1;
					 EX0=1;
					 IT0=1;
				
			         }break;
                 case(0xbf):					//年调整
		            {
					EA=1;
					 EX0=1;
					 IT0=1;
					
			         }break;
			     default:						 //时钟正常计时
	                {
					EA=1;
					TR0=1;
					EX0=0;
				
					}break;
				}break;
		 case(0x00) :switch(shuju)
					     {
			   case(0x7e):
	                {
					EA=1;
					 EX0=1;
					 IT0=1;
					
					}break;
	           case(0x7d):
	                {
					EA=1;
					 EX0=1;
					 IT0=1;
				
					}break;
	           case(0x7b):
	                {
					EA=1;
					 EX0=1;
					 IT0=1;
			    
					}break;
	           case(0x77):
	                {
					EA=1;
					 EX0=1;
					 IT0=1;
				
					}break;
	           case(0x6f):
	                {
					EA=1;
					 EX0=1;
					 IT0=1;
					
					}break;
	           case(0x5f):
	                {
					 EA=1;
					 EX0=1;
					 IT0=1;
					
					}break;
	           case(0x3f):
	                {
					EA=1;
					 EX0=1;
					 IT0=1;
					
					}break;
	           default:						 //时钟正常计时
	                {
					EA=1;
					TR0=1;
					EX0=0;
						
					}break;
		    	}break;       
		}
	}
}

void inter0()  interrupt 0  using 0
  {
  uchar result,z; 
  result=shuju;
       	switch(qxiang)
	    {
		 case(0x80):   switch(result)
					   {
                       	case(0xfe) :					  // if(result==0xfe)				   //秒调整	+
	                         {
	                           now.second++;
	                           if(now.second>=60)
	                              {
		                            now.second=0;
		                           }
	                           display();
	                          }break;
   
                         case(0xfd) :		             //if(result==0xfd)					 //分调整  +
	                         {
	                            now.minute++;
	                            if(now.minute>=60)
	                             {
		                           now.minute=0;
		                          }
	                             display();
	                         }break;
   
                            case(0xfb) :		   //if(result==0xfb)				   //时调整	+
	                          {
	                             now.hour++;
	                             if(now.hour>=24)
	                                {
		                              now.hour=0;
	                             	}
	                                display();
	                          }break;
 
                             case(0xf7)	:		  // if(result==0xf7)	               //星期调整 +
	                              {		   
	                                 today.week++;
	                                  if(today.week>=8)
	                                      {
		                                    today.week=1;
		                                   }
	                                  display();
	                              }break;

	                          case(0xef) :			//if(result==0xef)				   //日期调整	 +
	                              {
	                                 today.day++;
	                                 z = monthday( today.year[1]  ,  today.year[0] );
	                                 if((z==1)&&(today.month==2))
									    {
										  if(today.day>=30)
			                                 today.day=1;
										}

		                              else if (today.day>dayofmonth[today.month-1])
		                                            today.day=1;
	                                   display();
	                                }break;	  
   	
	                          case(0xdf) :			 //if(result==0xdf)					//月调整	+
		
		                            {
	                                	today.month++;
	           	                        if(today.month>=13)
		                                   {
			                                 today.month=1;
			                                }
		                                display();
		                               } break;
   
	    
		                       case(0xbf) :					 //if(result==0xbf)					  //年调整 +
		                             {
	                                   today.year[0]=today.year[0]+1;
		                               if(today.year[0]>=100)
		                                   {
			                                 today.year[0]=0;
			                                 today.year[1]=today.year[1]+1;
			                                 if(today.year[1]>=100)
			                                    {
				                                   today.year[1]=0;
				                                 }
			                                 }
		                                 display();
	 	                              }break;
		                       default:						 //时钟正常计时
	                                 {
									 EA=1;
					                 TR0=1;
					                 EX0=0;
									 		                 
					                 }break;
					         }break; 
					
  case(0x00): switch(result)
			{
			  case(0x7e):				//if(result==0x7f)					 //秒调整—
	                  {
	   	               if(now.second>0)
		                  now.second=now.second-1;
		               else  now.second=59;
		                    display();
	                  }break;
	
  case(0x7d):						//if(result==0x7d)					  //分调整—
	   {
	   	if(now.minute>0)
		   now.minute=now.minute-1;
		else now.minute=59;
		display();
	   }  break;
	
  case(0x7b) :					  //if(result==0x7b)					  //  时调整-
	   
	   {
	   	if(now.hour>0)
		   now.hour=now.hour-1;
		else now.hour=23 ;
		display();
	   }break;
	
	case(0x77) :					 //if(result==0x77)					 //	 周调整—
	   {
	    if(today.week>1)
		   today.week=today.week-1;
		else today.week=7;
		display();
	   }break;

	  
	case(0x6f):							   	//if(result==0x6f)				  //	 日期调整—
	   {
	    z = monthday( today.year[1]  ,  today.year[0] );
	   	if((z==1)&&(today.month==2))
		   {
		   if(today.day>1)
		      today.day=today.day-1;
			else today.day=29;
		   }
		else {
			  if(today.day>1)
			     today.day=today.day-1;
			  else today.day=dayofmonth[today.month-1];
		      }
		display();
	   }break;

	 case(0x5f):							//if(result==0x5f)					//	月调整—
	   {
	   	if(today.month>1)
		   today.month=today.month-1;
		else today.month=12;
		display();
	   }break;
	 case(0x3f) :	  // 年调整——
	   {
	   	if(today.year[0]>0)
		   today.year[0]=today.year[0]-1;
		else 
		    {
			 today.year[0]=99;
			 today.year[1]=today.year[1]-1;
			}
		display();
	   }break;
	 default:						 //时钟正常计时
	                {
				    EA=1;
					TR0=1;
					EX0=0;	
					}break;
	     }break;
		}
	}
 
void  timer0_int() interrupt 1 using 1
{
uchar c;
 TL0=(65536-1000)%256;		  //中断时间是10ms
 TH0=(65536-1000)/256;
 TR0=1;
 count++;
 if(count==35)
    {
	count=0;
	now.second=now.second+1;
	 if(now.second>=60)
	    {
		now.second=0;
		now.minute++;
		if(now.minute>=60)
		   {
		   now.minute=0;
		   now.hour++;
		   if(now.hour>=24)
		      {
			  now.hour=0;
			  today.week++;
			  today.day++;
			  if(today.week>=8)
			     {
				 today.week=1;
				 }
			  c=monthday( today.year[1], today.year[0]);
			  if((c==1)&&(today.month==2))
			     {
				 if(today.day>=30)
				   {
				    today.day=1;
					today.month++;
				   }
				  
				 }
			  else if(today.day>=(dayofmonth[today.month-1]+1))
			          {
					  today.day=1;
					  today.month++;
			   if(today.month>=13)
			      {
				   today.month=1;
				   today.year[0]=today.year[0]+1;
				   if(today.year[0]>=100)
				      {
					  today.year[0]=0;
					  today.year[1]=today.year[1]+1;
					  if(today.year[1]>=100)
					     {
						 today.year[1]=0;
						 }
					  }
				  }
			  }
		   }
		  }
		}
	}
    display();
}
void  delay(uchar  k)
  {
  uchar m,n;
  for(m=0;m<=k;m++)
   for(n=0;n<=40;n++);
  }
  //  计算年份程序
uchar  monthday(uchar a,uchar b)
  {
   uchar x,y;
   x=a*100+b;
   if(x%4!=0)
	  y=0;
   else if(x%100!=0)
      y=1;
   else if(x%400!=0)
      y=0;
   else y=1;
   
 //if((x%4==0 && x%100!=0)|| (x%400==0))
 //   y=1;
// else y=0; 
   return(y) ;
  }	
 void display()
 {
  buffer[0]=now.second%10;
  buffer[1]=now.second/10;
  buffer[2]=10;
  buffer[3]=now.minute%10;
  buffer[4]=now.minute/10;
  buffer[5]=10;
  buffer[6]=now.hour%10;
  buffer[7]=now.hour/10;
  buffer[8]=today.week%10;
  buffer[9]=today.week/10;
  buffer[10]=10;
  buffer[11]=today.day%10;
  buffer[12]=today.day/10;
  buffer[13]=10;
  buffer[14]=today.month%10;
  buffer[15]=today.month/10;
  buffer[16]=10;
  buffer[17]=today.year[0]%10;
  buffer[18]=today.year[0]/10;
  buffer[19]=today.year[1]%10;
  buffer[20]=today.year[1]/10;
  buffer[21]=10;
   for(i=0;i<=21;i++)
    {
	P0=table[buffer[i]];	
	P2=scan[i];
	delay(8);
	P2=0xFF;
	}
 }