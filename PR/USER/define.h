#ifndef __DEFINE_H
#define __DEFINE_H

#define PI					3.14159265358979f

#define ANGLE2RAD(x) (x/180.0f*PI)  //�Ƕ�ת����
#define RAD2ANGLE(x) (x/PI*180.0f)  //����ת�Ƕ�

//����ֵ
#define ABS(x)      ((x)>0? (x):(-(x)))

//GPIO����
//����
#define START_KEY             0x01       //��������      //E8
#define Cheak_KEY             0x02       //ң�ؿ���      //E9
#define TO_1st_KICK_KEY       0x04       //ȥ���򿪹�   //E10
#define GOTO_START  		      0x08       //��������     //E11
#define KICK_START_KEY  		  0x10       //���򿪹�     //E12
#define KICK_KEY              0x20       //��������     //E13
#define GOTO_1M               0x40                       //E14
 
#define ARM_RESET_LIMIT       0x0020       //�ֱ۸�λ
#define ARM_ARRIVE_LIMIT      0x0010       //�ֱ۵���









#endif
