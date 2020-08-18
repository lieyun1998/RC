#include "includes.h"
#include <app_cfg.h>

//开始任务
void start_task(void *pdata)
{
	OS_CPU_SR cpu_sr=0;
	pdata=pdata;
	bsp_init();
	//OSStatInit();  //开启统计任务
	
	OS_ENTER_CRITICAL();  //进入临界区(关闭中断)
	
	//创建轮子运动任务
	OSTaskCreate(cd_velocity_adjust,(void*)0,(OS_STK*)&Wheels_TASK_STK[Wheels_STK_SIZE-1],Wheels_TASK_PRIO); 
	//创建传球任务
	OSTaskCreate(pass_ball_task,(void*)0,(OS_STK*)&PASS_TASK_STK[PASS_STK_SIZE-1],PASS_TASK_PRIO);
	//创建轮运动规划任务
	OSTaskCreate(moving_task,(void*)0,(OS_STK*)&MOVE_TASK_STK[MOVE_STK_SIZE-1],MOVE_TASK_PRIO); 
	//创建状态机任务
	OSTaskCreate(FSM_RUN,(void*)0,(OS_STK*)&FSM_TASK_STK[FSM_STK_SIZE-1],FSM_TASK_PRIO); 
	//创建DEBUG任务
	OSTaskCreate(Debug_by_UART,(void*)0,(OS_STK*)&DEBUG_TASK_STK[DEBUG_STK_SIZE-1],DEBUG_TASK_PRIO); 
	//创建传感器更新任务
	OSTaskCreate(Sensor_Update,(void*)0,(OS_STK*)&SENSOR_TASK_STK[SENSOR_STK_SIZE-1],SENSOR_TASK_PRIO);
  //创建电机任务
  OSTaskCreate(Motor_motion_control,(void*)0,(OS_STK*)&MOTOR_TASK_STK[MOTOR_STK_SIZE-1],MOTOR_TASK_PRIO);	

	OSTaskSuspend(START_TASK_PRIO);//挂起开始任务
	OS_EXIT_CRITICAL();  //退出临界区(开中断)
}



void pass_ball_task(void *pdata)
{
	while(1)
	{
		//射球
		shoot_ball_task();
		//机械臂复位
		ARM_RESET();
		
		OSTimeDly(10);
	}
}


void shoot_ball_task(void)
{
	static u8 flow_counter = 0;

  if(ROBOT.SHOOTSTATE == THROW_START)
	{
		switch(flow_counter)
		{
			case 0:
			{
	      ARM_NOW_MOTION = &ARM_SHOOT_MOTION;
		
	      if(M3508_ARM_MOTOR_REAL_INFO.REAL_ANGLE >= -20.8)return;

				
				flow_counter ++;
			}break;	
			case 1:
			{
				
				//
				switch(ROBOT.NOW_STATE)
				{
					case THROW_1st_BALL:
					TURNPLATE_adjusting(-4);
					if(ABS(robot.turn - (-4))>=1) return;
          //TURNPLATE_adjust(SHOOT_INIT,-32.4,1500,2500,0,0.2,0.3,robot.turn);//1
					break;
					case THROW_2nd_BALL:
					TURNPLATE_adjusting(2);
					if(ABS(robot.turn - (2))>=1) return;
//          TURNPLATE_adjust(SHOOT_INIT,-43.9,1500,2500,0,0.2,0.3,robot.turn);//3
					break;
					case THROW_3rd_BALL:
					TURNPLATE_adjusting(-4);
					if(ABS(robot.turn - (-4))>=1) return;
//          TURNPLATE_adjust(SHOOT_INIT,-47.0,1500,2500,0,0.2,0.3,robot.turn);//4
					break;
					case THROW_4th_BALL:
					TURNPLATE_adjusting(2);
					if(ABS(robot.turn - (2))>=1) return;
//          TURNPLATE_adjust(SHOOT_INIT,-30.0,1500,2500,0,0.2,0.3,robot.turn);//2
					break;
					case THROW_5th_BALL:
					TURNPLATE_adjusting(-4);
					if(ABS(robot.turn - (-4))>=1) return;
//          TURNPLATE_adjust(SHOOT_INIT,-47.3,1500,2500,0,0.2,0.3,robot.turn);//4
					break;
					case THROW_6th_BALL:
          TURNPLATE_adjusting(2);
					if(ABS(robot.turn - (2))>=1) return;
					break;
					case THROW_7th_BALL:
          TURNPLATE_adjusting(-4);
					if(ABS(robot.turn - (-4))>=1) return;
					break;
					case THROW_8th_BALL:
          TURNPLATE_adjusting(2);
					if(ABS(robot.turn - (2))>=1) return;
					break;
					case THROW_9th_BALL:
          TURNPLATE_adjusting(-4);
					if(ABS(robot.turn - (-4))>=1) return;
					break;
					case THROW_10th_BALL:
          TURNPLATE_adjusting(2);
					if(ABS(robot.turn - (2))>=1) return;
					break;
					
			    default: break;
				}
				if(M3508_ARM_MOTOR_REAL_INFO.REAL_ANGLE >= -90.8)return;
        ARM_NOW_MOTION = &ARM_SHOOT_2_MOTION;
        if(!Get_limit(ARM_ARRIVE_LIMIT)) return;
	      ARM_NOW_MOTION = &ARM_HOLD_MOTION;
				flow_counter ++;
				
			}break;	

			default:
			{
        ROBOT.SHOOTSTATE = THROW_SUCCEEDED;	
				flow_counter = 0;
			}break;			
		}	
	}
}

