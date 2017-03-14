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

/*************        用户系统配置        **************/
#define 	D_TIMER0			125                        //选择定时器采样时间, us, 红外接收要求在60us~250us之间
sbit        	P_IR_RX = P4 ^ 5;                //定义红外接收输入端口

#if ((D_TIMER0 <= 250) && (D_TIMER0 >= 60))
        #define        D_IR_sample                        D_TIMER0                //定义采样时间，在60us~250us之间
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


extern struct state_struct Sys_State;	//声明外部结构体变量


#endif

