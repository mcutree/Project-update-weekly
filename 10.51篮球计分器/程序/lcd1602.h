#ifndef LCD1602_H
#define LCD1602_H

#include "reg52.h"

 //端口定义
#define  DBPort P0    //LCD数据端口

sbit LcdRs		= P3^5;
sbit LcdRw		= P3^6;
sbit LcdEn  	= P3^4;
sbit Lcdbf    = P0^7; //LCD忙标志 Busy Flag

void LCD_Initial(void);                                            //初始化；
void delay(unsigned int t);                                        //延时；
void LCD_Write(bit style, unsigned char input);										 //位写
void Print(unsigned char *str, unsigned char x, unsigned char y);	 //指定坐标输出字符串；
void display_int(unsigned int dat, unsigned char x, unsigned char y, unsigned char num_size);//显示整数（长度可调）；
#endif