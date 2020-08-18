#include "includes.h"


Pose_t *NOW_PATH = NULL;  // ��ǰ·����ָ��(��ȷ��ָ��ĳ��·���ٽ���·�����ٺ�����
PATH_FOLLOW    Path_Contorl = {0,1}; //������ʼ��Ϊ 1


// �����õı���
robot_struct robot = {0, 0, 0};

// �ƶ��йص�PID
PID point_pid;
PID yaw_pid;

// ����PID��outputmax���ϵ�ϵ��
float YAW_OUTPUTMAX_CONTROLLER     = 0.5;

/*
·�����ٺ�����
���� �� �㼯��
·�����ٵ��ú���
*/
float X[13] = { 0,0,0, 236,  400,  380,    0, -844,-1413, -1728,-1800,-1800,-1800};
float Y[13] = { 0,0,0, 770, 1586, 2430, 3230, 3300, 2714,  1898, 1400, 1400, 1400};

float X1[13] = {-1800,-1800,-1800,-1728,-1413, -844,   0,  380, 400,236,0,0,0};
float Y1[13] = { 1400, 1400, 1400, 1898, 2714, 3300,3230, 2430,1586,770,0,0,0};
/*************************************************************************************/
/************************************ ���ƺ��� ***************************************/
/*************************************************************************************/


// �ƶ����ܳ�ʼ��
void moving_init(void)  //***********************************************************************����
{
	// ��ʼ��PID����
	// 10, 0.04, 2

	PID_parameter_init(&point_pid, 0.05, 0.001, 2, 1, 0, 5);
	
	PID_parameter_init(&yaw_pid, 0.025,0.001, 0.01, 1, 0, -1);
}


// ʵ�ֻ����˵��ƶ�����
void moving_task(void *pdata)
{
	while(1)
	{
		if(ROBOT.MOVE_STATE == MOVING)
		{
	// �����˴����ƶ�״̬
	// ѡ������˵�ǰ���ƶ�·��
		switch(ROBOT.NOW_STATE)
		{
			case START_TO_BALL_1st:                          //��������ǰ����һ�������
			{
				
				point_follow(INIT_X,INIT_Y,1084.6,-21.9,0.2,0.6,0.0,0.2,0.4,ROBOT_REAL_POS_DATA.X_POS,ROBOT_REAL_POS_DATA.Y_POS);
//				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
//		    ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;
                                                                                                              
			}
			break;

			case TO_BALL_2nd:                                //�ӵ�һ�������ǰ���ڶ��������
			{
				
        point_follow(1084.6,-21.9,1084.6,525,0.2,0.6,0.05,0.2,0.3,ROBOT_REAL_POS_DATA.X_POS,ROBOT_REAL_POS_DATA.Y_POS);
				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
				
			}
			break;
//			
			case TO_BALL_3rd:                                //�ӵڶ��������ǰ�������������
			{
				
				point_follow(1084.6,525,1084.6,-20.4,0.2,0.6,0.05,0.2,0.3,ROBOT_REAL_POS_DATA.X_POS,ROBOT_REAL_POS_DATA.Y_POS);
				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;

			}
			break;
//				
			case TO_BALL_4th:                                //�ӵ��ĸ������ǰ������������
			{

				point_follow(1084.6,-20.4,1084.6,525,0.2,0.6,0.05,0.2,0.3,ROBOT_REAL_POS_DATA.X_POS,ROBOT_REAL_POS_DATA.Y_POS);
				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;

			}
			break;
//			
			
			case TO_BALL_5th:                                        //�ӵ���������ǰ������������ 
			{
				
				point_follow(1084.6,525,1084.6,-20.4,0.2,0.6,0.05,0.2,0.3,ROBOT_REAL_POS_DATA.X_POS,ROBOT_REAL_POS_DATA.Y_POS);
				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
			
			}
			break;
			
			case TO_BALL_6th:                                //�ӵ��ĸ������ǰ������������
			{

				point_follow(1084.6,-20.4,1084.6,525.7,0.2,0.6,0.05,0.2,0.3,ROBOT_REAL_POS_DATA.X_POS,ROBOT_REAL_POS_DATA.Y_POS);
				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;

			}
			break;
			
			case TO_BALL_7th:                                //�ӵڶ��������ǰ�������������
			{
				
				point_follow(1084.6,525.2,1084.6,-20.4,0.2,0.6,0.05,0.2,0.3,ROBOT_REAL_POS_DATA.X_POS,ROBOT_REAL_POS_DATA.Y_POS);
				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;

			}
			break;
			
			case TO_BALL_8th:                                //�ӵ�һ�������ǰ���ڶ��������
			{
				
        point_follow(1084.6,-20.4,1084.6,525.7,0.2,0.6,0.05,0.2,0.3,ROBOT_REAL_POS_DATA.X_POS,ROBOT_REAL_POS_DATA.Y_POS);
				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;

				
			}
			break;
			
			case TO_BALL_9th:                          //��������ǰ����һ�������
			{
				
				point_follow(1084.6,525,1084.6,-20.4,0.2,0.6,0.05,0.2,0.3,ROBOT_REAL_POS_DATA.X_POS,ROBOT_REAL_POS_DATA.Y_POS);
				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
                                                                                                          
			}
			break;

			case TO_BALL_10th:                          //��������ǰ����һ�������
			{
				
				point_follow(1084.6,-20.4,1084.6,525,0.2,0.6,0.05,0.2,0.3,ROBOT_REAL_POS_DATA.X_POS,ROBOT_REAL_POS_DATA.Y_POS);
				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;

                                                                                                                
			}
			break;
					
			case TO_START:                                           //�ӵ���������ǰ�������� 
			{
        point_follow(INIT_X,INIT_Y,5,5,0.1,0.6,0,0.2,0.3,ROBOT_REAL_POS_DATA.X_POS,ROBOT_REAL_POS_DATA.Y_POS);
			}
			break;
			
			case START_TO_1st_KICK:                                            //����������ǰ�������� 
			{
        Pathplan(Get_OSTime()/1000,5,10,X,Y);
			}
			break;
			
			case KICK_1st_TO_START:                                          //��������ǰ��������
			{
        Pathplan(Get_OSTime()/1000,5,10,X1,Y1);
			}
			break;
			
			case START_TO_2nd_KICK:                                           //��������ǰ�������� 
			{

			}
			break;
			

			
			default: 
			{
//						ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
//		        ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
//		        ROBOT_TARGET_VELOCITY_DATA.W_RPM  = 0;
			}
				break;
		}
		moving_yaw_adjusting(0);
	}

		OSTimeDly(10);
	}
}
	


