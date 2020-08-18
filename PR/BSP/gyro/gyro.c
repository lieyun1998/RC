#include "includes.h"


struct SAngle 	GYRO_ANGLE;

/*
struct STime		stcTime;
struct SAcc 		stcAcc;
struct SGyro 		stcGyro;
struct SMag 		stcMag;
struct SDStatus stcDStatus;
struct SPress 	stcPress;
struct SLonLat 	stcLonLat;
struct SGPSV 		stcGPSV;
struct SQ       stcQ;
*/


// ����������ʹ�õ�UART4
void gyro_UART4_init(u32 baud_rate)
{
	// �����ṹ��
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);  // ʹ��GPIOCʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);  // ʹ��USART4ʱ��
 
	// ����4��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4);  // PC10����ΪUSART4 TX
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4);  // PC11����ΪUSART4 RX
	
	// UART4�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;       // ���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 // �ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     // �������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       // ����
	GPIO_Init(GPIOC,&GPIO_InitStructure); 

  // UART4��ʼ������
	USART_InitStructure.USART_BaudRate = baud_rate;                                  // ����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                      // �ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                           // һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;                              // ����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  // ��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	                 // �շ�ģʽ
  USART_Init(UART4, &USART_InitStructure);
	
  USART_Cmd(UART4, ENABLE);  // ʹ�ܴ���4
	
	// �����ж�
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;           // ����4�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  // ��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		     // �����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			       // IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	
	
	USART_ClearFlag(UART4, USART_FLAG_TC);
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);  // ��������ж�
}


// ����4�����жϺ���
void UART4_IRQHandler(void)
{
	static uint8_t UART4_receive_data;

	if(USART_GetITStatus(UART4, USART_IT_RXNE) == SET)   
	{
		USART_ClearITPendingBit(UART4, USART_IT_RXNE);  // �����־λ
		UART4_receive_data = USART_ReceiveData(UART4);  // ��ȡ����
		gyro_processing_gyro_data((unsigned char)UART4_receive_data);  // ��������
	}
}


// ������4���ܵ�������
void gyro_processing_gyro_data(unsigned char ucData)
{
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	
	
	ucRxBuffer[ucRxCnt++] = ucData;	 // ���յ������ݴ��뻺������

	if(ucRxBuffer[0] != 0x55)  // ����ͷ���ԣ������¿�ʼѰ��0x55����ͷ(����ͷ�̶����䣩
	{
		ucRxCnt = 0;
		return;
	}
	if(ucRxCnt < 11) {return;}  // ���ݲ���11�����򷵻�
	else
	{
		// �ж��������������ݣ�Ȼ���俽������Ӧ�Ľṹ���У���Щ���ݰ���Ҫͨ����λ���򿪶�Ӧ������󣬲��ܽ��յ�������ݰ�������
		switch(ucRxBuffer[1])
		{
			// memcpyΪ�������Դ����ڴ濽��������������"string.h"�������ջ��������ַ����������ݽṹ�����棬�Ӷ�ʵ�����ݵĽ���
			case 0x53:	memcpy(&GYRO_ANGLE, &ucRxBuffer[2], 8); break;
			/*
			case 0x50:	memcpy(&stcTime, &ucRxBuffer[2], 8); break;
			case 0x51:	memcpy(&stcAcc, &ucRxBuffer[2], 8); break;
			case 0x52:	memcpy(&stcGyro, &ucRxBuffer[2], 8); break;
			case 0x54:	memcpy(&stcMag, &ucRxBuffer[2], 8); break;
			case 0x55:	memcpy(&stcDStatus, &ucRxBuffer[2], 8); break;
			case 0x56:	memcpy(&stcPress, &ucRxBuffer[2], 8); break;
			case 0x57:	memcpy(&stcLonLat, &ucRxBuffer[2], 8); break;
			case 0x58:	memcpy(&stcGPSV, &ucRxBuffer[2], 8); break;
			case 0x59:	memcpy(&stcQ, &ucRxBuffer[2], 8); break;
			*/
		} 
		ucRxCnt = 0;  // ��ջ�����
	}
}

