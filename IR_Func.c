/*----------Project Info------------------------------------------
** Descriptions: 	
** Created By:		Chain
** Created Data:	20170120
** Version:			V1.0
*****************************************************************/
#include		"IR_Func.h"



//红外遥控器解码程序
bit             P_IR_RX_temp;                //Last sample
bit             B_IR_Sync;                        //已收到同步标志
bit             B_IR_Press;                        //Key press flag,include repeat key.
uchar        IR_SampleCnt;                //采样计数
uchar        IR_BitCnt;                        //编码位数
uchar        IR_data;                        //数据原码
uchar        IR_DataShit;                //数据反码
uchar        IR_code;                        //IR code        红外键码
void IR_RX_VS1838B(void)
{
	uchar        SampleTime;
	
	IR_SampleCnt++;                                                        //Sample + 1
	F0 = P_IR_RX_temp;                                                //Save Last sample status
	P_IR_RX_temp = P_IR_RX;                                        //Read current status
	if(F0 && !P_IR_RX_temp)                                        //Last sample is high，and current sample is low, so is fall edge
		{
			SampleTime = IR_SampleCnt;                        //get the sample time
			IR_SampleCnt = 0;                                        //Clear the sample counter
			if(SampleTime > D_IR_SYNC_MAX) 
				B_IR_Sync = 0;        					//large the Maxim SYNC time, then error
			else if(SampleTime >= D_IR_SYNC_MIN)                                        //SYNC
				{
					if(SampleTime >= D_IR_SYNC_DIVIDE)
						{
							B_IR_Sync = 1;                                        //has received SYNC
							IR_BitCnt = D_IR_BIT_NUMBER;        //Load bit number
						}
				}
			else if(B_IR_Sync)                                                //has received SYNC
				{
					if(SampleTime > D_IR_DATA_MAX)               
						B_IR_Sync=0;        //data samlpe time to large
					else
						{
							IR_DataShit >>= 1;                                        //data shift right 1 bit
							if(SampleTime >= D_IR_DATA_DIVIDE)  
								IR_DataShit |= 0x80;        //devide data 0 or 1
							if(--IR_BitCnt == 0)                                //bit number is over?
								{
									B_IR_Sync = 0;                                        //Clear SYNC
									if(~IR_DataShit == IR_data)                //判断数据正反码
										{
											IR_code      = IR_data;
											B_IR_Press   = 1;                        //数据有效
										}
								}
 							else if((IR_BitCnt & 7)== 0)                //one byte receive
								{
									IR_data  = IR_DataShit;                        //Save the IR data byte
								}
						}
				}
	        }
}

//定时器1，125us中断一次
void Timer1() interrupt 3 using 1
{
	IR_RX_VS1838B();
}

