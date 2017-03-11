/*----------Project Info------------------------------------------
** Descriptions: 	
** Created By:		Chain
** Created Data:	20170120
** Version:			V1.0
*****************************************************************/

#include		"Key_Pad.h"

#define 		PowerKey			0x00
#define			LightKey 			0x60
#define    		AnionKey			0x20
#define 		TimeKey		   		0xC0
#define			PurificationKey		0x40
#define			FanKey	   			0xA0
#define			CueKey			   	0x80


struct 
{
	unsigned char Pwr_State;
	unsigned char Fan_State;
} Sys_State;
/*
void State_Init(void)
{
Sys_State.Pwr_State	= OFF;
Sys_State.Fan_State = OFF;
}
*/
void	Key_Int()	interrupt	10
{
	switch(P1 & 0xE0)
	{
    case PowerKey:
		Beep();	
		if(Sys_State.Pwr_State)
			{
				Sys_State.Pwr_State = OFF;
				Sys_State.Fan_State = OFF;
				WheelLedPort |= 0x0F;
				PowerLED = 1;
			}
		else
			{
				Sys_State.Pwr_State = ON; 
				Sys_State.Fan_State = MID; 
				PowerLED = 0;
			}
		break;
    case LightKey:
		Beep();	
		break;
    case AnionKey:
		Beep();	
		break;
    case TimeKey:
		Beep();	
		break;
    case PurificationKey:
		Beep();	
		break;
    case FanKey:
		Beep();	
		break;
    case CueKey:
		Beep();	
		break;
	}
}

unsigned char Delay1msCount = 0;
unsigned char i				= 0;
unsigned char n				= 0x01;

void Timer0() interrupt 1 using 1
{
	if(Sys_State.Pwr_State)
		{
		if(Sys_State.Fan_State == OFF)
			WheelLedPort |= 0x0F;
		else if(Sys_State.Fan_State == LOW)
			{
				Delay1msCount++;
				if(Delay1msCount>200)
				{
 					Delay1msCount = 0;
					WheelLedPort  = n;
					n=(n<<1);
					i++;
					if(i>=4)
						{
							i	=	0;
							n	= 	0x01;
						}
				
				}
			}
		else if(Sys_State.Fan_State == MID)
			{
				Delay1msCount++;
				if(Delay1msCount>100)
				{
 					Delay1msCount = 0;
					WheelLedPort  = n;
					n=(n<<1);
					i++;
					if(i>=4)
						{
							i	=	0;
							n	= 	0x01;
						}
				
				}
			}
		else if(Sys_State.Fan_State == HIGH)
			{
				Delay1msCount++;
				if(Delay1msCount>50)
				{
 					Delay1msCount = 0;
					WheelLedPort  = n;
					n=(n<<1);
					i++;
					if(i>=4)
						{
							i	=	0;
							n	= 	0x01;
						}
				
				}
			}
		}
}
	




