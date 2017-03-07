/*----------Project Info------------------------------------------
** Descriptions: 	
** Created By:		Chain
** Created Data:	20170120
** Version:			V1.0
*****************************************************************/

#ifndef		_BUZZER_H_
#define		_BUZZER_H_


#include 	"STC15F2K60S2.h"


sbit Buzzer			=	P4^6;

void Beep();
void Delay_Nms(unsigned char Nms);



#endif

