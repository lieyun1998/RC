#include "includes.h"


// ���ñ�����ʹ�õ�TIM4
// PD12 -> A��  
// PD13 -> B��
void encoder_TIM4_init(void)
{
	// �����ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  
	// ��ʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
  // ����GPIO
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;  // PD12 -> A��  PD13 -> B��
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  // ����ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;  // ��©���ģʽ ����ģʽ�²�����
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  // ��������ģʽ
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	// ���ø���
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
  
  // ���ö�ʱ��
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);  // ��ʼ���ṹ�����ֵ
	
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // ��Ԥ��Ƶֵ ������
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;  // Ԥװ��ֵ����Ϊ���
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  // ʱ�ӷ�Ƶ���� ����Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  // ���ϼ���ģʽ   
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  
  // ���ö�ʱ���ı�����ģʽ ֱ��ӳ�䵽TI1 TI2 ��������
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 0;  // �����˲�������Ϊ0
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
 
	// ������ʱ��
  TIM_Cmd(TIM4, ENABLE);  // ʹ�ܶ�ʱ��
}


// ���ñ�����ʹ�õ�TIM8
// PC6 -> A��  
// PC7 -> B��
void encoder_TIM8_init(void)
{
	// �����ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  
	// ��ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
  // ����GPIO
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;  // PC6 -> A��  PC7 -> B��
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  // ����ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;  // ��©���ģʽ ����ģʽ�²�����
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  // ��������ģʽ
  GPIO_Init(GPIOC, &GPIO_InitStructure);

	// ���ø���
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8);
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8);
  
  // ���ö�ʱ��
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);  // ��ʼ���ṹ�����ֵ
	
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // ��Ԥ��Ƶֵ ������
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;  // Ԥװ��ֵ����Ϊ���
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  // ʱ�ӷ�Ƶ���� ����Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  // ���ϼ���ģʽ   
  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
  
  // ���ö�ʱ���ı�����ģʽ ֱ��ӳ�䵽TI1 TI2 ��������
	TIM_EncoderInterfaceConfig(TIM8, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 0;  // �����˲�������Ϊ0
  TIM_ICInit(TIM8, &TIM_ICInitStructure);
 
	// ������ʱ��
  TIM_Cmd(TIM8, ENABLE);  // ʹ�ܶ�ʱ��
}

void Launch_Motor_init(u32 arr,u32 psc)//use TIM12 and PB14-15 as the PWM channel of Launch_motor
{					 
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);  	  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM12); 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_TIM12); 

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOB,&GPIO_InitStructure);              
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM12,&TIM_TimeBaseStructure);
	

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OCInitStructure.TIM_Pulse = 1000;
	TIM_OC1Init(TIM12, &TIM_OCInitStructure);  
	TIM_OC2Init(TIM12, &TIM_OCInitStructure);  
	TIM_OC1PreloadConfig(TIM12, TIM_OCPreload_Enable);  
  TIM_OC2PreloadConfig(TIM12, TIM_OCPreload_Enable); 
  TIM_ARRPreloadConfig(TIM12,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM12, ENABLE); 
 
}


void TIM9_PWM_Init(u32 arr,u32 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);  	//TIM9ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	//ʹ��PORTFʱ��	
	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9); //GPIOE5����Ϊ��ʱ��9
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource6,GPIO_AF_TIM9); //GPIOE6����Ϊ��ʱ��9
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOE,&GPIO_InitStructure);              //��ʼ��PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM9,&TIM_TimeBaseStructure);//��ʼ����ʱ��14
	
	//��ʼ��TIM14 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM9, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

	TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
 
  TIM_ARRPreloadConfig(TIM9,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM9, ENABLE);  //ʹ��TIM14
 
										  
}  


// ��ȡ��ʱ��CNT�Ĵ��������ֵ ������һ��λ����Ϣ�ļ���
u32 encoder_get_encoder_CNT(u8 TIMx)
{
	 u32 encoder_CNT;    
   switch(TIMx)
	 {	   
		 case 4: encoder_CNT = (short)TIM4 -> CNT; TIM4 -> CNT = 0; break;	// ��ȡ������
		 case 8: encoder_CNT = (short)TIM8 -> CNT; TIM8 -> CNT = 0; break;	// ��ȡ������
		 default: encoder_CNT = 0;
	 }
	return encoder_CNT;
}





