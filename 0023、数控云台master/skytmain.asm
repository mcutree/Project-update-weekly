;CodeVisionAVR C Compiler V1.24.7d Professional
;(C) Copyright 1998-2005 Pavel Haiduc, HP InfoTech s.r.l.
;http://www.hpinfotech.com

;Chip type              : ATmega8
;Program type           : Application
;Clock frequency        : 3.690000 MHz
;Memory model           : Small
;Optimize for           : Size
;(s)printf features     : int, width
;(s)scanf features      : int, width
;External SRAM size     : 0
;Data Stack size        : 256 byte(s)
;Heap size              : 0 byte(s)
;Promote char to int    : No
;char is unsigned       : Yes
;8 bit enums            : Yes
;Word align FLASH struct: Yes
;Enhanced core instructions    : On
;Automatic register allocation : On

	#pragma AVRPART ADMIN PART_NAME ATmega8
	#pragma AVRPART MEMORY PROG_FLASH 8192
	#pragma AVRPART MEMORY EEPROM 512
	#pragma AVRPART MEMORY INT_SRAM SIZE 1024
	#pragma AVRPART MEMORY INT_SRAM START_ADDR 0x60

	.EQU UDRE=0x5
	.EQU RXC=0x7
	.EQU USR=0xB
	.EQU UDR=0xC
	.EQU SPSR=0xE
	.EQU SPDR=0xF
	.EQU EERE=0x0
	.EQU EEWE=0x1
	.EQU EEMWE=0x2
	.EQU EECR=0x1C
	.EQU EEDR=0x1D
	.EQU EEARL=0x1E
	.EQU EEARH=0x1F
	.EQU WDTCR=0x21
	.EQU MCUCR=0x35
	.EQU GICR=0x3B
	.EQU SPL=0x3D
	.EQU SPH=0x3E
	.EQU SREG=0x3F

	.DEF R0X0=R0
	.DEF R0X1=R1
	.DEF R0X2=R2
	.DEF R0X3=R3
	.DEF R0X4=R4
	.DEF R0X5=R5
	.DEF R0X6=R6
	.DEF R0X7=R7
	.DEF R0X8=R8
	.DEF R0X9=R9
	.DEF R0XA=R10
	.DEF R0XB=R11
	.DEF R0XC=R12
	.DEF R0XD=R13
	.DEF R0XE=R14
	.DEF R0XF=R15
	.DEF R0X10=R16
	.DEF R0X11=R17
	.DEF R0X12=R18
	.DEF R0X13=R19
	.DEF R0X14=R20
	.DEF R0X15=R21
	.DEF R0X16=R22
	.DEF R0X17=R23
	.DEF R0X18=R24
	.DEF R0X19=R25
	.DEF R0X1A=R26
	.DEF R0X1B=R27
	.DEF R0X1C=R28
	.DEF R0X1D=R29
	.DEF R0X1E=R30
	.DEF R0X1F=R31

	.EQU __se_bit=0x80
	.EQU __sm_mask=0x70
	.EQU __sm_adc_noise_red=0x10
	.EQU __sm_powerdown=0x20
	.EQU __sm_powersave=0x30
	.EQU __sm_standby=0x60
	.EQU __sm_ext_standby=0x70

	.MACRO __CPD1N
	CPI  R30,LOW(@0)
	LDI  R26,HIGH(@0)
	CPC  R31,R26
	LDI  R26,BYTE3(@0)
	CPC  R22,R26
	LDI  R26,BYTE4(@0)
	CPC  R23,R26
	.ENDM

	.MACRO __CPD2N
	CPI  R26,LOW(@0)
	LDI  R30,HIGH(@0)
	CPC  R27,R30
	LDI  R30,BYTE3(@0)
	CPC  R24,R30
	LDI  R30,BYTE4(@0)
	CPC  R25,R30
	.ENDM

	.MACRO __CPWRR
	CP   R@0,R@2
	CPC  R@1,R@3
	.ENDM

	.MACRO __CPWRN
	CPI  R@0,LOW(@2)
	LDI  R30,HIGH(@2)
	CPC  R@1,R30
	.ENDM

	.MACRO __ADDB1MN
	SUBI R30,LOW(-@0-(@1))
	.ENDM
	.MACRO __ADDB2MN
	SUBI R26,LOW(-@0-(@1))
	.ENDM
	.MACRO __ADDW1MN
	SUBI R30,LOW(-@0-(@1))
	SBCI R31,HIGH(-@0-(@1))
	.ENDM
	.MACRO __ADDW2MN
	SUBI R26,LOW(-@0-(@1))
	SBCI R27,HIGH(-@0-(@1))
	.ENDM
	.MACRO __ADDW1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	.ENDM
	.MACRO __ADDD1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	SBCI R24,BYTE3(-2*@0-(@1))
	.ENDM
	.MACRO __ADDD1N
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	SBCI R22,BYTE3(-@0)
	SBCI R23,BYTE4(-@0)
	.ENDM

	.MACRO __ADDD2N
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	SBCI R24,BYTE3(-@0)
	SBCI R25,BYTE4(-@0)
	.ENDM

	.MACRO __SUBD1N
	SUBI R30,LOW(@0)
	SBCI R31,HIGH(@0)
	SBCI R22,BYTE3(@0)
	SBCI R23,BYTE4(@0)
	.ENDM

	.MACRO __SUBD2N
	SUBI R26,LOW(@0)
	SBCI R27,HIGH(@0)
	SBCI R24,BYTE3(@0)
	SBCI R25,BYTE4(@0)
	.ENDM

	.MACRO __ANDD1N
	ANDI R30,LOW(@0)
	ANDI R31,HIGH(@0)
	ANDI R22,BYTE3(@0)
	ANDI R23,BYTE4(@0)
	.ENDM

	.MACRO __ORD1N
	ORI  R30,LOW(@0)
	ORI  R31,HIGH(@0)
	ORI  R22,BYTE3(@0)
	ORI  R23,BYTE4(@0)
	.ENDM

	.MACRO __DELAY_USB
	LDI  R24,LOW(@0)
__DELAY_USB_LOOP:
	DEC  R24
	BRNE __DELAY_USB_LOOP
	.ENDM

	.MACRO __DELAY_USW
	LDI  R24,LOW(@0)
	LDI  R25,HIGH(@0)
