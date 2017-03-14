/*----------Project Info------------------------------------------
** Descriptions: 	
** Created By:		Chain
** Created Data:	20170120
** Version:			V1.0
*****************************************************************/

#ifndef		_INITIAL_H_
#define		_INITIAL_H_

#include 	"STC15F2K60S2.h"

#define			Time_1ms		(65536-Sys_Clock/1000)
#define			Time_125us		(65536 - 125)



sbit 		Key_Flag	=	P3 ^ 6;	//°´¼üÖÐ¶Ï½Å£¬INT2

void Initial_Sys(void);
void Initial_Port(void);
void Initial_Timers(void);
void Initial_EX_INT(void);


#endif

