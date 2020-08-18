#include "includes.h"

float RANGING_DISTANCE = 0;



// ��ʼ�������ഫ�����õ�ADC3
// PF9 -> ADC3CH7
void adc_adc3_init(void)
{
	// �����ṹ��
  GPIO_InitTypeDef      GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	NVIC_InitTypeDef      NVIC_InitStructure;
	
	// ��ʱ��
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);  // ʹ��GPIOFʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);  // ʹ��ADC3ʱ��

  //��ʼ��GPIO
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//PA5 ͨ��5
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;  // ģ������
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;  // ����������
  GPIO_Init(GPIOF, &GPIO_InitStructure);  // ��ʼ��  
 
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3, ENABLE);	  //ADC3��λ
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3, DISABLE);	 // ��λ����	 
 
  // ����ADC3
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;  // ����ģʽ
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;  // Ԥ��Ƶ4��Ƶ��ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz 
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; // DMAʧ�ܣ�����ģʽ�޹أ�
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;  // ���������׶�֮����ӳ�5��ʱ�ӣ�����ģʽ�޹أ�
	ADC_CommonInit(&ADC_CommonInitStructure);  // ��ʼ��
	
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;  // 12λģʽ
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;  // ��ɨ��ģʽ����ͨ������Ҫ��
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  // ����ת��
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;  // ��ֹ������⣬ʹ���������
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  // �Ҷ���	
  ADC_InitStructure.ADC_NbrOfConversion = 1;  // 1��ת���ڹ���������,Ҳ����ֻת����������1 
  ADC_Init(ADC3, &ADC_InitStructure);  // ADC��ʼ��
	
	ADC_RegularChannelConfig(ADC3, ADC_Channel_7, 1, ADC_SampleTime_480Cycles);  // ����ADC3CH7��һ��ת��������ʱ��Ϊ480������
	
	// �����жϣ�������ȼ���
	NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
	NVIC_Init(&NVIC_InitStructure);		

	ADC_ITConfig(ADC3, ADC_IT_EOC, ENABLE); // ����ADC3ת�������ж�
	
	ADC_Cmd(ADC3, ENABLE);  // ʹ��ADC3
	
	ADC_SoftwareStartConv(ADC3);  // ��ʼADCת�����������
	

}


// ADC�жϺ���
void ADC_IRQHandler(void)
{
	if(ADC_GetITStatus(ADC3, ADC_IT_EOC) == SET)
	{
		ADC_ClearITPendingBit(ADC3, ADC_IT_EOC);
	}
}





