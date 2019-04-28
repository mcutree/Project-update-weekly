/*********************************************
This program was produced by the
CodeWizardAVR V1.23.8c Standard
Automatic Program Generator
© Copyright 1998-2003 HP InfoTech s.r.l.
http://www.hpinfotech.ro
e-mail:office@hpinfotech.ro

Project : SKYT
Version : 0.01
Date    : 2006-12-6
Author  : hlchen                          
Company :                                 
Comments:   
Êý¿ØÔÆÌ¨ 
Chip type           : ATmega8 
Program type        : Application
Clock frequency     : 3.690000 MHz
Memory model        : Small 
External SRAM size  : 0 
Data Stack size     : 256 
*********************************************/
typedef unsigned char uchar;  
typedef unsigned int uint;
#include <mega8.h>   
#include <math.h>  
#include "macro.h"
#include "LCD.h" 
//#include "sed1565_s.h"
#define RXB8 1
#define TXB8 0
#define UPE 2
#define OVR 3
#define FE 4
#define UDRE 5
#define RXC 7
#define Light 5
#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<UPE)
#define DATA_OVERRUN (1<<OVR)
#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)
#define sysInitLcd 0
 // USART Receiver buffer
#define RX_BUFFER_SIZE 8
char rx_buffer[RX_BUFFER_SIZE];
unsigned char rx_wr_index,rx_rd_index,rx_counter;
// This flag is set on USART Receiver buffer overflow
bit rx_buffer_overflow,b_ComEnable;
uchar uc_syssta;
// USART Receiver interrupt service routine
#pragma savereg-
interrupt [USART_RXC] void uart_rx_isr(void)
{ 
char status,data;
#asm
    push r26
    push r27
    push r30
    push r31
    in   r26,sreg 
    push r26
#endasm
status=UCSRA;
data=UDR;

if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
   {
   rx_buffer[rx_wr_index]=data;
   if (++rx_wr_index == RX_BUFFER_SIZE) rx_wr_index=0;
   if (++rx_counter == RX_BUFFER_SIZE)
      {
      rx_counter=0;
      rx_buffer_overflow=1;
      };
   };
if ((rx_buffer[0]=='o')&&(rx_buffer[1]=='k')) b_ComEnable=1; 
#asm
    pop  r26
    out  sreg,r26
    pop  r31
    pop  r30
    pop  r27
    pop  r26
#endasm
}
#pragma savereg+

#ifndef _DEBUG_TERMINAL_IO_
// Get a character from the USART Receiver buffer
#define _ALTERNATE_GETCHAR_
#pragma used+
char getchar(void)
{
char data;
while (rx_counter==0);
data=rx_buffer[rx_rd_index];
if (++rx_rd_index == RX_BUFFER_SIZE) rx_rd_index=0;
#asm("cli")
--rx_counter;
#asm("sei")
return data;
}
#pragma used-
#endif

// USART Transmitter buffer
#define TX_BUFFER_SIZE 8
char tx_buffer[TX_BUFFER_SIZE];
unsigned char tx_wr_index,tx_rd_index,tx_counter;

// USART Transmitter interrupt service routine
#pragma savereg-
interrupt [USART_TXC] void uart_tx_isr(void)
{
#asm
    push r26
    push r27
    push r30
    push r31
    in   r26,sreg
    push r26
#endasm
if (tx_counter)
   {
   --tx_counter;
   UDR=tx_buffer[tx_rd_index];
   if (++tx_rd_index == TX_BUFFER_SIZE) tx_rd_index=0;
   }; 

#asm
    pop  r26
    out  sreg,r26
    pop  r31
    pop  r30
    pop  r27
    pop  r26
#endasm
}
#pragma savereg+

