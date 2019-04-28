/***************************************
名称:2008奥运会倒计时
***************************************/
#include<reg51.h>
#include<absacc.h>
#include<intrins.h>
#include "delay.h"
#define clock_segment XBYTE[0xBFFF] //时钟段码地址
#define clock_sel XBYTE[0x7FFF]     //时钟位码地址
#define year_segment XBYTE[0xEFFF]  //日历段码地址
#define year_sel XBYTE[0xDFFF]      //日历位码地址
#define retime_segment XBYTE[0xFBFF]//倒计时段码地址
#define retime_sel XBYTE[0xF7FF]    //倒计时位码地址

unsigned char time_num=0;//定时一秒次数
unsigned char shi_num=24;//小时位计数
unsigned char miao_ge=0; //秒个位
unsigned char miao_shi=0;//秒十位
unsigned char fen_ge=0;//分个位
unsigned char fen_shi=4;//分十位
unsigned char shi_ge=8;//时个位
unsigned char shi_shi=0;//时十位
unsigned char year_thousand=2;
unsigned char year_hundred=0;
unsigned char year_decade=0;
unsigned char year_unit=7;
unsigned char month_decade=0;
unsigned char month_unit=6;
unsigned char day_decade=2;
unsigned char day_unit=6;
unsigned char retime_unit=0;
unsigned char retime_decade=1;
unsigned char retime_hundred=4;
unsigned char retime_thousand=0;

