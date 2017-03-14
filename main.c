/*----------Project Info------------------------------------------
** Descriptions: 	
** Created By:		Chain
** Created Data:	20170120
** Version:			V1.0
*****************************************************************/

#include	"Sys_Include.h"

extern	bit	B_IR_Press;
extern	uchar	IR_code;

//上升下降电机控制函数
void UpDown_Motor_Ctrl(unsigned char state)
{
	if(state == Motor_Cmd_Up)
		{
			MotorUpPort 		= PortOn;
			MotorDownPort 	= PortOff;
		}
	else	if(state == Motor_Cmd_Down)
		{
			MotorUpPort 		= PortOn;
			MotorDownPort 	= PortOff;
		}
	else	if(state == Motor_Cmd_OFF)
		{
			MotorUpPort 		= PortOff;
			MotorDownPort 	= PortOff;
		}
	else
		{
			MotorUpPort 		= PortOff;
			MotorDownPort 	= PortOff;
		}
		
}


//红外遥控码判断程序
void	IR_Ctrl(void)
{
	if(B_IR_Press)
		{
			switch(IR_code)
				{
					case	IR_Pwr_On:
						Beep();	
						DebugMSG("收到的红外按钮是: 开机按钮 \r\n");
						if(Sys_State.Pwr_State)
							{
								Sys_State.Pwr_State =  OFF;
								Sys_State.Fan_State =  OFF;
								Sys_State.Smart_State = OFF;
								Sys_State.Timer_State = OFF;
								Sys_State.Move_State = ON;
								WheelLedPort 		|= 0x0F;
								PurificationPort_Ctrl(OFF);
								Light_Port_Ctrl(OFF);
								FanSpeed_Ctrl(OFF);
								Init_Led(OFF);
							}
						else
							{
								Sys_State.Pwr_State =  ON; 
								Sys_State.Fan_State =  MID;
								Sys_State.Move_State = OFF;
								Sys_State.Timer_State = OFF;
								WheelLedPort 		&= 0xF0; 
								PurificationPort_Ctrl(ON);
								Light_Port_Ctrl(ON);
								FanSpeed_Ctrl(MID);
								Init_Led(ON);
							}
						break;
					case	IR_Purify:
						if(Sys_State.Pwr_State)
							{
								Beep();	
								DebugMSG("收到的红外按钮是: 净化按钮 \r\n");
								PurificationPort = ~PurificationPort;
								PurificationLED  = PurificationPort;
							}
						break;
					case	IR_Timer:
						if(Sys_State.Pwr_State)
							{
								Beep();	
								DebugMSG("收到的红外按钮是:定时关机按钮 \r\n");
								if(Sys_State.Timer_State)
									Sys_State.Timer_State = OFF;
								else
									Sys_State.Timer_State = ON;
								TimeLED = ~TimeLED;
							}
						break;
					case	IR_Fan_Speed:
						if(Sys_State.Pwr_State)
							{
								Beep();	
								DebugMSG("收到的红外按钮是:风机调速按钮 \r\n");
								Sys_State.Fan_State++;
								if(Sys_State.Fan_State > HIGH)
									Sys_State.Fan_State = OFF;
							}
						break;
					case	IR_Anion:
						if(Sys_State.Pwr_State)
							{
								Beep();	
								DebugMSG("收到的红外按钮是:负离子按钮 \r\n");
								AnionPort	=	~AnionPort;
							}
						break;
					case	IR_Motor_Up:
						if(Sys_State.Pwr_State)
							{
								Beep();	
								DebugMSG("收到的红外按钮是:Motor_Up按钮 \r\n");
								UpDown_Motor_Ctrl(Motor_Cmd_Up);
							}
						break;
					case	IR_Motor_Down:
						if(Sys_State.Pwr_State)
							{
								Beep();	
								DebugMSG("收到的红外按钮是:电机下降按钮 \r\n");
								UpDown_Motor_Ctrl(Motor_Cmd_Down);
							}
						break;
					case	IR_Light:
						if(Sys_State.Pwr_State)
							{
								Beep();	
								DebugMSG("收到的红外按钮是:照明按钮 \r\n");
								LightPort = ~LightPort;
								LightLED  = LightPort;
							}
						break;
					default	:
								Beep();	
								DebugMSG("收到的红外按钮是:错误按钮 \r\n");
						break;
					}
			}
}






void main()
{
	Initial_Sys();
	Init_Uart1();
	DebugMSG("系统初始化完成\r\n");
	while(1)
	{
		IR_Ctrl();
		B_IR_Press = 0;
	}
}

