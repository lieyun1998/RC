#include "includes.h"


unsigned char can1_tx_success_flag = 0;  // �����ж�can1������Ϣ�Ƿ�ɹ�
unsigned int CAN_Time_Out = 0;  // can������Ϣ��ʱ�������

short Real_Current_Value[4] = {0};
short Real_Velocity_Value[4] = {0};
long Real_Position_Value[4] = {0};
char Real_Online[4] = {0};
char Real_Ctl1_Value[4] = {0};
char Real_Ctl2_Value[4] = {0};


static void robomodule_delay_us(unsigned int t)
{
	int i;
	for(i=0;i<t;i++)
	{
		int a=40;
		while(a--);
	}
}


/****************************************************************************************
                                       ��λָ��
Group   ȡֵ��Χ 0-7
Number  ȡֵ��Χ 0-15������Number==0ʱ��Ϊ�㲥����
*****************************************************************************************/
void CAN_RoboModule_DRV_Reset(unsigned char Group,unsigned char Number)
{
    unsigned short can_id = 0x000;
    CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD;    //��׼֡
    tx_message.RTR = CAN_RTR_DATA;  //����֡
    tx_message.DLC = 0x08;          //֡����Ϊ8
    
    if((Group<=7)&&(Number<=15))
    {
        can_id |= Group<<8;
        can_id |= Number<<4;
    }
    else
    {
        return;
    }
    
    tx_message.StdId = can_id;      //֡IDΪ���������CAN_ID
    
    tx_message.Data[0] = 0x55;
    tx_message.Data[1] = 0x55;
    tx_message.Data[2] = 0x55;
    tx_message.Data[3] = 0x55;
    tx_message.Data[4] = 0x55;
    tx_message.Data[5] = 0x55;
    tx_message.Data[6] = 0x55;
    tx_message.Data[7] = 0x55;
    
    can1_tx_success_flag = 0;
    CAN_Transmit(CAN1,&tx_message);
    
    CAN_Time_Out = 0;
    while(can1_tx_success_flag == 0)
    {
        robomodule_delay_us(1);
        CAN_Time_Out++;
        if(CAN_Time_Out>100)
        {
            break;
        }
    }
}


/****************************************************************************************
                                     ģʽѡ��ָ��
Group   ȡֵ��Χ 0-7
Number  ȡֵ��Χ 0-15������Number==0ʱ��Ϊ�㲥����

Mode    ȡֵ��Χ

OpenLoop_Mode                       0x01
Current_Mode                        0x02
Velocity_Mode                       0x03
Position_Mode                       0x04
Velocity_Position_Mode              0x05
Current_Velocity_Mode               0x06
Current_Position_Mode               0x07
Current_Velocity_Position_Mode      0x08
*****************************************************************************************/
void CAN_RoboModule_DRV_Mode_Choice(unsigned char Group,unsigned char Number,unsigned char Mode)
{
    unsigned short can_id = 0x001;
    CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD;    //��׼֡
    tx_message.RTR = CAN_RTR_DATA;  //����֡
    tx_message.DLC = 0x08;          //֡����Ϊ8
    
    if((Group<=7)&&(Number<=15))
    {
        can_id |= Group<<8;
        can_id |= Number<<4;
    }
    else
    {
        return;
    }
    
    tx_message.StdId = can_id;      //֡IDΪ���������CAN_ID
    
    tx_message.Data[0] = Mode;
    tx_message.Data[1] = 0x55;
    tx_message.Data[2] = 0x55;
    tx_message.Data[3] = 0x55;
    tx_message.Data[4] = 0x55;
    tx_message.Data[5] = 0x55;
    tx_message.Data[6] = 0x55;
    tx_message.Data[7] = 0x55;
    
    can1_tx_success_flag = 0;
    CAN_Transmit(CAN1,&tx_message);
    
    CAN_Time_Out = 0;
    while(can1_tx_success_flag == 0)
    {
        robomodule_delay_us(1);
        CAN_Time_Out++;
        if(CAN_Time_Out>100)
        {
            break;
        }
    }
}


