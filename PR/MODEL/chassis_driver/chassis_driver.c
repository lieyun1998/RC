#include "includes.h"


CHASSIS_MOTOR_RPM CHASSIS_MOTOR_RPM_DATA;
ROBOT_TARGET_VELOCITY ROBOT_TARGET_VELOCITY_DATA;

//// ��ʼ�����̵������
//void cd_chassis_driver_init(void)
//{
//	delay_ms(100);
//	CAN_RoboModule_DRV_Reset(0, 0);  // ��0�����������и�λ
//	delay_ms(500);                                     
//	CAN_RoboModule_DRV_Config(0, 0, 1, 0);  // ����Ϊ1ms����һ������ �ر�������λ����
//	delay_ms(50); 
//	CAN_RoboModule_DRV_Mode_Choice(0, 0, Velocity_Mode);  // ѡ������ٶ�ģʽ
//	delay_ms(500);
//}

// 4�ֻ���������ϵ���˶�ѧ
// ��������ϵ
// W����ֵ-��ʱ�� ��ֵ-˳ʱ��
void Robot_4wheels(float Vx_RPM, float Vy_RPM, float W_RPM)
{
	CHASSIS_MOTOR_RPM_DATA.MOTOR1_RPM = (-COS45 * Vx_RPM + SIN45 * Vy_RPM + Robot_R*W_RPM) * MS_TO_RPM;
	CHASSIS_MOTOR_RPM_DATA.MOTOR2_RPM = (-COS45 * Vx_RPM - SIN45 * Vy_RPM + Robot_R*W_RPM) * MS_TO_RPM;
	CHASSIS_MOTOR_RPM_DATA.MOTOR3_RPM = ( COS45 * Vx_RPM - SIN45 * Vy_RPM + Robot_R*W_RPM) * MS_TO_RPM;
	CHASSIS_MOTOR_RPM_DATA.MOTOR4_RPM = ( COS45 * Vx_RPM + SIN45 * Vy_RPM + Robot_R*W_RPM) * MS_TO_RPM;
}


// 4����������ϵ���˶�ѧ
// thetaΪ����������ϵx������������ϵx��н� ��λ����
// W����ֵ-��ʱ�� ��ֵ-˳ʱ��
void World_4wheels(float Vx_RPM, float Vy_RPM, float W_RPM, float theta)
{
	theta = PI * theta / 180.0f;
	CHASSIS_MOTOR_RPM_DATA.MOTOR1_RPM = (-cos(theta-PI/4.0f) * Vx_RPM - sin(theta-PI/4.0f) * Vy_RPM + Robot_R*W_RPM) * M3508_MS_To_RM;
	CHASSIS_MOTOR_RPM_DATA.MOTOR2_RPM = (-cos(theta+PI/4.0f) * Vx_RPM - sin(theta+PI/4.0f) * Vy_RPM + Robot_R*W_RPM) * M3508_MS_To_RM;
	CHASSIS_MOTOR_RPM_DATA.MOTOR3_RPM = ( cos(theta-PI/4.0f) * Vx_RPM + sin(theta-PI/4.0f) * Vy_RPM + Robot_R*W_RPM) * M3508_MS_To_RM;
	CHASSIS_MOTOR_RPM_DATA.MOTOR4_RPM = ( cos(theta+PI/4.0f) * Vx_RPM + sin(theta+PI/4.0f) * Vy_RPM + Robot_R*W_RPM) * M3508_MS_To_RM;
	
}

