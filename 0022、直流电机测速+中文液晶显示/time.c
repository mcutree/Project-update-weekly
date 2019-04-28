#include <intrins.h>
#include <at89x52.h>


extern uint c;

void delay(uchar i)
{  uchar j,k;
   for(;i>0;i--)
   for(j=0;j<10;j++)
   for(k=0;k<10;k++);
}


/*void time()interrupt 1 using 3
{   
    ET0=0;
    ET1=0;
    TH1=0x3c;
    TL1=0xb0;
    c=TL0;
    TH0=0x00;
    TL0=0x00;
    ET0=1;
    ET1=1;
}*/