/****************************************************************************************
                                   ����ģʽ�µ�����ָ��
Group   ȡֵ��Χ 0-7

Number  ȡֵ��Χ 0-15������Number==0ʱ��Ϊ�㲥����

temp_pwm��ȡֵ��Χ���£�
0 ~ +5000����ֵ5000������temp_pwm = ��5000ʱ����������ѹΪ��Դ��ѹ

*****************************************************************************************/
void CAN_RoboModule_DRV_OpenLoop_Mode(unsigned char Group,unsigned char Number,short Temp_PWM)
{
    unsigned short can_id = 0x002;
    CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD;    //��׼֡
    tx_message.RTR = CAN_RTR_DATA;  //����֡
    tx_message.DLC = 0x08;          //֡����Ϊ8
    
    if((Group<=7)&&(Number<=15))
    {
        can_id |= Group<<8;
        can_id |= Number<<4;
    }
    else
    {
        return;
    }
    
    tx_message.StdId = can_id;      //֡IDΪ���������CAN_ID

    if(Temp_PWM > 5000)
    {
        Temp_PWM = 5000;
    }
    else if(Temp_PWM < -5000)
    {
        Temp_PWM = -5000;
    }
    
    tx_message.Data[0] = (unsigned char)((Temp_PWM>>8)&0xff);
    tx_message.Data[1] = (unsigned char)(Temp_PWM&0xff);
    tx_message.Data[2] = 0x55;
    tx_message.Data[3] = 0x55;
    tx_message.Data[4] = 0x55;
    tx_message.Data[5] = 0x55;
    tx_message.Data[6] = 0x55;
    tx_message.Data[7] = 0x55;
    
    can1_tx_success_flag = 0;
    CAN_Transmit(CAN1,&tx_message);
    
    CAN_Time_Out = 0;
    while(can1_tx_success_flag == 0)
    {
        robomodule_delay_us(1);
        CAN_Time_Out++;
        if(CAN_Time_Out>100)
        {
            break;
        }
    }
}


/****************************************************************************************
                                   ����ģʽ�µ�����ָ��
Group   ȡֵ��Χ 0-7

Number  ȡֵ��Χ 0-15������Number==0ʱ��Ϊ�㲥����

temp_pwm��ȡֵ��Χ���£�
0 ~ +5000����ֵ5000������temp_pwm = 5000ʱ����������ѹΪ��Դ��ѹ

temp_current��ȡֵ��Χ���£�
-32768 ~ +32767����λmA

*****************************************************************************************/
void CAN_RoboModule_DRV_Current_Mode(unsigned char Group,unsigned char Number,short Temp_PWM,short Temp_Current)
{
    unsigned short can_id = 0x003;
    CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD;    //��׼֡
    tx_message.RTR = CAN_RTR_DATA;  //����֡
    tx_message.DLC = 0x08;          //֡����Ϊ8
    
    if((Group<=7)&&(Number<=15))
    {
        can_id |= Group<<8;
        can_id |= Number<<4;
    }
    else
    {
        return;
    }
    
    tx_message.StdId = can_id;      //֡IDΪ���������CAN_ID

    if(Temp_PWM > 5000)
    {
        Temp_PWM = 5000;
    }
    else if(Temp_PWM < -5000)
    {
        Temp_PWM = -5000;
    }
    
    if(Temp_PWM < 0)
    {
        Temp_PWM = abs(Temp_PWM);
    }
    
    tx_message.Data[0] = (unsigned char)((Temp_PWM>>8)&0xff);
    tx_message.Data[1] = (unsigned char)(Temp_PWM&0xff);
    tx_message.Data[2] = (unsigned char)((Temp_Current>>8)&0xff);
    tx_message.Data[3] = (unsigned char)(Temp_Current&0xff);
    tx_message.Data[4] = 0x55;
    tx_message.Data[5] = 0x55;
    tx_message.Data[6] = 0x55;
    tx_message.Data[7] = 0x55;
    
    can1_tx_success_flag = 0;
    CAN_Transmit(CAN1,&tx_message);
    
    CAN_Time_Out = 0;
    while(can1_tx_success_flag == 0)
    {
        robomodule_delay_us(1);
        CAN_Time_Out++;
        if(CAN_Time_Out>100)
        {
            break;
        }
    }
}


