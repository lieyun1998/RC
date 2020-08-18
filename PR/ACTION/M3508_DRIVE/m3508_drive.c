#include "includes.h"

ARM_VELOCITY_PLANNING *ARM_NOW_MOTION = NULL;  // ָ��ҡ�۵�ǰ������ָ��
ARM_VELOCITY_PLANNING ARM_HOLD_MOTION  = {0, 0, 0,   0, 0, 0, 0};  // ����
ARM_VELOCITY_PLANNING ARM_RESET_MOTION = {0, 130, 1000, 1500, 500, 0.2, 0.2};  // Ҫ���滮
ARM_VELOCITY_PLANNING ARM_SHOOT_MOTION = {ARM_INIT_POS, ARM_SHOOT_POS, 500, 800, 200, 0.2, 0.2};  // Ҫ���滮
ARM_VELOCITY_PLANNING ARM_SHOOT_2_MOTION = {ARM_INIT_POS, -30, 500, 800, 500, 0.2, 0.2};  // Ҫ���滮


void Motor_motion_control(void *pdata)
{
	while(1)
	{

		// �����ֱ۶�������
		M3508_arm_motor_motion_control();
		M2006_turnplate_motion_control();
		
	  m2006_send_motor_currents();
    m3508_send_motor_currents();
	
		KICK_control();
//		ak80_control_cmd(CMD_MOTOR_MODE);
//		AK80_motion_control(0,PI/4,0,5,0);

		OSTimeDly(5);
	}
}


// �����ֱ۶�������
void M3508_arm_motor_motion_control(void)
{
	// �滮�ٶ�
	ad_plan_arm_motor_RPM(*ARM_NOW_MOTION, M3508_ARM_MOTOR_REAL_INFO.REAL_ANGLE);
	
	// ����PID����Ŀ���ٶ�
	PID_incremental_PID_calculation(&M3508_ARM_MOTOR_PID_RPM, M3508_ARM_MOTOR_REAL_INFO.RPM, ARM_TURN_MOTOR_TARGET_RPM);
	
	// ���õ���
	M3508_ARM_MOTOR_REAL_INFO.TARGET_CURRENT = M3508_ARM_MOTOR_PID_RPM.output;
}

// ��ת�̶�������
void GM6020_turnplate_motion_control(void)   
{

	 // ����PID����Ŀ���ٶ�
	 PID_incremental_PID_calculation(&GM6020_TURN_MOTOR_PID_RPM, GM6020_TURN_MOTOR_REAL_INFO.RPM, TURN_MOTOR_TARGET_RPM);
	 // ���õ���
	 GM6020_TURN_MOTOR_REAL_INFO.TARGET_CURRENT = GM6020_TURN_MOTOR_PID_RPM.output;
}

// ��ת�̶�������
void M2006_turnplate_motion_control(void)   
{

	 // ����PID����Ŀ���ٶ�
	 PID_incremental_PID_calculation(&M2006_TURN_MOTOR_PID_RPM, M2006_TURN_MOTOR_REAL_INFO.RPM, TURN_MOTOR_TARGET_RPM);
	 // ���õ���
	 M2006_TURN_MOTOR_REAL_INFO.TARGET_CURRENT = M2006_TURN_MOTOR_PID_RPM.output;
}


