
/*****************************************/

#ifndef	_PMPDATAR_H 		// 防止PMPDataT.h被重复引用

#define	_PMPDATAR_H

#include <reg51.h>
#include <string.h>

#define uchar unsigned char
#define uint unsigned int

/* 握手信号宏定义 */
#define SUCC 0x2A		// 接收成功
#define ERR 0xF0		// 接收错误

#define MAXLEN 64    	// 缓冲区最大长度

uchar buf;
uchar addr;

sbit P23 = P2^3;		// 此引脚控制发光管

#endif