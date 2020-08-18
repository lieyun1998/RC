#include "includes.h"


// ��ʼ������״ֵ̬
ROBOT_STATE_ITEMS NOW_STATE = ROMOTE_PREPARATION;   //��ʼ״̬Ϊ׼��״̬
       
MOVING_STATE_ITEMS MOVING_STATE = MOVING_STOP;      //�ƶ�ģʽΪ�ƶ�״̬�ر�

CATCH_STATE_ITEMS CATCH_STATE = CATCH_STOP;         //����ģʽΪ����״̬�ر�

THROW_STATE_ITEMS THROW_STATE = THROW_STOP;         //����ģʽΪ����״̬�ر�

KICK_STATE_ITEMS KICK_STATE = KICK_STOP;            //����ģʽΪ����״̬�ر�

ROMOTE_STATE_ITEMS ROMOTE_STATE = ROMOTE_START;     // ��ʼʱ����ң��

OPTAINAL_MODE_ITEMS OPTAINAL_MODE = MODE_UNKNOWN;   //ѡ��ģʽΪδ֪״̬

TURN_RESET_STATE_ITEMS TURN_RESET_STATE = TURN_RESET_START;  // ��ת�̿�����λ

ARM_RESET_STATE_ITEMS ARM_RESET_STATE = ARM_RESET_STOP;        // ��е��צ������λ


