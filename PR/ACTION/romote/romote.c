#include "includes.h"


void romote_action_task(void)
{
	PS2_update_ps2_command();	 // ����PS2��ָ��
	
	if(ROMOTE_STATE == ROMOTE_START)
	{
		switch(NOW_STATE)
		{
			case ROMOTE_PREPARATION:
			{
				romote_choose_mode();
			}
			break;
			
			case ROMOTE_RELAY:
			{
				romote_control_relay();
			}
			break;
			
			case ROMOTE_SZ:
			{
				romote_control_moving_for_grab();				
			}
			break;

			case ROMOTE_TZ:
			{
				romote_control_moving_for_throw();					
			}
			break;	
			
			default: break;
		}
	}
	
	else if (ROMOTE_STATE == ROMOTE_FREE)
	{
		// ң�ؿ����ƶ�
		switch(PS2_KEY)
		{
			case PSB_PAD_UP:  // �ϼ�ͷ
			{
				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
				ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = -ROMOTE_FREE_Vy;
				ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;
			}
			break;
			
			case PSB_PAD_DOWN:  // �¼�ͷ
			{
				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
				ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = ROMOTE_FREE_Vy;
				ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;				
			}
			break;

			case PSB_PAD_LEFT:  // ���ͷ
			{
				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = ROMOTE_FREE_Vx*K;
				ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
				ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;			
			}
			break;		

			case PSB_PAD_RIGHT:  // �Ҽ�ͷ
			{
				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = (-ROMOTE_FREE_Vx)*K;
				ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
				ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;			
			}
			break;

			case PSB_L1:  // L1
			{
				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
				ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
				ROBOT_TARGET_VELOCITY_DATA.W_RPM  = ROMOTE_FREE_W;			
			}
			break;

			case PSB_R1:  // R1
			{
				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
				ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
				ROBOT_TARGET_VELOCITY_DATA.W_RPM  = -ROMOTE_FREE_W;			
			}
			break;
			
			default:  // δ���¹涨����ʱ 
			{
				// �û�����ֹͣ�ƶ�
				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
				ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
				ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;
			}
			break;
		}
		
		// ����·���л�����
		switch(NOW_STATE)
		{
			case MOVING_START_TO_LINE1:
			{
				moving_select_switch_mode_START_TO_LINE1();  // ѡ��ͬ���л�·����ʽ
			}
			break;

			case MOVING_RZ_TO_SZ:
			{
				moving_select_switch_mode_RZ_TO_SZ(); 
			}
			break;
			
			case MOVING_SZ_TO_WZ:
			{
				moving_select_switch_mode_SZ_TO_WZ();
			}
			break;
			
			case MOVING_WZ_TO_TZ:
			{
				moving_select_switch_mode_WZ_TO_TZ();
			}
			break;
			
			case MOVING_SZ_TO_TZ:
			{
				moving_select_switch_mode_SZ_TO_TZ();
			}
			break;
			
			case MOVING_TZ_TO_SZ:
			{
				moving_select_switch_mode_TZ_TO_SZ();
			}
			break;

			case MOVING_LINE1_TO_SZ:
			{
				moving_select_switch_mode_LINE1_TO_SZ();
			}
			break;
			
			default: break;
		}
		
		// �ж��л����˳�ң��ģʽ
		if((*switch_determine)() == 1)
		{
			// ����PID
			PID_reset_PID(&arc_pid);
			PID_reset_PID(&line_pid);
			PID_reset_PID(&yaw_pid);
			PID_reset_PID(&point_pid);
			PID_reset_PID(&mix_pid);
			
			PATH_POINT_COUNTER = 0;
			MOVING_STATE = MOVING_ARRIVED;  // �л��ƶ�״̬
			
			printf("################## PATH TRACK ARRIVED ##################\r\n");
		}
	}
	
	// һֱ��Ч
	if((PS2_RX < 10)&&(PS2_RY < 10)&&(PS2_KEY == PSB_L2))  // L2 ��ҡ�������ƶ�
	{
		MR2_STATE = ARRIVED;  // MR2���� �û����˼е��޹Ǻ�ֱ��ǰ��Ͷ����
	}
	if(MOVING_STATE == MOVING_GOING)
	{
		if((PS2_RX < 10)&&(PS2_RY < 10)&&(PS2_KEY == PSB_SELECT))  // SELECT ��ҡ�������ƶ�
		{
			MOVING_STATE = MOVING_ROMOTE;  // �л����ֶ�ң���ƶ�
			ROMOTE_STATE = ROMOTE_FREE;
			PATH_POINT_COUNTER = PATH_POINT_SUM-1;
		}
	}
}