/*************************************************************************************/
/************************************ ·������ ***************************************/
/*************************************************************************************/
void point_follow(float X_start,float Y_start, float X_end, float Y_end,float V_start, float V_max ,float V_end,float Rac ,float Rde ,float pos_x,float pos_y)
{
	float Ssu;   //��·��
	float Sac;   //����·��
	float Sde;   //����·��
	float Sco;   //����·��
	float Aac;   //���ټ��ٶ�
	float Ade;   //���ټ��ٶ�
	float S;     //��ǰ·��
	float REAL_V;
	float error;
	
	
	// ����һЩ����
	error = sqrt((pos_x - X_end) * (pos_x - X_end) + (pos_y - Y_end) * (pos_y - Y_end));
	Ssu = ABS(sqrt((X_start - X_end) * (X_start - X_end) + (Y_start - Y_end) * (Y_start - Y_end)));    
	Sac = Ssu * Rac;
	Sde = Ssu * Rde;
	Sco = Ssu - Sac - Sde;
	Aac = (V_max * V_max - V_start * V_start) / (2.0f * Sac);
	Ade = (V_end * V_end -   V_max *   V_max) / (2.0f * Sde);
	
	S = ABS(sqrt((X_start - pos_x) * (X_start - pos_x) + (Y_start - pos_y) * (Y_start - pos_y)));
		
	// �滮RPM
	if     (S < Sac)       REAL_V = sqrt(2.0f * Aac * S + V_start * V_start);         // ���ٽ׶�
	else if(S < (Sac+Sco)) REAL_V = V_max;                                            // ���ٽ׶�
	else                   REAL_V = sqrt(V_end * V_end - 2.0f * Ade * ABS(Ssu - S));  // ���ٽ׶�
	
  ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = REAL_V * (X_end - pos_x) / error;
	ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = REAL_V * (Y_end - pos_y) / error;
	
	if(Ssu - S <=5)
	{
		ROBOT.MOVE_STATE = ARRIVE;
	}
}


// ����PID����ƫ���ǵ���
void moving_yaw_adjusting(float Target_angle)
{
   float W;
   float error;
   robot.yaw = ROBOT_REAL_POS_DATA.YAW_POS;
   // �������
   if(robot.yaw*Target_angle >= 0)
   {
      error = Target_angle - robot.yaw;
   }
   else
   {
	 if(ABS(robot.yaw)+ABS(Target_angle) <= 180) error = Target_angle - robot.yaw;
	 else 
	 {
      AngleLimit(&error);
	 }
   }
   
   // ֱ������PID������ٶ�
   PID_position_PID_calculation_by_error(&yaw_pid, error);
   
   W = yaw_pid.output;	  // ���̽��ٶ� ��λ��rad/s
   
   ROBOT_TARGET_VELOCITY_DATA.W_RPM = -W;
}	





