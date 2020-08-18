#include <includes.h>

/*��ȡ��������Ϣ��������������
*/
//�����˲�����
float DT_LV ( int queue[] ,u8 num , int count )
{
	float all = 0 ; 
	u8 i,j;
  //�������	
	for(i=0; i<num-1; i++)                             
	{   
	  queue[i]=queue[i+1];  
	}
	//ĩβ��ֵ
	queue[num-1] = count;    
	//���
	for(j=0; j<num; j++ )
	{
	 all += queue[j] ;
	}
	
  return all/num;  
}

INFORMATION Sensor ;
//��ȡGPIO״̬��Ϣ
//��λ����
//��翪��
//ɫ�괫����
void Read_GPIO()
{
	//��ȡ��ƽ
	Sensor.GPIO_KEY = GET_GPIO_KEY();
	Sensor.GPIO_limit = Get_GPIO_limit();
}

//��ȡ����������
//ȫ����λ������
//�������
void Read_encoder()
{
	//��������������
//	static int Encoder[2][10] = {0};
	
	// ��ȡ��ʱ��CNT�Ĵ��������ֵ
	// �����˶���ֵӦ��Ϊ���������������������
//	Sensor.CNT_X =  DT_LV( Encoder[0] ,10,-encoder_get_encoder_CNT(4));  // ��˳ʱ��������
//	Sensor.CNT_Y =  DT_LV( Encoder[1] ,10,-encoder_get_encoder_CNT(8));  // ��˳ʱ��β����
	Sensor.CNT_X = encoder_get_encoder_CNT(4);
  Sensor.CNT_Y = encoder_get_encoder_CNT(8);
}

void Read_Gyro()
{
		// ֱ�ӻ�ȡƫ���ǣ������м򵥴���ƫ���Ƕ�ֵȫ����ʱ��Ϊ����˳ʱ��Ϊ����
	
	  robot.turn = (float)GYRO_ANGLE.Angle[2] / 32768 * 180 - SELF_GL_YAW_INIT_VALUE + OFFSET_YAW ;  /*WAITING_TEST*/
	
	  // ���Ʒ�Χ(-180�� 180]
	  if(robot.turn > 180)        robot.turn = -180 + (robot.turn - 180);
	  else if(robot.turn <= -180) robot.turn =  180 + (robot.turn + 180);	
}

void Read_V_real()
{
	static float last_x = 0;
	static float last_y = 0;
	
	Sensor.real_Vx = (ROBOT_REAL_POS_DATA.X_POS - last_x)/5;
	Sensor.real_Vy = (ROBOT_REAL_POS_DATA.Y_POS - last_y)/5;
	
	last_x = ROBOT_REAL_POS_DATA.X_POS;
	last_y = ROBOT_REAL_POS_DATA.Y_POS;
}

u8 Get_KEY(u16 name)
{
  return Sensor.GPIO_KEY & name ;
}

u8 Get_limit(u16 name)
{
	return Sensor.GPIO_limit & name ;
}

//���������º���  
void Sensor_Update(void *pdata)
{
    u32 ticks = 0;
	  u32 lastWakeTime = Get_OSTime();
	  while(1)
	  {
			OSTimeDlyHMSM(0,0,0,1);
			#if Self_Location	  
		  if (RATE_DO_EXECUTE(Encoder_UPDATE_RATE, ticks))
		  {
			 Read_encoder();
		  }

			if (RATE_DO_EXECUTE(GL_UPDATE_RATE, ticks))
		  {
       Update_self_gl_position();
		  }
      #endif
			if (RATE_DO_EXECUTE(GPIO_UPDATE_RATE, ticks))
		  {
			 Read_GPIO();
	    }	
			if (RATE_DO_EXECUTE(Gyro_UPDATE_RATE, ticks))
		  {
			 Read_Gyro();
		  }
		  if (RATE_DO_EXECUTE(Motor_UPDATE_RATE, ticks))
		  {
       romote_action_task();
		  }
			if (RATE_DO_EXECUTE(Motor_UPDATE_RATE, ticks))
		  {
       Read_V_real();				
		  }
			
		  ticks++; 

	  }
}
