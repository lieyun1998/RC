#ifndef __AK80_H
#define __AK80_H

#include "includes.h"

#define CMD_MOTOR_MODE      0x01
#define CMD_RESET_MODE      0x02
#define CMD_ZERO_POSITION   0x03

#define AK80_MOTOR_ID       0x01

//�����ֲ��޷�
#define P_MIN               -95.5
#define P_MAX                95.5
#define V_MIN               -30
#define V_MAX 							 30
#define T_MIN 							-18
#define T_MAX 							 18
#define Kp_MIN 								0
#define Kp_MAX 							 500
#define Kd_MIN 							  0
#define Kd_MAX   						  5
#define I_MAX  							 18
#define Test_Pos  					 0.0

// M3508���صĵ����ʵ��Ϣ
typedef struct AK80_REAL_INFO
{
	float ANGLE;   		        //�����Ƕ�	(rad)			
	float  V_angle;						  //�������ٶ�(rad/s	)	
	float  CURRENT;
	float  TARGET_CURRENT;
	float  TARGET_POS;
	float  TARGET_SPEED;
	float  REAL_ANGLE;         //���������ʵ�Ƕȣ�������float��
}AK80_REAL_INFO;


float fmaxf(float a, float b);
float fminf(float a, float b);
int float_to_uint(float x, float x_min, float x_max, int bits) ;
void AK80_motion_control(float p_des, float v_des, float kp, float kd, float t_ff);
void ak80_control_cmd(uint8_t cmd);
float uint_to_float(int x_int, float x_min, float x_max, int bits);
void AK80_update_info(CanRxMsg *msg);
extern struct AK80_REAL_INFO AK80_MOTOR_REAL_INFO;

#endif
