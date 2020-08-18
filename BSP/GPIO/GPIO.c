#include <GPIO.h>
#include <sys.h>
#include <stm32f4xx.h>

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

void cylinder_GPIO_init(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

		//��ʼ���������׵�GPIO
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12 | GPIO_Pin_11 | GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOF, &GPIO_InitStructure);
		
		// �ȹر����е�ŷ�
		GPIO_ResetBits(GPIOF, GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12 | GPIO_Pin_11 | GPIO_Pin_10);
}

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

void Key_GPIO_Init(void)//������ʼ��
{
	GPIO_InitTypeDef  GPIO_InitStructure;		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // ��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  // 100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  // ����
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
}

// ��������
void cylinder_on(u8 cylinder)
{
	switch(cylinder)
	{
		case HOLD_FOOT               : GPIO_SetBits(GPIOF, GPIO_Pin_15); break;
    case CATCH_SEAT_1            : GPIO_SetBits(GPIOF, GPIO_Pin_14); break;
    case CATCH_SEAT_2            : GPIO_SetBits(GPIOF, GPIO_Pin_13); break;
    case CATCH_SEAT_3            : GPIO_SetBits(GPIOF, GPIO_Pin_11); break; 
    case CATCH_BALL_1ST          : GPIO_SetBits(GPIOF, GPIO_Pin_12); break; 
		case CATCH_BALL_SEAT         : GPIO_SetBits(GPIOF, GPIO_Pin_10); break; 
		default: break;
	}
}


void cylinder_off(u8 cylinder)
{
	switch(cylinder)
	{
    case HOLD_FOOT               : GPIO_ResetBits(GPIOF, GPIO_Pin_15); break;
    case CATCH_SEAT_1            : GPIO_ResetBits(GPIOF, GPIO_Pin_14); break;
    case CATCH_SEAT_2            : GPIO_ResetBits(GPIOF, GPIO_Pin_13); break;
    case CATCH_SEAT_3            : GPIO_ResetBits(GPIOF, GPIO_Pin_11); break; 
    case CATCH_BALL_1ST          : GPIO_ResetBits(GPIOF, GPIO_Pin_12); break; 
		case CATCH_BALL_SEAT         : GPIO_ResetBits(GPIOF, GPIO_Pin_10); break; 
		default: break;
	}
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
    case ARM_ARRIVE_LIMIT_SWITCH             : status =  GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_8); break;
		case MOVE_ARM_RESET_LIMIT_SWITCH        : status =  GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_12); break;
		case MOVE_ARM_MIDDLE_LIMIT_SWITCH       : status =  GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_14); break;
		case ARM_RESET_LIMIT_SWITCH            : status =  GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_10); break;
		case LIGHT_SWITCH_1                     : status =  GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3); break;
		case LIGHT_SWITCH_2                     : status =  GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4); break;
		default: break;
	}
	
	return status;
}

u8 GET_GPIO_KEY(void)
{
 u8 GPIO_State = 0 ;
  //����
 if( PEin(8) )          //�������� 
     GPIO_State |= 0x01 ;
 else
   GPIO_State &= 0xfe ;
 if( PEin(9) )
     GPIO_State |= 0x02 ;
 else
   GPIO_State &= 0xfd ;
  if( PEin(10) )
     GPIO_State |= 0x04 ;
 else
   GPIO_State &= 0xfb ;
  if( PEin(11) )
     GPIO_State |= 0x08 ;
 else
   GPIO_State &= 0xf7 ;
 if( PEin(12) )
     GPIO_State |= 0x10 ;
 else
   GPIO_State &= 0xef ; 
 if( PEin(13) )
     GPIO_State |= 0x20 ;
 else
   GPIO_State &= 0xdf ;
 if( PEin(14) )
     GPIO_State |= 0x40 ;
 else
   GPIO_State &= 0xbf ;
 if( PEin(15) )
     GPIO_State |= 0x80 ;
 else
   GPIO_State &= 0x7f ;
 return GPIO_State;

}

//��ȡ��ƽֵ   ���
u16 Get_GPIO_limit(void)
{
	u16 GPIO_State = 0;
	
	//���
	if( PGin(1) )
     GPIO_State |= 0x01 ;
	else
		 GPIO_State &= 0xffe ;
	if( PGin(0) )
     GPIO_State |= 0x02 ;
	else
		 GPIO_State &= 0xffd ;
  if( PEin(7) )
     GPIO_State |= 0x04 ;
	else
		 GPIO_State &= 0xffb ;
  if( PGin(13) )
     GPIO_State |= 0x08 ;
	else
		 GPIO_State &= 0xff7 ;
		if( !PGin(11) )
     GPIO_State |= 0x100 ;
	else
		 GPIO_State &= 0xeff ;
 
	//��λ
	if( !PEin(0) )
     GPIO_State |= 0x10 ;
	else
		 GPIO_State &= 0xfef ;	
	if( !PDin(9) )
     GPIO_State |= 0x20 ;
	else
		 GPIO_State &= 0xfdf ;
	if( !PDin(10) )
     GPIO_State |= 0x40 ;
	else
		 GPIO_State &= 0xfbf ;
	
	
	if( !PDin(11) )
     GPIO_State |= 0x80 ;
	else
		 GPIO_State &= 0x7f ;


	return GPIO_State ; 
}