/****************************************************************************************
                                   �ٶ�ģʽ�µ�����ָ��
Group   ȡֵ��Χ 0-7

Number  ȡֵ��Χ 0-15������Number==0ʱ��Ϊ�㲥����

temp_pwm��ȡֵ��Χ���£�
0 ~ +5000����ֵ5000������temp_pwm = 5000ʱ����������ѹΪ��Դ��ѹ

temp_velocity��ȡֵ��Χ���£�
-32768 ~ +32767����λRPM

*****************************************************************************************/
void CAN_RoboModule_DRV_Velocity_Mode(unsigned char Group,unsigned char Number,short Temp_PWM,short Temp_Velocity)
{
    unsigned short can_id = 0x004;
    CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD;    //��׼֡
    tx_message.RTR = CAN_RTR_DATA;  //����֡
    tx_message.DLC = 0x08;          //֡����Ϊ8
    
    if((Group<=7)&&(Number<=15))
    {
        can_id |= Group<<8;
        can_id |= Number<<4;
    }
    else
    {
        return;
    }
    
    tx_message.StdId = can_id;      //֡IDΪ���������CAN_ID

    if(Temp_PWM > 5000)
    {
        Temp_PWM = 5000;
    }
    else if(Temp_PWM < -5000)
    {
        Temp_PWM = -5000;
    }
    
    if(Temp_PWM < 0)
    {
        Temp_PWM = abs(Temp_PWM);
    }
    
    tx_message.Data[0] = (unsigned char)((Temp_PWM>>8)&0xff);
    tx_message.Data[1] = (unsigned char)(Temp_PWM&0xff);
    tx_message.Data[2] = (unsigned char)((Temp_Velocity>>8)&0xff);
    tx_message.Data[3] = (unsigned char)(Temp_Velocity&0xff);
    tx_message.Data[4] = 0x55;
    tx_message.Data[5] = 0x55;
    tx_message.Data[6] = 0x55;
    tx_message.Data[7] = 0x55;
    
    can1_tx_success_flag = 0;
    CAN_Transmit(CAN1,&tx_message);
    
    CAN_Time_Out = 0;
    while(can1_tx_success_flag == 0)
    {
        robomodule_delay_us(1);
        CAN_Time_Out++;
        if(CAN_Time_Out>100)
        {
            break;
        }
    }
}


/****************************************************************************************
                                   λ��ģʽ�µ�����ָ��
Group   ȡֵ��Χ 0-7

Number  ȡֵ��Χ 0-15������Number==0ʱ��Ϊ�㲥����

temp_pwm��ȡֵ��Χ���£�
0 ~ +5000����ֵ5000������temp_pwm = 5000ʱ����������ѹΪ��Դ��ѹ

temp_position��ȡֵ��Χ���£�
-2147483648~+2147483647����λqc

*****************************************************************************************/
void CAN_RoboModule_DRV_Position_Mode(unsigned char Group,unsigned char Number,short Temp_PWM,long Temp_Position)
{
    unsigned short can_id = 0x005;
    CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD;    //��׼֡
    tx_message.RTR = CAN_RTR_DATA;  //����֡
    tx_message.DLC = 0x08;          //֡����Ϊ8
    
    if((Group<=7)&&(Number<=15))
    {
        can_id |= Group<<8;
        can_id |= Number<<4;
    }
    else
    {
        return;
    }
    
    tx_message.StdId = can_id;      //֡IDΪ���������CAN_ID

    if(Temp_PWM > 5000)
    {
        Temp_PWM = 5000;
    }
    else if(Temp_PWM < -5000)
    {
        Temp_PWM = -5000;
    }
    
    if(Temp_PWM < 0)
    {
        Temp_PWM = abs(Temp_PWM);
    }
    
    tx_message.Data[0] = (unsigned char)((Temp_PWM>>8)&0xff);
    tx_message.Data[1] = (unsigned char)(Temp_PWM&0xff);
    tx_message.Data[2] = 0x55;
    tx_message.Data[3] = 0x55;
    tx_message.Data[4] = (unsigned char)((Temp_Position>>24)&0xff);
    tx_message.Data[5] = (unsigned char)((Temp_Position>>16)&0xff);
    tx_message.Data[6] = (unsigned char)((Temp_Position>>8)&0xff);
    tx_message.Data[7] = (unsigned char)(Temp_Position&0xff);
    
    can1_tx_success_flag = 0;
    CAN_Transmit(CAN1,&tx_message);
    
    CAN_Time_Out = 0;
    while(can1_tx_success_flag == 0)
    {
        robomodule_delay_us(1);
        CAN_Time_Out++;
        if(CAN_Time_Out>100)
        {
            break;
        }
    }
}


