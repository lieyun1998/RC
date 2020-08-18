#include "includes.h"


ROBOT_STATE_ITEMS ROBOT = {0};

float INIT_POS;
float INIT_X;
float INIT_Y;
void FSM_RUN(void *pdata)
{
	while(1)
	{
	  switch(ROBOT.NOW_STATE)
	  {
		   case ROBOT_INIT:
		   {		
				 	TIM12->CCR1 = 0;
			    TIM12->CCR2 = 0;
			    INIT_POS = robot.turn;
				  
			    OSTimeDly(100);
				 	cylinder_off(CATCH_BALL_1ST);
					OSTimeDly(300);
					ROBOT.SHOOTSTATE = THROW_START;	
			    ROBOT.NOW_STATE = ROMOTE_PREPARATION;
		   }
		   break;
		   case ROMOTE_PREPARATION:
		   {
				 TURNPLATE_adjusting(-45.1);
		      if(Get_KEY(START_KEY))
		      {
							TIM12->CCR1 = 1300;
							TIM12->CCR2 = 1300;
							OSTimeDly(1000);
							TIM12->CCR1 = 1147;
							TIM12->CCR2 = 1147;
						  OSTimeDly(1000);
						  OSTimeDly(1000);

              ROBOT.NOW_STATE  = START_TO_BALL_1st;
				      ROBOT.MOVE_STATE = MOVING;
						  ROBOT.SHOOTSTATE = THROW_RESET;//�ֱ۸�λ
							OSTimeDly(100);
							cylinder_on(CATCH_BALL_1ST);//�ſ���צ
						  INIT_X = ROBOT_REAL_POS_DATA.X_POS;
						  INIT_Y = ROBOT_REAL_POS_DATA.Y_POS;
		      }
					if(Get_KEY(Cheak_KEY))
					{
						 ROBOT.NOW_STATE = ROMOTE_START;
				 
					}
					if(Get_KEY(TO_1st_KICK_KEY))
		      {
						 ROBOT.NOW_STATE = START_TO_1st_KICK;
						 ROBOT.MOVE_STATE = MOVING;
		      }
					if(Get_KEY(KICK_START_KEY))
					{
						 ROBOT.NOW_STATE = KICK_1st;
						 ROBOT.MOVE_STATE = STOP;
					}
			 }
			 break;
		
		   case ROMOTE_START:
			 {
	
			 }
			 break;
		
			 case START_TO_BALL_1st:
			 { 
		 
				  if(ROBOT.MOVE_STATE == ARRIVE)//����λ��
				  {
							ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;//ͣ��
							ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
							ROBOT_TARGET_VELOCITY_DATA.W_RPM 	= 0;
							TIM12->CCR1 = 1147;
							TIM12->CCR2 = 1147;
							cylinder_off(CATCH_BALL_1ST);
							OSTimeDly(500);

							ROBOT.NOW_STATE = THROW_1st_BALL;//���м�����

							ROBOT.SHOOTSTATE = THROW_START;		
					}
					else
					{
			 		TURNPLATE_adjusting(-45.1);
					}
			 }
			 break;
		
			 case THROW_1st_BALL:
			 {
				  if(ROBOT.SHOOTSTATE == THROW_SUCCEEDED)
				  { 
						  TIM12->CCR1 = 1152;
							TIM12->CCR2 = 1152;
							ROBOT.NOW_STATE = TO_BALL_2nd;
							ROBOT.MOVE_STATE = MOVING;

							ROBOT.SHOOTSTATE = THROW_RESET;//�ֱ۸�λ
							OSTimeDly(100);
							cylinder_on(CATCH_BALL_1ST);//�ſ���צ
						  INIT_X = ROBOT_REAL_POS_DATA.X_POS;
						  INIT_Y = ROBOT_REAL_POS_DATA.Y_POS;
				  }	

			 }
			 break;
		
			 case TO_BALL_2nd:
			 {
				  
				  if(ROBOT.MOVE_STATE == ARRIVE )//����λ��
				  {
				 	    TIM12->CCR1 = 1160;
							TIM12->CCR2 = 1160;
							ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;//ͣ��
							ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
							ROBOT_TARGET_VELOCITY_DATA.W_RPM 	= 0;
    
							if(ROBOT.SHOOTSTATE == THROW_RESET_SUCCEEDED)//�ֱ۸�λ��
							{
									ROBOT.NOW_STATE = THROW_2nd_BALL;//���м�����
									cylinder_off(CATCH_BALL_1ST);
									OSTimeDly(500);
									ROBOT.SHOOTSTATE = THROW_START;
							}
				  }
					else
					{
					    TURNPLATE_adjusting(47.1);
					}
			 }
			 break;
			
			 case THROW_2nd_BALL:
			 {
				  if(ROBOT.SHOOTSTATE == THROW_SUCCEEDED)//�������
				  {
							ROBOT.NOW_STATE = TO_BALL_3rd;//ȥ������������
							ROBOT.MOVE_STATE = MOVING;

							ROBOT.SHOOTSTATE = THROW_RESET;//�ֱ۸�λ
							OSTimeDly(100);
							cylinder_on(CATCH_BALL_1ST);//�ſ���צ
							INIT_X = ROBOT_REAL_POS_DATA.X_POS;
						  INIT_Y = ROBOT_REAL_POS_DATA.Y_POS;
				  }				
			 }	
			 break;
		
		
			 case TO_BALL_3rd:
			 {
				  
				  if(ROBOT.MOVE_STATE == ARRIVE)//����λ��
				  {
				  	  TIM12->CCR1 = 1160;
							TIM12->CCR2 = 1160;
							ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;//ͣ��
							ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
							ROBOT_TARGET_VELOCITY_DATA.W_RPM 	= 0;
        
							if(ROBOT.SHOOTSTATE == THROW_RESET_SUCCEEDED)//�ֱ۸�λ��
							{
									ROBOT.NOW_STATE = THROW_3rd_BALL;//���м�����
									cylinder_off(CATCH_BALL_1ST);
									OSTimeDly(500);
									ROBOT.SHOOTSTATE = THROW_START;	
							}
				  }
					else
					{
					    TURNPLATE_adjusting(-45.3);
					}								
			 }
			 break;
	
			 case THROW_3rd_BALL:
			 {
				  if(ROBOT.SHOOTSTATE == THROW_SUCCEEDED)
				  {
							ROBOT.NOW_STATE = TO_BALL_4th;
							ROBOT.MOVE_STATE = MOVING;

							ROBOT.SHOOTSTATE = THROW_RESET;//�ֱ۸�λ
							OSTimeDly(100);
							cylinder_on(CATCH_BALL_1ST);//�ſ���צ
							INIT_X = ROBOT_REAL_POS_DATA.X_POS;
						  INIT_Y = ROBOT_REAL_POS_DATA.Y_POS;
				  }	
			 }
			 break;
		
			 case TO_BALL_4th:
			 {
					if(ROBOT.MOVE_STATE == ARRIVE)//����λ��
					{
							TIM12->CCR1 = 1160;
							TIM12->CCR2 = 1160;
						  ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;//ͣ��
							ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
							ROBOT_TARGET_VELOCITY_DATA.W_RPM 	= 0;
        

							if(ROBOT.SHOOTSTATE == THROW_RESET_SUCCEEDED)//�ֱ۸�λ��
							{
									ROBOT.NOW_STATE = THROW_4th_BALL;//���м�����
									cylinder_off(CATCH_BALL_1ST);
									OSTimeDly(500);
									ROBOT.SHOOTSTATE = THROW_START;		
							}
			    }
					else
					{
					    TURNPLATE_adjusting(47.5);
					}

		   }
	     break;
		
		   case THROW_4th_BALL:
		   {
				 
			    if(ROBOT.SHOOTSTATE == THROW_SUCCEEDED)
			    {
						  ROBOT.NOW_STATE = TO_BALL_5th;
						  ROBOT.MOVE_STATE = MOVING;

							ROBOT.SHOOTSTATE = THROW_RESET;//�ֱ۸�λ
							OSTimeDly(100);
							cylinder_on(CATCH_BALL_1ST);//�ſ���צ
				 		  INIT_X = ROBOT_REAL_POS_DATA.X_POS;
						  INIT_Y = ROBOT_REAL_POS_DATA.Y_POS;
			    }	

			 }
			 break;
		
			 case TO_BALL_5th:
			 {
				 
				  if(ROBOT.MOVE_STATE == ARRIVE)//����λ��
				  {	 
							ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;//ͣ��
							ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
							ROBOT_TARGET_VELOCITY_DATA.W_RPM 	= 0;
					

							if(ROBOT.SHOOTSTATE == THROW_RESET_SUCCEEDED)//�ֱ۸�λ��
							{
									ROBOT.NOW_STATE = THROW_5th_BALL;//���м�����
									cylinder_off(CATCH_BALL_1ST);
									OSTimeDly(500);
									ROBOT.SHOOTSTATE = THROW_START;	
							}	
					}
					else
					{
					    TURNPLATE_adjusting(-45.3);
					}
			 }
			 break;
		
			 case THROW_5th_BALL:
			 {
					if(ROBOT.SHOOTSTATE == THROW_SUCCEEDED)
					{
							TIM12->CCR1 = 1160;
							TIM12->CCR2 = 1160;
							ROBOT.NOW_STATE = TO_BALL_6th;
							ROBOT.MOVE_STATE = MOVING;
							INIT_X = ROBOT_REAL_POS_DATA.X_POS;
						  INIT_Y = ROBOT_REAL_POS_DATA.Y_POS;
							ROBOT.SHOOTSTATE = THROW_RESET;//�ֱ۸�λ
							OSTimeDly(100);
							cylinder_on(CATCH_BALL_1ST);//�ſ���צ
			
					}
		
			 }
			 break;
		
			 case TO_BALL_6th:
			 { 			  
					if(ROBOT.MOVE_STATE == ARRIVE)//����λ��
					{
							ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;//ͣ��
							ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
							ROBOT_TARGET_VELOCITY_DATA.W_RPM 	= 0;


							if(ROBOT.SHOOTSTATE == THROW_RESET_SUCCEEDED)//�ֱ۸�λ��
							{
									ROBOT.NOW_STATE = THROW_6th_BALL;//���м�����
									cylinder_off(CATCH_BALL_1ST);
									OSTimeDly(500);
									ROBOT.SHOOTSTATE = THROW_START;						
							}
					}
					else
					{
					    TURNPLATE_adjusting(47.3);
					}					
			 }
			 break;
		
			 case THROW_6th_BALL:
			 {
					if(ROBOT.SHOOTSTATE == THROW_SUCCEEDED)
					{	
							TIM12->CCR1 = 1160;
							TIM12->CCR2 = 1160;
							ROBOT.NOW_STATE = TO_BALL_7th;
							ROBOT.MOVE_STATE = MOVING;

							ROBOT.SHOOTSTATE = THROW_RESET;//�ֱ۸�λ
							OSTimeDly(100);
							cylinder_on(CATCH_BALL_1ST);//�ſ���צ						
							INIT_X = ROBOT_REAL_POS_DATA.X_POS;
							INIT_Y = ROBOT_REAL_POS_DATA.Y_POS;	
					}
		
			 }
			 break;
		
			 case TO_BALL_7th:
			 { 
				  
					if(ROBOT.MOVE_STATE == ARRIVE)//����λ��
					{
							ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;//ͣ��
							ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
							ROBOT_TARGET_VELOCITY_DATA.W_RPM 	= 0;


							if(ROBOT.SHOOTSTATE == THROW_RESET_SUCCEEDED)//�ֱ۸�λ��
							{
									ROBOT.NOW_STATE = THROW_7th_BALL;//���м�����
									cylinder_off(CATCH_BALL_1ST);
									OSTimeDly(500);
									ROBOT.SHOOTSTATE = THROW_START;						
							}
					}
					else
					{
					    TURNPLATE_adjusting(-45.3);
					}					
			 }
			 break;
				 
			 case THROW_7th_BALL:
			 {
				  if(ROBOT.SHOOTSTATE == THROW_SUCCEEDED)
				  { 
						  TIM12->CCR1 = 1160;
							TIM12->CCR2 = 1160;
							ROBOT.NOW_STATE = TO_BALL_8th;
							ROBOT.MOVE_STATE = MOVING;

							ROBOT.SHOOTSTATE = THROW_RESET;//�ֱ۸�λ
							OSTimeDly(100);
							cylinder_on(CATCH_BALL_1ST);//�ſ���צ
						  INIT_X = ROBOT_REAL_POS_DATA.X_POS;
						  INIT_Y = ROBOT_REAL_POS_DATA.Y_POS;
				  }	

			 }
			 break;
		
			 case TO_BALL_8th:
			 {
				  if(ROBOT.MOVE_STATE == ARRIVE)//����λ��
				  {
				
							ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;//ͣ��
							ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
							ROBOT_TARGET_VELOCITY_DATA.W_RPM 	= 0;

							if(ROBOT.SHOOTSTATE == THROW_RESET_SUCCEEDED)//�ֱ۸�λ��
							{
									ROBOT.NOW_STATE = THROW_8th_BALL;//���м�����
									cylinder_off(CATCH_BALL_1ST);
									OSTimeDly(500);
									ROBOT.SHOOTSTATE = THROW_START;
							}
				  }
					else
					{
					    TURNPLATE_adjusting(47.3);
					}
			 }
			 break;
			
			 case THROW_8th_BALL:
			 {
				  if(ROBOT.SHOOTSTATE == THROW_SUCCEEDED)//�������
				  {
							TIM12->CCR1 = 1160;
							TIM12->CCR2 = 1160;
							ROBOT.NOW_STATE = TO_BALL_9th;//ȥ������������
							ROBOT.MOVE_STATE = MOVING;

							ROBOT.SHOOTSTATE = THROW_RESET;//�ֱ۸�λ
							OSTimeDly(100);
							cylinder_on(CATCH_BALL_1ST);//�ſ���צ
							INIT_X = ROBOT_REAL_POS_DATA.X_POS;
						  INIT_Y = ROBOT_REAL_POS_DATA.Y_POS;
				  }				
			 }	
			 break;
		
		
			 case TO_BALL_9th:
			 {
				  if(ROBOT.MOVE_STATE == ARRIVE)//����λ��
				  {
              TIM12->CCR1 = 1160;
							TIM12->CCR2 = 1160;
							ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;//ͣ��
							ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
							ROBOT_TARGET_VELOCITY_DATA.W_RPM 	= 0;
        

							if(ROBOT.SHOOTSTATE == THROW_RESET_SUCCEEDED)//�ֱ۸�λ��
							{
									ROBOT.NOW_STATE = THROW_9th_BALL;//���м�����
									cylinder_off(CATCH_BALL_1ST);
									OSTimeDly(500);
									ROBOT.SHOOTSTATE = THROW_START;	
							}
				  }
					else
					{
					    TURNPLATE_adjusting(-45.3);
					}					
			 }
			 break;
	
			 case THROW_9th_BALL:
			 {
				  if(ROBOT.SHOOTSTATE == THROW_SUCCEEDED)
				  {
							TIM12->CCR1 = 1160;
							TIM12->CCR2 = 1160;
							ROBOT.NOW_STATE = TO_BALL_10th;
							ROBOT.MOVE_STATE = MOVING;

							ROBOT.SHOOTSTATE = THROW_RESET;//�ֱ۸�λ
							OSTimeDly(100);
							cylinder_on(CATCH_BALL_1ST);//�ſ���צ
							INIT_X = ROBOT_REAL_POS_DATA.X_POS;
						  INIT_Y = ROBOT_REAL_POS_DATA.Y_POS;
				  }	
			 }
			 break;
		
			 case TO_BALL_10th:
			 {
					if(ROBOT.MOVE_STATE == ARRIVE)//����λ��
					{
              TIM12->CCR1 = 1160;
							TIM12->CCR2 = 1160;
						  ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;//ͣ��
							ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
							ROBOT_TARGET_VELOCITY_DATA.W_RPM 	= 0;
        
							if(ROBOT.SHOOTSTATE == THROW_RESET_SUCCEEDED)//�ֱ۸�λ��
							{
									ROBOT.NOW_STATE = THROW_10th_BALL;//���м�����
									cylinder_off(CATCH_BALL_1ST);
									OSTimeDly(500);
									ROBOT.SHOOTSTATE = THROW_START;		
							}
					}
					else
					{
					    TURNPLATE_adjusting(47.3);
					}					
			 }
			 break;
		
			 case THROW_10th_BALL:
			 {
					if(ROBOT.SHOOTSTATE == THROW_SUCCEEDED)
					{
							ROBOT.NOW_STATE = TO_START;
							ROBOT.MOVE_STATE = MOVING;
							OSTimeDly(100);
							INIT_X = ROBOT_REAL_POS_DATA.X_POS;
							INIT_Y = ROBOT_REAL_POS_DATA.Y_POS;
							TIM12->CCR1 = 0;
							TIM12->CCR2 = 0;
					}	
			 }
			 break;
			
			 case TO_START:
			 {
					if(ROBOT.MOVE_STATE == ARRIVE)//����λ��
					{
							ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
							ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
							ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;
							ROBOT.SHOOTSTATE = THROW_STOP;
							if(Get_KEY(TO_1st_KICK_KEY))
							{
									ROBOT.NOW_STATE = START_TO_1st_KICK;
									ROBOT.MOVE_STATE = MOVING;
							}
							if(Get_KEY(KICK_START_KEY))
							{
									ROBOT.NOW_STATE = KICK_1st;
									ROBOT.MOVE_STATE = STOP;
							}
					}
					else
					{
					    TURNPLATE_adjusting(0);
					}	
			 }
			 break;
		
			 case START_TO_1st_KICK:
			 {
				  if(ROBOT.MOVE_STATE == ARRIVE)//����λ��
					{
							ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
							ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
							ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;
							ROBOT.SHOOTSTATE = THROW_STOP;
							if(Get_KEY(GOTO_START))
							{
									ROBOT.NOW_STATE = KICK_1st_TO_START;
									ROBOT.MOVE_STATE = MOVING;
							}
							if(Get_KEY(KICK_START_KEY))
							{
									ROBOT.NOW_STATE = KICK_1st;
									ROBOT.MOVE_STATE = STOP;
							}
					}
			 }
			 break;	

			 case KICK_1st_TO_START:
			 {
					if(ROBOT.MOVE_STATE == ARRIVE)//����λ��
					{
							ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
							ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
							ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;
							ROBOT.SHOOTSTATE = THROW_STOP;
							if(Get_KEY(TO_1st_KICK_KEY))
							{
									ROBOT.NOW_STATE = START_TO_1st_KICK;
									ROBOT.MOVE_STATE = MOVING;
							}		   
					}
			 }
			 break;	   

			 case KICK_1st:
			 {
//				 	ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
//					ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
//					ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;
				  
			 }
			 break;

			 default:break;
		}

		OSTimeDly(5);
  }
}



