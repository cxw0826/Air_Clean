/*----------Project Info------------------------------------------
** Descriptions: 文件定义单片机IO口
** Created By:		Chain
** Created Data:	20170120
** Version:		V1.0
*****************************************************************/
#ifndef _PORT_DEFINE_H_
#define _PORT_DEFINE_H_



typedef unsigned char uchar;
typedef unsigned int uint;

//继电器控制列表
#define RelayPort				P2;		//继电器端口

sbit MotorDownPort			=	P2 ^ 6;	//电机下降继电器端口
sbit MotorUpPort			=	P2 ^ 7;	//电机上升继电器端口

sbit FanPort_High			=	P2 ^ 2;	//风机高速继电器端口
sbit FanPort_Mid			=	P2 ^ 3;	//风机中速继电器端口
sbit FanPort_Low			= 	P2 ^ 4;	//风机低速继电器端口

sbit LightPort				= 	P2 ^ 1;	//照明端口(照明和氛围灯共用一个端口)

sbit AnionPort				=	P2 ^ 5;	 //负离子端口
sbit PurificationPort		=	P2 ^ 0;	//净化端口

#define LEDPort					P4;		//LED灯端口

sbit PowerLED				=	P4 ^ 0;	//电源指示灯
sbit TimeLED				=	P4 ^ 2;	//定时灯
sbit PurificationLED		=	P4 ^ 1;	//净化灯

#define	WheelLedPort			P1
sbit RightLED				=	P1 ^ 0;
sbit UpLED					=	P1 ^ 1;
sbit LeftLED				=	P1 ^ 2;
sbit DownLED				=	P1 ^ 3;





#endif



