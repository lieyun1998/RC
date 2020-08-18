#ifndef __MOTOR_DRIVER_H
#define __MOTOR_DRIVER_H

#include "stm32f4xx.h"

#define COS45              0.70710678f
#define SIN45              0.70710678f

#define Robot_R            0.55f                  //���ֵ����ľ���(��λ��m)

#define V_REAL             0.128f/60                //���ӵ����ٶ�

#define WHEEL_R            0.152f/2                 //���Ӱ뾶(��λ��m) 
#define M3508_RM_To_MS     (PI*WHEEL_R)/570.0f      //ת�����ٶȵ�ת�� (��λ��m/s) 
#define M3508_MS_To_RM     570.0f/(PI*WHEEL_R)      //�ٶ���ת�ٵ�ת�� (��λ��m/s)  

#define RM3508             1
#define RE40               0
// ���㹫ʽ��1/��pi*����ֱ����*���ٱ�*60
#define MS_TO_RPM          21*60/(PI*WHEEL_R*2)     //����ֱ��152mm��������ٱ�1:21������һȦpi*152mm

// ���̵��RPM
typedef struct CHASSIS_MOTOR_RPM
{
	float MOTOR1_RPM;
	float MOTOR2_RPM;
	float MOTOR3_RPM;
	float MOTOR4_RPM;
}CHASSIS_MOTOR_RPM;

// ���������ٶ�
typedef struct ROBOT_TARGET_VELOCITY
{
	float Vx;
	float Vy;
	float W;
	float Vx_RPM;
	float Vy_RPM;
	float W_RPM;
}ROBOT_TARGET_VELOCITY;

extern struct ROBOT_REAL_POS ROBOT_REAL_POS_DATA;

void cd_chassis_driver_init(void);
void cd_robot_kinematic_conversion_3wheels(float Vx, float Vy, float Vz);
void cd_world_kinematic_conversion_3wheels(float Vx, float Vy, float W, float theta);
void Robot_4wheels(float Vx_RPM, float Vy_RPM, float W_RPM);
void World_4wheels(float Vx, float Vy, float W, float theta);
void cd_velocity_adjust(void *pdata);

#endif