__DELAY_USW_LOOP:
	SBIW R24,1
	BRNE __DELAY_USW_LOOP
	.ENDM

	.MACRO __CLRD1S
	LDI  R30,0
	STD  Y+@0,R30
	STD  Y+@0+1,R30
	STD  Y+@0+2,R30
	STD  Y+@0+3,R30
	.ENDM

	.MACRO __GETD1S
	LDD  R30,Y+@0
	LDD  R31,Y+@0+1
	LDD  R22,Y+@0+2
	LDD  R23,Y+@0+3
	.ENDM

	.MACRO __PUTD1S
	STD  Y+@0,R30
	STD  Y+@0+1,R31
	STD  Y+@0+2,R22
	STD  Y+@0+3,R23
	.ENDM

	.MACRO __PUTD2S
	STD  Y+@0,R26
	STD  Y+@0+1,R27
	STD  Y+@0+2,R24
	STD  Y+@0+3,R25
	.ENDM

	.MACRO __POINTB1MN
	LDI  R30,LOW(@0+@1)
	.ENDM

	.MACRO __POINTW1MN
	LDI  R30,LOW(@0+@1)
	LDI  R31,HIGH(@0+@1)
	.ENDM

	.MACRO __POINTW1FN
	LDI  R30,LOW(2*@0+@1)
	LDI  R31,HIGH(2*@0+@1)
	.ENDM

	.MACRO __POINTD1FN
	LDI  R30,LOW(2*@0+@1)
	LDI  R31,HIGH(2*@0+@1)
	LDI  R22,BYTE3(2*@0+@1)
	.ENDM

	.MACRO __POINTB2MN
	LDI  R26,LOW(@0+@1)
	.ENDM

	.MACRO __POINTW2MN
	LDI  R26,LOW(@0+@1)
	LDI  R27,HIGH(@0+@1)
	.ENDM

	.MACRO __POINTBRM
	LDI  R@0,LOW(@1)
	.ENDM

	.MACRO __POINTWRM
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __POINTBRMN
	LDI  R@0,LOW(@1+@2)
	.ENDM

	.MACRO __POINTWRMN
	LDI  R@0,LOW(@2+@3)
	LDI  R@1,HIGH(@2+@3)
	.ENDM

	.MACRO __POINTWRFN
	LDI  R@0,LOW(@2*2+@3)
	LDI  R@1,HIGH(@2*2+@3)
	.ENDM

	.MACRO __GETD1N
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __GETD2N
	LDI  R26,LOW(@0)
	LDI  R27,HIGH(@0)
	LDI  R24,BYTE3(@0)
	LDI  R25,BYTE4(@0)
	.ENDM

	.MACRO __GETD2S
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	LDD  R24,Y+@0+2
	LDD  R25,Y+@0+3
	.ENDM

	.MACRO __GETB1MN
	LDS  R30,@0+@1
	.ENDM

	.MACRO __GETB1HMN
	LDS  R31,@0+@1
	.ENDM

	.MACRO __GETW1MN
	LDS  R30,@0+@1
	LDS  R31,@0+@1+1
	.ENDM

	.MACRO __GETD1MN
	LDS  R30,@0+@1
	LDS  R31,@0+@1+1
	LDS  R22,@0+@1+2
	LDS  R23,@0+@1+3
	.ENDM

	.MACRO __GETBRMN
	LDS  R@0,@1+@2
	.ENDM

	.MACRO __GETWRMN
	LDS  R@0,@2+@3
	LDS  R@1,@2+@3+1
	.ENDM

	.MACRO __GETWRZ
	LDD  R@0,Z+@2
	LDD  R@1,Z+@2+1
	.ENDM

	.MACRO __GETD2Z
	LDD  R26,Z+@0
	LDD  R27,Z+@0+1
	LDD  R24,Z+@0+2
	LDD  R25,Z+@0+3
	.ENDM

	.MACRO __GETB2MN
	LDS  R26,@0+@1
	.ENDM

	.MACRO __GETW2MN
	LDS  R26,@0+@1
	LDS  R27,@0+@1+1
	.ENDM

	.MACRO __GETD2MN
	LDS  R26,@0+@1
	LDS  R27,@0+@1+1
	LDS  R24,@0+@1+2
	LDS  R25,@0+@1+3
	.ENDM

	.MACRO __PUTB1MN
	STS  @0+@1,R30
	.ENDM

	.MACRO __PUTW1MN
	STS  @0+@1,R30
	STS  @0+@1+1,R31
	.ENDM

	.MACRO __PUTD1MN
	STS  @0+@1,R30
	STS  @0+@1+1,R31
	STS  @0+@1+2,R22
	STS  @0+@1+3,R23
	.ENDM

	.MACRO __PUTDZ2
	STD  Z+@0,R26
	STD  Z+@0+1,R27
	STD  Z+@0+2,R24
	STD  Z+@0+3,R25
	.ENDM

	.MACRO __PUTBMRN
	STS  @0+@1,R@2
	.ENDM

	.MACRO __PUTWMRN
	STS  @0+@1,R@2
	STS  @0+@1+1,R@3
	.ENDM

	.MACRO __PUTBZR
	STD  Z+@1,R@0
	.ENDM

	.MACRO __PUTWZR
	STD  Z+@2,R@0
	STD  Z+@2+1,R@1
	.ENDM

	.MACRO __GETW1R
	MOV  R30,R@0
	MOV  R31,R@1
	.ENDM

	.MACRO __GETW2R
	MOV  R26,R@0
	MOV  R27,R@1
	.ENDM

	.MACRO __GETWRN
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __PUTW1R
	MOV  R@0,R30
	MOV  R@1,R31
	.ENDM

	.MACRO __PUTW2R
	MOV  R@0,R26
	MOV  R@1,R27
	.ENDM

	.MACRO __ADDWRN
	SUBI R@0,LOW(-@2)
	SBCI R@1,HIGH(-@2)
	.ENDM

	.MACRO __ADDWRR
	ADD  R@0,R@2
	ADC  R@1,R@3
	.ENDM

	.MACRO __SUBWRN
	SUBI R@0,LOW(@2)
	SBCI R@1,HIGH(@2)
	.ENDM

	.MACRO __SUBWRR
	SUB  R@0,R@2
	SBC  R@1,R@3
	.ENDM

	.MACRO __ANDWRN
	ANDI R@0,LOW(@2)
	ANDI R@1,HIGH(@2)
	.ENDM

	.MACRO __ANDWRR
	AND  R@0,R@2
	AND  R@1,R@3
	.ENDM

	.MACRO __ORWRN
	ORI  R@0,LOW(@2)
	ORI  R@1,HIGH(@2)
	.ENDM

	.MACRO __ORWRR
	OR   R@0,R@2
	OR   R@1,R@3
	.ENDM

	.MACRO __EORWRR
	EOR  R@0,R@2
	EOR  R@1,R@3
	.ENDM

	.MACRO __GETWRS
	LDD  R@0,Y+@2
	LDD  R@1,Y+@2+1
	.ENDM

	.MACRO __PUTWSR
	STD  Y+@2,R@0
	STD  Y+@2+1,R@1
	.ENDM

	.MACRO __MOVEWRR
	MOV  R@0,R@2
	MOV  R@1,R@3
	.ENDM

	.MACRO __INWR
	IN   R@0,@2
	IN   R@1,@2+1
	.ENDM

	.MACRO __OUTWR
	OUT  @2+1,R@1
	OUT  @2,R@0
	.ENDM

	.MACRO __CALL1MN
	LDS  R30,@0+@1
	LDS  R31,@0+@1+1
	ICALL
	.ENDM

	.MACRO __CALL1FN
	LDI  R30,LOW(2*@0+@1)
	LDI  R31,HIGH(2*@0+@1)
	RCALL __GETW1PF
	ICALL
	.ENDM

	.MACRO __CALL2EN
	LDI  R26,LOW(@0+@1)
	LDI  R27,HIGH(@0+@1)
	RCALL __EEPROMRDW
	ICALL
	.ENDM

	.MACRO __GETW1STACK
	IN   R26,SPL
	IN   R27,SPH
	ADIW R26,@0+1
	LD   R30,X+
	LD   R31,X
	.ENDM

	.MACRO __NBST
	BST  R@0,@1
	IN   R30,SREG
	LDI  R31,0x40
	EOR  R30,R31
	OUT  SREG,R30
	.ENDM


	.MACRO __PUTB1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	RCALL __PUTDP1
	.ENDM

	.MACRO __PUTB1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	RCALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	RCALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	RCALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	RCALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RNS
	MOVW R26,R@0
	ADIW R26,@1
	RCALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	RCALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	RCALL __PUTDP1
	.ENDM


	.MACRO __GETB1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R30,Z
	.ENDM

	.MACRO __GETB1HSX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	.ENDM

	.MACRO __GETW1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R31,Z
	MOV  R30,R0
	.ENDM

	.MACRO __GETD1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R1,Z+
	LD   R22,Z+
	LD   R23,Z
	MOVW R30,R0
	.ENDM

	.MACRO __GETB2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R26,X
	.ENDM

	.MACRO __GETW2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	.ENDM

	.MACRO __GETD2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R1,X+
	LD   R24,X+
	LD   R25,X
	MOVW R26,R0
	.ENDM

	.MACRO __GETBRSX
	MOVW R30,R28
	SUBI R30,LOW(-@1)
	SBCI R31,HIGH(-@1)
	LD   R@0,Z
	.ENDM

	.MACRO __GETWRSX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	LD   R@0,Z+
	LD   R@1,Z
	.ENDM

	.MACRO __LSLW8SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	CLR  R30
	.ENDM

	.MACRO __PUTB1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __CLRW1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	CLR  R0
	ST   Z+,R0
	ST   Z,R0
	.ENDM

	.MACRO __CLRD1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	CLR  R0
	ST   Z+,R0
	ST   Z+,R0
	ST   Z+,R0
	ST   Z,R0
	.ENDM

	.MACRO __PUTB2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z,R26
	.ENDM

	.MACRO __PUTW2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z,R27
	.ENDM

	.MACRO __PUTD2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z+,R27
	ST   Z+,R24
	ST   Z,R25
	.ENDM

	.MACRO __PUTBSRX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z,R@1
	.ENDM

	.MACRO __PUTWSRX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	ST   Z+,R@0
	ST   Z,R@1
	.ENDM

	.MACRO __PUTB1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __MULBRR
	MULS R@0,R@1
	MOV  R30,R0
	.ENDM

	.MACRO __MULBRRU
	MUL  R@0,R@1
	MOV  R30,R0
	.ENDM

	.CSEG
	.ORG 0

	.INCLUDE "skytmain.vec"
	.INCLUDE "skytmain.inc"

__RESET:
	CLI
	CLR  R30
	OUT  EECR,R30

;INTERRUPT VECTORS ARE PLACED
;AT THE START OF FLASH
	LDI  R31,1
	OUT  GICR,R31
	OUT  GICR,R30
	OUT  MCUCR,R30

;DISABLE WATCHDOG
	LDI  R31,0x18
	OUT  WDTCR,R31
	OUT  WDTCR,R30

;CLEAR R2-R14
	LDI  R24,13
	LDI  R26,2
	CLR  R27
__CLEAR_REG:
	ST   X+,R30
	DEC  R24
	BRNE __CLEAR_REG

;CLEAR SRAM
	LDI  R24,LOW(0x400)
	LDI  R25,HIGH(0x400)
	LDI  R26,0x60
__CLEAR_SRAM:
	ST   X+,R30
	SBIW R24,1
	BRNE __CLEAR_SRAM

;GLOBAL VARIABLES INITIALIZATION
	LDI  R30,LOW(__GLOBAL_INI_TBL*2)
	LDI  R31,HIGH(__GLOBAL_INI_TBL*2)
__GLOBAL_INI_NEXT:
	LPM  R24,Z+
	LPM  R25,Z+
	SBIW R24,0
	BREQ __GLOBAL_INI_END
	LPM  R26,Z+
	LPM  R27,Z+
	LPM  R0,Z+
	LPM  R1,Z+
	MOVW R22,R30
	MOVW R30,R0
__GLOBAL_INI_LOOP:
	LPM  R0,Z+
	ST   X+,R0
	SBIW R24,1
	BRNE __GLOBAL_INI_LOOP
	MOVW R30,R22
	RJMP __GLOBAL_INI_NEXT
__GLOBAL_INI_END:

;STACK POINTER INITIALIZATION
	LDI  R30,LOW(0x45F)
	OUT  SPL,R30
	LDI  R30,HIGH(0x45F)
	OUT  SPH,R30

;DATA STACK POINTER INITIALIZATION
	LDI  R28,LOW(0x160)
	LDI  R29,HIGH(0x160)

	RJMP _main

	.ESEG
	.ORG 0
	.DB  0 ; FIRST EEPROM LOCATION NOT USED, SEE ATMEL ERRATA SHEETS

	.DSEG
	.ORG 0x160