unsigned char year_thoustore; //保存年千位数据
unsigned char year_hundstore; //保存年百位数据
unsigned char year_decastore; //保存年十位数据
unsigned char year_unitstore; //保存年个位数据
unsigned char month_unitstore;//保存月个位数据
unsigned char month_decastore;//保存月十位数据
unsigned char day_unitstore;  //保存日个位数据
unsigned char day_decastore;  //保存日十位数据
unsigned char year_unitstore2;//保存年各位数据
unsigned char year_decastore2;//年位组合子程序用来保护数据用
unsigned char year_hundstore2;
unsigned char year_thoustore2;
unsigned char retime_ustore;  //保存倒计时各位数据
unsigned char retime_dstore;
unsigned char retime_hstore;
unsigned char retime_tstore;
unsigned char day_numj=31;  //奇数月31天
unsigned char day_numo=30;  //偶数月30天
unsigned char day_numooo=30;
unsigned char day_numoo;
unsigned char month_num=12;
unsigned int year_jointed; //年各位组合在一起,以便进行闰年判断
unsigned int year_help1;
unsigned int year_help2;
unsigned char xiaoshi_ge;//闪烁时存小时个位
unsigned char xiaoshi_shi;//闪烁时存小时十位
unsigned char fenzhong_ge;//闪烁时存分钟个位
unsigned char fenzhong_shi;//闪烁时存分钟十位
unsigned char cort=0;//判断第几次按下确认键
sbit key_sure=P1^0;//调时或确认键
sbit key_dec=P1^2;//调时减键
bit first_sure=0; //第一次按下确认键
bit second_sure=0;//第二次按下确认键
bit third_sure=0; //第三次按下确认键
bit fourth_sure=0;//第四次按下确认键
bit fifth_sure=0; //第五次按下确认键
bit sixth_sure=0; //第六次按下确认键
bit seventh_sure=0;//第七次按下确认键
unsigned code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};//段码表
/************函数声明*************/
void shannum_jian(void);
void inc_key(void);
void dec_key(void);
void dis_dingshi(void);
void hour_shanshuo(void);
void min_shanshuo(void);
void kbscan(void);
void display(void);
void year_joint(void);
unsigned char judgement_leap(void);
void retime_flash(void);
/********************************
显示子程序
*********************************/
void display(void)
{
    clock_sel=0xdf; 
    clock_segment=table[miao_ge];        //送秒个位段位码
    delay(3);
    clock_sel=0xef;
    clock_segment=table[miao_shi];       //送秒十位段位码
    delay(3);
    clock_sel=0xf7; 
    clock_segment=table[fen_ge]|0x80;    //送分个位段位码
    delay(3);
    clock_sel=0xfb;
    clock_segment=table[fen_shi];        //送分十位段位码
    delay(3);
    clock_sel=0xfd;
    clock_segment=table[shi_ge]|0x80;    //送时个位段位码
    delay(3);
    clock_sel=0xfe;
    clock_segment=table[shi_shi];        //送时十位段位码
    delay(3);
    year_sel=0x7f;
    year_segment=table[day_unit];        //送日个位段位码
    delay(3);
    year_sel=0xbf;
    year_segment=table[day_decade];      //送日十位段位码
    delay(3);
    year_sel=0xdf;
    year_segment=table[month_unit]|0x80; //送月个位段位码
    delay(3);
    year_sel=0xef;
    year_segment=table[month_decade];    //送月十位段位码
    delay(3);
    year_sel=0xf7;
    year_segment=table[year_unit]|0x80;  //送年个位段位码
    delay(3);
    year_sel=0xfb;
    year_segment=table[year_decade];     //送年十位段位码
    delay(3);
    year_sel=0xfd;
    year_segment=table[year_hundred];    //送年百位段位码
    delay(3);
    year_sel=0xfe;
    year_segment=table[year_thousand];   //送年千位段位码
    delay(3);
    retime_sel=0xf7;
    retime_segment=table[retime_unit];   //送倒计时个位段位码
    delay(3);
    retime_sel=0xfb;
    retime_segment=table[retime_decade]; //送倒计时十位段位码
    delay(3);
    retime_sel=0xfd;
    retime_segment=table[retime_hundred];//送倒计时百位段位码
    delay(3);
    retime_sel=0xfe;
    retime_segment=table[retime_thousand];//送倒计时千位段位码
    delay(3);

}
/**********************************
判断闰年子程序
***********************************/
unsigned char judgement_leap(void)
{
    year_joint();       //调用年各位组合子程序
    if((year_jointed%4==0&&year_jointed%100!=0)||(year_jointed%100==0&&year_jointed%400==0))return(29); //是闰年二月29天
    else return(28);    //是平年二月28天	
}
/**********************************
按键扫描子程序
***********************************/
void kbscan(void)
{
    unsigned char sccode;
    P1=0xff;
    if((P1&0xff)!=0xff)
    {
        //delay(5); 
        display();
        display();
        display();
            		
        if((P1&0xff)!=0xff)
    	{
             sccode=P1;
             //while((P1&0xff)!=0xff)     //按键后消陡
        	 //{
        	 //	;
        	// }
             switch(sccode)
        	 {
                case 0xfe:shannum_jian();break;
                case 0xfd:inc_key();	 break;
                case 0xfb:dec_key();	 break;
                default:			 	 break;
        	 }
    	}
    }
}
/********************************
确认键按键次数子程序
********************************/
void shannum_jian(void)
{   
    cort++;
    if(cort==1)          //第一次按下确认键
    {
        first_sure=1;
        second_sure=0;
        third_sure=0;
        fourth_sure=0;
        fifth_sure=0;
        sixth_sure=0;
        seventh_sure=0;
    	
    }
    else if(cort==2)    //第二次按下确认键
    {	
        first_sure=0;
        second_sure=1;
        third_sure=0;
        fourth_sure=0;
        fifth_sure=0;
        sixth_sure=0;
        seventh_sure=0;
    	
    }
    else if(cort==3)    //第三次按下确认键
    {
        first_sure=0;
        second_sure=0;
        third_sure=1;
        fourth_sure=0;
        fifth_sure=0;
        sixth_sure=0;
        seventh_sure=0;
    	
    }
    else if(cort==4)   //第四次按下确认键
    {
        first_sure=0;
        second_sure=0;
        third_sure=0;
        fourth_sure=1;
        fifth_sure=0;
        sixth_sure=0;
        seventh_sure=0;
    		
    }
    else if(cort==5)   //第五次按下确认键
    {
        first_sure=0;
        second_sure=0;
        third_sure=0;
        fourth_sure=0;
        fifth_sure=1;
        sixth_sure=0;
        seventh_sure=0;
    		
    }
    else if(cort==6)   //第六次按下确认键
    {
     	
        first_sure=0;
        second_sure=0;
        third_sure=0;
        fourth_sure=0;
        fifth_sure=0;
        sixth_sure=1;
        seventh_sure=0;
    		
    }
    else if(cort==7)  //第七次按下确认键
    {
        cort=0;
        first_sure=0;
        second_sure=0;
        third_sure=0;
        fourth_sure=0;
        fifth_sure=0;
        sixth_sure=0;
        seventh_sure=1;
    }		

}
/*******************************
减一键子程序
*******************************/
void dec_key(void)
{
    if(first_sure)                          //第一次按下确认键,小时位减
    {
        if(shi_num!=24)
    	{
            ++shi_num;
            if((--xiaoshi_ge)==255)
    		{
                xiaoshi_ge=9;
                if((--xiaoshi_shi)==255)
        		{
                    xiaoshi_shi=2;
                    xiaoshi_ge=3;
        		}
        	}	
    	}
        else if(shi_num==24)
    	{
            shi_num=1;
            xiaoshi_ge=3;
            xiaoshi_shi=2;
    	}
    }
    else if(second_sure)                         //第二次按下确认键,分钟位减
    {
        if((--fenzhong_ge)==255)
    	{
            fenzhong_ge=9;
            if((--fenzhong_shi)==255)
    		{
                fenzhong_shi=5;
    		}
    	}
    }
    else if(third_sure)                           //第三次按下确认键,年位减
    {
        if((--year_unitstore)==255)
    	{
            year_unitstore=9;
            if((--year_decastore)==255)
    		{
                year_decastore=9;
                if((--year_hundstore)==255)
        		{
                    year_hundstore=9;
                    if((--year_thoustore)==255)
        			{
                        year_thoustore=9;
        			}
        		}
    		}
    	}
    }
    else if(fourth_sure)                        //第四次按下确认键,月位减
    {
        if(month_num!=12)
    	{
              ++month_num;
              if((--month_unitstore)==255)
        	  {
                    month_unitstore=9;
                    --month_decastore;
        	  }
    	}
        else if(month_num==12)
    	{
            month_num=1;
            month_unitstore=2;
            month_decastore=1;
    	}
    }
    else if(fifth_sure)                         //第五次按下确认键,日位减
    {           										 
        if((month_unitstore|0xfe)==0xff)        //是奇数月,日为31天
         {	
            if((day_numj)!=31)
    		{
                ++day_numj;
                if((--day_unitstore)==255)
        		{
                    day_unitstore=9;
                    --day_decastore;
        		}
    		}
            else if(day_numj==31)
    		{
                day_numj=1;
                day_unitstore=1;
                day_decastore=3;
    		}
    	}
        else if((month_unitstore|0xfe)!=0xff)      //是偶数月,日为30天
    	{
    		
        	if(
    		
            month_unitstore==2)         	   //是二月
        	{	
                        if(day_numo!=day_numoo)
        				{	
                    		++day_numo;
                            if((--day_unitstore)==255)
        					{
                        	day_unitstore=9;
                        	--day_decastore;
        					}
        				}
    			
                        else if(day_numo==day_numoo)
        				{
                            if(day_numoo==28)
            				{	
                    			day_numo=1;
                        		day_unitstore=8;
                        		day_decastore=2;
        					}
                            else if(day_numoo==29)
        					{
                        	   	day_numo=1;
                        		day_unitstore=9;
                        		day_decastore=2;
        					}
    			
        				}
    		}
            else if(month_unitstore!=2)     		//不是二月
        	{	
                if(day_numooo!=30)
        		{
                    ++day_numooo;
                    day_numo=day_numooo;
                    if((--day_unitstore)==255)
        			{
                        day_unitstore=9;
                        --day_decastore;
                        day_numo=day_numooo;
        			}
        		}
                else if(day_numooo==30)
        		{
        	 	
                    	day_numooo=1;
                        day_unitstore=0;
                        day_decastore=3;
                        day_numo=day_numooo;
    			
        		}
    		}
    	}
    }
    else if(sixth_sure)                         //第六次按下确认键,倒计时位减
    {
         if((--retime_ustore)==255)
    	 {
               retime_ustore=9;
               if((--retime_dstore)==255)
        	   {
                     retime_dstore=9;
                     if((--retime_hstore)==255)
        			 {
                        	retime_hstore=9;
                            if((--retime_tstore)==255)retime_tstore=9;
        			 }
        	   }
    	 }
    }
}
/*******************************

年位闪烁子程序

*******************************/
void year_flash(void)
{
    unsigned char i;
    if(third_sure)
    {
         year_thoustore=year_thousand;
         year_hundstore=year_hundred;
         year_decastore=year_decade;
         year_unitstore=year_unit;
         while(third_sure)
    	 {
            for(i=0;i<18;i++)       //年位不显示,其它位都显示
    		{
                year_thousand=10;
                year_hundred=10;
                year_decade=10;
                year_unit=10;
                fen_ge=fenzhong_ge;
                fen_shi=fenzhong_shi;
                display();
                kbscan();
                if(!third_sure)i=51;   //如果不满足立即跳出
    		}
            if(third_sure)
    		{
                for(i=0;i<18;i++)      //年位和其它位都显示
        		{
                     year_thousand=year_thoustore;
                     year_hundred=year_hundstore;
                     year_decade=year_decastore;
                     year_unit=year_unitstore;
                     fen_ge=fenzhong_ge;
                     fen_shi=fenzhong_shi;
                	 display();
                	 kbscan();
                     if(!third_sure)i=51;   //如果不满足立即跳出
        		}
    		}
    	 }
    }
}
/*******************************
月位闪烁子程序
*******************************/
void month_flash(void)
{
    unsigned char i;
    if(TR0==0)                                  //为日位润平年二月天数做准备
    {
            day_numo=judgement_leap();
            day_numoo=day_numo;
    }
    if(fourth_sure)
    {
        month_unitstore=month_unit;
        month_decastore=month_decade;
        while(fourth_sure)
    	{
            for(i=0;i<18;i++)
    		{
                 month_unit=10;
                 month_decade=10;
                 year_thousand=year_thoustore;    //送原始数据避免取到不显示数据
                 year_hundred=year_hundstore;
                 year_decade=year_decastore;
                 year_unit=year_unitstore;
                 display();
                 kbscan();
                 if(!fourth_sure)i=51;
    		}
            if(fourth_sure)
    		{
                 for(i=0;i<18;i++)
        		 {	
                    month_unit=month_unitstore;
                    month_decade=month_decastore;//送原始数据避免取到不显示数据
                    year_thousand=year_thoustore;
                    year_hundred=year_hundstore;
                    year_decade=year_decastore;
                    year_unit=year_unitstore;
                	display();
                	kbscan();
                    if(!fourth_sure)i=51;
        		}
    		}
    	}

    }
}
/*******************************
日位闪烁子程序
******************************/
void day_flash(void)
{
    unsigned char i;
    if(fifth_sure)
    {
        day_unitstore=day_unit;
        day_decastore=day_decade;
        while(fifth_sure)
    	{
            for(i=0;i<18;i++)
    		{
                day_unit=10;
                day_decade=10;
                month_unit=month_unitstore;       //送原始数据避免取到不显示数据
                month_decade=month_decastore;
                year_thousand=year_thoustore;
                year_hundred=year_hundstore;
                year_decade=year_decastore;
                year_unit=year_unitstore;
                display();
                kbscan();
                if(!fifth_sure)i=51;
    		}
            if(fifth_sure)
    		{
                for(i=0;i<18;i++)
        		{
                     day_unit=day_unitstore;
                     day_decade=day_decastore;
                     month_unit=month_unitstore;     //送原始数据避免取到不显示数据
                     month_decade=month_decastore;
                     year_thousand=year_thoustore;
                     year_hundred=year_hundstore;
                     year_decade=year_decastore;
                     year_unit=year_unitstore;
                	 display();
                	 kbscan();
                     if(!fifth_sure)i=51;
        		}
    		}
    	}
    }
}
/*******************************
倒计时位闪烁子程序
*******************************/
void retime_flash(void)
{
    unsigned char i;
    if(sixth_sure)
    {
        retime_ustore=retime_unit;
        retime_dstore=retime_decade;
        retime_hstore=retime_hundred;
        retime_tstore=retime_thousand;
        while(sixth_sure)
    	{
             for(i=0;i<18;i++)
        	 {
                retime_unit=10;
                retime_decade=10;
                retime_hundred=10;
                retime_thousand=10;
                day_unit=day_unitstore;
                day_decade=day_decastore;
                display();
                kbscan();
                if(!sixth_sure)i=51;
        	 }
             if(sixth_sure)
        	 {
                for(i=0;i<18;i++)
        		{
                   retime_unit=retime_ustore;
                   retime_decade=retime_dstore;
                   retime_hundred=retime_hstore;
                   retime_thousand=retime_tstore;
                   day_unit=day_unitstore;
                   day_decade=day_decastore;
                   display();
                   kbscan();
                   if(!sixth_sure)i=51;
        		}
        	 }
    	}
        if(seventh_sure)                 //第八次确认键按下,启动定时器,将各位的数据全部弹出,时钟正常显示
    	{
            seventh_sure=0;
            fen_ge=fenzhong_ge;					
            fen_shi=fenzhong_shi;
            shi_ge=xiaoshi_ge;  
            shi_shi=xiaoshi_shi;
            year_unit=year_unitstore;
            year_decade=year_decastore;
            year_hundred=year_hundstore;
            year_thousand=year_thoustore;
            month_unit=month_unitstore;
            month_decade=month_decastore;
            day_unit=day_unitstore;
            day_decade=day_decastore;
            retime_unit=retime_ustore;
            retime_decade=retime_dstore;
            retime_hundred=retime_hstore;
            retime_thousand=retime_tstore;
            TR0=1;					
    	}
    }
}
/*******************************
小时位闪烁子程序
*******************************/
void hour_flash(void)
{   
    unsigned char i;
    if(first_sure)
    {	
        TR0=0;                //关定时器,进入闪烁 
        xiaoshi_ge=shi_ge;    //保存时个位显示的数据
        xiaoshi_shi=shi_shi;  //保存时十位显示的数据
        while(first_sure)     //第一次确认键按下,在小时位闪烁
    	{	
            for(i=0;i<18;i++) //小时位不显示,其它位显示
        	{	
                shi_ge=10;
                shi_shi=10;
                display();
                kbscan();
                if(!first_sure)i=51;
    		}
            if(first_sure)
    		{
                for(i=0;i<18;i++)//小时位和其它位都显示
        		{	
                    shi_ge=xiaoshi_ge;
                    shi_shi=xiaoshi_shi;
                	display();
                	kbscan();
                    if(!first_sure)i=51;
        		}
        	}  
    	}
    }
}
/******************************
分钟位闪烁子程序
*******************************/
void min_flash(void)    
{   
    unsigned char i;
    if(second_sure)
    {	
            fenzhong_ge=fen_ge;     //保存分个位显示的数据
            fenzhong_shi=fen_shi;   //保存分十位显示的数据
            while(second_sure)      //第二次确认键按下,在分钟位闪烁
    		{
                for(i=0;i<18;i++)//分钟位不显示，其它位都显示
        		{
                	fen_ge=10;
                	fen_shi=10;
                    shi_ge=xiaoshi_ge;  //送小时个位的原始数据,避免调到小时个位不显示时的数据
                    shi_shi=xiaoshi_shi;//送小时十位的原始数据,避免调到小时十位不显示时的数据
                	display();
                	kbscan();
                    if(!second_sure)i=51;
        		}
                if(second_sure)
        		{
                    for(i=0;i<18;i++)      //分钟位和其它位都显示
        			{
                        fen_ge=fenzhong_ge;
                        fen_shi=fenzhong_shi;
                        shi_ge=xiaoshi_ge;  //送小时个位的原始数据,避免调到小时个位不显示时的数据
                        shi_shi=xiaoshi_shi;//送小时十位的原始数据,避免调到小时十位不显示时的数据
                		display();
                		kbscan();
                        if(!second_sure)i=51;
        			}
        		}	
    		}
    }
}
/******************************
年位组合子程序
********************************/
void year_joint(void)
{   
    year_unitstore2=year_unitstore;       //保存年各位数据
    year_decastore2=year_decastore;
    year_hundstore2=year_hundstore;
    year_thoustore2=year_thoustore;
    year_jointed=year_unitstore;
    year_decastore=year_decastore<<4;
    year_decastore=year_decastore&0xf0;
    year_jointed=year_jointed+year_decastore;       //得到年的抵8位
    year_jointed=year_jointed<<8;               //将年的低8和高8互换
    year_jointed=year_jointed+year_hundstore;
    year_thoustore=year_thoustore<<4;
    year_thoustore=year_thoustore&0xf0;
    year_jointed=year_jointed+year_thoustore;   //得到年,需将其进行高8与低8互换
    year_help1=year_jointed&0xff00;
    year_help1=year_help1>>8;               	//得到年低8位
    year_help2=year_jointed&0x00ff;
    year_help2=year_help2<<8;               	//得到年高8位
    year_jointed=year_help1+year_help2;         // 得到年位
    year_unitstore=year_unitstore2;
    year_decastore=year_decastore2;
    year_hundstore=year_hundstore2;
    year_thoustore=year_thoustore2;             //弹出年各位数据
}