/*WAITING_CHANGE*/
void romote_choose_mode(void)
{
	#if TEST_ALL_PATH
	
	// ����λ��ƫ����
	ROBOT_REAL_POS_DATA.X_POS = START_OFFSET_X;
	ROBOT_REAL_POS_DATA.Y_POS = START_OFFSET_Y;
	YAW_OFFSET = START_OFFSET_YAW;
	
	// ����״̬
	OPTAINAL_MODE = MODE_MOVING_START_TO_LINE1;
	MR2_STATE = ARRIVED;  // �û����˼е��޹Ǻ�ֱ��ǰ��Ͷ����
	ROMOTE_STATE = ROMOTE_OVER;
	
	return;
	
	#endif

	switch(PS2_KEY)
	{
		case PSB_SQUARE:  // ���ΰ���
		{
			// ����λ��ƫ����
			#if K == 1
			ROBOT_REAL_POS_DATA.X_POS = START_OFFSET_X*K;
			ROBOT_REAL_POS_DATA.Y_POS = START_OFFSET_Y;
			OFFSET_YAW = START_OFFSET_YAW;	
			#else
			ROBOT_REAL_POS_DATA.X_POS = START_OFFSET_X*K;
			ROBOT_REAL_POS_DATA.Y_POS = START_OFFSET_Y;
			OFFSET_YAW = START_OFFSET_YAW*K;		
			#endif
			
			// ����״̬
			OPTAINAL_MODE = MODE_MOVING_START_TO_LINE1;  // �������������ӵ��ƶ�
			ROMOTE_STATE = ROMOTE_OVER;  // ����ң��״̬	

			printf("################### GO TO MOVING_START_TO_LINE1 ###################\r\n");			
		}
		break;
		
		case PSB_CROSS:  // �水��
		{
			// ����λ��ƫ����
			ROBOT_REAL_POS_DATA.X_POS = LINE1_OFFSET_X*K;
			ROBOT_REAL_POS_DATA.Y_POS = LINE1_OFFSET_Y;
			OFFSET_YAW = LINE1_OFFSET_YAW*K;	

			// ����״̬
			OPTAINAL_MODE = MODE_ROMOTE_RELAY;  // �ӽ���1�����ӵ㣬�����н��Ӷ���
			ROMOTE_STATE = ROMOTE_OVER;  // ����ң��״̬	

			printf("################### GO TO ROMOTE_RELAY ###################\r\n");				
		}
		break;

		case PSB_TRIANGLE:  // ���ǰ���
		{
			// ����λ��ƫ����
			ROBOT_REAL_POS_DATA.X_POS = LINE1_OFFSET_X*K;
			ROBOT_REAL_POS_DATA.Y_POS = LINE1_OFFSET_Y;
			OFFSET_YAW = LINE1_OFFSET_YAW*K;	

			// ����״̬
			OPTAINAL_MODE = MODE_MOVING_LINE1_TO_SZ;  // �ӽ���1���޹�λ��
			ROMOTE_STATE = ROMOTE_OVER;  // ����ң��״̬			

			printf("################### GO TO MOVING_LINE1_TO_SZ ###################\r\n");				
		}
		break;		
		
		default: break;
	}
}


void romote_control_relay(void)
{
	switch(PS2_KEY)
	{
		case PSB_CIRCLE:  // Բ��
		{
			// �û�����ֹͣ�ƶ�
			ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;
			
			RELAY_ACTION_FLAG = 1;
			
			ROMOTE_STATE = ROMOTE_OVER;  // ����ң��״̬	
		}
		break;
		
		default:  // δ���¹涨����ʱ 
		{
			ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = (-RELAY_Vx)*K;
			ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = -RELAY_Vy;
			ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;
		}
		break;
	}
}


void romote_control_moving_for_grab(void)
{
	#if TEST_ALL_PATH
	
	ROMOTE_STATE = ROMOTE_OVER;
	
	return;
	
	#endif
	
	switch(PS2_KEY)
	{
		case PSB_PAD_UP:  // �ϼ�ͷ
		{
			ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = -ROMOTE_SZ_Vy;
			ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;
		}
		break;
		
		case PSB_PAD_DOWN:  // �¼�ͷ
		{
			ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = ROMOTE_SZ_Vy;
			ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;				
		}
		break;

		case PSB_PAD_LEFT:  // ���ͷ
		{
			ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = ROMOTE_SZ_Vx;
			ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;			
		}
		break;		

		case PSB_PAD_RIGHT:  // �Ҽ�ͷ
		{
			ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = -ROMOTE_SZ_Vx;
			ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;			
		}
		break;

		case PSB_L1:  // L1
		{
			ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.W_RPM  = ROMOTE_SZ_W;			
		}
		break;

		case PSB_R1:  // R1
		{
			ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.W_RPM  = -ROMOTE_SZ_W;			
		}
		break;
		
		case PSB_CIRCLE:  // Բ��
		{
			// �û�����ֹͣ�ƶ�
			ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;

			ROMOTE_STATE = ROMOTE_OVER;  // ����ң��״̬	
		}
		break;
		
		default:  // δ���¹涨����ʱ 
		{
			// �û�����ֹͣ�ƶ�
			ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;
		}
		break;
		
		 
	}
}

void romote_control_moving_for_throw(void)
{
	#if TEST_ALL_PATH
	
	ROMOTE_STATE = ROMOTE_OVER;
	
	return;
	
	#endif
	
	switch(PS2_KEY)
	{
		case PSB_PAD_UP:  // �ϼ�ͷ
		{
			ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = ROMOTE_TZ_Vy;
			ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;
		}
		break;
		
		case PSB_PAD_DOWN:  // �¼�ͷ
		{
			ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = -ROMOTE_TZ_Vy;
			ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;				
		}
		break;

		case PSB_PAD_LEFT:  // ���ͷ
		{
			ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = -ROMOTE_TZ_Vx;
			ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;			
		}
		break;		

		case PSB_PAD_RIGHT:  // �Ҽ�ͷ
		{
			ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = ROMOTE_TZ_Vx;
			ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;			
		}
		break;

		case PSB_L1:  // L1
		{
			ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.W_RPM  = ROMOTE_TZ_W;			
		}
		break;

		case PSB_R1:  // R1
		{
			ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.W_RPM  = -ROMOTE_TZ_W;			
		}
		break;

		case PSB_CIRCLE:  // Բ��
		{
			// �û�����ֹͣ�ƶ�
			ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;

			ROMOTE_STATE = ROMOTE_OVER;  // ����ң��״̬	
		}
		break;
		
		default:  // δ���¹涨����ʱ 
		{
			// �û�����ֹͣ�ƶ�
			ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
			ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;
		}
		break;
	}

}
