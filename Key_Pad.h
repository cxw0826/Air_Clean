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

#define		Smart_Time_High		1000*60*5	
#define		Smart_Time_Low		1000*60*5	

#define		Boot_Idle_Time	1000*60*1

//����state_struct�ṹ��
struct state_struct
{
	uchar Pwr_State;		//��Դ״̬
	uchar Fan_State;		//���״̬
	uchar Timer_State;		//��ʱ��״̬
	uchar Smart_State;		//����״̬
	uchar Move_State;		//�ƶ����״̬
} ;









#endif