;       1 /*********************************************
;       2 This program was produced by the
;       3 CodeWizardAVR V1.23.8c Standard
;       4 Automatic Program Generator
;       5 © Copyright 1998-2003 HP InfoTech s.r.l.
;       6 http://www.hpinfotech.ro
;       7 e-mail:office@hpinfotech.ro
;       8 
;       9 Project : SKYT
;      10 Version : 0.01
;      11 Date    : 2006-12-6
;      12 Author  : hlchen                          
;      13 Company :                                 
;      14 Comments:   
;      15 Êý¿ØÔÆÌ¨ 
;      16 Chip type           : ATmega8 
;      17 Program type        : Application
;      18 Clock frequency     : 3.690000 MHz
;      19 Memory model        : Small 
;      20 External SRAM size  : 0 
;      21 Data Stack size     : 256 
;      22 *********************************************/
;      23 typedef unsigned char uchar;  
;      24 typedef unsigned int uint;
;      25 #include <mega8.h>   
;      26 #include <math.h>  
;      27 #include "macro.h"
;      28 #include "LCD.h" 

	.CSEG
_SinPout:
	LD   R30,Y
	ANDI R30,LOW(0x1)
	BREQ _0x3
	SBI  0x15,0
	RJMP _0x4
_0x3:
	CBI  0x15,0
_0x4:
	LD   R30,Y
	ANDI R30,LOW(0x2)
	BREQ _0x5
	SBI  0x15,1
	RJMP _0x6
_0x5:
	CBI  0x15,1
_0x6:
	LD   R30,Y
	ANDI R30,LOW(0x4)
	BREQ _0x7
	SBI  0x12,2
	RJMP _0x8
_0x7:
	CBI  0x12,2
_0x8:
	LD   R30,Y
	ANDI R30,LOW(0x8)
	BREQ _0x9
	SBI  0x12,3
	RJMP _0xA
_0x9:
	CBI  0x12,3
_0xA:
	LD   R30,Y
	ANDI R30,LOW(0x10)
	BREQ _0xB
	SBI  0x12,4
	RJMP _0xC
_0xB:
	CBI  0x12,4
_0xC:
	LD   R30,Y
	ANDI R30,LOW(0x20)
	BREQ _0xD
	SBI  0x12,5
	RJMP _0xE
_0xD:
	CBI  0x12,5
_0xE:
	LD   R30,Y
	ANDI R30,LOW(0x40)
	BREQ _0xF
	SBI  0x12,6
	RJMP _0x10
_0xF:
	CBI  0x12,6
_0x10:
	LD   R30,Y
	ANDI R30,LOW(0x80)
	BREQ _0x11
	SBI  0x12,7
	RJMP _0x12
_0x11:
	CBI  0x12,7
_0x12:
	ADIW R28,1
	RET
_nop:
	ST   -Y,R16
;	i -> R16
	LDI  R16,LOW(0)
_0x14:
	CPI  R16,20
	BRSH _0x15
	NOP
	SUBI R16,-1
	RJMP _0x14
_0x15:
	RJMP _0x103
_CheckState:
	ST   -Y,R16
;	dat -> R16
	LDI  R16,LOW(0)
	CBI  0x18,3
	SBI  0x18,4
_0x103:
	LD   R16,Y+
	RET
_WriteByte:
	RCALL _CheckState
	SBI  0x18,3
	CBI  0x18,4
	RCALL SUBOPT_0x0
	SBI  0x18,2
	CBI  0x18,2
	RJMP _0x102
_SendCommandToLCD:
	RCALL _CheckState
	CBI  0x18,4
	CBI  0x18,3
	RCALL SUBOPT_0x0
	SBI  0x18,2
	CBI  0x18,2
	RJMP _0x102
_SetLine:
	LD   R30,Y
	ANDI R30,LOW(0x7)
	RCALL SUBOPT_0x1
	ORI  R30,LOW(0xB8)
	RCALL SUBOPT_0x1
	RCALL SUBOPT_0x2
	RJMP _0x102
_SetColumn:
	LD   R30,Y
	ANDI R30,LOW(0x3F)
	RCALL SUBOPT_0x1
	ORI  R30,0x40
	RCALL SUBOPT_0x1
	RCALL SUBOPT_0x2
	RJMP _0x102
_SetOnOff:
	LD   R30,Y
	ORI  R30,LOW(0x3E)
	RCALL SUBOPT_0x1
	RCALL SUBOPT_0x2
	RJMP _0x102
_SelectScreen:
	LD   R30,Y
	CPI  R30,0
	BRNE _0x19
	CBI  0x15,4
	RCALL _nop
	CBI  0x15,5
	RCALL _nop
	RJMP _0x18
_0x19:
	CPI  R30,LOW(0x1)
	BRNE _0x1A
	SBI  0x15,4
	RCALL _nop
	CBI  0x15,5
	RCALL _nop
	RJMP _0x18
_0x1A:
	CPI  R30,LOW(0x2)
	BRNE _0x1C
	CBI  0x15,4
	RCALL _nop
	SBI  0x15,5
	RCALL _nop
_0x1C:
_0x18:
_0x102:
	ADIW R28,1
	RET
_ClearScreen:
	RCALL __SAVELOCR2
;	screen -> Y+2
;	i -> R16
;	j -> R17
	RCALL SUBOPT_0x3
	RCALL _SelectScreen
	LDI  R16,LOW(0)
_0x1E:
	CPI  R16,8
	BRSH _0x1F
	ST   -Y,R16
	RCALL _SetLine
	LDI  R17,LOW(0)
_0x21:
	CPI  R17,64
	BRSH _0x22
	RCALL SUBOPT_0x4
	RCALL _WriteByte
	SUBI R17,-1
	RJMP _0x21
_0x22:
	SUBI R16,-1
	RJMP _0x1E
_0x1F:
	RCALL __LOADLOCR2
	RJMP _0x101
_Show8x8:
	ST   -Y,R16
;	lin -> Y+4
;	column -> Y+3
;	num -> Y+2
;	add -> Y+1
;	i -> R16
	LDD  R26,Y+3
	CPI  R26,LOW(0x40)
	BRSH _0x23
	RCALL SUBOPT_0x5
	RCALL SUBOPT_0x6
	LDI  R16,LOW(0)
_0x25:
	CPI  R16,8
	BRSH _0x26
	RCALL SUBOPT_0x7
	BRSH _0x27
	RJMP _0x104
_0x27:
	RCALL SUBOPT_0x8
	RCALL SUBOPT_0x9
	RCALL SUBOPT_0xA
_0x104:
	LDD  R30,Y+2
	RCALL SUBOPT_0xB
	SUBI R16,-1
	RJMP _0x25
_0x26:
	RJMP _0x29
_0x23:
	RCALL SUBOPT_0x8
	LDD  R30,Y+3
	SUBI R30,LOW(64)
	STD  Y+3,R30
	RCALL SUBOPT_0x9
	RCALL SUBOPT_0x6
	LDI  R16,LOW(0)
_0x2B:
	CPI  R16,8
	BRSH _0x2C
	RCALL SUBOPT_0x7
	BRSH _0x2D
	RJMP _0x105
_0x2D:
	RCALL SUBOPT_0x5
	RCALL SUBOPT_0xA
_0x105:
	LDD  R30,Y+2
	RCALL SUBOPT_0xB
	SUBI R16,-1
	RJMP _0x2B
_0x2C:
_0x29:
	LDD  R16,Y+0
	ADIW R28,5
	RET
_Show_Circle:
	RCALL __SAVELOCR3
;	i -> R16
;	lin -> R17
;	column -> R18
	LDI  R18,LOW(8)
	LDI  R17,LOW(0)
_0x30:
	CPI  R17,6
	BRSH _0x31
	RCALL SUBOPT_0xC
	RCALL _SelectScreen
	RCALL SUBOPT_0xD
	LDI  R16,LOW(0)
_0x33:
	CPI  R16,48
	BRSH _0x34
	RCALL SUBOPT_0xE
	PUSH R27
	PUSH R26
	RCALL SUBOPT_0xF
	POP  R26
	POP  R27
	RCALL SUBOPT_0x10
	SUBI R16,-1
	RJMP _0x33
_0x34:
	SUBI R17,-1
	RJMP _0x30
_0x31:
	RCALL __LOADLOCR3
	RJMP _0x101
_Show_HalfCircle:
	RCALL __SAVELOCR3
;	i -> R16
;	lin -> R17
;	column -> R18
	LDI  R18,LOW(25)
	LDI  R17,LOW(0)
_0x36:
	CPI  R17,6
	BRSH _0x37
	RCALL SUBOPT_0x8
	RCALL SUBOPT_0xD
	LDI  R16,LOW(24)
_0x39:
	CPI  R16,48
	BRSH _0x3A
	RCALL SUBOPT_0xE
	PUSH R27
	PUSH R26
	RCALL SUBOPT_0xF
	POP  R26
	POP  R27
	RCALL SUBOPT_0x10
	SUBI R16,-1
	RJMP _0x39
_0x3A:
	SUBI R17,-1
	RJMP _0x36
_0x37:
	RCALL __LOADLOCR3
	RJMP _0x101
;	deg -> Y+4
;	bScreen -> Y+3
;	lin -> R16
;	column -> R17
;	i -> R18
_ShowChinese:
	RCALL SUBOPT_0x3
	RCALL SUBOPT_0x3
	RCALL SUBOPT_0x3
	RCALL SUBOPT_0x4
	RCALL _Show8x8
	RCALL SUBOPT_0x3
	RCALL SUBOPT_0x11
	LDI  R30,LOW(8)
	RCALL SUBOPT_0x12
	RCALL SUBOPT_0x3
	RCALL SUBOPT_0x3
	LDI  R30,LOW(16)
	RCALL SUBOPT_0x12
	RCALL SUBOPT_0x11
	LDI  R30,LOW(24)
	ST   -Y,R30
	RCALL _Show8x8
_0x101:
	ADIW R28,3
	RET
_InitLCD:
	RCALL __SAVELOCR2
;	i -> R16,R17
	LDI  R16,208
	LDI  R17,7
_0x43:
	MOVW R30,R16
	__SUBWRN 16,17,1
	SBIW R30,0
	BRNE _0x43
	RCALL SUBOPT_0xC
	RCALL _SetOnOff
	RCALL SUBOPT_0x4
	RCALL _ClearScreen
	RCALL __LOADLOCR2P
	RET
