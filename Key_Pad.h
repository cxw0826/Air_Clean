/*----------Project Info------------------------------------------
** Descriptions: 	
** Created By:		Chain
** Created Data:	20170120
** Version:			V1.0
*****************************************************************/

#ifndef		_KEY_PAD_H_
#define		_KEY_PAD_H_


#include 	"STC15F2K60S2.h"
#include	"Buzzer.h"
#include	"Port_Define.h"


#define		OFF				 	0
#define		ON				 	1

#define		LED_ON 			 	0
#define		LED_OFF			 	1

#define		MotorUp 		 		0
#define		MotorDown 		 	1

#define		PortOn			 	0
#define		PortOff			 	1

#define		LOW				 	1
#define		MID				 	2
#define		HIGH			 	3

#define		Smart_Time_High		1000*10	
#define		Smart_Time_Low		1000*5	

#define		Boot_Idle_Time		1000*5
#define		Time_10Sec			1000*5	//定义定时时长

//定义state_struct结构体
struct state_struct
{
	uchar Pwr_State;		//电源状态
	uchar Fan_State;		//电机状态
	uchar Timer_State;		//定时器状态
	uchar Smart_State;		//智能状态
	uchar Move_State;		//移动检测状态
} ;




void	Init_Led(uchar	state);
void	Light_Port_Ctrl(uchar state);
void	PurificationPort_Ctrl(uchar state);
void	FanSpeed_Ctrl(uchar state);
void	Smart_Function(void);
void	Move_Detect_Function(void);
void	Fan_Led_Speed_Fun(void);
void	Sys_State_Ctrl(void);








#endif

