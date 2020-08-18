#include "includes.h"


// ɫ�괫�������õ�GPIO��ʼ��
// ��ֱ���ɫ�� -> PA8
// ˮƽ���ɫ�� -> PC8
// ˮƽ�Ҳ�ɫ�� -> PC9
// ��ֱ�Ҳ�ɫ�� -> PB8
// NPN�� �����ӵ�
void cs_GPIO_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;		
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  // ��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);  // ��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);  // ��ʱ��
	
	//��ʼ����Ӧ��GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // ��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // ����
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//��ʼ����Ӧ��GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 ; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // ��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // ����
	
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	//��ʼ����Ӧ��GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // ��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // ����
	
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}


// ��ȡɫ�괫������ƽ״̬
// �͵�ƽ����0(RESET)
// �ߵ�ƽ����1(SET)
uint8_t Read_color(u8 sensor)
{
	uint8_t status = SET;  // Ĭ������
	
	switch(sensor)
	{
		case VERTICAL_LEFT_COLOR_SENSOR : status = GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_0) ; break;
		case ACLINIC_LEFT_COLOR_SENSOR  : status = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) ; break;		
		case ACLINIC_RIGHT_COLOR_SENSOR : status = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_14) ; break;
		case VERTICAL_RIGHT_COLOR_SENSOR: status = GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_1) ; break;
		default: break;
	}
	
	return status;
}

