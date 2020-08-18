#include "includes.h"


u8 BEEP_FLAG = 0;

// ��¼��������ʼ����ʱTIM2�Ĵ�����ֵ
u32 BEEP_TURN_ON_TIMESTAMP = 0;


// ����������GPIO��ʼ��
// BEEP -> PF8
void beep_GPIO_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;		
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);  // ��ʱ��

	//��ʼ����Ӧ��GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  // ��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  // �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	// �ȹرշ�����
	GPIO_ResetBits(GPIOF, GPIO_Pin_8);
}