#if RM3508
// ���Ƶ��̸����ٶ�����ֵ�����ٶ�
void cd_velocity_adjust(void *pdata)
{
	while(1)
	{
//		ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0.2;
//		ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
//		ROBOT_TARGET_VELOCITY_DATA.W_RPM = 0;						

	// �ٶȷֽ�
	World_4wheels(ROBOT_TARGET_VELOCITY_DATA.Vx_RPM,
								ROBOT_TARGET_VELOCITY_DATA.Vy_RPM, 
								ROBOT_TARGET_VELOCITY_DATA.W_RPM,
								ROBOT_REAL_POS_DATA.YAW_POS);
		
//	Robot_4wheels(ROBOT_TARGET_VELOCITY_DATA.Vx_RPM,
//								ROBOT_TARGET_VELOCITY_DATA.Vy_RPM, 
//								ROBOT_TARGET_VELOCITY_DATA.W_RPM);	

	
	// ����PID����
	PID_incremental_PID_calculation(&M3508_CHASSIS_MOTOR_PID_RPM[0], M3508_CHASSIS_MOTOR_REAL_INFO[0].RPM, CHASSIS_MOTOR_RPM_DATA.MOTOR1_RPM);
	PID_incremental_PID_calculation(&M3508_CHASSIS_MOTOR_PID_RPM[1], M3508_CHASSIS_MOTOR_REAL_INFO[1].RPM, CHASSIS_MOTOR_RPM_DATA.MOTOR2_RPM);
	PID_incremental_PID_calculation(&M3508_CHASSIS_MOTOR_PID_RPM[2], M3508_CHASSIS_MOTOR_REAL_INFO[2].RPM, CHASSIS_MOTOR_RPM_DATA.MOTOR3_RPM);
	PID_incremental_PID_calculation(&M3508_CHASSIS_MOTOR_PID_RPM[3], M3508_CHASSIS_MOTOR_REAL_INFO[3].RPM, CHASSIS_MOTOR_RPM_DATA.MOTOR4_RPM);
	
	// ���õ���
	M3508_CHASSIS_MOTOR_REAL_INFO[0].TARGET_CURRENT = M3508_CHASSIS_MOTOR_PID_RPM[0].output;
	M3508_CHASSIS_MOTOR_REAL_INFO[1].TARGET_CURRENT = M3508_CHASSIS_MOTOR_PID_RPM[1].output;
	M3508_CHASSIS_MOTOR_REAL_INFO[2].TARGET_CURRENT = M3508_CHASSIS_MOTOR_PID_RPM[2].output;
	M3508_CHASSIS_MOTOR_REAL_INFO[3].TARGET_CURRENT = M3508_CHASSIS_MOTOR_PID_RPM[3].output;
	

	OSTimeDly(5);
  }
}

#endif

