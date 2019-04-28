//*************************************************************************************************
//*																								  *
//*			 ******************************LCD12864驱动程序**************************			  *
//*																								  *
//*************************************************************************************************

//*************************************************************************************************
//*																								  *
//*			 ******************************头文件及宏定义**************************				  *
//*																								  *
//*************************************************************************************************
#include <at89x51.h>

#define	RST P2_0
#define	E P2_1
#define	RW P2_2
#define	DI P2_3
#define	CS1 P2_5
#define	CS2	P2_4
#define	LCDPORT P0


#define BUSYSTATUS P0_7				  //忙状态位。
//#define DISONSTATUS P0_5			  //显示开关状态位。
//#define RSTSTATUS P0_4			  //复位状态位。


#define LCDSTARTROW 0xC0			  //设置起始行指令。
#define LCDPAGE 0xB8				  //设置页指令。
#define LCDLINE 0x40				  //设置列指令。




//*************************************************************************************************
//*																								  *
//*			 ********************************读忙标志位*********************************		  *
//*																								  *
//*************************************************************************************************
bit bCheckBusy()
{
	LCDPORT=0xFF;
	RW=1;
	DI=0;
	E=1;
	E=0;
	return BUSYSTATUS; 
}

//*************************************************************************************************
//*																								  *
//*			 ********************************写数据*********************************			  *
//*																								  *
//*************************************************************************************************
void vWriteData(unsigned char ucData)
{
	while(bCheckBusy());
	LCDPORT=0xFF;

	RW=0;
	DI=1;
	LCDPORT=ucData;
	E=1;
	E=0;
}

//*************************************************************************************************
//*																								  *
//*			 ********************************写指令*********************************			  *
//*																								  *
//*************************************************************************************************
void vWriteCMD(unsigned char ucCMD)
{
	while(bCheckBusy());
	LCDPORT=0xFF;

	RW=0;
	DI=0;
	LCDPORT=ucCMD;
	E=1;
	E=0;
}

//*************************************************************************************************
//*																								  *
//*			 ********************************LCD初始化函数*******************************		  *
//*																								  *
//*************************************************************************************************
void vLCDInitialize()
{
	CS1=1;
	CS2=1;
	vWriteCMD(0x38);		//8位形式，两行字符。
	vWriteCMD(0x0F);		//开显示。
	vWriteCMD(0x01);		//清屏。
	vWriteCMD(0x06);		//画面不动，光标右移。
	vWriteCMD(LCDSTARTROW);	//设置起始行。
}

//*************************************************************************************************
//*																								  *
//*			 ******************************显示自定义行*********************************		  *
//*																								  *
//*************************************************************************************************
//在8×128的格子里显示自定义长度的一行
void vShowCustomRow(unsigned char ucPage,unsigned char ucLine,unsigned char ucWidth,unsigned char *ucaRow)
{
	unsigned char ucCount;				   //取值范围：ucPage:0～7；ucLine:0～127；
	if(ucLine<64)						   //ucWidth:0～127；ucLine+ucWidth<1128。
		{
		CS1=1;
		CS2=0;
		vWriteCMD(LCDPAGE+ucPage);
		vWriteCMD(LCDLINE+ucLine);
		if((ucLine+ucWidth)<64)
			{
			for(ucCount=0;ucCount<ucWidth;ucCount++)
				vWriteData(*(ucaRow+ucCount));
			}
		else
			{
			for(ucCount=0;ucCount<64-ucLine;ucCount++)
				vWriteData(*(ucaRow+ucCount));

			CS1=0;
			CS2=1;
			vWriteCMD(LCDPAGE+ucPage);
			vWriteCMD(LCDLINE);
			for(ucCount=64-ucLine;ucCount<ucWidth;ucCount++)
				vWriteData(*(ucaRow+ucCount));
			}
		}
	else
		{
		CS1=0;
		CS2=1;
		vWriteCMD(LCDPAGE+ucPage);
		vWriteCMD(LCDLINE+ucLine-64);
		for(ucCount=0;ucCount<ucWidth;ucCount++)
			vWriteData(*(ucaRow+ucCount));
		}
}
//*************************************************************************************************
//*																								  *
//*			 *****************************汉字显示函数***********************************		  *
//*																								  *
//*************************************************************************************************
//此函数将16×16汉字显示在8×128的格子里。
void vShowOneChin(unsigned char ucPage,unsigned char ucLine,unsigned char *ucaChinMap)
{
	vShowCustomRow(ucPage,ucLine,16,ucaChinMap);
	vShowCustomRow(ucPage+1,ucLine,16,ucaChinMap+16);

}
//*************************************************************************************************
//*																								  *
//*			 *****************************字符显示函数***********************************		  *
//*																								  *
//*************************************************************************************************
//此函数将8×16字符显示在8×128的格子里。
void vShowOneChar(unsigned char ucPage,unsigned char ucLine,unsigned char *ucaCharMap)
{
	vShowCustomRow(ucPage,ucLine,8,ucaCharMap);
	vShowCustomRow(ucPage+1,ucLine,8,ucaCharMap+8);

}


//*************************************************************************************************
//*																								  *
//*			 **********************************显示图片***********************************		  *
//*																								  *
//*************************************************************************************************
void vShowGraph(unsigned char ucPage,unsigned char ucLine,unsigned char ucWidth,unsigned char ucHigh,unsigned char * ucaGraph)
{
	unsigned char ucCount;
	for(ucCount=0;ucCount<ucHigh;ucCount++)
		vShowCustomRow(ucPage+ucCount,ucLine,ucWidth,ucaGraph+ucCount*ucWidth);
}
