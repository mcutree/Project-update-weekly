#include <REGX52.H>
#include "Max7221.h"

unsigned char DisplayBuffer[8]={0,1,2,3,4,5,6,7};//ÏÔÊ¾»º³åÇø

main()
{
	InitialMax7221();
	Max7221Display(&DisplayBuffer[0]);
	while(1);	
}
