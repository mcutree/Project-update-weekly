#include <absacc.h>
#include <intrins.h>
#include <reg51.h>

sbit adcdo=P0^0;
sbit adccs=P0^2;
sbit adcclk=P0^1;

uchar bdata ch;
sbit ch_0 = ch^0;

void delay1(uchar x)
{
	uchar i;
	for(i=0;i<x;i++); 
}

void adcck(void) 
{ 
	adcclk=1; 
	delay1(1); 
	adcclk=0; 
	delay1(1); 
}

uchar readadc(void)
{ 
    uchar i;
 	ch=0;
    adccs=0;
    adcck();
    while(adcdo); 
    for (i=0; i<8; i++) 
    { 
         adcck();
         ch <<= 1;
		 ch_0 = adcdo;
    }
    adccs=1;
    return(ch);
}