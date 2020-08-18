#include "includes.h"

/*********************
 velocity �����˵��ٶ� 
 speed    �����rpm 
 RPM      ���ת��rpm
 *********************/

M3508_REAL_INFO M3508_CHASSIS_MOTOR_REAL_INFO[4];   // 1-4�ֱ��Ӧ˳ʱ�뷽��ĵ��̵��
M3508_REAL_INFO M3508_ARM_MOTOR_REAL_INFO;          // �������Ĳ����ṹ��
M3508_REAL_INFO GM6020_TURN_MOTOR_REAL_INFO;         // ת�̵���Ĳ����ṹ��
M3508_REAL_INFO M2006_TURN_MOTOR_REAL_INFO;

PID M3508_ARM_MOTOR_PID_RPM;            // �������ٶȻ�PID
PID GM6020_TURN_MOTOR_PID_RPM;           // GM6020����ٶȻ�PID
PID M2006_TURN_MOTOR_PID_POS;
PID M3508_CHASSIS_MOTOR_PID_RPM[4];
PID M2006_TURN_MOTOR_PID_RPM;           // ת�̵���ٶȻ�PID

int16_t ARM_TURN_MOTOR_TARGET_RPM = 0;    // ������Ŀ���ٶ�
int16_t TURN_MOTOR_TARGET_RPM = 0;    // ��̨���Ŀ���ٶ�

// M3508��ʼ��
void m3508_motor_init(void)
{
	// PID��ʼ��
	
	PID_parameter_init(&M3508_ARM_MOTOR_PID_RPM       , 10.0, 1.0, 0.0, 16384, 16384, -1);  // �������ٶȻ�PID��ʼ��
	PID_parameter_init(&GM6020_TURN_MOTOR_PID_RPM     , 20.0,50.0, 30.0, 30000, 30000, -1);
//	PID_parameter_init(&GM6020_TURN_MOTOR_PID_RPM     , 100.0, 0.0,0.0, 30000, 30000, -1);
	PID_parameter_init(&M2006_TURN_MOTOR_PID_POS      ,   80, 0.0, 900, 10000,   500, -1);
	PID_parameter_init(&M2006_TURN_MOTOR_PID_RPM      , 10.0, 1.0, 0.0, 10000, 10000, -1);  // ת�̵���ٶȻ�PID��ʼ��
	PID_parameter_init(&M3508_CHASSIS_MOTOR_PID_RPM[0], 10.0, 1.0, 0.0, 16384, 16384, -1);
	PID_parameter_init(&M3508_CHASSIS_MOTOR_PID_RPM[1], 10.0, 1.0, 0.0, 16384, 16384, -1);
	PID_parameter_init(&M3508_CHASSIS_MOTOR_PID_RPM[2], 10.0, 1.0, 0.0, 16384, 16384, -1);
	PID_parameter_init(&M3508_CHASSIS_MOTOR_PID_RPM[3], 10.0, 1.0, 0.0, 16384, 16384, -1);
	
}


