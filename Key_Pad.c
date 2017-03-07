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


void	Key_Int()	interrupt	10
{
	switch(P1 & 0xE0)
	{
    case PowerKey:
		Beep();	
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