_Show_Preset:
	RCALL SUBOPT_0x13
	LDI  R30,LOW(20)
	ST   -Y,R30
	RCALL SUBOPT_0x4
	RCALL _ShowChinese
	RCALL SUBOPT_0x13
	LDI  R30,LOW(34)
	ST   -Y,R30
	RCALL SUBOPT_0xC
	RCALL _ShowChinese
	RET
_Show_Slow:
	RCALL SUBOPT_0x13
	LDI  R30,LOW(86)
	ST   -Y,R30
	LDI  R30,LOW(3)
	ST   -Y,R30
	RCALL _ShowChinese
	RET
;      29 //#include "sed1565_s.h"
;      30 #define RXB8 1
;      31 #define TXB8 0
;      32 #define UPE 2
;      33 #define OVR 3
;      34 #define FE 4
;      35 #define UDRE 5
;      36 #define RXC 7
;      37 #define Light 5
;      38 #define FRAMING_ERROR (1<<FE)
;      39 #define PARITY_ERROR (1<<UPE)
;      40 #define DATA_OVERRUN (1<<OVR)
;      41 #define DATA_REGISTER_EMPTY (1<<UDRE)
;      42 #define RX_COMPLETE (1<<RXC)
;      43 #define sysInitLcd 0
;      44  // USART Receiver buffer
;      45 #define RX_BUFFER_SIZE 8
;      46 char rx_buffer[RX_BUFFER_SIZE];

	.DSEG
_rx_buffer:
	.BYTE 0x8
;      47 unsigned char rx_wr_index,rx_rd_index,rx_counter;
;      48 // This flag is set on USART Receiver buffer overflow
;      49 bit rx_buffer_overflow,b_ComEnable;
;      50 uchar uc_syssta;
;      51 // USART Receiver interrupt service routine
;      52 #pragma savereg-
;      53 interrupt [USART_RXC] void uart_rx_isr(void)
;      54 { 

	.CSEG
_uart_rx_isr:
;      55 char status,data;
;      56 #asm
	RCALL __SAVELOCR2
;	status -> R16
;	data -> R17
;      57     push r26
    push r26
;      58     push r27
    push r27
;      59     push r30
    push r30
;      60     push r31
    push r31
;      61     in   r26,sreg 
    in   r26,sreg 
;      62     push r26
    push r26
;      63 #endasm
;      64 status=UCSRA;
	IN   R16,11
;      65 data=UDR;
	IN   R17,12
;      66 
;      67 if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
	MOV  R30,R16
	ANDI R30,LOW(0x1C)
	BRNE _0x46
;      68    {
;      69    rx_buffer[rx_wr_index]=data;
	MOV  R26,R4
	LDI  R27,0
	SUBI R26,LOW(-_rx_buffer)
	SBCI R27,HIGH(-_rx_buffer)
	ST   X,R17
;      70    if (++rx_wr_index == RX_BUFFER_SIZE) rx_wr_index=0;
	INC  R4
	LDI  R30,LOW(8)
	CP   R30,R4
	BRNE _0x47
	CLR  R4
;      71    if (++rx_counter == RX_BUFFER_SIZE)
_0x47:
	INC  R6
	LDI  R30,LOW(8)
	CP   R30,R6
	BRNE _0x48
;      72       {
;      73       rx_counter=0;
	CLR  R6
;      74       rx_buffer_overflow=1;
	SET
	BLD  R2,0
;      75       };
_0x48:
;      76    };
_0x46:
;      77 if ((rx_buffer[0]=='o')&&(rx_buffer[1]=='k')) b_ComEnable=1; 
	LDS  R26,_rx_buffer
	CPI  R26,LOW(0x6F)
	BRNE _0x4A
	__GETB1MN _rx_buffer,1
	CPI  R30,LOW(0x6B)
	BREQ _0x4B
_0x4A:
	RJMP _0x49
_0x4B:
	SET
	BLD  R2,1
;      78 #asm
_0x49:
;      79     pop  r26
    pop  r26
;      80     out  sreg,r26
    out  sreg,r26
;      81     pop  r31
    pop  r31
;      82     pop  r30
    pop  r30
;      83     pop  r27
    pop  r27
;      84     pop  r26
    pop  r26
;      85 #endasm
;      86 }
	RCALL __LOADLOCR2P
	RETI
;      87 #pragma savereg+
;      88 
;      89 #ifndef _DEBUG_TERMINAL_IO_
;      90 // Get a character from the USART Receiver buffer
;      91 #define _ALTERNATE_GETCHAR_
;      92 #pragma used+
;      93 char getchar(void)
;      94 {
;      95 char data;
;      96 while (rx_counter==0);
;	data -> R16
;      97 data=rx_buffer[rx_rd_index];
;      98 if (++rx_rd_index == RX_BUFFER_SIZE) rx_rd_index=0;
;      99 #asm("cli")
;     100 --rx_counter;
;     101 #asm("sei")
;     102 return data;
;     103 }
;     104 #pragma used-
;     105 #endif
;     106 
;     107 // USART Transmitter buffer
;     108 #define TX_BUFFER_SIZE 8
;     109 char tx_buffer[TX_BUFFER_SIZE];

	.DSEG
_tx_buffer:
	.BYTE 0x8
;     110 unsigned char tx_wr_index,tx_rd_index,tx_counter;
;     111 
;     112 // USART Transmitter interrupt service routine
;     113 #pragma savereg-
;     114 interrupt [USART_TXC] void uart_tx_isr(void)
;     115 {

	.CSEG
_uart_tx_isr:
;     116 #asm
;     117     push r26
    push r26
;     118     push r27
    push r27
;     119     push r30
    push r30
;     120     push r31
    push r31
;     121     in   r26,sreg
    in   r26,sreg
;     122     push r26
    push r26
;     123 #endasm
;     124 if (tx_counter)
	TST  R10
	BREQ _0x50
;     125    {
;     126    --tx_counter;
	DEC  R10
;     127    UDR=tx_buffer[tx_rd_index];
	MOV  R30,R9
	RCALL SUBOPT_0x14
	LD   R30,Z
	OUT  0xC,R30
;     128    if (++tx_rd_index == TX_BUFFER_SIZE) tx_rd_index=0;
	INC  R9
	LDI  R30,LOW(8)
	CP   R30,R9
	BRNE _0x51
	CLR  R9
;     129    }; 
_0x51:
_0x50:
;     130 
;     131 #asm
;     132     pop  r26
    pop  r26
;     133     out  sreg,r26
    out  sreg,r26
;     134     pop  r31
    pop  r31
;     135     pop  r30
    pop  r30
;     136     pop  r27
    pop  r27
;     137     pop  r26
    pop  r26
;     138 #endasm
;     139 }
	RETI
;     140 #pragma savereg+
;     141 
;     142 #ifndef _DEBUG_TERMINAL_IO_
;     143 // Write a character to the USART Transmitter buffer
;     144 #define _ALTERNATE_PUTCHAR_
;     145 #pragma used+
;     146 void putchar(char c)
;     147 {
_putchar:
;     148 while (tx_counter == TX_BUFFER_SIZE);
_0x52:
	LDI  R30,LOW(8)
	CP   R30,R10
	BREQ _0x52
;     149 #asm("cli")
	cli
;     150 if (tx_counter || ((UCSRA & DATA_REGISTER_EMPTY)==0))
	TST  R10
	BRNE _0x56
	SBIC 0xB,5
	RJMP _0x55
_0x56:
;     151    {
;     152    tx_buffer[tx_wr_index]=c;
	MOV  R30,R8
	RCALL SUBOPT_0x14
	LD   R26,Y
	STD  Z+0,R26
;     153    if (++tx_wr_index == TX_BUFFER_SIZE) tx_wr_index=0;
	INC  R8
	LDI  R30,LOW(8)
	CP   R30,R8
	BRNE _0x58
	CLR  R8
;     154    ++tx_counter;
_0x58:
	INC  R10
;     155    }
;     156 else UDR=c;
	RJMP _0x59
_0x55:
	LD   R30,Y
	OUT  0xC,R30
;     157 #asm("sei")
_0x59:
	sei
;     158 }
	ADIW R28,1
	RET
;     159 #pragma used-
;     160 #endif
;     161 // Standard Input/Output functions
;     162 #include <stdio.h>  
;     163 uchar ucInputValue;
;     164 uint uiLastADValue[3];

	.DSEG
_uiLastADValue:
	.BYTE 0x6
;     165 uchar ucInputParam0; 
;     166 uchar ucChannelN,uc_ReceiveSta;
;     167 bit bInputChange,bMotorSpeed,bLight,bReceiveOpend;         
;     168 void inputdeal(void); 
;     169 void TransmitEnable(void);
;     170 void ReceiveEnable(void); 
;     171 void Communication(void);
;     172 void LcdShow(void);
;     173 #define HighSpeed 0x33
;     174 #define SlowSpeed 0x99
;     175 #define ADC_VREF_TYPE 0x00      
;     176 #define RE 0
;     177 #define DE 1
;     178 // ADC interrupt service routine
;     179 interrupt [TIM0_OVF] void timer0_ovf_isr(void)
;     180 {

	.CSEG
_timer0_ovf_isr:
	ST   -Y,R30
;     181 // Place your code here 
;     182 TCNT0=0xf0;
	RCALL SUBOPT_0x15
;     183 }
	LD   R30,Y+
	RETI
