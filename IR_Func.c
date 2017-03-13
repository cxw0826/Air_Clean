/*----------Project Info------------------------------------------
** Descriptions: 	
** Created By:		Chain
** Created Data:	20170120
** Version:			V1.0
*****************************************************************/
#include		"IR_Func.h"

//定时器1，10MS中断一次
ulint	Sleep_Time_Counter = 0;
void Timer1() interrupt 3 using 1
{
	if(Sys_State.Timer_State)
		{
			if(Sleep_Time_Counter > Time_10Sec )
				{
					Sleep_Time_Counter = 0;
					TimeLED		=	LED_OFF;
					Sys_State.Pwr_State = OFF;
				}
			else
				Sleep_Time_Counter ++;
		}
	else
		{
			Sleep_Time_Counter = 0;
		}
	
		/*if(Sleep_Time_Counter <= 100 )
			{
				Sleep_Time_Counter++;
				P42	=	0;
			}
		else if(Sleep_Time_Counter > 100 && Sleep_Time_Counter <= 200 )
			{
				Sleep_Time_Counter++;
				P42	=	1;
			}
		else if(Sleep_Time_Counter > 200)
				Sleep_Time_Counter = 0;*/
}

