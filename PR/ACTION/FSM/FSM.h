#ifndef __FSM_H
#define __FSM_H
#include "stm32f4xx.h"

// �����˵���״̬
typedef enum ROBOT_STATE_ITEMS
{
	ROMOTE_PREPARATION,                                 //׼��״̬
	
	START_TO_BALL_1st,                                  //��������ǰ����һ�������
	CATCH_1st_BALL,                                 	  //ץȡ��һ��1����   
	THROW_1st_BALL,                                   	//����һ��1����
	
	TO_BALL_2nd,                                        //ǰ���ڶ��������
	CATCH_2nd_BALL,                                     //ץȡ�ڶ���1����
	THROW_2nd_BALL,                                     //���ڶ���1����
  
	TO_BALL_3rd,                                        //ǰ�������������
	CATCH_3rd_BALL,                                     //ץȡ������1����
	BALL_3st_TO_PASS_3rd,                               //�������������
	THROW_3rd_BALL,                                     //������1����
	
	TO_BALL_4th,                                        //ǰ�����ĸ������
	CATCH_4th_BALL,                                     //ץȡ�ڵ��ĸ�1����
	BALL_4th_TO_PASS_4th,                               //�����ĸ������
	THROW_4th_BALL,                                     //�����ĸ�1����
	
	PASS_4th_TO_START,                                  //�ӵ��ĸ������ǰ��������
	
	START_TO_1st_KICK,                                    //��������ǰ��2����������
	KICK_1st,                                           //��2��������
	
	KICK_1st_TO_START,                                  //��2����������ǰ��������
	
	START_TO_2nd_KICK,                                    //��������ǰ��3����������
	
  KICK_2nd,                                           //��3��������
	
  TO_BALL_5th,                                        //�������ǰ������������
	CATCH_5th_BALL,                                     //ץȡ�ڵ����1����
	BALL_5th_TO_PASS_5th,                               //������������
	THROW_5th_BALL,                                     //�������1����
	PASS_5th_TO_START,                                  //�ӵ���������ǰ��������
	
}ROBOT_STATE_ITEMS;

// �ƶ��ľ���״̬
typedef enum MOVING_STATE_ITEMS
{
	MOVING_STOP,
	MOVING_GOING,
	MOVING_ROMOTE,
	MOVING_ARRIVED,
}MOVING_STATE_ITEMS;

// ��Ͷ�ľ���״̬
typedef enum THROW_STATE_ITEMS
{
	THROW_STOP,
	THROW_START,
	THROW_SUCCEEDED,
}THROW_STATE_ITEMS;

//ץ��ľ���״̬
typedef enum CATCH_STATE_ITEMS
{
	CATCH_STOP,
	CATCH_START,
	CATCH_PICK_SUCCEEDED,
	CATCH_SUCCEEDED,
}CATCH_STATE_ITEMS;

//����ľ���״̬
typedef enum KICK_STATE_ITEMS
{
	KICK_STOP,
	KICK_START,
	KICK_SUCCEEDED,
}KICK_STATE_ITEMS;

// ң�صľ���״̬
typedef enum ROMOTE_STATE_ITEMS
{
	ROMOTE_STOP,
	ROMOTE_START,
	ROMOTE_OVER,
	ROMOTE_FREE,
}ROMOTE_STATE_ITEMS;

// ׼���׶ο�ѡ���ģʽ
typedef enum OPTAINAL_MODE_ITEMS
{
	MODE_UNKNOWN,
	MODE_MOVING_START_TO_CATCH_1st_BALL_POINT,
	MODE_MOVING_CATCH_4th_BALL_POINT_TO_START,
	MODE_ROMOTE_CATCH_4th_BALL_POINT_TO_CATCH_5th_BALL_POINT,
	MODE_MOVING_START_TO_1st_KICK_POINT,	
	MODE_MOVING_START_TO_2nd_KICK_POINT,	
}OPTAINAL_MODE_ITEMS;

typedef enum ARM_RESET_STATE_ITEMS
{
	ARM_RESET_STOP,
	ARM_RESET_START,
	ARM_ARRIVE_SUCCEEDED,
	ARM_RESET_SUCCEEDED,
}ARM_RESET_STATE_ITEMS;

typedef enum TURN_RESET_STATE_ITEMS
{
	TURN_RESET_STOP,
	TURN_RESET_START,
	TURN_RESET_SUCCEEDED,
}TURN_RESET_STATE_ITEMS;


void FSM_RUN(void *pdata);

extern enum ROBOT_STATE_ITEMS NOW_STATE;
extern enum MOVING_STATE_ITEMS MOVING_STATE;
extern enum THROW_STATE_ITEMS THROW_STATE;
extern enum ROMOTE_STATE_ITEMS ROMOTE_STATE;
extern enum OPTAINAL_MODE_ITEMS OPTAINAL_MODE;
extern enum CATCH_STATE_ITEMS CATCH_STATE;
extern enum KICK_STATE_ITEMS KICK_STATE;
extern enum TURN_RESET_STATE_ITEMS TURN_RESET_STATE;
extern enum PULL_RESET_STATE_ITEMS PULL_RESET_STATE;
extern enum ARM_RESET_STATE_ITEMS ARM_RESET_STATE;
extern enum MOVE_ARM_RESET_STATE_ITEMS MOVE_ARM_RESET_STATE;

#endif
