#ifndef __KICK_H
#define __KICK_H
#include "stm32f4xx.h"


#define RESET_KICK_DELAY    100     // �����������׵���ʱ����
#define WAIT_KICK_DELAY     400     // ҡ�ۼ�����ʱ����
#define KICK_BALL_DELAY     100     // ���������ʱ����
#define PREPARE_KICK_DELAY  100     // ׼��̧�����ʱ����

void kick_action_task(void);

#endif

