/*****************************************/
/* Copyright (c) 2005, 通信工程学院      */
/* All rights reserved.                  */
/* 作    者：戴 佳						 */
/*****************************************/

#ifndef	_PMPDATAT_H 		// 防止PMPDataT.h被重复引用

#define	_PMPDATAT_H

#include <reg51.h>
#include <string.h>

#define uchar unsigned char
#define uint unsigned int

/* 握手信号宏定义 */
#define SUCC 0x2A		// 接收成功
#define ERR 0xF0		// 接收错误

#define MAXLEN 64    	// 缓冲区最大长度

uchar buf;
uchar addr,get_key,key;

#endif