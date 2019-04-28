#include<reg51.h>
//¶¨ÒåÒ»¸öÊý×é,Ê¹ÊýÂë¹ÜÏÔÊ¾µÄÊý×ÖºÍÊý×éÔªËØµÄÏÂ±êÏàµÈ
unsigned char code table[]={0x3f,0x06,0x5b,0x4f,0x66,
                            0x6d,0x7d,0x07,0x7f,0x6f};
sbit shuiman=P1^0;//Ë®Âú
sbit sw5=P1^1;//Ë®Î»5
sbit sw4=P1^2;//Ë®Î»4
sbit sw3=P1^3;//Ë®Î»3
sbit sw2=P1^4;//Ë®Î»2
sbit sw1=P1^5;//Ë®Î»1
sbit shougong=P1^6;//ÊÖ¹¤ÉÏË®
sbit dianji=P1^7;//µç»ú¿ØÖÆÎ»
sbit state=P3^7;//µç»ú¹¤×÷Ö¸Ê¾
/*ÑÓÊ±³ÌÐò*/
void delay02s(void)
{
  unsigned char i,j,k;
  for(i=100;i>0;i--)
  for(j=100;j>0;j--)
  for(k=248;k>0;k--);
}
main()
{
	P0=0;
	while(1)
		{  /*************************´«¸ÐÆ÷ÊÇÉè¼ÆµÄÒ»´ÎÖ»ÄÜ´¥·¢Ò»¸ö´«¸ÐÆ÷µ¥Ô*****************************
	      //Ë®Âú
			if(shuiman==0&&sw5==1&&sw4==1&&sw3==1&&sw2==1&&sw1==1)//µ±Î¨Ò»µÄ±ÕºÏÒ»¸ö´«¸ÐÆ÷µ¥Ôª:Ë®Î»6Ê±·¢Éú
			{
				dianji=1;//¹Øµç»ú
				state=1;//µç»ú¹¤×÷Ö¸Ê¾µÆÏ¨Ãð
            P0=table[6];//ÏÔÊ¾Ë®Î»Éî¶È:6**** ÒÑÂú
				delay02s();//ÑÓÊ±Ò»¶ÎÊ±¼äÈÃÊýÂë¹ÜÏÔÊ¾¸øÈËÒÔÌáÊ¾£ºË®ÒÑÂú
			}
				//Ë®Î»5
			if(shuiman==1&&sw5==0&&sw4==1&&sw3==1&&sw2==1&&sw1==1)//µ±Î¨Ò»µÄ±ÕºÏÒ»¸ö´«¸ÐÆ÷µ¥Ôª:Ë®Î»5Ê±·¢Éú
			{
				P0=table[5];//ÏÔÊ¾Ë®Î»Éî¶È:5
			}
			//Ë®Î»4
			if(shuiman==1&&sw5==1&&sw4==0&&sw3==1&&sw2==1&&sw1==1)//µ±Î¨Ò»µÄ±ÕºÏÒ»¸ö´«¸ÐÆ÷µ¥Ôª:Ë®Î»4Ê±·¢Éú
			{
				P0=table[4];//ÏÔÊ¾Ë®Î»Éî¶È:4
			}
			//Ë®Î»3
			if(shuiman==1&&sw5==1&&sw4==1&&sw3==0&&sw2==1&&sw1==1)//µ±Î¨Ò»µÄ±ÕºÏÒ»¸ö´«¸ÐÆ÷µ¥Ôª:Ë®Î»3Ê±·¢Éú
			{
			  	P0=table[3];//ÏÔÊ¾Ë®Î»Éî¶È:5
			}
			//Ë®Î»2
	      if(shuiman==1&&sw5==1&&sw4==1&&sw3==1&&sw2==0&&sw1==1)//µ±Î¨Ò»µÄ±ÕºÏÒ»¸ö´«¸ÐÆ÷µ¥Ôª:Ë®Î»2Ê±·¢Éú
			{
				P0=table[2];//ÏÔÊ¾Ë®Î»Éî¶È:2
			}
			//Ë®Î»µÍ
			if(shuiman==1&&sw5==1&&sw4==1&&sw3==1&&sw2==1&&sw1==0)//µ±Î¨Ò»µÄ±ÕºÏÒ»¸ö´«¸ÐÆ÷µ¥Ôª:Ë®Î»1Ê±·¢Éú
			{
				dianji=0;//¿ªµç»ú
				state=0;//µç»ú¹¤×÷Ö¸Ê¾µÆ´ò¿ª
			P0=table[1];//ÏÔÊ¾Ë®Î»Éî¶È:1
			}
			//ÊÖ¹¤ÉÏË®
		    if(shougong==0)//µ±°´ÊÖ¹¤ÉÏË®°´Å¥Ê±·¢Éú
			{  
		      dianji=0;//¿ªµç»ú
				state=0;//µç»ú¹¤×÷Ö¸Ê¾µÆ´ò¿ª
				P0=table[0];//ÏÔÊ¾0±íÊ¾ÊÖ¹¤ÉÏË®ÒÑÓÐ·´Ó¦
				delay02s();//ÑÓÊ±Ò»¶ÎÊ±¼äÈÃÊýÂë¹ÜÏÔÊ¾¸øÈËÒÔÌáÊ¾£ºÒÑ¿ªÊ¼ÊÖ¹¤ÉÏË®
			}
		
		}
	 
}