;     184 interrupt [ADC_INT] void adc_isr(void)
;     185 {
_adc_isr:
	ST   -Y,R0
	ST   -Y,R1
	ST   -Y,R15
	ST   -Y,R22
	ST   -Y,R23
	ST   -Y,R24
	ST   -Y,R25
	ST   -Y,R26
	ST   -Y,R27
	ST   -Y,R30
	ST   -Y,R31
	IN   R30,SREG
	ST   -Y,R30
;     186 uint adc_data;
;     187 // Read the AD conversion result
;     188 adc_data=ADCW;
	RCALL __SAVELOCR2
;	adc_data -> R16,R17
	__INWR 16,17,4
;     189 
;     190 // Place your code here 
;     191 switch (ucChannelN)
	MOV  R30,R13
;     192 {
;     193 case 0:
	CPI  R30,0
	BRNE _0x5D
;     194  	       	if (uiLastADValue[0]!=adc_data)
	LDS  R26,_uiLastADValue
	LDS  R27,_uiLastADValue+1
	CP   R16,R26
	CPC  R17,R27
	BREQ _0x5E
;     195  		{
;     196  		uiLastADValue[0]=adc_data;
	__PUTWMRN _uiLastADValue,0,16,17
;     197  		ucInputParam0=uiLastADValue[0]*24/1024;
	LDS  R26,_uiLastADValue
	LDS  R27,_uiLastADValue+1
	LDI  R30,LOW(24)
	LDI  R31,HIGH(24)
	RCALL SUBOPT_0x16
;     198 		//ucInputParam0 = tmp/100;
;     199 		//ucInputParam1 = (tmp%100)/10;
;     200 		//ucInputParam2 = (tmp%100)%10;
;     201 		bInputChange=1;
	BLD  R2,2
;     202 		ucInputValue=0x01;
	LDI  R30,LOW(1)
	MOV  R11,R30
;     203 	       
;     204 		} 
;     205 		ADMUX=0x01;
_0x5E:
	LDI  R30,LOW(1)
	OUT  0x7,R30
;     206 		break;  
	RJMP _0x5C
;     207 case 1: 
_0x5D:
	CPI  R30,LOW(0x1)
	BRNE _0x5F
;     208         	if (uiLastADValue[1]!=adc_data)
	__GETW2MN _uiLastADValue,2
	CP   R16,R26
	CPC  R17,R27
	BREQ _0x60
;     209  		{
;     210  		uiLastADValue[1]=adc_data;
	__PUTWMRN _uiLastADValue,2,16,17
;     211  		ucInputParam0=uiLastADValue[1]*12/1024;
	__GETW1MN _uiLastADValue,2
	LDI  R26,LOW(12)
	LDI  R27,HIGH(12)
	RCALL SUBOPT_0x16
;     212 		//ucInputParam0 = tmp/100;
;     213 		//ucInputParam1 = (tmp%100)/10;
;     214 		//ucInputParam2 = (tmp%100)%10;
;     215 		bInputChange=1;
	BLD  R2,2
;     216 		ucInputValue=0x02; 
	LDI  R30,LOW(2)
	MOV  R11,R30
;     217 	     
;     218 		} 
;     219 		ADMUX=0x02;
_0x60:
	LDI  R30,LOW(2)
	OUT  0x7,R30
;     220 		break;  
	RJMP _0x5C
;     221 case 2:
_0x5F:
	CPI  R30,LOW(0x2)
	BREQ PC+2
	RJMP _0x71
;     222 		if (uiLastADValue[2]!=adc_data)
	__GETW2MN _uiLastADValue,4
	CP   R16,R26
	CPC  R17,R27
	BRNE PC+2
	RJMP _0x62
;     223  		{
;     224  		uiLastADValue[2]=adc_data;
	__PUTWMRN _uiLastADValue,4,16,17
;     225  		//ucInputParam0=uiLastADValue[2]*6/1024; 
;     226  	       	if (abs(uiLastADValue[2]-1023)<100)
	__GETW1MN _uiLastADValue,4
	SUBI R30,LOW(1023)
	SBCI R31,HIGH(1023)
	RCALL SUBOPT_0x17
	CPI  R30,LOW(0x64)
	LDI  R26,HIGH(0x64)
	CPC  R31,R26
	BRSH _0x63
;     227  	       		 ucInputValue=3;
	LDI  R30,LOW(3)
	MOV  R11,R30
;     228    	        else if (abs(uiLastADValue[2]-465)<50)
	RJMP _0x64
_0x63:
	__GETW1MN _uiLastADValue,4
	SUBI R30,LOW(465)
	SBCI R31,HIGH(465)
	RCALL SUBOPT_0x17
	SBIW R30,50
	BRSH _0x65
;     229  	       		 ucInputValue=4;
	LDI  R30,LOW(4)
	MOV  R11,R30
;     230        		else if (abs(uiLastADValue[2]-292)<25)
	RJMP _0x66
_0x65:
	__GETW1MN _uiLastADValue,4
	SUBI R30,LOW(292)
	SBCI R31,HIGH(292)
	RCALL SUBOPT_0x17
	SBIW R30,25
	BRSH _0x67
;     231  	       		 ucInputValue=5;	 
	LDI  R30,LOW(5)
	MOV  R11,R30
;     232  	       	else if (abs(uiLastADValue[2]-204)<25)
	RJMP _0x68
_0x67:
	__GETW1MN _uiLastADValue,4
	SUBI R30,LOW(204)
	SBCI R31,HIGH(204)
	RCALL SUBOPT_0x17
	SBIW R30,25
	BRSH _0x69
;     233  	       		 ucInputValue=6;
	LDI  R30,LOW(6)
	MOV  R11,R30
;     234  	       	else if (abs(uiLastADValue[2]-146)<12)
	RJMP _0x6A
_0x69:
	__GETW1MN _uiLastADValue,4
	SUBI R30,LOW(146)
	SBCI R31,HIGH(146)
	RCALL SUBOPT_0x17
	SBIW R30,12
	BRSH _0x6B
;     235  	       		 ucInputValue=7;
	LDI  R30,LOW(7)
	MOV  R11,R30
;     236  	       	else if (abs(uiLastADValue[2]-93)<12) 
	RJMP _0x6C
_0x6B:
	__GETW1MN _uiLastADValue,4
	SUBI R30,LOW(93)
	SBCI R31,HIGH(93)
	RCALL SUBOPT_0x17
	SBIW R30,12
	BRSH _0x6D
;     237  	       	         ucInputValue=8;
	LDI  R30,LOW(8)
	MOV  R11,R30
;     238  	       	else if (abs(uiLastADValue[2])<6)
	RJMP _0x6E
_0x6D:
	__GETW1MN _uiLastADValue,4
	RCALL SUBOPT_0x17
	SBIW R30,6
	BRSH _0x6F
;     239  	       		 ucInputValue=9;
	LDI  R30,LOW(9)
	MOV  R11,R30
;     240  	       	else break;
	RJMP _0x70
_0x6F:
	RJMP _0x5C
;     241  	       //	else if (abs(uiLastADValue[2]-512
;     242 		//ucInputParam0 = tmp/100;
;     243 		//ucInputParam1 = (tmp%100)/10;
;     244 		//ucInputParam2 = (tmp%100)%10;
;     245 		bInputChange=1;
_0x70:
_0x6E:
_0x6C:
_0x6A:
_0x68:
_0x66:
_0x64:
	SET
	BLD  R2,2
;     246 //		ucInputValue=ucInputParam0+2; 
;     247 	     
;     248 		} 
;     249 		ADMUX=0x00;
_0x62:
	RCALL SUBOPT_0x18
;     250 		break;              
;     251 default:
_0x71:
;     252 		break;
;     253 }   
_0x5C:
;     254 ADCSRA|=0x40;
	SBI  0x6,6
;     255 //ADMUX^=0x01;   
;     256 if (ucChannelN++==3)    ucChannelN=0;
	MOV  R30,R13
	INC  R13
	CPI  R30,LOW(0x3)
	BRNE _0x72
	CLR  R13
;     257 
;     258 }
_0x72:
	RCALL __LOADLOCR2P
	LD   R30,Y+
	OUT  SREG,R30
	LD   R31,Y+
	LD   R30,Y+
	LD   R27,Y+
	LD   R26,Y+
	LD   R25,Y+
	LD   R24,Y+
	LD   R23,Y+
	LD   R22,Y+
	LD   R15,Y+
	LD   R1,Y+
	LD   R0,Y+
	RETI
