/*----------Project Info------------------------------------------
** Descriptions: 	
** Created By:		Chain
** Created Data:	20170120
** Version:			V1.0
*****************************************************************/
#include		"Buzzer.h"

//ϵͳ������ʱ����
//15*20*40 = 12 000 /12 000 000 = 1/1000 Լ����1����
void Delay_Nms(uint	Nms)   
{
    uchar 	i,j,k;
    while(Nms--)
    {
      for(i=15;i>0;i--) 
     	 for(j=20;j>0;j--) 
        	 for(k=40;k>0;k--);
    }
}

//�������������к���
void Beep(void)
{
	Buzzer	=	1;
	Delay_Nms(30);
	Buzzer	=	0;
}