// ���õ��ͨ��CAN���������ݸ���m3508��״̬��Ϣ
// ����Ƶ�ʣ�1kHz
void m3508_update_m3508_info(CanRxMsg *msg)
{
	switch(msg -> StdId)  // ����׼ID
	{
			
		case M3508_ARM_MOTOR_ID:
		{ 
			M3508_ARM_MOTOR_REAL_INFO.ANGLE   = (msg -> Data[0] << 8) | msg -> Data[1];  // ת�ӻ�е�Ƕ�
			M3508_ARM_MOTOR_REAL_INFO.RPM     = (msg -> Data[2] << 8) | msg -> Data[3];  // ʵ��ת��ת��
			M3508_ARM_MOTOR_REAL_INFO.CURRENT = (msg -> Data[4] << 8) | msg -> Data[5];  // ʵ��ת�ص���
			// ���нǶȻ���
			m3508_ARM_angle_integral(&M3508_ARM_MOTOR_REAL_INFO);
		}; break;
			
    case M3508_CHASSIS_MOTOR_ID_1:
		{ 
			M3508_CHASSIS_MOTOR_REAL_INFO[0].ANGLE   = (msg -> Data[0] << 8) | msg -> Data[1];  // ת�ӻ�е�Ƕ�
			M3508_CHASSIS_MOTOR_REAL_INFO[0].RPM     = (msg -> Data[2] << 8) | msg -> Data[3];  // ʵ��ת��ת��
			M3508_CHASSIS_MOTOR_REAL_INFO[0].CURRENT = (msg -> Data[4] << 8) | msg -> Data[5];  // ʵ��ת�ص���
		}; break;
		
		case M3508_CHASSIS_MOTOR_ID_2:
		{ 
			M3508_CHASSIS_MOTOR_REAL_INFO[1].ANGLE   = (msg -> Data[0] << 8) | msg -> Data[1];  // ת�ӻ�е�Ƕ�
			M3508_CHASSIS_MOTOR_REAL_INFO[1].RPM     = (msg -> Data[2] << 8) | msg -> Data[3];  // ʵ��ת��ת��
			M3508_CHASSIS_MOTOR_REAL_INFO[1].CURRENT = (msg -> Data[4] << 8) | msg -> Data[5];  // ʵ��ת�ص���
		}; break;
		
		case M3508_CHASSIS_MOTOR_ID_3:
		{ 
			M3508_CHASSIS_MOTOR_REAL_INFO[2].ANGLE   = (msg -> Data[0] << 8) | msg -> Data[1];  // ת�ӻ�е�Ƕ�
			M3508_CHASSIS_MOTOR_REAL_INFO[2].RPM     = (msg -> Data[2] << 8) | msg -> Data[3];  // ʵ��ת��ת��
			M3508_CHASSIS_MOTOR_REAL_INFO[2].CURRENT = (msg -> Data[4] << 8) | msg -> Data[5];  // ʵ��ת�ص���
		}; break;	
		
		case M3508_CHASSIS_MOTOR_ID_4:
		{ 
			M3508_CHASSIS_MOTOR_REAL_INFO[3].ANGLE   = (msg -> Data[0] << 8) | msg -> Data[1];  // ת�ӻ�е�Ƕ�
			M3508_CHASSIS_MOTOR_REAL_INFO[3].RPM     = (msg -> Data[2] << 8) | msg -> Data[3];  // ʵ��ת��ת��
			M3508_CHASSIS_MOTOR_REAL_INFO[3].CURRENT = (msg -> Data[4] << 8) | msg -> Data[5];  // ʵ��ת�ص���
			
		}; break;
		
		case M2006_TURN_MOTOR_ID:
		{ 
			M2006_TURN_MOTOR_REAL_INFO.ANGLE   = (msg -> Data[0] << 8) | msg -> Data[1];  // ת�ӻ�е�Ƕ�
			M2006_TURN_MOTOR_REAL_INFO.RPM     = (msg -> Data[2] << 8) | msg -> Data[3];  // ʵ��ת��ת��
			M2006_TURN_MOTOR_REAL_INFO.CURRENT = (msg -> Data[4] << 8) | msg -> Data[5];  // ʵ��ת�ص���
			// ���нǶȻ���
			m2006_TURN_MOTOR_angle_integral(&M2006_TURN_MOTOR_REAL_INFO);	
		}; break;
		
		case GM6020_MOTOR_ID:
		{ 
			GM6020_TURN_MOTOR_REAL_INFO.ANGLE   = (msg -> Data[0] << 8) | msg -> Data[1];  // ת�ӻ�е�Ƕ�
			GM6020_TURN_MOTOR_REAL_INFO.RPM     = (msg -> Data[2] << 8) | msg -> Data[3];  // ʵ��ת��ת��
			GM6020_TURN_MOTOR_REAL_INFO.CURRENT = (msg -> Data[4] << 8) | msg -> Data[5];  // ʵ��ת�ص���
			// ���нǶȻ���
			
		}; break;

		default: break;
	}
}


