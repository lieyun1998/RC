#ifndef __GLOBAL_LOCATION_H
#define __GLOBAL_LOCATION_H

#include "stm32f4xx.h"

// ѡ��ʹ���Ŀ�ȫ����λ
#define USE_ACTION_GL	1
#define USE_SELF_GL	  0 

// ѡ��ʹ���Ŀ�ȫ����λ
#define Action_Location  1  
#define Self_Location    0

// ��ʼʱ��λ��ƫ����
#define ROBOT_SZ_POS_OFFSET_X    (0) /*PARA*/
#define ROBOT_SZ_POS_OFFSET_Y    (0)

#define WHEEL_DIAMETER          50.8f  // ����ֱ��
#define ENCODER_RESIOLUTION       1000  // �������ֱ���
#define DISTANCE_PER_CNT (PI*WHEEL_DIAMETER/(ENCODER_RESIOLUTION*4))  // ÿ��CNT�����·��ֵ

#define Lx 173.18f  // ˳ʱ�������Ӵ�ֱ�������ľ��루��λ��mm��
#define Ly 173.18f  // ˳ʱ��β���Ӵ�ֱ�������ľ��루��λ��mm��

#define YAW0  45  // ˳ʱ������������������ϵ�ĽǶȣ���Χ(-180, 180]��

// �����˵���ʵλ��
typedef struct ROBOT_REAL_POS
{
  float X_POS;
  float Y_POS;     
  float YAW_POS;
}ROBOT_REAL_POS;

// ����ȫ����λģ�鶨λ��λ��
typedef struct ACTION_GL_POS
{
	float ANGLE_Z;
	float ANGLE_X;
	float ANGLE_Y;	
	float POS_X;
	float POS_Y;
	float W_Z;
	
	float LAST_POS_X;
	float LAST_POS_Y;
	
	float DELTA_POS_X;
	float DELTA_POS_Y;	
}ACTION_GL_POS;


extern float OFFSET_YAW;
extern float SELF_GL_YAW_INIT_VALUE;
extern struct ROBOT_REAL_POS ROBOT_REAL_POS_DATA;

void Location_init(void);
void Update_Action_gl_position(float value[6]);
void Update_self_gl_position(void);

#endif