#ifndef _DEBUG_TERMINAL_IO_
// Write a character to the USART Transmitter buffer
#define _ALTERNATE_PUTCHAR_
#pragma used+
void putchar(char c)
{
while (tx_counter == TX_BUFFER_SIZE);
#asm("cli")
if (tx_counter || ((UCSRA & DATA_REGISTER_EMPTY)==0))
   {
   tx_buffer[tx_wr_index]=c;
   if (++tx_wr_index == TX_BUFFER_SIZE) tx_wr_index=0;
   ++tx_counter;
   }
else UDR=c;
#asm("sei")
}
#pragma used-
#endif
// Standard Input/Output functions
#include <stdio.h>  
uchar ucInputValue;
uint uiLastADValue[3];
uchar ucInputParam0; 
uchar ucChannelN,uc_ReceiveSta;
bit bInputChange,bMotorSpeed,bLight,bReceiveOpend;         
void inputdeal(void); 
void TransmitEnable(void);
void ReceiveEnable(void); 
void Communication(void);
void LcdShow(void);
#define HighSpeed 0x33
#define SlowSpeed 0x99
#define ADC_VREF_TYPE 0x00      
#define RE 0
#define DE 1
// ADC interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
// Place your code here 
TCNT0=0xf0;
}
interrupt [ADC_INT] void adc_isr(void)
{
uint adc_data;
// Read the AD conversion result
adc_data=ADCW;

// Place your code here 
switch (ucChannelN)
{
case 0:
 	       	if (uiLastADValue[0]!=adc_data)
 		{
 		uiLastADValue[0]=adc_data;
 		ucInputParam0=uiLastADValue[0]*24/1024;
		//ucInputParam0 = tmp/100;
		//ucInputParam1 = (tmp%100)/10;
		//ucInputParam2 = (tmp%100)%10;
		bInputChange=1;
		ucInputValue=0x01;
	       
		} 
		ADMUX=0x01;
		break;  
case 1: 
        	if (uiLastADValue[1]!=adc_data)
 		{
 		uiLastADValue[1]=adc_data;
 		ucInputParam0=uiLastADValue[1]*12/1024;
		//ucInputParam0 = tmp/100;
		//ucInputParam1 = (tmp%100)/10;
		//ucInputParam2 = (tmp%100)%10;
		bInputChange=1;
		ucInputValue=0x02; 
	     
		} 
		ADMUX=0x02;
		break;  
case 2:
		if (uiLastADValue[2]!=adc_data)
 		{
 		uiLastADValue[2]=adc_data;
 		//ucInputParam0=uiLastADValue[2]*6/1024; 
 	       	if (abs(uiLastADValue[2]-1023)<100)
 	       		 ucInputValue=3;
   	        else if (abs(uiLastADValue[2]-465)<50)
 	       		 ucInputValue=4;
       		else if (abs(uiLastADValue[2]-292)<25)
 	       		 ucInputValue=5;	 
 	       	else if (abs(uiLastADValue[2]-204)<25)
 	       		 ucInputValue=6;
 	       	else if (abs(uiLastADValue[2]-146)<12)
 	       		 ucInputValue=7;
 	       	else if (abs(uiLastADValue[2]-93)<12) 
 	       	         ucInputValue=8;
 	       	else if (abs(uiLastADValue[2])<6)
 	       		 ucInputValue=9;
 	       	else break;
 	       //	else if (abs(uiLastADValue[2]-512
		//ucInputParam0 = tmp/100;
		//ucInputParam1 = (tmp%100)/10;
		//ucInputParam2 = (tmp%100)%10;
		bInputChange=1;
//		ucInputValue=ucInputParam0+2; 
	     
		} 
		ADMUX=0x00;
		break;              
default:
		break;
}   
ADCSRA|=0x40;
//ADMUX^=0x01;   
if (ucChannelN++==3)    ucChannelN=0;

}

// Declare your global variables here

