#ifndef __ROBOT_H
#define __ROBOT_H

#include "stm32f4xx.h"

#define RESET_DELAY_10MS 100  // 摇臂重置时的延时长度
#define RESET_PULL_DELAY_10MS 1000  // 摇臂重置时的延时长度
#define PREPARE_DELAY_1S 100

//走行状态变量枚举类型变量
typedef enum
{
	
  ROBOT_INIT,                                         //初始化
	ROMOTE_PREPARATION,                                 //准备状态
	ROMOTE_START,                                       //遥控开始
	
	START_TO_BALL_1st,                                  //从启动区前往第一个夹球点 
	THROW_1st_BALL,                                   	//传第一个1类球
	
	TO_BALL_2nd,                                        //前往第二个夹球点
	THROW_2nd_BALL,                                     //传第二个1类球
  
	TO_BALL_3rd,                                        //前往第三个夹球点
	THROW_3rd_BALL,                                     //传第三1类球
	
	TO_BALL_4th,                                        //前往第四个夹球点
	THROW_4th_BALL,                                     //传第四个1类球
	
	THROW_5th_BALL,                                     //传第五个1类球
	
	TO_START,                                           //从第五个夹球点前往启动区
	
	START_TO_1st_KICK,                                  //从启动区前往2分区踢球区
	KICK_1st,                                           //在2分区踢球
	
	KICK_1st_TO_START,                                  //从2分区踢球区前往启动区
	
	START_TO_2nd_KICK,                                  //从启动区前往3分区踢球区
	
  KICK_2nd,                                           //在3分区踢球
	
  TO_BALL_5th,                                        //从踢球点前往第五个夹球点

  THROW_6th_BALL,                                     //传第6个一类球
	
	TO_BALL_6th,                                      //回到第四个传球区
	
	THROW_7th_BALL,                                     //传第7个一类球
	
	TO_BALL_7th,                                      //回到第三个传球区
	
	THROW_8th_BALL,                                     //传第8个一类球
	
	TO_BALL_8th,                                      //回到第二个传球区
	
	THROW_9th_BALL,                                     //传第9个一类球
	
	TO_BALL_9th,                                      //回到第一个传球区
	
	THROW_10th_BALL,                                     //传第10个一类球
	
	TO_BALL_10th,                                      //回到第一个传球区
	
	
	


	
}NOWStatus_t;

typedef enum
{
	THROW_STOP,
	THROW_START,
	THROW_SUCCEEDED,
	THROW_RESET,
	THROW_RESET_SUCCEEDED,
}shootStatus_t;

typedef enum
{
	STOP,
	MOVING,
	ARRIVE,
}moveStatus_t;

typedef enum
{
	TURN_STOP,
	TURN_SUCCEED,
}turnplateStatus_t;

typedef enum
{
	KICK_STOP,
	KICK_START1,
	KICK_START2,
	KICK_END1,
	KICK_END2,
	KICK_SUCCEED,
	ROBOT_STOP,
	GO_1M,
	BACK_1M,
}kickStatus_t;


//全局变量结构体
typedef struct{
	NOWStatus_t   NOW_STATE;
	moveStatus_t  MOVE_STATE;
	shootStatus_t SHOOTSTATE;
	turnplateStatus_t TURNSTATE;
	kickStatus_t KICK_STATE;
	
}ROBOT_STATE_ITEMS;

extern float INIT_POS;
extern float INIT_X;
extern float INIT_Y;
extern ROBOT_STATE_ITEMS ROBOT;	

void FSM_RUN(void *pdata);
#endif
