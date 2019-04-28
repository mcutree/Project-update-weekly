#include "reg51.h"

sbit  key0 = P1^0;

delay(unsigned int dd)
{
	while(--dd);
}

disp(unsigned char aa)
{
		P2 = 0xff;
		P0 = aa;
		P2 = 0x7f;
		
		delay(1000);

		P2 = 0xff;
		P0 = 0x06;
		P2 = 0xbf;
		delay(1000);	

		P2 = 0xff;
		P0 = 0x5b;
		P2 = 0xdf;
		
		delay(1000);

		P2 = 0xff;
		P0 = 0x4f;
		P2 = 0xef;
		delay(1000);	
		P2 = 0xff;
		P0 = 0x66;
		P2 = 0xf7;
		
		delay(1000);

		P2 = 0xff;
		P0 = 0x6d;
		P2 = 0xfb;
		delay(1000);	
}

main()
{
	unsigned char aa=0;
	while(1)
	{
	  if(!key0) aa++;
	  disp(aa);
	}

}