#include <REGX52.H>
#include "LCD1602.h"

unsigned char TempBuffer[10];
void IntToStr(unsigned int t, unsigned char *str, unsigned char n) 
{
	unsigned char a[5]; char i, j;                                 	
	a[0]=(t/10000)%10;         //取得整数值到数组         	
	a[1]=(t/1000)%10;                                     	
	a[2]=(t/100)%10;                                      	
	a[3]=(t/10)%10;                                       	
	a[4]=(t/1)%10;                                        	
                                                      
	for(i=0; i<5; i++)         //转成ASCII码              	
		a[i]=a[i]+'0';                                    	
	for(i=0; a[i]=='0' && i<=3; i++);                     	
	for(j=5-n; j<i; j++)       //填充空格                 	
		{ *str=' ';  str++; }                             	
	for(; i<5; i++)                                       	
		{ *str=a[i]; str++; }  //加入有效的数字           	
	*str='\0'; 
} 

void Delay1ms(unsigned int count)
{
	unsigned int i,j;
	for(i=0;i<count;i++)
	for(j=0;j<120;j++);
}

main()
{
	unsigned int Count = 0;
	LCD_Initial();
	GotoXY(0,0);
	Print("The 1602LCD Test");
	GotoXY(0,1);
	Print("GO:       by JJJ");

	while(1)
	{
		IntToStr(Count++,&TempBuffer[0],5);
		GotoXY(3,1);
		Print(&TempBuffer[0]);
		Delay1ms(100);
	}
}
