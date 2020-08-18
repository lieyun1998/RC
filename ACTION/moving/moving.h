#ifndef __MOVING_H
#define __MOVING_H

#include "stm32f4xx.h"


// ���������ٶȺ�������������
#define TRACK_RUN_PERIOD 1  // ��λ��ms

// �Ƿ���PID˥������
#define IF_OPEN_PID_ATTENUATION_ARC_PID 0
#define IF_OPEN_PID_ATTENUATION_LINE_PID 0
#define IF_OPEN_PID_ATTENUATION_POINT_PID 0

// �Ƿ����������ٶȵĹ���
#define IF_LIMIT_TOTAL_VELOCITY_ARC_TRACK 1
#define IF_LIMIT_TOTAL_VELOCITY_LINE_TRACK 1

typedef struct robot_struct
{
	float x;
	float y;
	float yaw;
	float turn;
}robot_struct;

typedef struct yaw_struct
{
	float yaw;
}yaw_struct;

//������·������ʱ�����
typedef struct TIMES
{
	double TIME_LAST;           //�ϴε�ʱ��
	double TIME_pass;           //������ʱ��   
} TIMES;

typedef struct PATH_FOLLOW
{
	TIMES  Times;            //ʱ��ṹ��
	int     COUNT;            //����
} PATH_FOLLOW;


//��Ľṹ�� ��λmm
typedef struct Point_t
{
	float x;
	float y;
}Point_t;


typedef struct Pose_t
{
	Point_t point;
	//�Ƕ���
	float  direction;
	//�ٶ�
	float vel;
	//ʱ��
	float T;
	
}Pose_t;

extern struct ROBOT_TARGET_VELOCITY ROBOT_TARGET_VELOCITY_DATA;
extern struct Pose_t *NOW_PATH;
extern struct PID point_pid;
extern struct PID yaw_pid;
extern struct robot_struct robot;

void moving_task(void *pdata);
void moving_init(void);

void point_follow(float X_start,float Y_start, float X_end, float Y_end,float V_start, float V_max ,float V_end,float Rac ,float Rde ,float pos_x,float pos_y);
void PATH_TRACKING(Pose_t *Path , int PATH_POINT_SUM);
void Pathplan(float t,float Target_t,int num ,float *X ,float *Y );
void moving_yaw_adjusting(float Target_angle);
void moving_point_track(float X_POS,float Y_POS);
/**
* @brief  AngleLimit�Ƕ��޷������Ƕ�������-180�㵽180��
  * @note
* @param  angle:Ҫ���Ƶ�ֵ
* @retval 
  */
void AngleLimit(float *angle);

//�����Ƕ�
float Angle_adjust(float Sx_error,float Sy_error);

#endif