void ARM_RESET(void)                                         //手臂复位
{
	static u8 flow_counter = 0;

	
	if(ROBOT.SHOOTSTATE == THROW_RESET)
	{
	  switch(flow_counter)
		{
			case 0:
			{	
				
				ARM_NOW_MOTION = &ARM_RESET_MOTION;

				if(!Get_limit(ARM_RESET_LIMIT)) return;
				
				M3508_ARM_MOTOR_REAL_INFO.REAL_ANGLE = ARM_INIT_POS;  /*WAITING_DEBUG*/

				ARM_NOW_MOTION = &ARM_HOLD_MOTION;
				
				flow_counter ++;
			}break;
				
			default:
			{
				ROBOT.SHOOTSTATE = THROW_RESET_SUCCEEDED;	
				flow_counter = 0;
			}
		}
	}
}

void romote_action_task(void)
{
	PS2_update_ps2_command();	 // 更新PS2的指令
//	moving_yaw_adjusting(0);
//  if(ROBOT.NOW_STATE == ROMOTE_START)
//	{
//		// 遥控控制移动
//		switch(PS2_KEY)
//		{
//			case PSB_PAD_UP:  // 上箭头
//			{
//				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
//				ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0.2;
//				ROBOT_TARGET_VELOCITY_DATA.W_RPM = 0;
//			}
//			break;
//			
//			case PSB_PAD_DOWN:  // 下箭头
//			{
//				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
//				ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = -0.2;
//				ROBOT_TARGET_VELOCITY_DATA.W_RPM = 0;				
//			}
//			break;

//			case PSB_PAD_LEFT:  // 左箭头
//			{
//				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = -0.2;
//				ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
//				ROBOT_TARGET_VELOCITY_DATA.W_RPM = 0;		
//			}
//			break;		

//			case PSB_PAD_RIGHT:  // 右箭头
//			{
//				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0.2;
//				ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
//				ROBOT_TARGET_VELOCITY_DATA.W_RPM = 0;	
//			}
//			break;

//			case PSB_L1:  // L1
//			{
//				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
//				ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
//				ROBOT_TARGET_VELOCITY_DATA.W_RPM = -0.5;

//			}
//			break;

//			case PSB_R1:  // R1
//			{
//				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = -0;
//				ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
//				ROBOT_TARGET_VELOCITY_DATA.W_RPM = 0.5;
//			}
//			break;
//			
//		  case PSB_CIRCLE:  // 圆形
//		  { 
//			  cylinder_off(CATCH_BALL_1ST);
//			  OSTimeDly(100);
//			  ROBOT.SHOOTSTATE = THROW_START;
//		  }
//		  break;
//			
//			case PSB_CROSS:  // 圆形
//		  { 
//        OSTimeDly(500);
//			  ROBOT.SHOOTSTATE = THROW_RESET;
//			  OSTimeDly(500);
//			  cylinder_on(CATCH_BALL_1ST);
//		  }
//		  break;
//			
//			default:  // 未按下规定按键时 
//			{
//				// 让机器人停止移动

//				ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
//				ROBOT_TARGET_VELOCITY_DATA.W_RPM = 0;

//			}
//			break;
//		}
//	}
	
	if(ROBOT.NOW_STATE == KICK_1st)
	{
		INIT_X = ROBOT_REAL_POS_DATA.X_POS;
		INIT_Y = ROBOT_REAL_POS_DATA.Y_POS;
		// 遥控控制移动
		switch(PS2_KEY)
		{
			case PSB_PAD_UP:  // 上箭头
			{

			}
			break;
			
			case PSB_PAD_DOWN:  // 下箭头
			{
			
			}
			break;

			case PSB_PAD_LEFT:  // 左箭头
			{

			}
			break;		

			case PSB_PAD_RIGHT:  // 右箭头
			{
         ROBOT.KICK_STATE = ROBOT_STOP;
			}
			break;

			case PSB_L1:  // L1
			{
				 ROBOT.KICK_STATE = KICK_START1;

			}
			break;

			case PSB_R1:  // R1
			{
				 ROBOT.KICK_STATE = KICK_START2;
				
			}
			break;
			
			
			case PSB_L2:  // L1
			{
				 ROBOT.KICK_STATE = KICK_END1;

			}
			break;

			case PSB_R2:  // R1
			{
				 ROBOT.KICK_STATE = KICK_END2;
				
			}
			break;
			
		  case PSB_CIRCLE:  // 圆形
		  { 
			   cylinder_off(CATCH_SEAT_1);
				
		  }
		  break;
			
			case PSB_CROSS:  // 叉按键
		  { 
			   cylinder_on(CATCH_SEAT_1);
		  }
		  break;
			
			case PSB_TRIANGLE:  // 三角按键
		  {
         ROBOT.KICK_STATE = GO_1M;
			}
			break;
			
			case PSB_SQUARE:  // 方形按键
		  {
          ROBOT.KICK_STATE = BACK_1M;
			}
			break;
			
			default:  // 未按下规定按键时 
			{
					
//				// 让机器人停止移动
//				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
//				ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
//				ROBOT_TARGET_VELOCITY_DATA.W_RPM = 0;

			}
			break;
		}
	}
}

