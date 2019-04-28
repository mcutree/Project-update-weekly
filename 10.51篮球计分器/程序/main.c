#include <reg52.h>
#include "lcd1602.h"

sbit S1 = P3^0;//暂停、开始
sbit S2 = P3^1;//换场
sbit S3 = P3^2;//a
sbit S4 = P3^3;//b

unsigned char Ascore, Bscore; // A/B两队比分；
unsigned char ChangeFlag;//换场标志； 比赛节数；
unsigned char StartFlag = 1; //开始比赛标志；

void KeyCon(void)
{
	static unsigned char flag1, flag2, flag3, flag4;//消抖变量；
	if(S1 == 0) flag1 = 1;
	if(S1 == 1 && flag1 == 1) {flag1 = 0; StartFlag =! StartFlag; Print("                ", 0, 0);}

	if(S2 == 0) flag2 = 1;
	if(S2 == 1 && flag2 == 1) {flag2 = 0; ChangeFlag =! ChangeFlag;}

	if(S3 == 0) flag3 = 1;
	if(S3 == 1 && flag3 == 1) {flag3 = 0; if(StartFlag)Ascore++;}

	if(S4 == 0) flag4 = 1;
	if(S4 == 1 && flag4 == 1) {flag4 = 0; if(StartFlag)Bscore++;}
}

void main(void)
{	
	LCD_Initial();//初始化LCD;
	while(1)
	{	
		KeyCon(); //按键扫描；
		if(StartFlag == 1)//比赛开始；
		{	
			Print("VS", 8, 0);//固定显示；
			Print(":", 8, 1);
			if(ChangeFlag == 1)//场地转换；
			{
				Print(" IG", 2, 0);//显示队名；
				Print("RNG", 12, 0);

				display_int( Ascore, 2, 1, 3);//显示比分；
				display_int(Bscore, 12, 1, 3);
			}
			else //交换显示；
			{
				Print(" IG", 12, 0);
				Print("RNG", 2, 0);
				display_int( Ascore, 12, 1, 3);
				
				display_int(Bscore, 2, 1, 3);
			}
			
		}
		else  Print(" *****STOP***** ", 0, 0); //比赛暂停，暂停提示；			
	}
}