;     259 
;     260 // Declare your global variables here
;     261 
;     262 void main(void)
;     263 {
_main:
;     264 // Declare your local variables here
;     265  
;     266 uint i;
;     267 // Input/Output Ports initialization
;     268 // Port B initialization
;     269 // Func0=Out Func1=Out Func2=Out Func3=Out Func4=Out Func5=Out Func6=Out Func7=Out 
;     270 // State0=0 State1=0 State2=0 State3=0 State4=0 State5=0 State6=0 State7=0 
;     271 PORTB=0x00;
;	i -> R16,R17
	LDI  R30,LOW(0)
	OUT  0x18,R30
;     272 DDRB=0xFF;
	LDI  R30,LOW(255)
	OUT  0x17,R30
;     273 
;     274 // Port C initialization
;     275 // Func0=Out Func1=Out Func2=Out Func3=Out Func4=Out Func5=Out Func6=Out 
;     276 // State0=0 State1=0 State2=0 State3=0 State4=0 State5=0 State6=0 
;     277 PORTC=0x00;
	LDI  R30,LOW(0)
	OUT  0x15,R30
;     278 DDRC=0xff;
	LDI  R30,LOW(255)
	OUT  0x14,R30
;     279 
;     280 // Port D initialization
;     281 // Func0=Out Func1=Out Func2=Out Func3=Out Func4=Out Func5=Out Func6=Out Func7=Out 
;     282 // State0=0 State1=0 State2=0 State3=0 State4=0 State5=0 State6=0 State7=0 
;     283 PORTD=0x00;
	LDI  R30,LOW(0)
	OUT  0x12,R30
;     284 DDRD=0x73;
	LDI  R30,LOW(115)
	OUT  0x11,R30
;     285 
;     286 // Timer/Counter 0 initialization
;     287 // Clock source: System Clock
;     288 // Clock value: 3690.000 kHz
;     289 TCCR0=0x03;
	LDI  R30,LOW(3)
	OUT  0x33,R30
;     290 TCNT0=0xf0;
	RCALL SUBOPT_0x15
;     291 
;     292 
;     293 // Timer/Counter 1 initialization
;     294 // Clock source: System Clock
;     295 // Clock value: Timer 1 Stopped
;     296 // Mode: Normal top=FFFFh
;     297 // OC1A output: Discon.
;     298 // OC1B output: Discon. 
;     299 // Noise Canceler: Off
;     300 // Input Capture on Falling Edge
;     301 //Ä£Ê½1(¼ÆÊýÆ÷ÉÏÏÞÖµ=0xff) PWMÆµÂÊ = ÏµÍ³Ê±ÖÓÆµÂÊ/£¨·ÖÆµÏµÊý*2*¼ÆÊýÆ÷ÉÏÏÞÖµ£©£© 
;     302 TCCR1A=0x00;
	LDI  R30,LOW(0)
	OUT  0x2F,R30
;     303 //COM1A1,COM1A0,COM1B1,COM1B0=1±íÊ¾ÉýÐò¼ÇÊýÊ±±È½ÏÆ¥Åä½«ÖÃÎ»OC1A/OC1B£¬½µÐò¼ÇÊýÊ±±È½ÏÆ¥Åä½«ÇåÁãOC1A/OC1B
;     304 //¼´OCR1AL<tcnt1<TOP(0xff)Ê± OC1AÎª¸ß tcnt1<OCR1ALÊ±OC1AÎªµÍ
;     305 //WGM11=0 WGM10=1
;     306 TCCR1B=0x00;
	OUT  0x2E,R30
;     307 //WGM13=0 WGM12=0 CS12=1 CS11=0 CS10=0 ·ÖÆµÏµÊý=256
;     308 TCNT1H=0x00;
	OUT  0x2D,R30
;     309 TCNT1L=0x00;
	OUT  0x2C,R30
;     310 OCR1AH=0x00;
	OUT  0x2B,R30
;     311 OCR1AL=0x00; //Õ¼¿Õ±È=40% (0xff-0x99)/0xff=0.4
	OUT  0x2A,R30
;     312 		//Õ¼¿Õ±È=80% 0x33
;     313 OCR1BH=0x00;
	OUT  0x29,R30
;     314 OCR1BL=0x00;
	OUT  0x28,R30
;     315 
;     316 // Timer/Counter 2 initialization
;     317 // Clock source: System Clock
;     318 // Clock value: Timer 2 Stopped
;     319 // Mode: Normal top=FFh
;     320 // OC2 output: Disconnected
;     321 ASSR=0x00;
	OUT  0x22,R30
;     322 TCCR2=0x00;
	OUT  0x25,R30
;     323 TCNT2=0x00;
	OUT  0x24,R30
;     324 OCR2=0x00;
	OUT  0x23,R30
;     325 
;     326 // External Interrupt(s) initialization
;     327 // INT0: Off
;     328 // INT1: Off
;     329 GICR|=0x00;
	IN   R30,0x3B
	OUT  0x3B,R30
;     330 MCUCR=0x00;
	LDI  R30,LOW(0)
	OUT  0x35,R30
;     331 
;     332 // Timer(s)/Counter(s) Interrupt(s) initialization
;     333 TIMSK=0X01;
	LDI  R30,LOW(1)
	OUT  0x39,R30
;     334 
;     335 // USART initialization
;     336 // Communication Parameters: 8 Data, 1 Stop, No Parity
;     337 // USART Receiver: On
;     338 // USART Transmitter: On
;     339 // USART Mode: Asynchronous
;     340 // USART Baud rate: 1200
;     341 
;     342 UCSRA=0x00;
	LDI  R30,LOW(0)
	OUT  0xB,R30
;     343 UCSRB=0xD8;
	LDI  R30,LOW(216)
	OUT  0xA,R30
;     344 UCSRC=0x86;
	LDI  R30,LOW(134)
	OUT  0x20,R30
;     345 UBRRH=0x00;
	LDI  R30,LOW(0)
	OUT  0x20,R30
;     346 UBRRL=0x33;
	LDI  R30,LOW(51)
	OUT  0x9,R30
;     347 // Analog Comparator initialization
;     348 // Analog Comparator: Off
;     349 // Analog Comparator Input Capture by Timer/Counter 1: Off
;     350 // Analog Comparator Output: Off
;     351 ACSR=0x80;
	LDI  R30,LOW(128)
	OUT  0x8,R30
;     352 SFIOR=0x00;
	LDI  R30,LOW(0)
	OUT  0x30,R30
;     353 
;     354 // ADC initialization
;     355 // ADC Clock frequency: 115.313 kHz
;     356 // ADC Voltage Reference: AREF pin
;     357 // ADC High Speed Mode: Off
;     358 // ADC Auto Trigger Source: Timer0 Overflow
;     359 ADMUX=0x00;
	RCALL SUBOPT_0x18
;     360 ADCSRA=0x00;
	LDI  R30,LOW(0)
	OUT  0x6,R30
;     361 //SFIOR&=0x0F;
;     362 //SFIOR|=0x80;
;     363 
;     364 // Global enable interrupts   
;     365 
;     366 InitLCD();
	RCALL _InitLCD
;     367 
;     368 
;     369  
;     370 
;     371 
;     372 
;     373  
;     374 #asm("sei")
	sei
;     375 TransmitEnable();
	RCALL _TransmitEnable
;     376 printf("Ready?");
	__POINTW1FN _0,0
	ST   -Y,R31
	ST   -Y,R30
	LDI  R24,0
	RCALL _printf
	ADIW R28,2
;     377 for (i=0;i<10000;i++); 
	__GETWRN 16,17,0
_0x74:
	__CPWRN 16,17,10000
	BRSH _0x75
	__ADDWRN 16,17,1
	RJMP _0x74
_0x75:
;     378 while (1)
_0x76:
;     379       {
;     380       // Place your code here
;     381       if (tx_counter==0) ReceiveEnable();   
	TST  R10
	BRNE _0x79
	RCALL _ReceiveEnable
;     382  
;     383       if (b_ComEnable)
_0x79:
	SBRS R2,1
	RJMP _0x7A
;     384         {
;     385       	b_ComEnable=0;
	CLT
	BLD  R2,1
;     386       	LcdShow();
	RCALL _LcdShow
;     387       	break;
	RJMP _0x78
;     388 	    }
;     389       };
_0x7A:
	RJMP _0x76
_0x78:
;     390 while(1)
_0x7B:
;     391 {
;     392 
;     393       //inputdeal();
;     394 }
	RJMP _0x7B
;     395 }
_0x7E:
	RJMP _0x7E
;     396 void LcdShow(void)
;     397 {
_LcdShow:
;     398 	Show_Circle();
	RCALL _Show_Circle
;     399 	Show_HalfCircle();
	RCALL _Show_HalfCircle
;     400 	Show_Preset();
	RCALL _Show_Preset
;     401 	Show_Slow();
	RCALL _Show_Slow
;     402 }
	RET
;     403 void TransmitEnable(void)
;     404 {
_TransmitEnable:
;     405 PORTB|=Bit(RE);
	SBI  0x18,0
;     406 PORTB|=Bit(DE);
	SBI  0x18,1
;     407 }
	RET
;     408 void ReceiveEnable(void)
;     409 {
_ReceiveEnable:
;     410 
;     411 PORTB&=Bit(RE);
	IN   R30,0x18
	ANDI R30,LOW(0x1)
	OUT  0x18,R30
;     412 PORTB&=Bit(DE);
	IN   R30,0x18
	ANDI R30,LOW(0x2)
	OUT  0x18,R30
;     413 
;     414 }
	RET
;     415 void TransmitCommandOk(void)
;     416 {
;     417 	//if (uc_syssta==sysInitLcd)
;     418 	//	LcdShow();	
;     419 }
;     420 void Communication(void)
;     421 {
;     422 	
;     423      switch (uc_ReceiveSta)
;     424       {
;     425       case 0:
;     426       		if (getchar()=='R')
;     427 	       		uc_ReceiveSta++;
;     428 	        else if (getchar()=='O')
;     429 	        	uc_ReceiveSta++;
;     430 	        	
;     431 		break;
;     432       case 1:
;     433       		if (getchar()=='e')
;     434 			uc_ReceiveSta++;
;     435 		else if (getchar()=='k')
;     436 			{
;     437 			uc_ReceiveSta=0;
;     438 			b_ComEnable=1;
;     439 			}
;     440 		else 
;     441 			uc_ReceiveSta=0;
;     442 		break; 
;     443       case 2:
;     444       		if (getchar()=='a')
;     445 			uc_ReceiveSta++;
;     446 		else
;     447 	       		uc_ReceiveSta=0;
;     448 		break;
;     449       case 3:
;     450       		if (getchar()=='d')
;     451 			uc_ReceiveSta++;
;     452 		else
;     453 			uc_ReceiveSta=0;
;     454        		break;  
;     455       case 4:
;     456       		uc_ReceiveSta=0;
;     457 	      	if (getchar()=='y')
;     458 			printf("ok");
;     459 		break;
;     460       }                     
;     461       
;     462      
;     463 }
;     464 void inputdeal(void)
;     465 {
;     466 	if (!bInputChange) return;
;     467 	bInputChange=0;
;     468 	switch (ucInputValue)
;     469 	{
;     470 	case 0x01:
;     471 		//printf("%bu,%bu,%bu\n",ucInputParam0,ucInputParam1,ucInputParam2);
;     472 	       //	PaintDegree(ucInputParam0,0);   
;     473 	
;     474 		break;
;     475 	case 0x02:
;     476 	       //	PaintDegree(ucInputParam0,1);
;     477 	
;     478 		break; 
;     479 	case 0x03://key1
;     480 	      	if (!bLight) PORTB|=Bit(Light); 
;     481 	      	else PORTB&=~Bit(Light);
;     482 	      	bLight=!bLight;
;     483 		PORTD|=0x04;
;     484 		break;
;     485 	case 0x04://key2
;     486 	       //	PORTD&=0xc3;
;     487 		PORTD|=0x08;   
;     488 	      //	if (bMotorSpeed)       {Show_Slow();OCR1AL=SlowSpeed;}
;     489 	     //	else   {Show_Quick();OCR1AL=HighSpeed;}
;     490 		bMotorSpeed=!bMotorSpeed;
;     491 		
;     492 		break;  
;     493 	case 0x05://key3
;     494 	       //	PORTD&=0xc3;
;     495 		PORTD|=0x0c;
;     496 		break;
;     497 	case 0x06://key4
;     498 	      //	PORTD&=0xc3;
;     499 		PORTD|=0x10;
;     500 		break;
;     501 	case 0x07://key5
;     502 	       //	PORTD&=0xc3;
;     503 		PORTD|=0x14;
;     504 		break;
;     505 	case 0x08://key6  
;     506 	        //PORTD&=0xc3;
;     507 		PORTD|=0x18;
;     508 		break;
;     509 	case 0x09://keyrelease 
;     510 		PORTD&=0xc3;    
;     511 		break;
;     512 	default:
;     513 		break;
;     514 	}
;     515 }