/****************************************************************************************
                                  �ٶ�λ��ģʽ�µ�����ָ��
Group   ȡֵ��Χ 0-7

Number  ȡֵ��Χ 0-15������Number==0ʱ��Ϊ�㲥����

temp_pwm��ȡֵ��Χ���£�
0 ~ +5000����ֵ5000������temp_pwm = 5000ʱ����������ѹΪ��Դ��ѹ

temp_velocity��ȡֵ��Χ���£�
0 ~ +32767����λRPM

temp_position��ȡֵ��Χ���£�
-2147483648~+2147483647����λqc
*****************************************************************************************/
void CAN_RoboModule_DRV_Velocity_Position_Mode(unsigned char Group,unsigned char Number,short Temp_PWM,short Temp_Velocity,long Temp_Position)
{
    unsigned short can_id = 0x006;
    CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD;    //��׼֡
    tx_message.RTR = CAN_RTR_DATA;  //����֡
    tx_message.DLC = 0x08;          //֡����Ϊ8
    
    if((Group<=7)&&(Number<=15))
    {
        can_id |= Group<<8;
        can_id |= Number<<4;
    }
    else
    {
        return;
    }
    
    tx_message.StdId = can_id;      //֡IDΪ���������CAN_ID

    if(Temp_PWM > 5000)
    {
        Temp_PWM = 5000;
    }
    else if(Temp_PWM < -5000)
    {
        Temp_PWM = -5000;
    }
    
    if(Temp_PWM < 0)
    {
        Temp_PWM = abs(Temp_PWM);
    }
    
    if(Temp_Velocity < 0)
    {
        Temp_Velocity = abs(Temp_Velocity);
    }
    
    tx_message.Data[0] = (unsigned char)((Temp_PWM>>8)&0xff);
    tx_message.Data[1] = (unsigned char)(Temp_PWM&0xff);
    tx_message.Data[2] = (unsigned char)((Temp_Velocity>>8)&0xff);
    tx_message.Data[3] = (unsigned char)(Temp_Velocity&0xff);
    tx_message.Data[4] = (unsigned char)((Temp_Position>>24)&0xff);
    tx_message.Data[5] = (unsigned char)((Temp_Position>>16)&0xff);
    tx_message.Data[6] = (unsigned char)((Temp_Position>>8)&0xff);
    tx_message.Data[7] = (unsigned char)(Temp_Position&0xff);
    
    can1_tx_success_flag = 0;
    CAN_Transmit(CAN1,&tx_message);
    
    CAN_Time_Out = 0;
    while(can1_tx_success_flag == 0)
    {
        robomodule_delay_us(1);
        CAN_Time_Out++;
        if(CAN_Time_Out>100)
        {
            break;
        }
    }
}


/****************************************************************************************
                                  �����ٶ�ģʽ�µ�����ָ��
Group   ȡֵ��Χ 0-7

Number  ȡֵ��Χ 0-15������Number==0ʱ��Ϊ�㲥����

temp_current��ȡֵ��Χ���£�
0 ~ +32767����λmA

temp_velocity��ȡֵ��Χ���£�
-32768 ~ +32767����λRPM

*****************************************************************************************/
void CAN_RoboModule_DRV_Current_Velocity_Mode(unsigned char Group,unsigned char Number,short Temp_Current,short Temp_Velocity)
{
    unsigned short can_id = 0x007;
    CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD;    //��׼֡
    tx_message.RTR = CAN_RTR_DATA;  //����֡
    tx_message.DLC = 0x08;          //֡����Ϊ8
    
    if((Group<=7)&&(Number<=15))
    {
        can_id |= Group<<8;
        can_id |= Number<<4;
    }
    else
    {
        return;
    }
    
    tx_message.StdId = can_id;      //֡IDΪ���������CAN_ID
    
    if(Temp_Current < 0)
    {
        Temp_Current = abs(Temp_Current);
    }
    
    tx_message.Data[0] = (unsigned char)((Temp_Current>>8)&0xff);
    tx_message.Data[1] = (unsigned char)(Temp_Current&0xff);
    tx_message.Data[2] = (unsigned char)((Temp_Velocity>>8)&0xff);
    tx_message.Data[3] = (unsigned char)(Temp_Velocity&0xff);
    tx_message.Data[4] = 0x55;
    tx_message.Data[5] = 0x55;
    tx_message.Data[6] = 0x55;
    tx_message.Data[7] = 0x55;
    
    can1_tx_success_flag = 0;
    CAN_Transmit(CAN1,&tx_message);
    
    CAN_Time_Out = 0;
    while(can1_tx_success_flag == 0)
    {
        robomodule_delay_us(1);
        CAN_Time_Out++;
        if(CAN_Time_Out>100)
        {
            break;
        }
    }
}


