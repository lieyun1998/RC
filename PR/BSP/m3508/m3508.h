#ifndef __M3508_H
#define __M3508_H
#include "stm32f4xx.h"

// M3508������
#define M3508_CHASSIS_MOTOR_ID_1      0x201
#define M3508_CHASSIS_MOTOR_ID_2      0x202
#define M3508_CHASSIS_MOTOR_ID_3      0x203
#define M3508_CHASSIS_MOTOR_ID_4      0x204
#define M3508_ARM_MOTOR_ID            0x205
#define M2006_TURN_MOTOR_ID           0x206
#define GM6020_MOTOR_ID               0x20b


// M3508���صĵ����ʵ��Ϣ
typedef struct M3508_REAL_INFO
{
	uint16_t ANGLE;   		        //�����Ƕ�						
	int16_t  RPM;								
	int16_t  CURRENT;
	int16_t  TARGET_CURRENT;
	  float  REAL_ANGLE;         //���������ʵ�Ƕȣ�������float��
}M3508_REAL_INFO;


extern struct M3508_REAL_INFO M3508_CHASSIS_MOTOR_REAL_INFO[4];   // 1-4�ֱ��Ӧ˳ʱ�뷽��ĵ��̵��
extern struct M3508_REAL_INFO M3508_ARM_MOTOR_REAL_INFO;          // �ƶ�����Ĳ����ṹ��
extern struct M3508_REAL_INFO GM6020_TURN_MOTOR_REAL_INFO;         // ��̨����Ĳ����ṹ��
extern struct M3508_REAL_INFO M2006_TURN_MOTOR_REAL_INFO;

extern struct PID M3508_ARM_MOTOR_PID_RPM;            // �������ٶȻ�PID
extern struct PID M3508_CHASSIS_MOTOR_PID_RPM[4];     // �������
extern struct PID GM6020_TURN_MOTOR_PID_RPM;          // GM6020����ٶȻ�PID
extern struct PID M2006_TURN_MOTOR_PID_POS;           // M2006���λ�û�PID
extern struct PID M2006_TURN_MOTOR_PID_RPM;           // ת�̵���ٶȻ�PID

extern int16_t ARM_TURN_MOTOR_TARGET_RPM ;    // ������Ŀ���ٶ�
extern int16_t TURN_MOTOR_TARGET_RPM;    // ��̨���Ŀ���ٶ�

void m3508_motor_init(void);
void m3508_update_m3508_info(CanRxMsg *msg);
void m2006_send_motor_currents(void);
void m3508_send_motor_currents(void);
void GM6020_send_motor_currents(void);
void m3508_ARM_angle_integral(M3508_REAL_INFO *M3508_MOTOR);
void m2006_TURN_MOTOR_angle_integral(M3508_REAL_INFO *M3508_MOTOR);

#endif