// ����״̬��
void FSM_RUN(void *pdata)
{ 
	while(1)
	{
	switch(NOW_STATE)
	{		
		// ͨ��ң��ѡ��ģʽ
		case ROMOTE_PREPARATION:         //ң��ģʽ�¿�ѡ���·��
		{		
			  MOVING_STATE   = MOVING_GOING;  //�ƶ�ģʽ����
				CATCH_STATE    = CATCH_STOP;   //����ģʽ�ر�
				THROW_STATE    = THROW_STOP;   //����ģʽ�ر�
			  KICK_STATE     = KICK_STOP;    //����ģʽ�ر�
			  NOW_STATE = START_TO_BALL_1st;  
			  ROMOTE_STATE = ROMOTE_STOP; 
			  MOVING_STATE = MOVING_GOING;

		}
		break;
		
		case START_TO_BALL_1st:    //��������ǰ�������1
		{

			// �����������1
			if((MOVING_STATE == MOVING_ARRIVED)&&(Read_limit_switch(TURNPLATE_RESET_LIMIT_SWITCH) == RESET)&&(Read_limit_switch(ARM_RESET_LIMIT_SWITCH) == RESET))
			{
				TURN_RESET_STATE = TURN_RESET_STOP;  //��λת�̿���
				MOVING_STATE    = MOVING_STOP;        //�ƶ�ģʽ�ر�
				CATCH_STATE     = CATCH_START;        //����ģʽ����
				THROW_STATE     = THROW_STOP;         //����ģʽ�ر�
				KICK_STATE      = KICK_STOP;          //����ģʽ�ر�
				ROMOTE_STATE    = ROMOTE_STOP;        //ң��ģʽ�ر�
        NOW_STATE       = CATCH_1st_BALL;       //��ǰ״̬Ϊץȡ��1��һ����
			}
		}
		break;
		
			case CATCH_1st_BALL:     //ץȡ��1��һ����
		{
	    //�������ɹ�
			if(CATCH_STATE == CATCH_SUCCEEDED) 				
			{
				TURN_RESET_STATE = TURN_RESET_STOP;  //��λת�̹ر�
				ARM_RESET_STATE = ARM_RESET_START;   //��λ��е�ۿ���
				MOVING_STATE    = MOVING_STOP;       //�ƶ�ģʽ�ر�
				CATCH_STATE     = CATCH_STOP;        //����ģʽ�ر�
				THROW_STATE     = THROW_START;       //����ģʽ����
				KICK_STATE      = KICK_STOP;         //����ģʽ�ر�
				ROMOTE_STATE    = ROMOTE_START;      //ң��ģʽ����
        NOW_STATE       = THROW_1st_BALL;       //��ǰ״̬Ϊ����1��һ����
			}
		}
		break;
		
		case THROW_1st_BALL:      //����1��һ����
		{
			//�������ɹ�
			if(THROW_STATE == THROW_SUCCEEDED)
			{
				TURN_RESET_STATE = TURN_RESET_START; //��λת�̿���
				ARM_RESET_STATE = ARM_RESET_STOP;    //��λ��е�۹ر�				
				MOVING_STATE   = MOVING_STOP;       //�ƶ�ģʽ����
				CATCH_STATE    = CATCH_START;         //����ģʽ����
				THROW_STATE    = THROW_STOP;       //����ģʽ�ر�
				KICK_STATE     = KICK_STOP;          //����ģʽ�ر�
				ROMOTE_STATE   = ROMOTE_STOP;       //ң��ģʽ�ر�
        NOW_STATE      = TO_BALL_2nd;  //��ǰ״̬Ϊ�Ӽ����1�������2
			}
		}
		break;
		
		case TO_BALL_2nd:    //�Ӽ����1�������2
		{
			// ��������ȡ��2
			if((MOVING_STATE == MOVING_ARRIVED)&&(Read_limit_switch(TURNPLATE_RESET_LIMIT_SWITCH) == RESET)&&(Read_limit_switch(PULL_RESET_LIMIT_SWITCH) == RESET))
			{
				TURN_RESET_STATE = TURN_RESET_START;  //��λת�̿���
				ARM_RESET_STATE = ARM_RESET_STOP;   //��λ��е�۹ر�				
				MOVING_STATE   = MOVING_STOP;       //�ƶ�ģʽ�ر�
				CATCH_STATE    = CATCH_START;       //����ģʽ����
				THROW_STATE    = THROW_STOP;        //����ģʽ�ر�
				KICK_STATE     = KICK_STOP;         //����ģʽ�ر�
				ROMOTE_STATE   = ROMOTE_STOP;       //ң��ģʽ�ر�
        NOW_STATE      = CATCH_2nd_BALL;       //��ǰ״̬Ϊץȡ��2��һ����
			}
		}
		break;
		
	  case CATCH_2nd_BALL:       //ץȡ��2��һ����
		{
	    //�������ɹ�
			if((CATCH_STATE == CATCH_SUCCEEDED)&&(Read_limit_switch(TURNPLATE_RESET_LIMIT_SWITCH) == RESET)&&(Read_limit_switch(PULL_RESET_LIMIT_SWITCH) == RESET))   
			{
				TURN_RESET_STATE = TURN_RESET_STOP;  //��λת�̹ر�
				ARM_RESET_STATE = ARM_RESET_START;   //��λ��е�ۿ���
				MOVING_STATE   = MOVING_STOP;        //�ƶ�ģʽ�ر�
				CATCH_STATE    = CATCH_STOP;         //����ģʽ�ر�
				THROW_STATE    = THROW_START;        //����ģʽ����
				KICK_STATE     = KICK_STOP;          //����ģʽ�ر�
				ROMOTE_STATE   = ROMOTE_STOP;        //ң��ģʽ�ر�
        NOW_STATE      = THROW_2nd_BALL;  //��ǰ״̬Ϊ����2��һ����
			}
		}
		break;
		
		case THROW_2nd_BALL:     //����2��һ����   
		{
			// �������ɹ�
			if((THROW_STATE == THROW_SUCCEEDED)&&(ARM_RESET_STATE == ARM_RESET_SUCCEEDED))
			{
				TURN_RESET_STATE = TURN_RESET_START;  //��λת�̿���
				ARM_RESET_STATE = ARM_RESET_START;     //��λ��е�ۿ�ʼ
				MOVING_STATE   = MOVING_GOING;        //�ƶ�ģʽ����
				CATCH_STATE    = CATCH_STOP;          //����ģʽ����
				THROW_STATE    = THROW_STOP;          //����ģʽ�ر�
				KICK_STATE     = KICK_STOP;           //����ģʽ�ر�
				ROMOTE_STATE   = ROMOTE_START;        //ң��ģʽ�ر�
        NOW_STATE      = TO_BALL_3rd;//��ǰ״̬Ϊ�Ӽ����2�������3
			}
		}
		break;
		
    case TO_BALL_3rd://�Ӽ����2�������3
		{
			// �����������3
			if((MOVING_STATE == MOVING_ARRIVED)&&(Read_limit_switch(TURNPLATE_RESET_LIMIT_SWITCH) == RESET)&&(Read_limit_switch(PULL_RESET_LIMIT_SWITCH) == RESET))
			{
				TURN_RESET_STATE = TURN_RESET_START; //��λת�̹ر�
				ARM_RESET_STATE = ARM_RESET_STOP;    //��λ��е�۹ر�				
				MOVING_STATE   = MOVING_STOP;        //�ƶ�ģʽ�ر�
//				MOVING_STATE   = MOVING_GOING;     //�ƶ�ģʽ����
				CATCH_STATE    = CATCH_START;        //����ģʽ����
				THROW_STATE    = THROW_STOP;         //����ģʽ�ر�
				KICK_STATE     = KICK_STOP;          //����ģʽ�ر�
				ROMOTE_STATE   = ROMOTE_STOP;        //ң��ģʽ�ر�
				NOW_STATE      = CATCH_3rd_BALL;     //ץȡ��3��һ����
			}
		}
		break; 
		
		case CATCH_3rd_BALL:                     //��ǰ״̬Ϊץȡ��1��һ����
		{
	    //�������ɹ�
			if(CATCH_STATE == CATCH_SUCCEEDED)   
			{
				TURN_RESET_STATE = TURN_RESET_STOP;  //��λת�̹ر�
				ARM_RESET_STATE = ARM_RESET_START;   //��λ��е�ۿ���
				MOVING_STATE   = MOVING_STOP;        //�ƶ�ģʽ�ر�
				CATCH_STATE    = CATCH_STOP;         //����ģʽ����
				THROW_STATE    = THROW_START;        //����ģʽ�ر�
				KICK_STATE     = KICK_STOP;          //����ģʽ�ر�
				ROMOTE_STATE   = ROMOTE_STOP;        //ң��ģʽ�ر�
        NOW_STATE      = BALL_3st_TO_PASS_3rd;  //��ǰ״̬Ϊ����3��һ����
			}
		}
		break;
		
		case BALL_3st_TO_PASS_3rd:                 //��ǰ״̬Ϊץȡ��1��һ����
		{
	    //�������ɹ�
			if(CATCH_STATE == CATCH_SUCCEEDED)   
			{
				TURN_RESET_STATE = TURN_RESET_STOP; //��λת�̹ر�
				ARM_RESET_STATE = ARM_RESET_START;   //��λ��е�ۿ���
				MOVING_STATE   = MOVING_STOP;        //�ƶ�ģʽ�ر�
				CATCH_STATE    = CATCH_STOP;         //����ģʽ����
				THROW_STATE    = THROW_START;        //����ģʽ�ر�
				KICK_STATE     = KICK_STOP;          //����ģʽ�ر�
				ROMOTE_STATE   = ROMOTE_STOP;        //ң��ģʽ�ر�
        NOW_STATE      = THROW_3rd_BALL;  //��ǰ״̬Ϊ����3��һ����
			}
		}
		break;
		
		case THROW_3rd_BALL:     //����3��һ����
		{
			// �������ɹ�
			if((THROW_STATE == THROW_SUCCEEDED)&&(ARM_RESET_STATE == ARM_RESET_SUCCEEDED))
			{	
				TURN_RESET_STATE = TURN_RESET_START; //��λת�̿���
				ARM_RESET_STATE = ARM_RESET_START;    //��λ��е�۹ر�				
				MOVING_STATE   = MOVING_GOING;       //�ƶ�ģʽ����
				CATCH_STATE    = CATCH_STOP;         //����ģʽ����
				THROW_STATE    = THROW_STOP;         //����ģʽ�ر�
				KICK_STATE     = KICK_STOP;          //����ģʽ�ر�
				ROMOTE_STATE   = ROMOTE_STOP;        //ң��ģʽ�ر�
        NOW_STATE      = TO_BALL_4th;//��ǰ״̬Ϊ�Ӽ����3�������4
			}
		}
		break;
		
		case TO_BALL_4th://�Ӽ����3�������4
		{
			// �����������4
			if((MOVING_STATE == MOVING_ARRIVED)&&(Read_limit_switch(TURNPLATE_RESET_LIMIT_SWITCH) == RESET)&&(Read_limit_switch(PULL_RESET_LIMIT_SWITCH) == RESET))
			{			
				TURN_RESET_STATE = TURN_RESET_START;  //��λת�̹ر�
				ARM_RESET_STATE = ARM_RESET_STOP;    //��λ��е�۹ر�				
				MOVING_STATE   = MOVING_STOP;        //�ƶ�ģʽ�ر�
				CATCH_STATE    = CATCH_START;        //����ģʽ����
				THROW_STATE    = THROW_STOP;         //����ģʽ�ر�
				KICK_STATE     = KICK_STOP;          //����ģʽ�ر�
				ROMOTE_STATE   = ROMOTE_STOP;        //ң��ģʽ�ر�
				NOW_STATE      = CATCH_4th_BALL;  //��ǰ״̬Ϊץȡ��4��һ����
			}
		}
		break;
		
			case CATCH_4th_BALL:    //ץȡ��4��һ����
		{
	    //�������ɹ�
			if(CATCH_STATE == CATCH_SUCCEEDED)   
			{
				TURN_RESET_STATE = TURN_RESET_STOP; //��λת�̹ر�
        ARM_RESET_STATE = ARM_RESET_START;   //��λ��е�ۿ���
				MOVING_STATE   = MOVING_STOP;       //�ƶ�ģʽ�ر�
				CATCH_STATE    = CATCH_STOP;        //����ģʽ�ر�
				THROW_STATE    = THROW_START;       //����ģʽ����
				KICK_STATE     = KICK_STOP;         //����ģʽ�ر�
				ROMOTE_STATE   = ROMOTE_START;      //ң��ģʽ����
        NOW_STATE      = BALL_4th_TO_PASS_4th;       //��ǰ״̬Ϊ����4��һ����
			}
		}
		break;
		
			case BALL_4th_TO_PASS_4th:    //ץȡ��4��һ����
		{
	    //�������ɹ�
			if(CATCH_STATE == CATCH_SUCCEEDED)   
			{
				TURN_RESET_STATE = TURN_RESET_STOP; //��λת�̹ر�
        ARM_RESET_STATE = ARM_RESET_START;   //��λ��е�ۿ���
				MOVING_STATE   = MOVING_STOP;       //�ƶ�ģʽ�ر�
				CATCH_STATE    = CATCH_STOP;        //����ģʽ�ر�
				THROW_STATE    = THROW_START;       //����ģʽ����
				KICK_STATE     = KICK_STOP;         //����ģʽ�ر�
				ROMOTE_STATE   = ROMOTE_START;      //ң��ģʽ����
        NOW_STATE      = THROW_4th_BALL;       //��ǰ״̬Ϊ����4��һ����
			}
		}
		break;
		
		case THROW_4th_BALL:
		{
			// �������ɹ�
			if((THROW_STATE == THROW_SUCCEEDED)&&(ARM_RESET_STATE == ARM_RESET_SUCCEEDED))
			{
				TURN_RESET_STATE = TURN_RESET_START;  //��λת�̿���
				ARM_RESET_STATE = ARM_RESET_START;     //��λ��е�۹ر�				
				MOVING_STATE   = MOVING_GOING;        //�ƶ�ģʽ����
				CATCH_STATE    = CATCH_STOP;          //����ģʽ����
				THROW_STATE    = THROW_STOP;          //����ģʽ�ر�
				KICK_STATE     = KICK_STOP;           //����ģʽ�ر�
//				ROMOTE_STATE   = ROMOTE_START;        //ң��ģʽ����
        NOW_STATE      = PASS_4th_TO_START;//��ǰ״̬Ϊ׼��״̬������ң��ģʽ
			}
		}
		break;
		
		case PASS_4th_TO_START://�Ӽ����4ǰ��������
		{
			// �������������
			if(MOVING_STATE == MOVING_ARRIVED)
			{
				TURN_RESET_STATE = TURN_RESET_STOP; //��λת�̹ر�
				ARM_RESET_STATE = ARM_RESET_STOP;   //��λ��е�۹ر�				
				MOVING_STATE   = MOVING_STOP;       //�ƶ�ģʽ�ر�
				CATCH_STATE    = CATCH_STOP;        //����ģʽ�ر�
				THROW_STATE    = THROW_STOP;        //����ģʽ�ر�
				KICK_STATE     = KICK_STOP;         //����ģʽ�ر�
				ROMOTE_STATE   = ROMOTE_START;      //ң��ģʽ����
				NOW_STATE      = START_TO_1st_KICK;//��������ǰ��2����������
			}
		}
		break;
		
		case START_TO_1st_KICK:    //��������ǰ�������5�����ֽ����в��������������ң��ѡ��
		{
			// �����������5
			if((MOVING_STATE == MOVING_ARRIVED)&&(Read_limit_switch(TURNPLATE_RESET_LIMIT_SWITCH) == RESET)&&(Read_limit_switch(PULL_RESET_LIMIT_SWITCH) == RESET))
			{
				TURN_RESET_STATE = TURN_RESET_START; //��λת�̹ر�
				ARM_RESET_STATE = ARM_RESET_STOP;   //��λ��е�۹ر�				
				MOVING_STATE   = MOVING_STOP;       //�ƶ�ģʽ�ر�
				CATCH_STATE    = CATCH_START;       //����ģʽ����
				THROW_STATE    = THROW_STOP;        //����ģʽ�ر�
				KICK_STATE     = KICK_STOP;         //����ģʽ�ر�
				ROMOTE_STATE   = ROMOTE_STOP;       //ң��ģʽ�ر�
        NOW_STATE      = KICK_1st;       //��ǰ״̬Ϊץȡ��5��һ����
			}
		}
		break;
		
			case KICK_1st:    //��ǰ״̬Ϊץȡ��5��һ����
		{
	    //�������ɹ�
			if(CATCH_STATE == CATCH_SUCCEEDED)   
			{
				TURN_RESET_STATE = TURN_RESET_STOP;   //��λת�̹ر�
        ARM_RESET_STATE = ARM_RESET_START;    //��λ��е�ۿ���
				MOVING_STATE    = MOVING_STOP;        //�ƶ�ģʽ�ر�
				CATCH_STATE     = CATCH_STOP;         //����ģʽ�ر�
				THROW_STATE     = THROW_START;        //����ģʽ����
				KICK_STATE      = KICK_STOP;          //����ģʽ�ر�
				ROMOTE_STATE    = ROMOTE_START;       //ң��ģʽ����
        NOW_STATE       = KICK_1st_TO_START;  //��ǰ״̬Ϊ����5��һ����
			}
		}
		break;
		
		case KICK_1st_TO_START:
		{
			//�������ɹ�
			if((THROW_STATE == THROW_SUCCEEDED)&&(ARM_RESET_STATE == ARM_RESET_SUCCEEDED))
			{
				TURN_RESET_STATE = TURN_RESET_START;  //��λת�̿���
				ARM_RESET_STATE = ARM_RESET_START;     //��λ��е�۹ر�				
				MOVING_STATE   = MOVING_GOING;        //�ƶ�ģʽ����
				CATCH_STATE    = CATCH_STOP;          //����ģʽ����
				THROW_STATE    = THROW_STOP;          //����ģʽ�ر�
				KICK_STATE     = KICK_STOP;           //����ģʽ�ر�
				ROMOTE_STATE   = ROMOTE_START;        //ң��ģʽ�ر�
   			NOW_STATE      = START_TO_2nd_KICK;  //��ǰ״̬Ϊ�Ӽ����5��������
			}
		}
		break;
		
		case START_TO_2nd_KICK://�Ӽ����5��������
		{
			// �������������
			if(MOVING_STATE == MOVING_ARRIVED)
			{
        TURN_RESET_STATE = TURN_RESET_STOP;   //��λת�̹ر�
				ARM_RESET_STATE = ARM_RESET_STOP;   //��λ��е�۹ر�				
				MOVING_STATE   = MOVING_STOP;       //�ƶ�ģʽ�ر�
				CATCH_STATE    = CATCH_STOP;        //����ģʽ�ر�
				THROW_STATE    = THROW_STOP;        //����ģʽ�ر�
				KICK_STATE     = KICK_STOP;         //����ģʽ�ر�
				ROMOTE_STATE   = ROMOTE_STOP;       //ң��ģʽ�ر�
				NOW_STATE      = KICK_2nd;          //��ǰ״̬Ϊ����
			}
		}
		
		case KICK_2nd:
		{
			// �������������2����
			if(MOVING_STATE == MOVING_ARRIVED)
			{
				TURN_RESET_STATE = TURN_RESET_STOP;   //��λת�̹ر�
				ARM_RESET_STATE = ARM_RESET_STOP;     //��λ��е�۹ر�				
				MOVING_STATE   = MOVING_STOP;         //�ƶ�ģʽ�ر�
//				MOVING_STATE   = MOVING_GOING;       //�ƶ�ģʽ����
				CATCH_STATE    = CATCH_STOP;          //����ģʽ�ر�
				THROW_STATE    = THROW_STOP;          //����ģʽ�ر�
				KICK_STATE     = KICK_START;          //����ģʽ����
				ROMOTE_STATE   = ROMOTE_START;        //ң��ģʽ����
				NOW_STATE      = TO_BALL_5th;      //��ǰ״̬Ϊ��2������������
			}
		}
		break;
		
		case TO_BALL_5th:  //��2������������
		{
			// �������ɹ�
			if(KICK_STATE == KICK_SUCCEEDED)
			{
				TURN_RESET_STATE = TURN_RESET_STOP;   //��λת�̹ر�
				ARM_RESET_STATE = ARM_RESET_STOP;     //��λ��е�۹ر�				
				MOVING_STATE   = MOVING_GOING;        //�ƶ�ģʽ����
				CATCH_STATE    = CATCH_STOP;          //����ģʽ�ر�
				THROW_STATE    = THROW_STOP;          //����ģʽ�ر�
				KICK_STATE     = KICK_STOP;           //����ģʽ�ر�
				ROMOTE_STATE   = ROMOTE_STOP;         //ң��ģʽ�ر�
				NOW_STATE      = CATCH_5th_BALL;  //��ǰ״̬Ϊ��2��������ǰ��������
			}
		}
		break;
		
		case CATCH_5th_BALL: //��2��������ǰ��������
		{
			// �������������
			if(MOVING_STATE == MOVING_ARRIVED)
			{
				TURN_RESET_STATE = TURN_RESET_STOP;   //��λת�̹ر�
				ARM_RESET_STATE = ARM_RESET_STOP;     //��λ��е�۹ر�				
				MOVING_STATE   = MOVING_STOP;         //�ƶ�ģʽ�ر�
				CATCH_STATE    = CATCH_STOP;          //����ģʽ�ر�
				THROW_STATE    = THROW_STOP;          //����ģʽ�ر�
				KICK_STATE     = KICK_STOP;           //����ģʽ�ر�
				ROMOTE_STATE   = ROMOTE_START;        //ң��ģʽ����
				NOW_STATE      = BALL_5th_TO_PASS_5th;//��ǰ״̬Ϊң��ģʽ
			}
		}
		break;
		
		case BALL_5th_TO_PASS_5th:  //��������ǰ��3��������
		{
			// �������3��������
			if(MOVING_STATE == MOVING_ARRIVED)
			{
				TURN_RESET_STATE = TURN_RESET_STOP;   //��λת�̹ر�
				ARM_RESET_STATE = ARM_RESET_STOP;     //��λ��е�۹ر�				
				MOVING_STATE   = MOVING_STOP;         //�ƶ�ģʽ�ر�
				CATCH_STATE    = CATCH_STOP;          //����ģʽ�ر�
				THROW_STATE    = THROW_STOP;          //����ģʽ�ر�
				KICK_STATE     = KICK_START;          //����ģʽ����
				ROMOTE_STATE   = ROMOTE_STOP;         //ң��ģʽ�ر�
				NOW_STATE      = THROW_5th_BALL;  //��ǰ״̬Ϊ��3������������
			}
		}
		break;
		
		case THROW_5th_BALL://��3������������
		{
			// �������ɹ�
			if(MOVING_STATE == MOVING_ARRIVED)
			{
				TURN_RESET_STATE = TURN_RESET_STOP;   //��λת�̹ر�
				ARM_RESET_STATE = ARM_RESET_STOP;     //��λ��е�۹ر�				
				MOVING_STATE   = MOVING_STOP;         //�ƶ�ģʽ�ر�
				CATCH_STATE    = CATCH_STOP;          //����ģʽ�ر�
				THROW_STATE    = THROW_STOP;          //����ģʽ�ر�
				KICK_STATE     = KICK_STOP;           //����ģʽ�ر�
				ROMOTE_STATE   = ROMOTE_STOP;         //ң��ģʽ�ر�
				NOW_STATE      = ROMOTE_PREPARATION;  //��������
			}
		}
		break;
		
		default: break;
	}
	  OSTimeDly(2);
  }
}