// �滮��צ��е�۵��Ӧ�е�RPM
void ad_plan_arm_motor_RPM(ARM_VELOCITY_PLANNING motion, float pos)
{
	float Ssu;   //��·��
	float Sac;   //����·��
	float Sde;   //����·��
	float Sco;   //����·��
	float Aac;   //���ټ��ٶ�
	float Ade;   //���ټ��ٶ�
	float S;     //��ǰ·��
	
	// �����������������ִ���ٶȹ滮
	if((motion.Rac > 1) || (motion.Rac < 0) ||
		 (motion.Rde > 1) || (motion.Rde < 0) ||
		 (motion.Vmax < motion.Vstart) )
	{
		ARM_TURN_MOTOR_TARGET_RPM = 0;  // ���צ���˶�
		return;
	}
	
	// ����ģʽ
	if(motion.Pstart == motion.Pend)
	{
		ARM_TURN_MOTOR_TARGET_RPM = motion.Vstart * motion.Vmax;
		return;
	}
	
	// ����һЩ����
	Ssu = ABS(motion.Pend - motion.Pstart);    
	Sac = Ssu * motion.Rac;
	Sde = Ssu * motion.Rde;
	Sco = Ssu - Sac - Sde;
	Aac = (motion.Vmax * motion.Vmax - motion.Vstart * motion.Vstart) / (2.0f * Sac);
	Ade = (motion.Vend * motion.Vend -   motion.Vmax *   motion.Vmax) / (2.0f * Sde);
	
	// �����쳣���
	if(((motion.Pend > motion.Pstart) && (pos < motion.Pstart)) ||
		 ((motion.Pend < motion.Pstart) && (pos > motion.Pstart)))
	{
		ARM_TURN_MOTOR_TARGET_RPM = motion.Vstart;
	}
	else if(((motion.Pend > motion.Pstart) && (pos > motion.Pend)) ||
		      ((motion.Pend < motion.Pstart) && (pos < motion.Pend)))
	{
		ARM_TURN_MOTOR_TARGET_RPM = motion.Vend;
	}
	else
	{
		S = ABS(pos - motion.Pstart);
		
		// �滮RPM
		if     (S < Sac)       ARM_TURN_MOTOR_TARGET_RPM = sqrt(2.0f * Aac * S + motion.Vstart * motion.Vstart);               // ���ٽ׶�
		else if(S < (Sac+Sco)) ARM_TURN_MOTOR_TARGET_RPM = motion.Vmax;                                                        // ���ٽ׶�
		else                   ARM_TURN_MOTOR_TARGET_RPM = sqrt(motion.Vend * motion.Vend - 2.0f * Ade * ABS(Ssu - S));  // ���ٽ׶�
	}
	
	// ������ʵ�������
	if(motion.Pend < motion.Pstart) ARM_TURN_MOTOR_TARGET_RPM = -ARM_TURN_MOTOR_TARGET_RPM;
}

// �滮ת�̵��Ӧ�е�RPM
void ad_plan_turnplate_motor_RPM(TURNPLATE_VELOCITY_PLANNING motion, float pos)
{
	float Ssu;   //��·��
	float Sac;   //����·��
	float Sde;   //����·��
	float Sco;   //����·��
	float Aac;   //���ټ��ٶ�
	float Ade;   //���ټ��ٶ�
	float S;     //��ǰ·��
	
	// �����������������ִ���ٶȹ滮
	if((motion.Rac > 1) || (motion.Rac < 0) ||
		 (motion.Rde > 1) || (motion.Rde < 0) ||
		 (motion.Vmax < motion.Vstart) || (motion.Vmax < motion.Vend))
	{
		TURN_MOTOR_TARGET_RPM = 0;  // ���צ���˶�
		return;
	}
	
	// ����ģʽ
	if(motion.Pstart == motion.Pend)
	{
		TURN_MOTOR_TARGET_RPM = motion.Vstart * motion.Vmax;
		return;
	}
	
	// ����һЩ����
	Ssu = ABS(motion.Pend - motion.Pstart);
	Sac = Ssu * motion.Rac;
	Sde = Ssu * motion.Rde;
	Sco = Ssu - Sac - Sde;
	Aac = (motion.Vmax * motion.Vmax - motion.Vstart * motion.Vstart) / (2.0f * Sac);
	Ade = (motion.Vend * motion.Vend -   motion.Vmax *   motion.Vmax) / (2.0f * Sde);
	
	// �����쳣���
	if(((motion.Pend > motion.Pstart) && (pos < motion.Pstart)) ||
		 ((motion.Pend < motion.Pstart) && (pos > motion.Pstart)))
	{
		TURN_MOTOR_TARGET_RPM = motion.Vstart;
	}
	else if(((motion.Pend > motion.Pstart) && (pos > motion.Pend)) ||
		      ((motion.Pend < motion.Pstart) && (pos < motion.Pend)))
	{
		TURN_MOTOR_TARGET_RPM = motion.Vend;
	}
	else
	{
		S = ABS(pos - motion.Pstart);
		
		// �滮RPM
		if     (S < Sac)       TURN_MOTOR_TARGET_RPM = sqrt(2.0f * Aac * S + motion.Vstart * motion.Vstart);               // ���ٽ׶�
		else if(S < (Sac+Sco)) TURN_MOTOR_TARGET_RPM = motion.Vmax;                                                        // ���ٽ׶�
		else                   TURN_MOTOR_TARGET_RPM = sqrt(motion.Vend * motion.Vend - 2.0f * Ade * ABS(Ssu - S));  // ���ٽ׶�
	}
	// ������ʵ�������
	if(motion.Pend < motion.Pstart) TURN_MOTOR_TARGET_RPM = -TURN_MOTOR_TARGET_RPM;
	if(ABS(Ssu - S)<=1)
		TURN_MOTOR_TARGET_RPM=0;
		
}
