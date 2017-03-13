/*----------Project Info------------------------------------------
** Descriptions: 	
** Created By:		Chain
** Created Data:	20170120
** Version:			V1.0
*****************************************************************/

#include		"Initial.h"
#define			Sys_Clock	12000000L
#define			Time_1ms	(65536-Sys_Clock/1000)

//--------------------------------------------------------------
//PN口设定<PN.7~PN.0>
//		PNM1[1:0]			PNM0[1:0]		说明
//			0					0			双向口
//			0					1			推挽输出，20MA
//			1					0			高阻态输入
//			1					1			开漏双向
//--------------------------------------------------------------

//初始化端口
void Initial_Port(void)
{
		//P0全部推挽输出
	    P0M1 = 0x00;
	    P0M0 = 0xFF;
	    //P1.7~P1.5	高阻态输入	P1.4~P1.0推挽输出
	    P1M1 = 0xE0;	//1110	0000
	    P1M0 = 0x1F;	//0001	1111
	    //P2.5是高阻态输入	其余是推挽输出
	    P2M1 = 0x20;	//0010	0000
	    P2M0 = 0xDF;	//1101	1111
		//P3.6-P3.3-P3.2是高阻态输入	其余是推挽输出
	    P3M1 = 0x4C;	//0100	1100
	    P3M0 = 0xB3;	//1011	0011
	    //P4.5是高阻态输入	其余是推挽输出
	    P4M1 = 0x20;	//0010	0000
	    P4M0 = 0xDF;	//1101	1111
	    //P5是双向口
	    P5M1 = 0x00;
	    P5M0 = 0x00;

		//整体初始化各个IO口

		//	P0.7		P0.6		P0.5
		//				KEY_DAT2	KEY_DAT1
	    P0	 = 0x00;	//0000	0000
	    //	P1.7		P1.6		P1.5		P1.4		P1.3		P1.2		P1.1		P1.0
	    //	KEY_DAT0										DOWN_LED	LEFT_LED	UP_LED		RIGHT_LED
	    P1 	 = 0xFF;	//0000	0000
	    P2 	 = 0xFF;	//0000	0000
	    P3   = 0xFF;		//0000	0000
	    P4   = 0xBF;		//0000	0000
	    P5   = 0xFF;		//0000	0000
}

//初始化定时器
void Initial_Timers(void)
{
	    EA 		= 0;				//关闭总中断

	//Timer0Init:
	    AUXR 	|= 	0x80;			//定时器0工作模式为12倍，辅助特殊功能寄存器	
	    TMOD 	&= 	0xF0;			//定时器0为16位自动重装定时器
	    TL0 	= 	Time_1ms;		//装载低八位
	    TH0 	= 	Time_1ms>>8;		//装载高八位	
	    TF0 	= 	0;				//清除定时器0标志位
	    TR0 	= 	1;				//开启定时器0	
	    ET0 	= 	1;				//允许定时器0中断

	//Timer1Init:			
	    AUXR 	&= 	0xBF;		//定时器1工作模式为12分频
	    TMOD	&= 	0x0F;		//定时器1为16位自动重装定时器
	    TL1 	= 	Time_1ms;		//装载低八位
	    TH1 	= 	Time_1ms>>8;		//装载高八位
	    TF1 	= 	0;				//清除定时器1标志位
	    TR1 	= 	1;				//开启定时器1	
	    ET1 	= 	1;				//允许定时器1中断
	    
	//Timer2Init:			
	    //AUXR 	&= 	0xEF;			//不允许定时器2运行
	    //IE2 	&= 	0xBF;			//禁止定时器4产生中断
	    
	    EA 		= 	1;				//打开总中断
}

//初始化中断
void Initial_EX_INT(void)
{
	    EA 			= 	0;			//关闭总中断

	//exint0:
	    IT0 		= 	0;			//外部中断0上升下降都可触发
	    EX0 		= 	0;			//允许外部中断0
	    IE0 		= 	0;			//清除外部中断0标志位
	//exint1:
	    IT1 		= 	1;			//外部中断1上升下降都可触发
	    EX1 		= 	1;			//允许外部中断1
	    IE1 		= 	0;			//清除外部中断1标志位
	//exint2:
	    INT_CLKO 	|= 	0x10;		//允许外部中断2
	//exint3:
	    INT_CLKO 	&= 	0xDF;		//禁止外部中断3
	//exint4:
	    INT_CLKO 	&= 	0xBF;		//禁止外部中断4

	    EA 			= 	1;			//打开总中断
}

//初始化函数入口
void Initial_Sys(void)
{
	Initial_Port();
	Initial_EX_INT();
	Initial_Timers();
}