/****************************************************************************************
                                  ����λ��ģʽ�µ�����ָ��
Group   ȡֵ��Χ 0-7

Number  ȡֵ��Χ 0-15������Number==0ʱ��Ϊ�㲥����

temp_current��ȡֵ��Χ���£�
0 ~ +32767����λmA

temp_position��ȡֵ��Χ���£�
-2147483648~+2147483647����λqc

*****************************************************************************************/
void CAN_RoboModule_DRV_Current_Position_Mode(unsigned char Group,unsigned char Number,short Temp_Current,long Temp_Position)
{
    unsigned short can_id = 0x008;
    CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD;    //��׼֡
    tx_message.RTR = CAN_RTR_DATA;  //����֡
    tx_message.DLC = 0x08;          //֡����Ϊ8
    
    if((Group<=7)&&(Number<=15))
    {
        can_id |= Group<<8;
        can_id |= Number<<4;
    }
    else
    {
        return;
    }
    
    tx_message.StdId = can_id;      //֡IDΪ���������CAN_ID

    
    if(Temp_Current < 0)
    {
        Temp_Current = abs(Temp_Current);
    }
    
    tx_message.Data[0] = (unsigned char)((Temp_Current>>8)&0xff);
    tx_message.Data[1] = (unsigned char)(Temp_Current&0xff);
    tx_message.Data[2] = 0x55;
    tx_message.Data[3] = 0x55;
    tx_message.Data[4] = (unsigned char)((Temp_Position>>24)&0xff);
    tx_message.Data[5] = (unsigned char)((Temp_Position>>16)&0xff);
    tx_message.Data[6] = (unsigned char)((Temp_Position>>8)&0xff);
    tx_message.Data[7] = (unsigned char)(Temp_Position&0xff);
    
    can1_tx_success_flag = 0;
    CAN_Transmit(CAN1,&tx_message);
    
    CAN_Time_Out = 0;
    while(can1_tx_success_flag == 0)
    {
        robomodule_delay_us(1);
        CAN_Time_Out++;
        if(CAN_Time_Out>100)
        {
            break;
        }
    }
}


/****************************************************************************************
                                  �����ٶ�λ��ģʽ�µ�����ָ��
Group   ȡֵ��Χ 0-7

Number  ȡֵ��Χ 0-15������Number==0ʱ��Ϊ�㲥����

temp_current��ȡֵ��Χ���£�
0 ~ +32767����λmA

temp_velocity��ȡֵ��Χ���£�
0 ~ +32767����λRPM

temp_position��ȡֵ��Χ���£�
-2147483648~+2147483647����λqc

*****************************************************************************************/
void CAN_RoboModule_DRV_Current_Velocity_Position_Mode(unsigned char Group,unsigned char Number,short Temp_Current,short Temp_Velocity,long Temp_Position)
{
    unsigned short can_id = 0x009;
    CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD;    //��׼֡
    tx_message.RTR = CAN_RTR_DATA;  //����֡
    tx_message.DLC = 0x08;          //֡����Ϊ8
    
    if((Group<=7)&&(Number<=15))
    {
        can_id |= Group<<8;
        can_id |= Number<<4;
    }
    else
    {
        return;
    }
    
    tx_message.StdId = can_id;      //֡IDΪ���������CAN_ID
    
    if(Temp_Current < 0)
    {
        Temp_Current = abs(Temp_Current);
    }
    
    if(Temp_Velocity < 0)
    {
        Temp_Velocity = abs(Temp_Velocity);
    }
    
    tx_message.Data[0] = (unsigned char)((Temp_Current>>8)&0xff);
    tx_message.Data[1] = (unsigned char)(Temp_Current&0xff);
    tx_message.Data[2] = (unsigned char)((Temp_Velocity>>8)&0xff);
    tx_message.Data[3] = (unsigned char)(Temp_Velocity&0xff);
    tx_message.Data[4] = (unsigned char)((Temp_Position>>24)&0xff);
    tx_message.Data[5] = (unsigned char)((Temp_Position>>16)&0xff);
    tx_message.Data[6] = (unsigned char)((Temp_Position>>8)&0xff);
    tx_message.Data[7] = (unsigned char)(Temp_Position&0xff);
    
    can1_tx_success_flag = 0;
    CAN_Transmit(CAN1,&tx_message);
    
    CAN_Time_Out = 0;
    while(can1_tx_success_flag == 0)
    {
        robomodule_delay_us(1);
        CAN_Time_Out++;
        if(CAN_Time_Out>100)
        {
            break;
        }
    }
}


