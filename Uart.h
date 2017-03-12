/*----------Project Info------------------------------------------
** Descriptions: 	
** Created By:		Chain
** Created Data:	20170120
** Version:			V1.0
*****************************************************************/

#ifndef		_UART_H_
#define		_UART_H_

#include 	"STC15F2K60S2.h"
#include	"intrins.h"

#define		Sys_Clk				12000000L
#define		BaudRate			115200
#define		NoneParity			0
#define		OddParity			1
#define		EvenParity			2
#define		MarkParity			3
#define		SpaceParity			4

#define		ParityBit			NoneParity



void Init_Uart1(void);
void DebugMSG(char *Dat);





#endif

