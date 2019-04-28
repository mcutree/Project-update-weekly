#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"

void Delay1ms(unsigned int count)
{
	unsigned int i,j;
	for(i=0;i<count;i++)
	for(j=0;j<120;j++);
}

main()
{
	SYSTEMTIME CurrentTime;
	LCD_Initial();
	Initial_DS1302();

	GotoXY(0,0);
	Print(" www.ourhc.cn");
	GotoXY(0,1);
	Print("Time: ");
	
	while(1)
	{
		DS1302_GetTime(&CurrentTime);
		TimeToStr(&CurrentTime);
		GotoXY(6,1);
		Print(CurrentTime.TimeString);

		Delay1ms(400);
	}
}