_abs:
    ld   r30,y+
    ld   r31,y+
    sbiw r30,0
    brpl __abs0
    com  r30
    com  r31
    adiw r30,1
__abs0:
    ret
__put_G3:
	RCALL SUBOPT_0x19
	SBIW R30,0
	BREQ _0xA3
	RCALL SUBOPT_0x19
	ADIW R30,1
	ST   X+,R30
	ST   X,R31
	SBIW R30,1
	LDD  R26,Y+2
	STD  Z+0,R26
	RJMP _0xA4
_0xA3:
	RCALL SUBOPT_0x3
	RCALL _putchar
_0xA4:
	ADIW R28,3
	RET
__print_G3:
	SBIW R28,6
	RCALL __SAVELOCR6
	LDI  R16,0
_0xA5:
	LDD  R30,Y+16
	LDD  R31,Y+16+1
	ADIW R30,1
	STD  Y+16,R30
	STD  Y+16+1,R31
	RCALL SUBOPT_0x1A
	MOV  R19,R30
	CPI  R30,0
	BRNE PC+2
	RJMP _0xA7
	MOV  R30,R16
	CPI  R30,0
	BRNE _0xAB
	CPI  R19,37
	BRNE _0xAC
	LDI  R16,LOW(1)
	RJMP _0xAD
_0xAC:
	RCALL SUBOPT_0x1B
_0xAD:
	RJMP _0xAA
_0xAB:
	CPI  R30,LOW(0x1)
	BRNE _0xAE
	CPI  R19,37
	BRNE _0xAF
	RCALL SUBOPT_0x1B
	LDI  R16,LOW(0)
	RJMP _0xAA
_0xAF:
	LDI  R16,LOW(2)
	LDI  R21,LOW(0)
	LDI  R17,LOW(0)
	CPI  R19,45
	BRNE _0xB0
	LDI  R17,LOW(1)
	RJMP _0xAA
_0xB0:
	CPI  R19,43
	BRNE _0xB1
	LDI  R21,LOW(43)
	RJMP _0xAA
_0xB1:
	CPI  R19,32
	BRNE _0xB2
	LDI  R21,LOW(32)
	RJMP _0xAA
_0xB2:
	RJMP _0xB3
_0xAE:
	CPI  R30,LOW(0x2)
	BRNE _0xB4
_0xB3:
	LDI  R20,LOW(0)
	LDI  R16,LOW(3)
	CPI  R19,48
	BRNE _0xB5
	ORI  R17,LOW(128)
	RJMP _0xAA
_0xB5:
	RJMP _0xB6
_0xB4:
	CPI  R30,LOW(0x3)
	BREQ PC+2
	RJMP _0xAA
_0xB6:
	CPI  R19,48
	BRLO _0xB9
	CPI  R19,58
	BRLO _0xBA
_0xB9:
	RJMP _0xB8
_0xBA:
	MOV  R26,R20
	LDI  R30,LOW(10)
	MUL  R30,R26
	MOV  R30,R0
	MOV  R20,R30
	MOV  R30,R19
	SUBI R30,LOW(48)
	ADD  R20,R30
	RJMP _0xAA
_0xB8:
	MOV  R30,R19
	CPI  R30,LOW(0x63)
	BRNE _0xBE
	RCALL SUBOPT_0x1C
	LD   R30,X
	RCALL SUBOPT_0x1D
	RJMP _0xBF
_0xBE:
	CPI  R30,LOW(0x73)
	BRNE _0xC1
	RCALL SUBOPT_0x1C
	RCALL SUBOPT_0x1E
	RCALL _strlen
	MOV  R16,R30
	RJMP _0xC2
_0xC1:
	CPI  R30,LOW(0x70)
	BRNE _0xC4
	RCALL SUBOPT_0x1C
	RCALL SUBOPT_0x1E
	RCALL _strlenf
	MOV  R16,R30
	ORI  R17,LOW(8)
_0xC2:
	ORI  R17,LOW(2)
	ANDI R17,LOW(127)
	LDI  R18,LOW(0)
	RJMP _0xC5
_0xC4:
	CPI  R30,LOW(0x64)
	BREQ _0xC8
	CPI  R30,LOW(0x69)
	BRNE _0xC9
_0xC8:
	ORI  R17,LOW(4)
	RJMP _0xCA
_0xC9:
	CPI  R30,LOW(0x75)
	BRNE _0xCB
_0xCA:
	LDI  R30,LOW(_tbl10_G3*2)
	LDI  R31,HIGH(_tbl10_G3*2)
	STD  Y+6,R30
	STD  Y+6+1,R31
	LDI  R16,LOW(5)
	RJMP _0xCC
_0xCB:
	CPI  R30,LOW(0x58)
	BRNE _0xCE
	ORI  R17,LOW(8)
	RJMP _0xCF
_0xCE:
	CPI  R30,LOW(0x78)
	BREQ PC+2
	RJMP _0x100
_0xCF:
	LDI  R30,LOW(_tbl16_G3*2)
	LDI  R31,HIGH(_tbl16_G3*2)
	STD  Y+6,R30
	STD  Y+6+1,R31
	LDI  R16,LOW(4)
_0xCC:
	SBRS R17,2
	RJMP _0xD1
	RCALL SUBOPT_0x1C
	RCALL SUBOPT_0x1F
	LDD  R26,Y+10
	LDD  R27,Y+10+1
	SBIW R26,0
	BRGE _0xD2
	LDD  R30,Y+10
	LDD  R31,Y+10+1
	RCALL __ANEGW1
	STD  Y+10,R30
	STD  Y+10+1,R31
	LDI  R21,LOW(45)
_0xD2:
	CPI  R21,0
	BREQ _0xD3
	SUBI R16,-LOW(1)
	RJMP _0xD4
_0xD3:
	ANDI R17,LOW(251)
_0xD4:
	RJMP _0xD5
_0xD1:
	RCALL SUBOPT_0x1C
	RCALL SUBOPT_0x1F
_0xD5:
_0xC5:
	SBRC R17,0
	RJMP _0xD6
_0xD7:
	CP   R16,R20
	BRSH _0xD9
	SBRS R17,7
	RJMP _0xDA
	SBRS R17,2
	RJMP _0xDB
	ANDI R17,LOW(251)
	MOV  R19,R21
	SUBI R16,LOW(1)
	RJMP _0xDC
_0xDB:
	LDI  R19,LOW(48)
_0xDC:
	RJMP _0xDD
_0xDA:
	LDI  R19,LOW(32)
_0xDD:
	RCALL SUBOPT_0x1B
	SUBI R20,LOW(1)
	RJMP _0xD7
_0xD9:
_0xD6:
	MOV  R18,R16
	SBRS R17,1
	RJMP _0xDE
_0xDF:
	CPI  R18,0
	BREQ _0xE1
	SBRS R17,3
	RJMP _0xE2
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	ADIW R30,1
	STD  Y+6,R30
	STD  Y+6+1,R31
	RCALL SUBOPT_0x1A
	RJMP _0x106
_0xE2:
	LDD  R26,Y+6
	LDD  R27,Y+6+1
	LD   R30,X+
	STD  Y+6,R26
	STD  Y+6+1,R27
_0x106:
	ST   -Y,R30
	RCALL SUBOPT_0x20
	CPI  R20,0
	BREQ _0xE4
	SUBI R20,LOW(1)
_0xE4:
	SUBI R18,LOW(1)
	RJMP _0xDF
_0xE1:
	RJMP _0xE5
_0xDE:
_0xE7:
	LDI  R19,LOW(48)
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	ADIW R30,2
	STD  Y+6,R30
	STD  Y+6+1,R31
	SBIW R30,2
	RCALL __GETW1PF
	STD  Y+8,R30
	STD  Y+8+1,R31
_0xE9:
	LDD  R30,Y+8
	LDD  R31,Y+8+1
	LDD  R26,Y+10
	LDD  R27,Y+10+1
	CP   R26,R30
	CPC  R27,R31
	BRLO _0xEB
	SUBI R19,-LOW(1)
	LDD  R26,Y+8
	LDD  R27,Y+8+1
	LDD  R30,Y+10
	LDD  R31,Y+10+1
	SUB  R30,R26
	SBC  R31,R27
	STD  Y+10,R30
	STD  Y+10+1,R31
	RJMP _0xE9
_0xEB:
	CPI  R19,58
	BRLO _0xEC
	SBRS R17,3
	RJMP _0xED
	SUBI R19,-LOW(7)
	RJMP _0xEE
_0xED:
	SUBI R19,-LOW(39)