// ͨ��CAN1���͵���m3508�ĵ���
// ����Ƶ�ʣ�1kHz
// ת�ӽǶȷ�Χֵ��0-8191����Ӧ0��360�ȣ�
// ת��ת�ٵ�λΪRPM
// ����¶ȵ�λΪ���϶�
void m2006_send_motor_currents(void)
{
	CanTxMsg tx_message;

	// ���ÿ��ƶ�
	tx_message.IDE = CAN_Id_Standard;
	tx_message.RTR = CAN_RTR_Data;
	tx_message.DLC = 0x08;
	
	// �����ٲöκ����ݶ�
	
	tx_message.StdId = 0x200;  // ����IDΪ 1 2 3 4 �ĵ��
	tx_message.Data[0] = (uint8_t)(M3508_CHASSIS_MOTOR_REAL_INFO[0].TARGET_CURRENT >> 8);
	tx_message.Data[1] = (uint8_t) M3508_CHASSIS_MOTOR_REAL_INFO[0].TARGET_CURRENT;
	tx_message.Data[2] = (uint8_t)(M3508_CHASSIS_MOTOR_REAL_INFO[1].TARGET_CURRENT >> 8);
	tx_message.Data[3] = (uint8_t) M3508_CHASSIS_MOTOR_REAL_INFO[1].TARGET_CURRENT;
	tx_message.Data[4] = (uint8_t)(M3508_CHASSIS_MOTOR_REAL_INFO[2].TARGET_CURRENT >> 8);
	tx_message.Data[5] = (uint8_t) M3508_CHASSIS_MOTOR_REAL_INFO[2].TARGET_CURRENT;
	tx_message.Data[6] = (uint8_t)(M3508_CHASSIS_MOTOR_REAL_INFO[3].TARGET_CURRENT >> 8);
	tx_message.Data[7] = (uint8_t) M3508_CHASSIS_MOTOR_REAL_INFO[3].TARGET_CURRENT;
	
	CAN_Transmit(CAN1, &tx_message);
}

void m3508_send_motor_currents(void)
{
	CanTxMsg tx_message;

	// ���ÿ��ƶ�
	tx_message.IDE = CAN_Id_Standard;
	tx_message.RTR = CAN_RTR_Data;
	tx_message.DLC = 0x08;
	
	// �����ٲöκ����ݶ�	
	tx_message.StdId = 0x1ff;  // ����IDΪ 5 6 7 8 �ĵ��
	tx_message.Data[0] = (uint8_t)(M3508_ARM_MOTOR_REAL_INFO.TARGET_CURRENT >> 8);
	tx_message.Data[1] = (uint8_t) M3508_ARM_MOTOR_REAL_INFO.TARGET_CURRENT;
	tx_message.Data[2] = (uint8_t)(M2006_TURN_MOTOR_REAL_INFO.TARGET_CURRENT >> 8);
	tx_message.Data[3] = (uint8_t) M2006_TURN_MOTOR_REAL_INFO.TARGET_CURRENT;


	CAN_Transmit(CAN1, &tx_message);
}

void GM6020_send_motor_currents(void)
{
	CanTxMsg tx_message;

	// ���ÿ��ƶ�
	tx_message.IDE = CAN_Id_Standard;
	tx_message.RTR = CAN_RTR_Data;
	tx_message.DLC = 0x08;
	
	// �����ٲöκ����ݶ�	
	tx_message.StdId = 0x2ff;  // ����IDΪ 5 6 7 8 �ĵ��

	tx_message.Data[2] = (uint8_t)(GM6020_TURN_MOTOR_REAL_INFO.TARGET_CURRENT >> 8)&0xff;
	tx_message.Data[3] = (uint8_t)(GM6020_TURN_MOTOR_REAL_INFO.TARGET_CURRENT)&0xff;
	tx_message.Data[4] = (uint8_t)(GM6020_TURN_MOTOR_REAL_INFO.TARGET_CURRENT >> 8)&0xff;
	tx_message.Data[5] = (uint8_t)(GM6020_TURN_MOTOR_REAL_INFO.TARGET_CURRENT)&0xff;

	CAN_Transmit(CAN1, &tx_message);
}



