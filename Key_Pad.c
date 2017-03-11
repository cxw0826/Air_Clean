/*----------Project Info------------------------------------------
** Descriptions: 	
** Created By:		Chain
** Created Data:	20170120
** Version:			V1.0
*****************************************************************/

#include		"Key_Pad.h"

#define 		PowerKey			0x00
#define			LightKey 			0x60
#define    		SmartKey			0x20
#define 		TimeKey		   		0xC0
#define			PurificationKey		0x40
#define			ReserveKey	  		0xA0
#define			MoveKey			   	0x80

//系统状态结构体
struct 
{
	unsigned char Pwr_State;
	unsigned char Fan_State;
} Sys_State;

//初始化全部LED函数
void Init_Led(unsigned char state)
{
	if(state)
		{
			LightLED 		= LED_ON;
			PurificationLED = LED_ON;
			TimeLED 		= LED_ON;
			PowerLED 		= LED_ON;
			RightLED 		= LED_ON;
			UpLED 			= LED_ON;
			LeftLED 		= LED_ON;
			DownLED 		= LED_ON;
			SmartLED		= LED_ON;
			MoveLED			= LED_ON;
		}
	else
		{
			LightLED 		= LED_OFF;
			PurificationLED = LED_OFF;
			TimeLED 		= LED_OFF;
			PowerLED 		= LED_OFF;
			RightLED 		= LED_OFF;
			UpLED 			= LED_OFF;
			LeftLED 		= LED_OFF;
			DownLED 		= LED_OFF;
			SmartLED		= LED_OFF;
			MoveLED			= LED_OFF;
		}
}

//照明端口控制函数
void Light_Port_Ctrl(unsigned char state)
{
	if(state)
		{
			LightPort 		= PortOn;
			
		}
	else
		{
			LightPort 		= PortOff;
		}
}

//上升下降电机控制函数
void UpDown_Motor_Ctrl(unsigned char state)
{
	if(state)
		{
			MotorUpPort 	= PortOn;
			MotorDownPort 	= PortOff;
		}
	else
		{
			MotorUpPort 	= PortOn;
			MotorDownPort 	= PortOff;
		}
}


//净化端口控制函数
void PurificationPort_Ctrl(unsigned char state)
{
	if(state)
		{
			PurificationPort 		= PortOn;
		}
	else
		{
			PurificationPort 		= PortOff;
		}
}


//风扇速度控制函数
void FanSpeed_Ctrl(unsigned char state)
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
				SmartLED  = ~SmartLED;
			}
		break;
    case TimeKey:
		if(Sys_State.Pwr_State)
			{
				Beep();	
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
		if(Sys_State.Pwr_State)
			{
				Beep();	
				MoveLED = ~MoveLED;
			}
		break;
    case ReserveKey:
		break;
	default:
		break;
	}
}

unsigned char Delay1msCount = 0;
unsigned char i				= 0;
unsigned char n				= 0x01;

void Timer0() interrupt 1 using 1
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
 					Delay1msCount = 0;
					WheelLedPort  &= 0xF0;
					WheelLedPort  |= n;
					n=(n<<1);
					i++;
					if(i>=4)
						{
							i	=	0;
							n	= 	0x01;
						}
				
				}
			}
		else if(Sys_State.Fan_State == MID)
			{
				FanSpeed_Ctrl(MID);
				Delay1msCount++;
				if(Delay1msCount>100)
				{
 					Delay1msCount = 0;
					WheelLedPort  &= 0xF0;
					WheelLedPort  |= n;
					n=(n<<1);
					i++;
					if(i>=4)
						{
							i	=	0;
							n	= 	0x01;
						}
				
				}
			}
		else if(Sys_State.Fan_State == HIGH)
			{
				FanSpeed_Ctrl(HIGH);
				Delay1msCount++;
				if(Delay1msCount>50)
				{
 					Delay1msCount = 0;
					WheelLedPort  &= 0xF0;
					WheelLedPort  |= n;
					n=(n<<1);
					i++;
					if(i>=4)
						{
							i	=	0;
							n	= 	0x01;
						}
				
				}
			}
		}
}
	




