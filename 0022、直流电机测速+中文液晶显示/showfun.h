#include <At89x52.h>
#include <intrins.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <absacc.h>
#include <string.h>

#define ulong unsigned long
#define uint unsigned int
#define uchar unsigned char

sbit ce=P2^7;
sbit reset=P3^3;

//以8*8字符计算,显示屏横向、纵向可以显示的字符个数
//以240*128为例:
#define LineChar 30 //一行16个字符(8*8)
#define ColumnChar 16 //总共16列

#define STX 0x02
#define ETX 0x03
#define EOT 0x04
#define ENQ 0x05
#define BS 0x08
#define CR 0x0D
#define LF 0x0A
#define DLE 0x10
#define ETB 0x17
#define SPACE 0x20
#define COMMA 0x2C

#define TRUE 1
#define FALSE 0

#define HIGH 1
#define LOW 0

// T6963C 端口定义
#define LCMDW XBYTE[0x8000] // 数据口
#define LCMCW XBYTE[0x8100] // 命令口

//显示内存分配
//0000h-67ffh 文本区
//6800h-77ffh 4K 图形区
//7800h-7fffh 2k CGRAM区
#define DISRAM_SIZE 0X7FFF  //设置显示ram的大小
#define TXTSTART 0x0000      //设置文本区的起始地址
#define GRSTART 0x6800       //设置图形区的起始地址
#define CGRAMSTART 0x7800  //设置CGRAM的起始地址

// T6963C 命令定义
#define LC_CUR_POS 0x21 // 光标位置设置
#define LC_CGR_POS 0x22 // CGRAM偏置地址设置
#define LC_ADD_POS 0x24 // 地址指针位置
#define LC_TXT_STP 0x40 // 文本区首址
#define LC_TXT_WID 0x41 // 文本区宽度
#define LC_GRH_STP 0x42 // 图形区首址
#define LC_GRH_WID 0x43 // 图形区宽度
#define LC_MOD_OR 0x80 // 显示方式：逻辑“或”
#define LC_MOD_XOR 0x81 // 显示方式：逻辑“异或”
#define LC_MOD_AND 0x82 // 显示方式：逻辑“与”
#define LC_MOD_TCH 0x83 // 显示方式：文本特征
#define LC_DIS_SW 0x90 	// 显示开关：
                        // D0=1/0:光标闪烁启用/禁用;
						// D1=1/0:光标显示启用/禁用；
						// D2=1/0:文本显示启用/禁用；
						// D3=1/0:图形显示启用/禁用；
#define LC_CUR_SHP 0xA0 // 光标形状选择：0xA0-0xA7表示光标占的行数
#define LC_AUT_WR 0xB0 // 自动写设置
#define LC_AUT_RD 0xB1 // 自动读设置
#define LC_AUT_OVR 0xB2 // 自动读/写结束
#define LC_INC_WR 0xC0 // 数据一次写，地址加1
#define LC_INC_RD 0xC1 // 数据一次读，地址加1
#define LC_DEC_WR 0xC2 // 数据一次写，地址减1
#define LC_DEC_RD 0xC3 // 数据一次读，地址减1
#define LC_NOC_WR 0xC4 // 数据一次写，地址不变
#define LC_NOC_RD 0xC5 // 数据一次读，地址不变
#define LC_SCN_RD 0xE0 // 屏读
#define LC_SCN_CP 0xE8 // 屏拷贝
#define LC_BIT_OP 0xF0 // 位操作：D0-D2：定义D0-D7位；D3：1置位；0：清除