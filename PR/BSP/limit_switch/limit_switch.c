#include "includes.h"


// ��λ����GPIO��ʼ��
// CHASSIS_LEFT_LIMIT_SWITCH -> PD5
// CHASSIS_RIGHT_LIMIT_SWITCH -> PD4
void ls_GPIO_init(void) // ***************************/*WAITING_CHANGE*/
{
	GPIO_InitTypeDef  GPIO_InitStructure;		

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	//��ʼ��������λ���ص�GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11; // ��λ���ؽӿ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // ��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  // 100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  // ����
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; // ��λ���ؽӿ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // ��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  // 100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  // ����
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 ; //TIM9_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // ��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  // 100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  // ����
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
}


// ��ȡ��λ���ص�ƽ״̬
// �͵�ƽ����0(RESET)
// �ߵ�ƽ����1(SET)
// ���������ȡ��
uint8_t Read_limit_switch(u8 limit_switch)
{
	uint8_t status = SET;  // Ĭ������
	
	switch(limit_switch)
	{
    case UNDER_ARM_RESET_LIMIT_SWITCH       : status =  GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_13); break;
    case TURNPLATE_RESET_LIMIT_SWITCH       : status =  GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_9); break; 
    case PULL_RESET_LIMIT_SWITCH            : status =  GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9); break; 
    case CHASSIS_RIGHT_LIMIT_SWITCH         : status =  GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9); break; 
    case CHASSIS_LEFT_LIMIT_SWITCH          : status =  GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_11); break; 
    case ARM_RESET_LIMIT_SWITCH             : status =  GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_8); break;
		case MOVE_ARM_RESET_LIMIT_SWITCH        : status =  GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_12); break;
		case MOVE_ARM_MIDDLE_LIMIT_SWITCH       : status =  GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_14); break;
		case ARM_ARRIVE_LIMIT_SWITCH            : status =  GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_10); break;
		case LIGHT_SWITCH_1                     : status =  GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3); break;
		case LIGHT_SWITCH_2                     : status =  GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4); break;
		default: break;
	}
	
	return status;
}


// ������λ���������˶��ٶ�
void ls_use_limit_switch_limit_velocity(void)
{

}

