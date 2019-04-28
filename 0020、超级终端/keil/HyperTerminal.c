#include "HyperTerminal.h"

/*****************************************************************************/
char idata SerialBuffer[MAX_SERIAL_BUFFER_SIZE];
char idata PromptBuffer[MAX_PROMPT_BUFFER_SIZE];
char idata CursorPosion;
char idata ExecCommandFlag;

COMMAND CommandList[MAX_COMMAND_NUM] = {
	{"help",Help," help -- Command help"},
	{"prompt",Prompt," prompt <string> -- Change a prompt"},
	{"clear",Clear," clear -- Clear screen"},
	{"reboot",Reboot," reboot -- Reboot the MCU"}
};

/*****************************************************************************/
void Help(char argc, const char **argv)
{
	char i;
	argv = argv;
	switch(argc)
	{
	case 1:
		for(i = 0; i < MAX_COMMAND_NUM; i++)
		{
			SerialSendStr(CommandList[i].HelpString);
			SerialSendStr("\r\n");
		}
		SerialSendStr("\r\n");
		break;
	default:
		SerialSendStr(" Invalid 'help' command: too many arguments\r\n");
		SerialSendStr(" Usage:\r\n");
		SerialSendStr("     help\r\n");
		break;
	}
}

void Prompt(char argc, const char **argv)
{
	switch(argc)
	{
	case 2:
		if(strlen(argv[1]) >= MAX_PROMPT_BUFFER_SIZE)
		{
			SerialSendStr(" Warnning:Your argument is too long!\r\n\r\n");
			break;
		}
		memcpy(PromptBuffer,argv[1],MAX_PROMPT_BUFFER_SIZE);
		SerialSendStr(" Prompt is chagned to \"");
		sprintf(&SerialBuffer[0],"%s\"\r\n\r\n",&PromptBuffer[0]);
		SerialSendStr(&SerialBuffer[0]);
		break;
	default:
		SerialSendStr(" Invalid 'prompt' command: too few or many arguments\r\n");
		SerialSendStr(" Usage:\r\n");
		SerialSendStr("     prompt <string>\r\n");
		break;
	}
}

void Clear(char argc, const char **argv)
{
	argv = argv;
	switch(argc)
	{
	case 1:
		SerialSendStr(CLEARSCREEN);	
		break;
	default:
		SerialSendStr(" Invalid 'clear' command: too many arguments\r\n");
		SerialSendStr(" Usage:\r\n");
		SerialSendStr("     clear\r\n");
		break;
	}
}

void Reboot(char argc, const char **argv)
{
	argv = argv;
	switch(argc)
	{
	case 1:
		(*(void(*)())0)(); 
		break;
	default:
		SerialSendStr(" Invalid 'reboot' command: too many arguments\r\n");
		SerialSendStr(" Usage:\r\n");
		SerialSendStr("     reboot\r\n");
		break;
	}
}
/*****************************************************************************/
void InitHyperTerminal(void)
{
	TMOD |= 0x20; 		/* timer1, mode 2, 8 bit reload */
	SCON  = 0x50; 		/* serial mode 1, 8 bit uart, enable receive  */
	PCON  = 0x80; 		/* SMOD = 1, double baud */ 
	TH1   = 0xFF;		/* baud = 57600, fosc = 11.0592MHZ */
	TL1   = 0xFF;		
	RI    = 0; 			/* clear receive flag */
	TI    = 0;			/* clear send flag */
	TR1   = 1; 			/* start timer1 */
	ES    = 1;			/* enable serial interrupt */
	EA    = 1;			/* enable all interrupt */

	CursorPosion = 0;
	ExecCommandFlag = 0;
	memset(&SerialBuffer[0],'\0',MAX_SERIAL_BUFFER_SIZE);
	memcpy(&PromptBuffer[0],"-->>",MAX_PROMPT_BUFFER_SIZE);
	SerialSendStr(F_LIGHTGREEN);
	SerialSendStr(B_BLACK);
	SerialSendStr(CLEARSCREEN);
	SerialSendStr("-----------------------------\r\n");
	SerialSendStr("  The 8051 Hyper Terminal,by JJJ\r\n");
	SerialSendStr("  http://www.proteus.com.cn \r\n");
	SerialSendStr("-----------------------------\r\n");
	SerialSendStr("\r\n");
	SerialSendStr(&PromptBuffer[0]);
}

