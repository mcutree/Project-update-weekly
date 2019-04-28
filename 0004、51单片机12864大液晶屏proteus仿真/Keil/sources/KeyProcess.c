//*************************************************************************************************
//*																								  *
//*			 ******************************¼üÂë´¦Àí³ÌÐò**************************				  *
//*																								  *
//*************************************************************************************************

#include "LCD12864.h"
#include "LCDShowMap.h"

#define NUMROW 0
#define NUMLINE 20
void vKeyProcess(unsigned char ucKeyCode)
{	

	switch(ucKeyCode)
		{
		case 11:vShowOneChar(NUMROW,NUMLINE,uca_7);break;							  //'7'
		case 12:vShowOneChar(NUMROW,NUMLINE,uca_8);break;							  //'8'
		case 13:vShowOneChar(NUMROW,NUMLINE,uca_9);break;							  //'9'
		case 21:vShowOneChar(NUMROW,NUMLINE,uca_4);break;							  //'4'
		case 22:vShowOneChar(NUMROW,NUMLINE,uca_5);break;							  //'5'
		case 23:vShowOneChar(NUMROW,NUMLINE,uca_6);break;							  //'6'
		case 31:vShowOneChar(NUMROW,NUMLINE,uca_1);break;							  //'1'
		case 32:vShowOneChar(NUMROW,NUMLINE,uca_2);break;							  //'2'
		case 33:vShowOneChar(NUMROW,NUMLINE,uca_3);break;							  //'3'
		case 42:vShowOneChar(NUMROW,NUMLINE,uca_0);break;							  //'0'

		case 14:vShowOneChar(NUMROW,NUMLINE,uca_CHU);break;							  //'/'
		case 24:vShowOneChar(NUMROW,NUMLINE,uca_CHENG);break;						  //'*'
		case 34:vShowOneChar(NUMROW,NUMLINE,uca_JIAN);break;						  //'-'
		case 44:vShowOneChar(NUMROW,NUMLINE,uca_JIA);break;							  //'+'
							  
		case 43:vShowOneChar(NUMROW,NUMLINE,uca_DENG);break;							  //'='

		case 41:vShowCustomRow(NUMROW,NUMLINE,8,uca_BLANK);
				vShowCustomRow(NUMROW+1,NUMLINE,8,uca_BLANK);
				break;							  //'ON/C'
		
		default:break;
		}
}