void main(void)
{
// Declare your local variables here
 
uint i;
// Input/Output Ports initialization
// Port B initialization
// Func0=Out Func1=Out Func2=Out Func3=Out Func4=Out Func5=Out Func6=Out Func7=Out 
// State0=0 State1=0 State2=0 State3=0 State4=0 State5=0 State6=0 State7=0 
PORTB=0x00;
DDRB=0xFF;

// Port C initialization
// Func0=Out Func1=Out Func2=Out Func3=Out Func4=Out Func5=Out Func6=Out 
// State0=0 State1=0 State2=0 State3=0 State4=0 State5=0 State6=0 
PORTC=0x00;
DDRC=0xff;

// Port D initialization
// Func0=Out Func1=Out Func2=Out Func3=Out Func4=Out Func5=Out Func6=Out Func7=Out 
// State0=0 State1=0 State2=0 State3=0 State4=0 State5=0 State6=0 State7=0 
PORTD=0x00;
DDRD=0x73;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 3690.000 kHz
TCCR0=0x03;
TCNT0=0xf0;


// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer 1 Stopped
// Mode: Normal top=FFFFh
// OC1A output: Discon.
// OC1B output: Discon. 
// Noise Canceler: Off
// Input Capture on Falling Edge
//Ä£Ê½1(¼ÆÊýÆ÷ÉÏÏÞÖµ=0xff) PWMÆµÂÊ = ÏµÍ³Ê±ÖÓÆµÂÊ/£¨·ÖÆµÏµÊý*2*¼ÆÊýÆ÷ÉÏÏÞÖµ£©£© 
TCCR1A=0x00;
//COM1A1,COM1A0,COM1B1,COM1B0=1±íÊ¾ÉýÐò¼ÇÊýÊ±±È½ÏÆ¥Åä½«ÖÃÎ»OC1A/OC1B£¬½µÐò¼ÇÊýÊ±±È½ÏÆ¥Åä½«ÇåÁãOC1A/OC1B
//¼´OCR1AL<tcnt1<TOP(0xff)Ê± OC1AÎª¸ß tcnt1<OCR1ALÊ±OC1AÎªµÍ
//WGM11=0 WGM10=1
TCCR1B=0x00;
//WGM13=0 WGM12=0 CS12=1 CS11=0 CS10=0 ·ÖÆµÏµÊý=256
TCNT1H=0x00;
TCNT1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00; //Õ¼¿Õ±È=40% (0xff-0x99)/0xff=0.4
		//Õ¼¿Õ±È=80% 0x33
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer 2 Stopped
// Mode: Normal top=FFh
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
GICR|=0x00;
MCUCR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0X01;

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud rate: 1200

UCSRA=0x00;
UCSRB=0xD8;
UCSRC=0x86;
UBRRH=0x00;
UBRRL=0x33;
// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
// Analog Comparator Output: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC Clock frequency: 115.313 kHz
// ADC Voltage Reference: AREF pin
// ADC High Speed Mode: Off
// ADC Auto Trigger Source: Timer0 Overflow
ADMUX=0x00;
ADCSRA=0x00;
//SFIOR&=0x0F;
//SFIOR|=0x80;

// Global enable interrupts   

InitLCD();


 



 
#asm("sei")
TransmitEnable();
printf("Ready?");
for (i=0;i<10000;i++); 
while (1)
      {
      // Place your code here
      if (tx_counter==0) ReceiveEnable();   
 
      if (b_ComEnable)
        {
      	b_ComEnable=0;
      	LcdShow();
      	break;
	    }
      };
while(1)
{

      //inputdeal();
}
}
void LcdShow(void)
{
	Show_Circle();
	Show_HalfCircle();
	Show_Preset();
	Show_Slow();
}
void TransmitEnable(void)
{
PORTB|=Bit(RE);
PORTB|=Bit(DE);
}
void ReceiveEnable(void)
{

PORTB&=Bit(RE);
PORTB&=Bit(DE);

}
void TransmitCommandOk(void)
{
	//if (uc_syssta==sysInitLcd)
	//	LcdShow();	
}
void Communication(void)
{
	
     switch (uc_ReceiveSta)
      {
      case 0:
      		if (getchar()=='R')
	       		uc_ReceiveSta++;
	        else if (getchar()=='O')
	        	uc_ReceiveSta++;
	        	
		break;
      case 1:
      		if (getchar()=='e')
			uc_ReceiveSta++;
		else if (getchar()=='k')
			{
			uc_ReceiveSta=0;
			b_ComEnable=1;
			}
		else 
			uc_ReceiveSta=0;
		break; 
      case 2:
      		if (getchar()=='a')
			uc_ReceiveSta++;
		else
	       		uc_ReceiveSta=0;
		break;
      case 3:
      		if (getchar()=='d')
			uc_ReceiveSta++;
		else
			uc_ReceiveSta=0;
       		break;  
      case 4:
      		uc_ReceiveSta=0;
	      	if (getchar()=='y')
			printf("ok");
		break;
      }                     
      
     
}
void inputdeal(void)
{
	if (!bInputChange) return;
	bInputChange=0;
	switch (ucInputValue)
	{
	case 0x01:
		//printf("%bu,%bu,%bu\n",ucInputParam0,ucInputParam1,ucInputParam2);
	       //	PaintDegree(ucInputParam0,0);   
	
		break;
	case 0x02:
	       //	PaintDegree(ucInputParam0,1);
	
		break; 
	case 0x03://key1
	      	if (!bLight) PORTB|=Bit(Light); 
	      	else PORTB&=~Bit(Light);
	      	bLight=!bLight;
		PORTD|=0x04;
		break;
	case 0x04://key2
	       //	PORTD&=0xc3;
		PORTD|=0x08;   
	      //	if (bMotorSpeed)       {Show_Slow();OCR1AL=SlowSpeed;}
	     //	else   {Show_Quick();OCR1AL=HighSpeed;}
		bMotorSpeed=!bMotorSpeed;
		
		break;  
	case 0x05://key3
	       //	PORTD&=0xc3;
		PORTD|=0x0c;
		break;
	case 0x06://key4
	      //	PORTD&=0xc3;
		PORTD|=0x10;
		break;
	case 0x07://key5
	       //	PORTD&=0xc3;
		PORTD|=0x14;
		break;
	case 0x08://key6  
	        //PORTD&=0xc3;
		PORTD|=0x18;
		break;
	case 0x09://keyrelease 
		PORTD&=0xc3;    
		break;
	default:
		break;
	}
}
