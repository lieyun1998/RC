#ifndef __PATH_H
#define __PATH_H

#include "includes.h"

typedef struct PLANNING_PATH
{
	u8 track_type;
	u8 yaw_adjusting_type;
	float x0_or_xcenter;
	float y0_or_ycenter;
	float x1_or_R;
	float y1_or_none;
	float V;
	float para;
	float yaw;
}PLANNING_PATH;

#define TEST_ALL_PATH 0  // �Ƿ�������ʱ��DEBUG·��
#define TEST_ALL_PATH_DELAY_MS 1000  // ÿ��������ʱ��ʱ��

/***************************************PATH*****************************************/

PLANNING_PATH START_TO_CATCH_1st_BALL_POINT =                                   //��������ǰ����һ�������
{
	0,
	1, 
	1000, 0, 0, 0, 
	500, 0, 0,
};

PLANNING_PATH CATCH_1st_BALL_POINT_TO_CATCH_2nd_BALL_POINT =                  //�ӵ�һ�������ǰ���ڶ��������
{
	0, 
	1,
	1000, 0, 0, 0, 
	300, 0, 0,
};

PLANNING_PATH CATCH_2nd_BALL_POINT_TO_CATCH_3rd_BALL_POINT =                  //�ӵڶ��������ǰ�������������
{
	0, 
	1,
	1000, 280, 0, 0, 
	300, 0, 0,
};


PLANNING_PATH CATCH_3rd_BALL_POINT_TO_CATCH_4th_BALL_POINT =                  //�ӵ����������ǰ�����ĸ������
{
	0, 
	1,
	1000, 520, 0, 0, 
	300, 0, 0,
};

PLANNING_PATH CATCH_4th_BALL_POINT_TO_CATCH_5th_BALL_POINT =                  //�ӵ����������ǰ�����ĸ������
{
	0, 
	1,
	1000, 780, 0, 0, 
	300, 0, 0,
};
 

PLANNING_PATH CATCH_4th_BALL_POINT_TO_START =                                 //�ӵ��ĸ������ǰ��������
{
	0, 
	0, 0, 0, 0, 
	300, 0, 0,
};
    
PLANNING_PATH CATCH_5th_BALL_POINT_TO_START =                                 //�ӵ���������ǰ�������� 
{
	0, 
	0, 0, 0, 0, 
	300, 0, 0,
};

PLANNING_PATH CATCH_5th_BALL_POINT_TO_2_KICK_POINT =                                         //��������ǰ��2���������� 
{
	3, 
	0,
	0, 0, 0, 0, 
	0, 0, 0,
};



#endif