_0xEE:
_0xEC:
	SBRC R17,4
	RJMP _0xF0
	CPI  R19,49
	BRSH _0xF2
	LDD  R26,Y+8
	LDD  R27,Y+8+1
	SBIW R26,1
	BRNE _0xF1
_0xF2:
	ORI  R17,LOW(16)
	RJMP _0xF4
_0xF1:
	CP   R20,R18
	BRLO _0xF6
	SBRS R17,0
	RJMP _0xF7
_0xF6:
	RJMP _0xF5
_0xF7:
	LDI  R19,LOW(32)
	SBRS R17,7
	RJMP _0xF8
	LDI  R19,LOW(48)
	ORI  R17,LOW(16)
_0xF4:
	SBRS R17,2
	RJMP _0xF9
	ANDI R17,LOW(251)
	ST   -Y,R21
	RCALL SUBOPT_0x20
	CPI  R20,0
	BREQ _0xFA
	SUBI R20,LOW(1)
_0xFA:
_0xF9:
_0xF8:
_0xF0:
	RCALL SUBOPT_0x1B
	CPI  R20,0
	BREQ _0xFB
	SUBI R20,LOW(1)
_0xFB:
_0xF5:
	SUBI R18,LOW(1)
	LDD  R26,Y+8
	LDD  R27,Y+8+1
	SBIW R26,2
	BRLO _0xE8
	RJMP _0xE7
_0xE8:
_0xE5:
	SBRS R17,0
	RJMP _0xFC
_0xFD:
	CPI  R20,0
	BREQ _0xFF
	SUBI R20,LOW(1)
	LDI  R30,LOW(32)
	RCALL SUBOPT_0x1D
	RJMP _0xFD
_0xFF:
_0xFC:
_0x100:
_0xBF:
	LDI  R16,LOW(0)
_0xAA:
	RJMP _0xA5
_0xA7:
	RCALL __LOADLOCR6
	ADIW R28,18
	RET
_printf:
	PUSH R15
	MOV  R15,R24
	SBIW R28,2
	RCALL __SAVELOCR2
	MOVW R26,R28
	RCALL __ADDW2R15
	MOVW R16,R26
	LDI  R30,0
	STD  Y+2,R30
	STD  Y+2+1,R30
	MOVW R26,R28
	ADIW R26,4
	RCALL __ADDW2R15
	RCALL __GETW1P
	ST   -Y,R31
	ST   -Y,R30
	ST   -Y,R17
	ST   -Y,R16
	MOVW R30,R28
	ADIW R30,6
	ST   -Y,R31
	ST   -Y,R30
	RCALL __print_G3
	RCALL __LOADLOCR2
	ADIW R28,4
	POP  R15
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x0:
	LD   R30,Y
	ST   -Y,R30
	RJMP _SinPout

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES
SUBOPT_0x1:
	ST   Y,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES
SUBOPT_0x2:
	ST   -Y,R30
	RJMP _SendCommandToLCD

;OPTIMIZER ADDED SUBROUTINE, CALLED 10 TIMES
SUBOPT_0x3:
	LDD  R30,Y+2
	ST   -Y,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES
SUBOPT_0x4:
	LDI  R30,LOW(0)
	ST   -Y,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x5:
	LDI  R30,LOW(1)
	ST   -Y,R30
	RCALL _SelectScreen
	LDD  R30,Y+4
	ST   -Y,R30
	RCALL _SetLine
	LDD  R30,Y+3
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES
SUBOPT_0x6:
	ST   -Y,R30
	RJMP _SetColumn

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x7:
	MOV  R30,R16
	LDD  R26,Y+3
	ADD  R26,R30
	CPI  R26,LOW(0x40)
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES
SUBOPT_0x8:
	LDI  R30,LOW(2)
	ST   -Y,R30
	RJMP _SelectScreen

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x9:
	LDD  R30,Y+4
	ST   -Y,R30
	RCALL _SetLine
	LDD  R30,Y+3
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0xA:
	SUBI R30,LOW(64)
	ADD  R30,R16
	RJMP SUBOPT_0x6

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0xB:
	LDI  R26,LOW(_HZcode*2)
	LDI  R27,HIGH(_HZcode*2)
	LDI  R31,0
	LSL  R30
	ROL  R31
	RCALL __LSLW4
	ADD  R30,R26
	ADC  R31,R27
	MOVW R0,R30
	MOV  R30,R16
	LDD  R26,Y+1
	ADD  R30,R26
	MOVW R26,R0
	LDI  R31,0
	ADD  R30,R26
	ADC  R31,R27
	LPM  R30,Z
	ST   -Y,R30
	RJMP _WriteByte

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES
SUBOPT_0xC:
	LDI  R30,LOW(1)
	ST   -Y,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0xD:
	ST   -Y,R17
	RCALL _SetLine
	ST   -Y,R18
	RJMP _SetColumn

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0xE:
	MOV  R30,R17
	LDI  R26,LOW(_CirCode*2)
	LDI  R27,HIGH(_CirCode*2)
	LDI  R31,0
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0xF:
	LDI  R26,LOW(48)
	LDI  R27,HIGH(48)
	RCALL __MULW12U
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x10:
	ADD  R26,R30
	ADC  R27,R31
	MOV  R30,R16
	LDI  R31,0
	ADD  R30,R26
	ADC  R31,R27
	LPM  R30,Z
	ST   -Y,R30
	RJMP _WriteByte

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x11:
	LDD  R30,Y+2
	SUBI R30,-LOW(8)
	ST   -Y,R30
	RJMP SUBOPT_0x3

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x12:
	ST   -Y,R30
	RCALL _Show8x8
	LDD  R30,Y+2
	SUBI R30,-LOW(1)
	ST   -Y,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES
SUBOPT_0x13:
	LDI  R30,LOW(6)
	ST   -Y,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x14:
	LDI  R31,0
	SUBI R30,LOW(-_tx_buffer)
	SBCI R31,HIGH(-_tx_buffer)
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x15:
	LDI  R30,LOW(240)
	OUT  0x32,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x16:
	RCALL __MULW12U
	RCALL __LSRW2
	MOV  R30,R31
	LDI  R31,0
	MOV  R12,R30
	SET
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 7 TIMES
SUBOPT_0x17:
	ST   -Y,R31
	ST   -Y,R30
	RJMP _abs

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x18:
	LDI  R30,LOW(0)
	OUT  0x7,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x19:
	LD   R26,Y
	LDD  R27,Y+1
	RCALL __GETW1P
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x1A:
	SBIW R30,1
	LPM  R30,Z
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES
SUBOPT_0x1B:
	ST   -Y,R19
	LDD  R30,Y+13
	LDD  R31,Y+13+1
	ST   -Y,R31
	ST   -Y,R30
	RJMP __put_G3

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES
SUBOPT_0x1C:
	LDD  R26,Y+14
	LDD  R27,Y+14+1
	SBIW R26,4
	STD  Y+14,R26
	STD  Y+14+1,R27
	ADIW R26,4
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x1D:
	ST   -Y,R30
	LDD  R30,Y+13
	LDD  R31,Y+13+1
	ST   -Y,R31
	ST   -Y,R30
	RJMP __put_G3

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x1E:
	RCALL __GETW1P
	STD  Y+6,R30
	STD  Y+6+1,R31
	ST   -Y,R31
	ST   -Y,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x1F:
	RCALL __GETW1P
	STD  Y+10,R30
	STD  Y+10+1,R31
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x20:
	LDD  R30,Y+13
	LDD  R31,Y+13+1
	ST   -Y,R31
	ST   -Y,R30
	RJMP __put_G3

_strlen:
	ld   r26,y+
	ld   r27,y+
	clr  r30
	clr  r31
__strlen0:
	ld   r22,x+
	tst  r22
	breq __strlen1
	adiw r30,1
	rjmp __strlen0
__strlen1:
	ret

_strlenf:
	clr  r26
	clr  r27
	ld   r30,y+
	ld   r31,y+
__strlenf0:
	lpm  r0,z+
	tst  r0
	breq __strlenf1
	adiw r26,1
	rjmp __strlenf0
__strlenf1:
	movw r30,r26
	ret

__ADDW2R15:
	CLR  R0
	ADD  R26,R15
	ADC  R27,R0
	RET

__ANEGW1:
	COM  R30
	COM  R31
	ADIW R30,1
	RET

__LSLW4:
	LSL  R30
	ROL  R31
__LSLW3:
	LSL  R30
	ROL  R31
__LSLW2:
	LSL  R30
	ROL  R31
	LSL  R30
	ROL  R31
	RET

__LSRW2:
	LSR  R31
	ROR  R30
	LSR  R31
	ROR  R30
	RET

__MULW12U:
	MUL  R31,R26
	MOV  R31,R0
	MUL  R30,R27
	ADD  R31,R0
	MUL  R30,R26
	MOV  R30,R0
	ADD  R31,R1
	RET

__GETW1P:
	LD   R30,X+
	LD   R31,X
	SBIW R26,1
	RET

__GETW1PF:
	LPM  R0,Z+
	LPM  R31,Z
	MOV  R30,R0
	RET

__SAVELOCR6:
	ST   -Y,R21
__SAVELOCR5:
	ST   -Y,R20
__SAVELOCR4:
	ST   -Y,R19
__SAVELOCR3:
	ST   -Y,R18
__SAVELOCR2:
	ST   -Y,R17
	ST   -Y,R16
	RET

__LOADLOCR6:
	LDD  R21,Y+5
__LOADLOCR5:
	LDD  R20,Y+4
__LOADLOCR4:
	LDD  R19,Y+3
__LOADLOCR3:
	LDD  R18,Y+2
__LOADLOCR2:
	LDD  R17,Y+1
	LD   R16,Y
	RET

__LOADLOCR2P:
	LD   R16,Y+
	LD   R17,Y+
	RET

;END OF CODE MARKER
__END_OF_CODE:
