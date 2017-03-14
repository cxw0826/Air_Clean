/*----------Project Info------------------------------------------
** Descriptions: 	
** Created By:		Chain
** Created Data:	20170120
** Version:			V1.0
*****************************************************************/

#ifndef		_SYS_INCLUDE_H_
#define		_SYS_INCLUDE_H_

#include 	"STC15F2K60S2.h"
#include	"Buzzer.h"
#include	"Initial.h"
#include	"Key_Pad.h"
#include	"IR_Func.h"
#include	"Uart.h"
#include	"Port_Define.h"

//红外遥控器按钮定义
#define	IR_Pwr_On		0x18
#define	IR_Purify			0x0D
#define	IR_Timer			0x04
#define	IR_Fan_Speed		0x55
#define	IR_Reserve1		0x46
#define	IR_Reserve2		0x16
#define	IR_Reserve3		0x47
#define	IR_Reserve4		0x15
#define	IR_Anion			0x40
#define	IR_Motor_Up		0x19
#define	IR_Motor_Down	0x17
#define	IR_Light			0x1E

//定义电机操作参数
#define	Motor_Cmd_OFF	0
#define	Motor_Cmd_Up	1
#define	Motor_Cmd_Down	2

//extern struct state_struct Sys_State;	//声明外部结构体变量







#endif

