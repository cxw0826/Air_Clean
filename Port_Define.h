/*----------Project Info------------------------------------------
** Descriptions: �ļ����嵥Ƭ��IO��
** Created By:		Chain
** Created Data:	20170120
** Version:		V1.0
*****************************************************************/
#ifndef _PORT_DEFINE_H_
#define _PORT_DEFINE_H_



typedef unsigned char uchar;
typedef unsigned int uint;

//�̵��������б�
#define RelayPort				P2;		//�̵����˿�

sbit MotorDownPort			=	P2 ^ 6;	//����½��̵����˿�
sbit MotorUpPort			=	P2 ^ 7;	//��������̵����˿�

sbit FanPort_High			=	P2 ^ 2;	//������ټ̵����˿�
sbit FanPort_Mid			=	P2 ^ 3;	//������ټ̵����˿�
sbit FanPort_Low			= 	P2 ^ 4;	//������ټ̵����˿�

sbit LightPort				= 	P2 ^ 1;	//�����˿�(�����ͷ�Χ�ƹ���һ���˿�)

sbit AnionPort				=	P2 ^ 5;	 //�����Ӷ˿�
sbit PurificationPort		=	P2 ^ 0;	//�����˿�

#define LEDPort					P4;		//LED�ƶ˿�

sbit PowerLED				=	P4 ^ 0;	//��Դָʾ��
sbit TimeLED				=	P4 ^ 2;	//��ʱ��
sbit PurificationLED		=	P4 ^ 1;	//������

#define	WheelLedPort			P1
sbit RightLED				=	P1 ^ 0;
sbit UpLED					=	P1 ^ 1;
sbit LeftLED				=	P1 ^ 2;
sbit DownLED				=	P1 ^ 3;





#endif