/*******************************
定时器0中断子程序
********************************/
void timer0(void) interrupt 1 using 1
{
    TH0=0x3c;
    TL0=0xb0;
    if((++time_num)==20)
    	{
            time_num=0;
            ++miao_ge;   //定时一秒到,秒个位加一
    	}
}   		
/******************************
 当秒个位加到9时进一，
……
*******************************/    
void dis_dingshi(void)  
{   
    if(miao_ge==10)    			
    {
        miao_ge=0;
        if((++miao_shi)==6)		
    	{	
            miao_shi=0;
            if((++fen_ge)==10)		
    		{
                fen_ge=0;
                if((++fen_shi)==6)
        		{
                	fen_shi=0;
                    if((--shi_num)!=0)
        			{
                        if((++shi_ge)==10)
        				{
                			shi_ge=0;
                    		++shi_shi;
        				}
        			}
                    else if(shi_num==0)
        			{
                    	shi_num=24;
                		shi_ge=0;
                		shi_shi=0;
                            if(retime_unit==0&retime_decade==0&retime_hundred==0&retime_thousand==0)//倒计时减一
        					{
            					;
        					}
            				else 
        					{
                                 if((--retime_unit)==10)
            					 {
                            	  	retime_unit=0;
                                    if((--retime_decade)==10)
            						{
                            		 	retime_decade=0;
                                    	if((--retime_hundred)==10)
            							{
                                		 	retime_hundred=0;
                                        	if((--retime_thousand)==10)
            								{
                                			 	retime_thousand=0;
            								}
            							}
            						}
            					 }
        					}

                        if((month_unit|0xfe)==0xff)     //是奇数月,日为31天
        				{	
                                    if((--day_numj)!=0)			//31天没到
                				    {	
                                		if((++day_unit)==10)
            							{
                         					day_unit=0;
                        					++day_decade;
            							}
            						}
                                    else if(day_numj==0)			//31天到了
            						{
                               			day_numj=31;
                        	   			day_unit=1;
                               			day_decade=0;
            							
                                        if((--month_num)!=0)		 //12个月没到
                			   			{	
                                    			if((++month_unit)==10)
                			   					{
                            						month_unit=0;
                            						++month_decade;
                			   					}
            							}
                                        else if(month_num==0)	 //12个月到了
            							{
                        					month_num=12;
                        					month_unit=1;
                            				month_decade=0;
                                            if((++year_unit)==10)	//年个位是否到9
            								{
                            		 	 		year_unit=0;
                                    	 		if((++year_decade)==10)
                						 		{
                            			 			year_decade=0;
                                        			if((++year_hundred)==10)
                									{
                                			 			year_hundred=0;
                                                        if((++year_thousand)==10)year_thousand=0;
                									}
                						 		}
            								}
            							}
            						}
        				}
                        else if((month_unit|0xfe)!=0xff)    //是偶数月,日为30天
        				{
                            if((--day_numo)!=0)			//30天没到
            				{	
                            	if((++day_unit)==10)
            					{
                         			day_unit=0;
                        			++day_decade;
            					}
        					}
                            else if(day_numo==0)			//30天到了
        					{
                               	if(month_unit==2)
            					{	
                            		if(day_numoo==28)
            						{	
                        				day_numo=28;
                        				day_unit=1;
                        				day_decade=0;
            						}
                                	else if(day_numoo==29)
            						{
                        				day_numo=29;
                        				day_unit=1;
                        				day_decade=0;
            						}
            					}			
                				else 
            					{	
                        			day_numj=30;
                        	   		day_unit=1;
                               		day_decade=0;
            					}
                               if((--month_num)!=0)		 //12个月没到
            				   {	
                                	if((++month_unit)==10)
                			   		{
                        				month_unit=0;
                            			++month_decade;
                			   		}
            					}
                                else if(month_num==0)	 //12个月到了
            					{
                        			month_num=12;
                        			month_unit=1;
                        			month_decade=0;
                                    if((++year_unit)==10)	//年个位是否到9
            						{
                        			 	 year_unit=0;
                                    	 if((++year_decade)==10)
            							 {
                            			 	year_decade=0;

                                    		if((++year_hundred)==10)
            								{
                            				 	year_hundred=0;
                                                if((++year_thousand)==10)year_thousand=0;
            								}
            							 }
            						}
            					}
        					}
        				}
        			}
        		}
    		}
    	}
    }
}   
/*************主程序**************/
void main(void)
{  
    TMOD=0x01;
    TH0=0x3c;
    TL0=0xb0;
    EA=1;
    ET0=1;
    TR0=1;
    while(1)
    {   
        kbscan();       //调按键扫描
        display();      //六个数码管显示
        hour_flash();   //调小时位闪烁
        min_flash();    //调分钟位闪烁
        year_flash();   //年闪烁
        month_flash();  //月闪烁
        day_flash();    //日闪烁
        retime_flash();
        dis_dingshi();  //到一秒加一，到一分加一，到一小时加一，到24点清零
    }
}