void Pathplan(float t,float Target_t,int num ,float *X ,float *Y )
{   
	float S_x;
	float S_y;
	float V_x;
	float V_y; 
	float real_t;
  static int i = 0;
	int k;
	//ʱ���һ��
   
	if(i==0)
	{
		Path_Contorl.Times.TIME_LAST = t;
		i = i+1;
	}
	
	 real_t = t - Path_Contorl.Times.TIME_LAST;
	
	//k = (int)real_t;
	//t = real_t -k;

	k = (int)(real_t * num/Target_t);
	t = real_t - k * Target_t/num;
  t = t * num/Target_t;

	if (t < 0.001f) t = 0;
	//λ�������������ٶ���������

	float f1s = (1 - t) * (1 - t) * (1 - t) / 6;
	float f2s = (3 * t * t * t - 6 * t * t + 4) / 6;
	float f3s = (-3 * t * t * t + 3 * t * t + 3 * t + 1) / 6;
	float f4s = (t * t * t) / 6;
	float v1s = -(1 - t) * (1 - t) / 2;
	float v2s = 3 * t * t / 2 - 2 * t;
	float v3s = -3 * t * t / 2 + t + 0.5f;
	float v4s = t * t / 2; 
	float Sx_error;
	float Sy_error;
	
           S_x = X[k] * f1s + X[k+1] * f2s + X[k+2] * f3s + X[k+3] * f4s;
           S_y = Y[k] * f1s + Y[k+1] * f2s + Y[k+2] * f3s + Y[k+3] * f4s;
           V_x = X[k] * v1s + X[k+1] * v2s + X[k+2] * v3s + X[k+3] * v4s;
           V_y = Y[k] * v1s + Y[k+1] * v2s + Y[k+2] * v3s + Y[k+3] * v4s;
					 
					 Sx_error = S_x - (ROBOT_REAL_POS_DATA.X_POS);
           Sy_error = S_y - (ROBOT_REAL_POS_DATA.Y_POS);
           
					 V_x =  1.0f * Sx_error + V_x * num/Target_t;
					 V_y =  1.0f * Sy_error + V_y * num/Target_t;
					 
	         //�����ٶ�
	         ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = V_x/1000;
           ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = V_y/1000;	
					 
					 printf("%f ,  %f ,  %f  \r\n",ROBOT_TARGET_VELOCITY_DATA.Vx_RPM,ROBOT_TARGET_VELOCITY_DATA.Vy_RPM,real_t);
					 //printf("%f ,%f \r\n",V_x,V_y);

					//printf("%f\r\n",t);
          if(real_t>Target_t)
          {
	         ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
					 ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
           ROBOT.MOVE_STATE = ARRIVE	;	
           i = 0;						
          } 
            moving_yaw_adjusting(0);					
}
 
// �����
void moving_point_track(float X_POS,float Y_POS)
{
	float error;
	float Vx;
	float Vy;
	
	// �������
	error = sqrt((ROBOT_REAL_POS_DATA.X_POS - X_POS) * (ROBOT_REAL_POS_DATA.X_POS - X_POS) + (ROBOT_REAL_POS_DATA.Y_POS - Y_POS) * (ROBOT_REAL_POS_DATA.Y_POS - Y_POS));  // �������
	
	PID_position_PID_calculation_by_error(&point_pid, error);  // PID����
	
	Vx = point_pid.output * (X_POS - ROBOT_REAL_POS_DATA.X_POS) / error;
	Vy = point_pid.output * (Y_POS - ROBOT_REAL_POS_DATA.Y_POS) / error;
	
	// ��������ٶ�
	ROBOT_TARGET_VELOCITY_DATA.Vx_RPM =  Vx;
	ROBOT_TARGET_VELOCITY_DATA.Vy_RPM =  Vy;	
}
	

/**
* @brief  AngleLimit�Ƕ��޷������Ƕ�������-180�㵽180��
  * @note
* @param  angle:Ҫ���Ƶ�ֵ
* @retval 
  */
void AngleLimit(float *angle)
{
	static uint8_t recursiveTimes = 0;
	
	recursiveTimes++;
	
	if(recursiveTimes<100)
	{
		if(*angle>180.0f)
		{
			*angle-=360.0f;
			AngleLimit(angle);
		}
		else if(*angle<-180.0f)
		{
			*angle+=360.0f;
			AngleLimit(angle);
		}
	}
	
	recursiveTimes--;
}

float Angle_adjust(float Sx_error,float Sy_error)
{
    float direction;
    if(Sy_error>0&&Sx_error>0)direction = RAD2ANGLE(atan(Sy_error/Sx_error));
    if(Sy_error>=0&&Sx_error<0)direction = RAD2ANGLE(atan(Sy_error/Sx_error))+180;
    if(Sy_error<=0&&Sx_error<0)direction = RAD2ANGLE(atan(Sy_error/Sx_error))+180;
    if(Sy_error<0&&Sx_error>0)direction = RAD2ANGLE(atan(Sy_error/Sx_error))-90;   
    
    return direction;
}