#if RE40
// ���Ƶ��̸����ٶ�����ֵ�����ٶ�
void cd_velocity_adjust(void *pdata)
{
	static u8 can_send_order_flag = 1;


	
//	if(MOVING_STATE == MOVING_ROMOTE)  // ������ң�ؿ����ƶ�״̬ ��ʹ�û���������ϵ
//	{
//		Robot_4wheels(ROBOT_TARGET_VELOCITY_DATA.Vx_RPM,
//																					ROBOT_TARGET_VELOCITY_DATA.Vy_RPM, 
//																					ROBOT_TARGET_VELOCITY_DATA.W_RPM);
//	}
//	else  // �������Զ��ƶ�״̬ ��ʹ����������ϵ
//	{
//		World_4wheels(ROBOT_TARGET_VELOCITY_DATA.Vx_RPM,
//																					ROBOT_TARGET_VELOCITY_DATA.Vy_RPM, 
//																					ROBOT_TARGET_VELOCITY_DATA.W_RPM,
//																					ROBOT_REAL_POS_DATA.YAW_POS);
//	}

//	World_4wheels(ROBOT_TARGET_VELOCITY_DATA.Vx_RPM,
//																				ROBOT_TARGET_VELOCITY_DATA.Vy_RPM, 
//																				ROBOT_TARGET_VELOCITY_DATA.W_RPM,
//																				ROBOT_REAL_POS_DATA.YAW_POS);
//	
   while(1)
   {
    switch(NOW_STATE)
		{
			case MOVING_START_TO_CATCH_1st_BALL_POINT:
			{
				
		    Robot_4wheels(ROBOT_TARGET_VELOCITY_DATA.Vx_RPM,
																					    ROBOT_TARGET_VELOCITY_DATA.Vy_RPM, 
																					    ROBOT_TARGET_VELOCITY_DATA.W_RPM);
				
			}break;
			
			case MOVING_CATCH_1st_BALL_POINT_TO_CATCH_2nd_BALL_POINT:
			{
				
		    Robot_4wheels(ROBOT_TARGET_VELOCITY_DATA.Vx_RPM,
																					    ROBOT_TARGET_VELOCITY_DATA.Vy_RPM, 
																					    ROBOT_TARGET_VELOCITY_DATA.W_RPM);

			}break;
			
			case MOVING_CATCH_2nd_BALL_POINT_TO_CATCH_3rd_BALL_POINT:
			{
				
		    Robot_4wheels(ROBOT_TARGET_VELOCITY_DATA.Vx_RPM,
																					    ROBOT_TARGET_VELOCITY_DATA.Vy_RPM, 
																					    ROBOT_TARGET_VELOCITY_DATA.W_RPM);

			}break;
			
			case MOVING_CATCH_3rd_BALL_POINT_TO_CATCH_4th_BALL_POINT:
			{
				
		    Robot_4wheels(ROBOT_TARGET_VELOCITY_DATA.Vx_RPM,
																					    ROBOT_TARGET_VELOCITY_DATA.Vy_RPM, 
																					    ROBOT_TARGET_VELOCITY_DATA.W_RPM);

			}break;
			
			case MOVING_CATCH_4th_BALL_POINT_TO_CATCH_5th_BALL_POINT:
			{
				
		    Robot_4wheels(ROBOT_TARGET_VELOCITY_DATA.Vx_RPM,
																					    ROBOT_TARGET_VELOCITY_DATA.Vy_RPM, 
																					    ROBOT_TARGET_VELOCITY_DATA.W_RPM);

			}break;
			
			default:
			{
			  World_4wheels(ROBOT_TARGET_VELOCITY_DATA.Vx_RPM,
																				      ROBOT_TARGET_VELOCITY_DATA.Vy_RPM, 
																					    ROBOT_TARGET_VELOCITY_DATA.W_RPM,
																					    ROBOT_REAL_POS_DATA.YAW_POS);
				
			}break;
			
		}
		
	// ������ֵ�����ٶ�
	// ��Ϊ�������ԭ�����ת���������
	CHASSIS_MOTOR_RPM_DATA.MOTOR1_RPM = -CHASSIS_MOTOR_RPM_DATA.MOTOR1_RPM;
	CHASSIS_MOTOR_RPM_DATA.MOTOR2_RPM =  CHASSIS_MOTOR_RPM_DATA.MOTOR2_RPM;
	CHASSIS_MOTOR_RPM_DATA.MOTOR3_RPM = -CHASSIS_MOTOR_RPM_DATA.MOTOR3_RPM;
	CHASSIS_MOTOR_RPM_DATA.MOTOR4_RPM = -CHASSIS_MOTOR_RPM_DATA.MOTOR4_RPM;
	
	
	// ����ָ��
	switch(can_send_order_flag)
	{
		case 1:
		{
			CAN_RoboModule_DRV_Velocity_Mode(0, 1, 5000, CHASSIS_MOTOR_RPM_DATA.MOTOR1_RPM);
			CAN_RoboModule_DRV_Velocity_Mode(0, 2, 5000, CHASSIS_MOTOR_RPM_DATA.MOTOR2_RPM);
			CAN_RoboModule_DRV_Velocity_Mode(0, 3, 5000, CHASSIS_MOTOR_RPM_DATA.MOTOR3_RPM);
			CAN_RoboModule_DRV_Velocity_Mode(0, 4, 5000, CHASSIS_MOTOR_RPM_DATA.MOTOR4_RPM);

			can_send_order_flag = 0;
		}
		break;
		
		case 0:
		{
			CAN_RoboModule_DRV_Velocity_Mode(0, 4, 5000, CHASSIS_MOTOR_RPM_DATA.MOTOR4_RPM);
			CAN_RoboModule_DRV_Velocity_Mode(0, 3, 5000, CHASSIS_MOTOR_RPM_DATA.MOTOR3_RPM);
			CAN_RoboModule_DRV_Velocity_Mode(0, 2, 5000, CHASSIS_MOTOR_RPM_DATA.MOTOR2_RPM);
			CAN_RoboModule_DRV_Velocity_Mode(0, 1, 5000, CHASSIS_MOTOR_RPM_DATA.MOTOR1_RPM);

			can_send_order_flag = 1;			
		}
		break;

		default: break;
	}
	//printf("������� SUCCEEDED\r\n");
	  OSTimeDly(5);
  }
}

#endif