void KICK_control()
{
	  static float X_POS;
	  static float Y_POS;
	  switch(ROBOT.KICK_STATE)
		{
			case KICK_START1:  
			{
          Odrive_Control_pos1(CAN2,1, 4000*8, 4000*9*0.3, 4000*9*0.2, 4000*9*0.2);
			}
			break;
			
			case KICK_START2:  
			{
			    Odrive_Control_pos1(CAN2,2, 4000*8, 4000*9*0.3, 4000*9*0.2, 4000*9*0.2);
			}
			break;
			
			case KICK_END1:  
			{
          Odrive_Control_pos1(CAN2,1, 0, 4000*9*0.3, 4000*9*0.2, 4000*9*0.2);
			}
			break;
			
			case KICK_END2:  
			{
			    Odrive_Control_pos1(CAN2,2, 0, 4000*9*0.3, 4000*9*0.2, 4000*9*0.2);	
			}
			break;
			
			

			case ROBOT_STOP:  
			{
           moving_point_track(X_POS,Y_POS);
			}
			break;		

			case GO_1M:  // 右箭头
			{
				 if(ROBOT_REAL_POS_DATA.X_POS<-1000)
				 {
						 ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
						 ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;					 
				 }
				 else
				 {
						 ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = -0.4;
						 ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
				 }
			}
			break;

			case BACK_1M:  // L1
			{
				 if(ROBOT_REAL_POS_DATA.X_POS>0)
				 {
						 ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
						 ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
						 
				 }
				 else
				 {
						 ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0.4;
						 ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
						 
				 }
			}
			break;


			
			default:  // 未按下规定按键时 
			{
//					X_POS = ROBOT_REAL_POS_DATA.X_POS;
//				  Y_POS = ROBOT_REAL_POS_DATA.Y_POS;
//				// 让机器人停止移动
//				ROBOT_TARGET_VELOCITY_DATA.Vx_RPM = 0;
//				ROBOT_TARGET_VELOCITY_DATA.Vy_RPM = 0;
//				ROBOT_TARGET_VELOCITY_DATA.W_RPM = 0;

			}
			break;
		}
	
}

void TURNPLATE_adjusting(float Target_angle)
{
   static float error;

	 error = Target_angle - robot.turn;
	 PID_position_PID_calculation_by_error(&M2006_TURN_MOTOR_PID_POS,error);
	 
	 TURN_MOTOR_TARGET_RPM = M2006_TURN_MOTOR_PID_POS.output;
	
	
	 
}	

void TURNPLATE_adjust(float P_start, float P_end, float V_start, float V_max ,float V_end,float Rac ,float Rde ,float pos)
{
	float Ssu;   //总路程
	float Sac;   //加速路程
	float Sde;   //减速路程
	float Sco;   //匀速路程
	float Aac;   //加速加速度
	float Ade;   //减速加速度
	float S;     //当前路程
		
	// 计算一些变量
	
	Ssu = ABS(P_end - P_start);    
	Sac = Ssu * Rac;
	Sde = Ssu * Rde;
	Sco = Ssu - Sac - Sde;
	Aac = (V_max * V_max - V_start * V_start) / (2.0f * Sac);
	Ade = (V_end * V_end -   V_max *   V_max) / (2.0f * Sde);
	
	S = ABS(pos - P_start);
		
	// 规划RPM
	if     (S < Sac)       TURN_MOTOR_TARGET_RPM = sqrt(2.0f * Aac * S + V_start * V_start);         // 加速阶段
	else if(S < (Sac+Sco)) TURN_MOTOR_TARGET_RPM = V_max;                                            // 匀速阶段
	else                   TURN_MOTOR_TARGET_RPM = sqrt(V_end * V_end - 2.0f * Ade * ABS(Ssu - S));  // 减速阶段
	
	// 分配合适的正负号
	if(P_end < P_start) TURN_MOTOR_TARGET_RPM = -TURN_MOTOR_TARGET_RPM;
	
	if(Ssu - S <=2)
	{
		TURN_MOTOR_TARGET_RPM = 0;
		
	}
}
