/*----------Project Info------------------------------------------
** Descriptions: 	
** Created By:		Chain
** Created Data:	20170120
** Version:			V1.0
*****************************************************************/

#include		"Key_Pad.h"

#define		PowerKey			0x00
#define		LightKey			0x60
#define		SmartKey			0x20
#define		TimeKey		   		0xC0
#define		PurificationKey		0x40
#define		ReserveKey	  		0xA0
#define		MoveKey			   	0x80

//声明并初始化系统状态结构体
struct state_struct Sys_State = {OFF};

//初始化全部LED函数
void Init_Led(uchar	state)
{
	if(state)
		{
			LightLED 			= LED_ON;
			PurificationLED 	= LED_ON;
			//TimeLED 			= LED_ON;
			PowerLED 			= LED_ON;
			RightLED 			= LED_ON;
			UpLED 				= LED_ON;
			LeftLED 			= LED_ON;
			DownLED 			= LED_ON;
			//SmartLED			= LED_ON;
			MoveLED				= LED_ON;
		}
	else
		{
			LightLED 			= LED_OFF;
			PurificationLED 	= LED_OFF;
			//TimeLED 			= LED_OFF;
			PowerLED 			= LED_OFF;
			RightLED 			= LED_OFF;
			UpLED 				= LED_OFF;
			LeftLED 			= LED_OFF;
			DownLED 			= LED_OFF;
			//SmartLED			= LED_OFF;
			MoveLED				= LED_OFF;
		}
}




//照明端口控制函数
void Light_Port_Ctrl(uchar state)
{
	if(state)
		LightPort 		= PortOn;
	else
		LightPort 		= PortOff;
}

//上升下降电机控制函数
/*void UpDown_Motor_Ctrl(unsigned char state)
{
	if(state)
		{
			MotorUpPort 		= PortOn;
			MotorDownPort 	= PortOff;
		}
	else
		{
			MotorUpPort 		= PortOn;
			MotorDownPort 	= PortOff;
		}
}
*/

//净化端口控制函数
void PurificationPort_Ctrl(uchar state)
{
	if(state)
		PurificationPort 		= PortOn;
	else
		PurificationPort 		= PortOff;
}

//风扇速度控制函数
void FanSpeed_Ctrl(uchar state)
{
	if(state == LOW)
		{
			FanPort_Low  = PortOn;
			FanPort_Mid  = PortOff;
			FanPort_High = PortOff;
		}
	else if(state == MID)
		{
			FanPort_Low  = PortOff;
			FanPort_Mid  = PortOn;
			FanPort_High = PortOff;
		}
	else if(state == HIGH)
		{
			FanPort_Low  = PortOff;
			FanPort_Mid  = PortOff;
			FanPort_High = PortOn;
		}
	else if(state == OFF)
		{
			FanPort_Low  = PortOff;
			FanPort_Mid  = PortOff;
			FanPort_High = PortOff;
		}
}

//按钮中断函数
void	Key_Int()	interrupt	10
{
	switch(P1 & 0xE0)
	{
    case PowerKey:
		Beep();	
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
   /* case LightKey:
		if(Sys_State.Pwr_State)
			{
				Beep();	
				Sys_State.Fan_State++;
				if(Sys_State.Fan_State > HIGH)
					Sys_State.Fan_State = OFF;
			}
		break;*/
    case LightKey:
		if(Sys_State.Pwr_State)
			{
				Beep();	
				LightPort = ~LightPort;
				LightLED  = LightPort;
			}
		break;
    case SmartKey:
		if(Sys_State.Pwr_State)
			{
				Beep();	
				if(Sys_State.Smart_State)
					Sys_State.Smart_State = OFF;
				else
					Sys_State.Smart_State = ON;
				SmartLED  = ~SmartLED;
			}
		break;
    case TimeKey:
		if(Sys_State.Pwr_State)
			{
				Beep();	
				if(Sys_State.Timer_State)
					Sys_State.Timer_State = OFF;
				else
					Sys_State.Timer_State = ON;
				TimeLED = ~TimeLED;
			}
		break;
    case PurificationKey:
		if(Sys_State.Pwr_State)
			{
				Beep();	
				PurificationPort = ~PurificationPort;
				PurificationLED  = PurificationPort;
			}
		break;
    case MoveKey:
		/*if(Sys_State.Pwr_State == OFF)
			{
				Beep();	
				if(Sys_State.Move_State)
					Sys_State.Move_State= OFF;
				else
					Sys_State.Move_State = ON;
				MoveLED = ~MoveLED;
			}*/
		break;
    case ReserveKey:
		break;
	default:
		break;
	}
}