void SerialSendByte(char dat)
{
	SBUF = dat;
	while(TI == 0);
	TI = 0;
}

void SerialSendStr(char *str)
{
	while(*str != '\0')
	{
		SerialSendByte(*str);
		str++;
	}
}
	
void SerialInterrupt(void) interrupt 4 using 3
{
	char SbufTemp;
	if(RI)
	{
		RI = 0;
		SbufTemp = SBUF;
		switch(SbufTemp)
		{
		case 0x08:
		case 0x06:
		case 0x07:
		case 0x7E:
		case 0x7F:
			if(CursorPosion > 0)
			{
				CursorPosion--;
				SerialSendByte(0x08);
				SerialSendByte(' ');
				SerialSendByte(0x08);
			}
			SerialBuffer[CursorPosion] = '\0';
			break;
		case '\r':
		case '\n':
		case '\0':
			SerialSendByte('\r');
			SerialSendByte('\n');
			ExecCommandFlag = 1;
			break;
	   	case '\t':
			break;
		default:
			if(CursorPosion < MAX_SERIAL_BUFFER_SIZE)
			{
				SerialBuffer[CursorPosion] = SbufTemp;
				SerialSendByte(SbufTemp);
				CursorPosion++;
			}
			else
			{
				CursorPosion = 0;
				memset(&SerialBuffer[0],'\0',MAX_SERIAL_BUFFER_SIZE);
				SerialSendStr("\r\n Warnning:Your command string is too long!\r\n\r\n");
				SerialSendStr(&PromptBuffer[0]);
			}
			break;
		}
	}
}

void ParseArgs(char *argstr,char *argc_p,char **argv, char **resid)
{
	char argc = 0;
	char c;
	PARSESTATE stackedState,lastState = PS_WHITESPACE;

	while ((c = *argstr) != 0)
	{
		PARSESTATE newState;

		if (c == ';' && lastState != PS_STRING && lastState != PS_ESCAPE)
			break;

		if (lastState == PS_ESCAPE)
		{
			newState = stackedState;
		}
		else if (lastState == PS_STRING)
		{
			if (c == '"')
		 	{
				newState = PS_WHITESPACE;
				*argstr = 0;
			}
		 	else 
			{
				newState = PS_STRING;
			}
		}
	 	else if ((c == ' ') || (c == '\t'))
		{
			*argstr = 0;
			newState = PS_WHITESPACE;
		}
	 	else if (c == '"') 
		{
			newState = PS_STRING;
			*argstr++ = 0;
			argv[argc++] = argstr;
		}
	 	else if (c == '\\') 
		{
			stackedState = lastState;
			newState = PS_ESCAPE;
		}
	 	else 
		{
			if (lastState == PS_WHITESPACE) 
			{
				argv[argc++] = argstr;
			}
			newState = PS_TOKEN;
		}

		lastState = newState;
		argstr++;
	}

	argv[argc] = NULL;
	if (argc_p != NULL)
		*argc_p = argc;

	if (*argstr == ';') 
	{
		*argstr++ = '\0';
	}
	*resid = argstr;
}

void ExecCommand(char *buf)
{
	char argc,*argv[8],*resid,i;
	COMMAND *Command = 0;

	while(*buf)
 	{
		memset(argv,0,sizeof(argv));
		ParseArgs(buf, &argc, argv, &resid);
		if(argc > 0)
		{
			for(i = 0; i < MAX_COMMAND_NUM; i++)
			{
				Command = &CommandList[i];	
				if(strncmp(Command->CommandName,argv[0],strlen(argv[0])) == 0)
					break;
				else
					Command = 0;
			}
			if(Command == 0)
			{
				SerialSendStr(" Could not found \"");
				SerialSendStr(argv[0]);
				SerialSendStr("\" command\r\n");
				SerialSendStr(" If you want to konw available commands, type 'help'\r\n\r\n"); 
		   	}
			else
			{
				Command->CommandFunc(argc,argv);
			}
		}
		buf = resid;
	}
}

void RunHyperTerminal(void)
{
	if(ExecCommandFlag)
	{
		ExecCommand(&SerialBuffer[0]);
		SerialSendStr(&PromptBuffer[0]);
		memset(&SerialBuffer[0],'\0',MAX_SERIAL_BUFFER_SIZE);
		CursorPosion = 0;
		ExecCommandFlag = 0;
	}
}
