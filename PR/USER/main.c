#include "includes.h"
#include <app_cfg.h>


int main(void)
{	
	
	OSInit();  //UCOS��ʼ��

	OSTaskCreate(start_task,(void*)0,(OS_STK*)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO); //������ʼ����
	
	OSStart(); //��ʼ����
	
	return (0);
}


 