// ��е�۵���ǶȻ���
void m3508_ARM_angle_integral(M3508_REAL_INFO *M3508_MOTOR)
{
	static uint16_t last_angle = 0;
	static u8 first_enter_flag = 1;
	float delta_pos = 0;
	
	// ��¼��һ�ν���ʱ������
	if(first_enter_flag)
	{
		last_angle = M3508_MOTOR->ANGLE;
		first_enter_flag = 0;
		return;
	}
	
	// ����仯�ĽǶ�
	if(M3508_MOTOR->RPM >= 0)
	{
		if(M3508_MOTOR->ANGLE < last_angle)
		{
			if(abs(8191 + M3508_MOTOR->ANGLE - last_angle) < 1250)  // ��������CAN����ʱ�������ת���ǶȽ����˲�
				delta_pos = ((float)(8191 + M3508_MOTOR->ANGLE - last_angle) / 8191.0f) * (360.0f/19.0f);
		}
		else
		{
			delta_pos = ((float)(M3508_MOTOR->ANGLE - last_angle) / 8191.0f) * (360.0f/19.0f);
		}
		
		// �˲�
		if(delta_pos > 0) 
			M3508_MOTOR->REAL_ANGLE += delta_pos;  // ����
	}
	else if(M3508_MOTOR->RPM < 0)
	{
		if(M3508_MOTOR->ANGLE > last_angle)
		{
			if(abs(8191 - M3508_MOTOR->ANGLE + last_angle) < 1250)  // ��������CAN����ʱ�������ת���ǶȽ����˲�			
				delta_pos = ((float)(8191 - M3508_MOTOR->ANGLE + last_angle) / 8191.0f) * (360.0f/19.0f);
		}	
		else
		{
			delta_pos = ((float)(M3508_MOTOR->ANGLE - last_angle) / 8191.0f) * (360.0f/19.0f);
		}
		
		// �˲�
		if(delta_pos < 0) 
			M3508_MOTOR->REAL_ANGLE += delta_pos;  // ����
	}

	// �洢�Ƕ�ֵ
	last_angle = M3508_MOTOR->ANGLE;

}

// ת�̵���ǶȻ���
void m2006_TURN_MOTOR_angle_integral(M3508_REAL_INFO *M3508_MOTOR)
{
	static uint16_t last_angle = 0;
	static u8 first_enter_flag = 1;
	float delta_pos = 0;
	
	// ��¼��һ�ν���ʱ������
	if(first_enter_flag)
	{
		last_angle = M3508_MOTOR->ANGLE;
		first_enter_flag = 0;
		return;
	}
	
	// ����仯�ĽǶ�
	if(M3508_MOTOR->RPM >= 0)
	{
		if(M3508_MOTOR->ANGLE < last_angle)
		{
			if(abs(8191 + M3508_MOTOR->ANGLE - last_angle) < 1250)  // ��������CAN����ʱ�������ת���ǶȽ����˲�
				delta_pos = ((float)(8191 + M3508_MOTOR->ANGLE - last_angle) / 8191.0f) * ((360.0f*15)/(36.0f*66));
		}
		else
		{
			delta_pos = ((float)(M3508_MOTOR->ANGLE - last_angle) / 8191.0f) * ((360.0f*15)/(36.0f*66));
		}
		
		// �˲�
		if(delta_pos > 0) 
			M3508_MOTOR->REAL_ANGLE += delta_pos;  // ����
	}
	else if(M3508_MOTOR->RPM < 0)
	{
		if(M3508_MOTOR->ANGLE > last_angle)
		{
			if(abs(8191 - M3508_MOTOR->ANGLE + last_angle) < 1250)  // ��������CAN����ʱ�������ת���ǶȽ����˲�			
				delta_pos = ((float)(8191 - M3508_MOTOR->ANGLE + last_angle) / 8191.0f) * ((360.0f*15)/(36.0f*66));
		}	
		else
		{
			  delta_pos = ((float)(M3508_MOTOR->ANGLE - last_angle) / 8191.0f) * ((360.0f*15)/(36.0f*66));
		}
		// �˲�
		if(delta_pos < 0) 
			M3508_MOTOR->REAL_ANGLE += delta_pos;  // ����
	}

	// �洢�Ƕ�ֵ
	last_angle = M3508_MOTOR->ANGLE;

}