/****************************************************************************************
                                      ����ָ��
Temp_Time1��ȡֵ��Χ: 0 ~ 255��Ϊ0ʱ��Ϊ�رյ����ٶ�λ�÷�������
Temp_Time2��ȡֵ��Χ: 0 ~ 255��Ϊ0ʱ��Ϊ�ر���λ�źŷ�������
*****************************************************************************************/
void CAN_RoboModule_DRV_Config(unsigned char Group,unsigned char Number,unsigned char Temp_Time1,unsigned char Temp_Time2)
{
    unsigned short can_id = 0x00A;
    CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD;    //��׼֡
    tx_message.RTR = CAN_RTR_DATA;  //����֡
    tx_message.DLC = 0x08;          //֡����Ϊ8
    
    if((Group<=7)&&(Number<=15))
    {
        can_id |= Group<<8;
        can_id |= Number<<4;
    }
    else
    {
        return;
    }
    
    tx_message.StdId = can_id;
    
    tx_message.Data[0] = Temp_Time1;
    tx_message.Data[1] = Temp_Time2;
    tx_message.Data[2] = 0x55;
    tx_message.Data[3] = 0x55;
    tx_message.Data[4] = 0x55;
    tx_message.Data[5] = 0x55;
    tx_message.Data[6] = 0x55;
    tx_message.Data[7] = 0x55;
    
    can1_tx_success_flag = 0;
    CAN_Transmit(CAN1,&tx_message);
    
    CAN_Time_Out = 0;
    while(can1_tx_success_flag == 0)
    {
        robomodule_delay_us(1);
        CAN_Time_Out++;
        if(CAN_Time_Out>100)
        {
            break;
        }
    }
}


/****************************************************************************************
                                      ���߼��
*****************************************************************************************/
void CAN_RoboModule_DRV_Online_Check(unsigned char Group,unsigned char Number)
{
    unsigned short can_id = 0x00F;
    CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD;    //��׼֡
    tx_message.RTR = CAN_RTR_DATA;  //����֡
    tx_message.DLC = 0x08;          //֡����Ϊ8
    
    if((Group<=7)&&(Number<=15))
    {
        can_id |= Group<<8;
        can_id |= Number<<4;
    }
    else
    {
        return;
    }
    
    tx_message.StdId = can_id;      //֡IDΪ���������CAN_ID
    
    tx_message.Data[0] = 0x55;
    tx_message.Data[1] = 0x55;
    tx_message.Data[2] = 0x55;
    tx_message.Data[3] = 0x55;
    tx_message.Data[4] = 0x55;
    tx_message.Data[5] = 0x55;
    tx_message.Data[6] = 0x55;
    tx_message.Data[7] = 0x55;
    
    can1_tx_success_flag = 0;
    CAN_Transmit(CAN1,&tx_message);
    
    CAN_Time_Out = 0;
    while(can1_tx_success_flag == 0)
    {
        robomodule_delay_us(1);
        CAN_Time_Out++;
        if(CAN_Time_Out>100)
        {
            break;
        }
    }
}
