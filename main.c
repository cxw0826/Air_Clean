/*----------Project Info------------------------------------------
** Descriptions: 	
** Created By:		Chain
** Created Data:	20170120
** Version:			V1.0
*****************************************************************/

#include	"Sys_Include.h"

extern	bit	B_IR_Press;
extern	uchar	IR_code;

//�����½�������ƺ���
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


//����ң�����жϳ���
void	IR_Ctrl(void)
{
	if(B_IR_Press)
		{
			switch(IR_code)
				{
					case	IR_Pwr_On:
						Beep();	
						DebugMSG("�յ��ĺ��ⰴť��: ������ť \r\n");
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
								DebugMSG("�յ��ĺ��ⰴť��: ������ť \r\n");
								PurificationPort = ~PurificationPort;
								PurificationLED  = PurificationPort;
							}
						break;
					case	IR_Timer:
						if(Sys_State.Pwr_State)
							{
								Beep();	
								DebugMSG("�յ��ĺ��ⰴť��:��ʱ�ػ���ť \r\n");
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
								DebugMSG("�յ��ĺ��ⰴť��:������ٰ�ť \r\n");
								Sys_State.Fan_State++;
								if(Sys_State.Fan_State > HIGH)
									Sys_State.Fan_State = OFF;
							}
						break;
					case	IR_Anion:
						if(Sys_State.Pwr_State)
							{
								Beep();	
								DebugMSG("�յ��ĺ��ⰴť��:�����Ӱ�ť \r\n");
								AnionPort	=	~AnionPort;
							}
						break;
					case	IR_Motor_Up:
						if(Sys_State.Pwr_State)
							{
								Beep();	
								DebugMSG("�յ��ĺ��ⰴť��:Motor_Up��ť \r\n");
								UpDown_Motor_Ctrl(Motor_Cmd_Up);
							}
						break;
					case	IR_Motor_Down:
						if(Sys_State.Pwr_State)
							{
								Beep();	
								DebugMSG("�յ��ĺ��ⰴť��:����½���ť \r\n");
								UpDown_Motor_Ctrl(Motor_Cmd_Down);
							}
						break;
					case	IR_Light:
						if(Sys_State.Pwr_State)
							{
								Beep();	
								DebugMSG("�յ��ĺ��ⰴť��:������ť \r\n");
								LightPort = ~LightPort;
								LightLED  = LightPort;
							}
						break;
					default	:
								Beep();	
								DebugMSG("�յ��ĺ��ⰴť��:����ť \r\n");
						break;
					}
			}
}






void main()
{
	Initial_Sys();
	Init_Uart1();
	DebugMSG("ϵͳ��ʼ�����\r\n");
	while(1)
	{
		IR_Ctrl();
		B_IR_Press = 0;
	}
}

