/*----------Project Info------------------------------------------
** Descriptions: 	
** Created By:		Chain
** Created Data:	20170120
** Version:			V1.0
*****************************************************************/
#ifndef		_IR_FUNC_H_
#define		_IR_FUNC_H_
	
#include 		"STC15F2K60S2.h"
#include		"Key_Pad.h"

/*************        �û�ϵͳ����        **************/
#define 	D_TIMER0			125                        //ѡ��ʱ������ʱ��, us, �������Ҫ����60us~250us֮��
sbit        	P_IR_RX = P4 ^ 5;                //��������������˿�

#if ((D_TIMER0 <= 250) && (D_TIMER0 >= 60))
        #define        D_IR_sample                        D_TIMER0                //�������ʱ�䣬��60us~250us֮��
#endif

#define D_IR_SYNC_MAX			(15000/D_IR_sample)        //SYNC max time
#define D_IR_SYNC_MIN			(9700 /D_IR_sample)        //SYNC min time
#define D_IR_SYNC_DIVIDE		(12375/D_IR_sample)        //decide data 0 or 1
#define D_IR_DATA_MAX		(3000 /D_IR_sample)        //data max time
#define D_IR_DATA_MIN			(600  /D_IR_sample)        //data min time
#define D_IR_DATA_DIVIDE		(1687 /D_IR_sample)        //decide data 0 or 1
#define D_IR_BIT_NUMBER		32                                        //bit number




void	Timer_Shutdown(void);
void IR_RX_VS1838B(void);


extern struct state_struct Sys_State;	//�����ⲿ�ṹ�����


#endif