//智能功能函数
ulint		Smart_Time_Counter	=	0;
void	Smart_Function(void)
{
	if(Sys_State.Pwr_State)	//开机状态下
		{
			if(Sys_State.Smart_State)		//打开智能功能
				{
					if(Smart_Time_Counter	>=	Smart_Time_High)	//超过一定时间
						{
							Smart_Time_Counter	=	0;
							Sys_State.Pwr_State		=	OFF;		//关机
						}
					else	if(Smart_Time_Counter	>=	Smart_Time_Low && Smart_Time_Counter	<=	Smart_Time_High)	
						{
							if(Move_Detect_Port)	//检测到移动
								{
									Sys_State.Fan_State		=	HIGH;	//低速转高速
									Smart_Time_Counter	=	0;		//重新计数
								}
							else
								{
									Smart_Time_Counter++;
									Sys_State.Fan_State		=	LOW;	//一定时间没有检测到人进入低速状态
								}
						}
					else	
						Smart_Time_Counter++;
				}
			else
				Smart_Time_Counter	=	0;
		}
}

//移动侦测函数
ulint		Move_Time_Counter	=	0;
void	Move_Detect_Function(void)
{	
	if(Sys_State.Pwr_State == OFF)		//关机状态
		{
			if(Sys_State.Move_State)		//打开移动检测功能
				{
					if(Move_Time_Counter >= Boot_Idle_Time)	//延时到稳定时间
						{
							if(Move_Detect_Port)	//触发开机
								{
									Move_Time_Counter = 0;
									Sys_State.Pwr_State = ON;
									Sys_State.Fan_State =  HIGH;	//触发开机是高速状态
									WheelLedPort 		&= 0xF0; 
									PurificationPort_Ctrl(ON);
									FanSpeed_Ctrl(HIGH);	//触发开机是高速状态
									Light_Port_Ctrl(ON);
									Init_Led(ON);
								}
						}
					else
						Move_Time_Counter++;
				}
		}
}

//电机转速指示灯控制函数
uchar	Delay1msCount 	= 0;
uchar	Cycle_Count		= 0;
uchar	Port_Val			= 0x01;
void	Fan_Led_Speed_Fun(void)
{
	if(Sys_State.Pwr_State)
		{
		if(Sys_State.Fan_State == OFF)
			{
				FanSpeed_Ctrl(OFF);
				WheelLedPort |= 0x0F;
			}
		else if(Sys_State.Fan_State == LOW)
			{
				FanSpeed_Ctrl(LOW);
				Delay1msCount++;
				if(Delay1msCount>200)
				{
 					Delay1msCount 		= 	0;
					WheelLedPort  			&= 	0xF0;
					WheelLedPort  			|= 	Port_Val;
					Port_Val 				=	(Port_Val<<1);
					Cycle_Count++;
					if(Cycle_Count	>=	4)
						{
							Cycle_Count	=	0;
							Port_Val		= 	0x01;
						}
				
				}
			}
		else if(Sys_State.Fan_State == MID)
			{
				FanSpeed_Ctrl(MID);
				Delay1msCount++;
				if(Delay1msCount>100)
				{
 					Delay1msCount 		= 	0;
					WheelLedPort  			&= 	0xF0;
					WheelLedPort  			|= 	Port_Val;
					Port_Val				=	(Port_Val<<1);
					Cycle_Count++;
					if(Cycle_Count	>=	4)
						{
							Cycle_Count	=	0;
							Port_Val		= 	0x01;
						}
				
				}
			}
		else if(Sys_State.Fan_State == HIGH)
			{
				FanSpeed_Ctrl(HIGH);
				Delay1msCount++;
				if(Delay1msCount>50)
				{
 					Delay1msCount 		= 	0;
					WheelLedPort  			&= 	0xF0;
					WheelLedPort  			|= 	Port_Val;
					Port_Val				=	(Port_Val<<1);
					Cycle_Count++;
					if(Cycle_Count	>=	4)
						{
							Cycle_Count	=	0;
							Port_Val		= 	0x01;
						}
				}
			}
		}
}

//开关机状态控制函数
void Sys_State_Ctrl(void)
{
	if(Sys_State.Pwr_State ==  OFF)
		{
			Sys_State.Fan_State =  OFF;
			Sys_State.Smart_State = OFF;
			Sys_State.Timer_State = OFF;
			TimeLED 			= LED_OFF;
			SmartLED			= LED_OFF;
			//Sys_State.Move_State = ON;
			WheelLedPort 		|= 0x0F;
			PurificationPort_Ctrl(OFF);
			Light_Port_Ctrl(OFF);
			FanSpeed_Ctrl(OFF);
			Init_Led(OFF);
		}
		
}

//定时器0中断函数,1ms中断一次
void Timer0() interrupt 1 using 1
{
	Smart_Function();
	Move_Detect_Function();
	Fan_Led_Speed_Fun();
	Sys_State_Ctrl();
}
	




