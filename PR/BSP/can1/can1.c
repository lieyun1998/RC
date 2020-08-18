#include "includes.h"


// CAN1��ʼ�� ����ROBOMODULE
// PA11 -> CANRX
// PA12 -> CANTX
void can1_CAN1_init(void)
{
	CAN_InitTypeDef        can; 
	CAN_FilterInitTypeDef  can_filter;
	GPIO_InitTypeDef       gpio;
	NVIC_InitTypeDef       nvic;

	// ��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

	// ��������IO��
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_CAN1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_CAN1);

	gpio.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA, &gpio);
	
	// ����CAN�Ĺ���ģʽ
	CAN_DeInit(CAN1);
	CAN_StructInit(&can);
	
	can.CAN_TTCM = DISABLE;
	can.CAN_ABOM = DISABLE;
	can.CAN_AWUM = DISABLE;
	can.CAN_NART = DISABLE;
	can.CAN_RFLM = DISABLE;
	can.CAN_TXFP = ENABLE;
	can.CAN_Mode = CAN_Mode_Normal;
	can.CAN_SJW  = CAN_SJW_1tq;
	can.CAN_BS1 = CAN_BS1_9tq;
	can.CAN_BS2 = CAN_BS2_4tq;
	can.CAN_Prescaler = 3;   //����CAN������Ϊ 42/(1+9+4)/3=1Mbps
	CAN_Init(CAN1, &can);

	// ����ɸѡ��
	can_filter.CAN_FilterNumber = 0;
	can_filter.CAN_FilterMode = CAN_FilterMode_IdMask;
	can_filter.CAN_FilterScale = CAN_FilterScale_32bit;
	can_filter.CAN_FilterIdHigh = 0x0000;
	can_filter.CAN_FilterIdLow = 0x0000;
	can_filter.CAN_FilterMaskIdHigh = 0x0000;
	can_filter.CAN_FilterMaskIdLow = 0x0000;
	can_filter.CAN_FilterFIFOAssignment = 0;
	can_filter.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&can_filter);
	
	// �����жϿ�����
	nvic.NVIC_IRQChannel = CAN1_RX0_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 1;
	nvic.NVIC_IRQChannelSubPriority = 0;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	
	nvic.NVIC_IRQChannel = CAN1_TX_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 1;
	nvic.NVIC_IRQChannelSubPriority = 1;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	
	// ʹ��CAN�ж�
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);  // FIFO0�����ж�
	CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE);  // �����ж�
}


// CAN1�ķ����жϺ���
void CAN1_TX_IRQHandler(void)
{
    if(CAN_GetITStatus(CAN1,CAN_IT_TME)!= RESET) 
		{
	   CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
     
    }
}

/*WAITING_TEST*/
// CAN1��FIFO0�����жϺ���
void CAN1_RX0_IRQHandler(void)
{
  CanRxMsg CAN1_RX0_message;  // ��ʱ��Ž������ݵĽṹ��
	
  if(CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET) 
  {
		CAN_Receive(CAN1, CAN_FIFO0, &CAN1_RX0_message);  // ��ȡ����
		
//		// RE40��Ϣ����
//		if((CAN1_RX0_message.IDE == CAN_Id_Standard)&&(CAN1_RX0_message.IDE == CAN_RTR_Data)&&(CAN1_RX0_message.DLC == 8)) //��׼֡������֡�����ݳ���Ϊ8
//		{
//			if(CAN1_RX0_message.StdId == 0x1B)
//			{
//					Real_Current_Value[0] = (CAN1_RX0_message.Data[0]<<8)|(CAN1_RX0_message.Data[1]);
//					Real_Velocity_Value[0] = (CAN1_RX0_message.Data[2]<<8)|(CAN1_RX0_message.Data[3]);
//					Real_Position_Value[0] = ((CAN1_RX0_message.Data[4]<<24)|(CAN1_RX0_message.Data[5]<<16)|(CAN1_RX0_message.Data[6]<<8)|(CAN1_RX0_message.Data[7]));
//			}
//			else if(CAN1_RX0_message.StdId == 0x2B)
//			{
//					Real_Current_Value[1] = (CAN1_RX0_message.Data[0]<<8)|(CAN1_RX0_message.Data[1]);
//					Real_Velocity_Value[1] = (CAN1_RX0_message.Data[2]<<8)|(CAN1_RX0_message.Data[3]);
//					Real_Position_Value[1] = ((CAN1_RX0_message.Data[4]<<24)|(CAN1_RX0_message.Data[5]<<16)|(CAN1_RX0_message.Data[6]<<8)|(CAN1_RX0_message.Data[7]));
//			}
//			else if(CAN1_RX0_message.StdId == 0x3B)
//			{
//					Real_Current_Value[2] = (CAN1_RX0_message.Data[0]<<8)|(CAN1_RX0_message.Data[1]);
//					Real_Velocity_Value[2] = (CAN1_RX0_message.Data[2]<<8)|(CAN1_RX0_message.Data[3]);
//					Real_Position_Value[2] = ((CAN1_RX0_message.Data[4]<<24)|(CAN1_RX0_message.Data[5]<<16)|(CAN1_RX0_message.Data[6]<<8)|(CAN1_RX0_message.Data[7]));
//			}
//			else if(CAN1_RX0_message.StdId == 0x4B)
//			{
//					Real_Current_Value[3] = (CAN1_RX0_message.Data[0]<<8)|(CAN1_RX0_message.Data[1]);
//					Real_Velocity_Value[3] = (CAN1_RX0_message.Data[2]<<8)|(CAN1_RX0_message.Data[3]);
//					Real_Position_Value[3] = ((CAN1_RX0_message.Data[4]<<24)|(CAN1_RX0_message.Data[5]<<16)|(CAN1_RX0_message.Data[6]<<8)|(CAN1_RX0_message.Data[7]));
//			}
//			else if(CAN1_RX0_message.StdId == 0x1F)
//			{
//					Real_Online[0] = 1;
//			}
//			else if(CAN1_RX0_message.StdId == 0x2F)
//			{
//					Real_Online[1] = 1;
//			}
//			else if(CAN1_RX0_message.StdId == 0x3F)
//			{
//					Real_Online[2] = 1;
//			}
//			else if(CAN1_RX0_message.StdId == 0x4F)
//			{
//					Real_Online[3] = 1;
//			}
//			else if(CAN1_RX0_message.StdId == 0x1C)
//			{
//					Real_Ctl1_Value[0] = CAN1_RX0_message.Data[0];
//					Real_Ctl2_Value[0] = CAN1_RX0_message.Data[1];
//			}
//			else if(CAN1_RX0_message.StdId == 0x2C)
//			{
//					Real_Ctl1_Value[1] = CAN1_RX0_message.Data[0];
//					Real_Ctl2_Value[1] = CAN1_RX0_message.Data[1];
//			}
//			else if(CAN1_RX0_message.StdId == 0x3C)
//			{
//					Real_Ctl1_Value[2] = CAN1_RX0_message.Data[0];
//					Real_Ctl2_Value[2] = CAN1_RX0_message.Data[1];
//			}
//			else if(CAN1_RX0_message.StdId == 0x4C)
//			{
//					Real_Ctl1_Value[3] = CAN1_RX0_message.Data[0];
//					Real_Ctl2_Value[3] = CAN1_RX0_message.Data[1];
//			}
//    }
    AK80_update_info(&CAN1_RX0_message);
		m3508_update_m3508_info(&CAN1_RX0_message);  // M3508������ݴ���
		CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
  }
}

