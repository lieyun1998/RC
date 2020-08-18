#include "includes.h"


unsigned int CAN_Time_Out = 0;
unsigned char can_tx_success_flag = 0;

static void CAN_Delay_Us(unsigned int t)
{
	int i;
	for(i=0;i<t;i++)
	{
		int a=40;
		while(a--);
	}
}




void Odrive_Control_pos1(CAN_TypeDef *CANx, u8 motor_num, int pos, float vel_limit, float accel_limit, float decel_limit)
{
	int cmd_id[3] = {0x00C, 0x011, 0x012}; // ��github�ϵ�md�еĶ�Ӧid
	CanTxMsg tx_message;
	Pos_limit set_point_limit;
	
	for(int i=2;i>-1;i--)
	{	
		tx_message.StdId = (motor_num << 5) + cmd_id[i]; 
		tx_message.IDE = CAN_Id_Standard;
		tx_message.RTR = CAN_RTR_Data;
		tx_message.DLC = 0x08;
		if(i==0)
			{
				tx_message.Data[0] = pos;	
				tx_message.Data[1] = pos>>8;	
				tx_message.Data[2] = pos>>16;	
				tx_message.Data[3] = pos>>24;	
				tx_message.Data[4] = 0;
				tx_message.Data[5] = 0;
				tx_message.Data[6] = 0;
				tx_message.Data[7] = 0;
			}
			
			if(i==1)
			{
				set_point_limit.ActVal =  vel_limit;
				tx_message.Data[0] = set_point_limit.data[0];	
				tx_message.Data[1] = set_point_limit.data[1];	
				tx_message.Data[2] = set_point_limit.data[2];	
				tx_message.Data[3] = set_point_limit.data[3];	
				tx_message.Data[4] = 0;
				tx_message.Data[5] = 0;
				tx_message.Data[6] = 0;
				tx_message.Data[7] = 0;
			}
			
			if(i==2)
			{
				set_point_limit.ActVal =  accel_limit;
				tx_message.Data[0] = set_point_limit.data[0];	
				tx_message.Data[1] = set_point_limit.data[1];	
				tx_message.Data[2] = set_point_limit.data[2];	
				tx_message.Data[3] = set_point_limit.data[3];	
				
				set_point_limit.ActVal =  decel_limit;
				tx_message.Data[4] = set_point_limit.data[0];	
				tx_message.Data[5] = set_point_limit.data[1];	
				tx_message.Data[6] = set_point_limit.data[2];	
				tx_message.Data[7] = set_point_limit.data[3];	
			}

		can_tx_success_flag = 0;
		CAN_Transmit(CANx,&tx_message);

		CAN_Time_Out = 0;
		while(can_tx_success_flag == 0)
		{
				CAN_Delay_Us(1);
				CAN_Time_Out++;
				if(CAN_Time_Out>100)
				{
						break;
				}
		}
	}
}















/****************************************************************************************
                                    ����ָ��
Get_Encoder_Estimates_Tx(CAN_TypeDef *CANx, u8 drive_num)

����������Ϊ call & respond
�˺���Ϊcall��������Ҫ�鿴�����ĵ����ţ�����
����������can�ж��н��ж�ȡ
��������Ϊλ�����ٶ�

drive_num   ȡֵ��Χ 1-12

*****************************************************************************************/

	void Get_Encoder_Estimates_Tx(CAN_TypeDef *CANx, u8 drive_num)
{
    CanTxMsg tx_message;
    tx_message.StdId = (drive_num << 5) + 0x009;
    tx_message.IDE = CAN_Id_Standard;
    tx_message.RTR = CAN_RTR_Data;
    tx_message.DLC = 0x08;
    
    tx_message.Data[0] = 0;	
    tx_message.Data[1] = 0;	
    tx_message.Data[2] = 0;	
    tx_message.Data[3] = 0;	
    tx_message.Data[4] = 0;
    tx_message.Data[5] = 0;
    tx_message.Data[6] = 0;
    tx_message.Data[7] = 0;
	
		can_tx_success_flag = 0;
    CAN_Transmit(CANx,&tx_message);
		
		CAN_Time_Out = 0;
    while(can_tx_success_flag == 0)
    {
        CAN_Delay_Us(1);
        CAN_Time_Out++;
        if(CAN_Time_Out>100)
        {
            break;
        }
    }
}
/****************************************************************************************
                                    ����ָ��
Get_Encoder_Estimates_Rx(CanRxMsg * msg)

�˺�����can�����ж����Զ����ã�

Encoder_Estimates���������ݽṹ

bldc_motor[num].ActVal[0] Ϊnum��λ��
bldc_motor[num].ActVal[1] Ϊnum���ٶ�

num: 1-12
*****************************************************************************************/

Encoder_Estimates bldc_motor[13];

void Get_Encoder_Estimates_Rx(CanRxMsg * msg)
{
	u8 i = 0;
	switch(msg->StdId)
	{
		case 0x020*1 + 0x009:					//0x01      0x020 * num +0x009
		{
			for(i=0;i<8;i++)
			{
				bldc_motor[1].data[i] = msg->Data[i];
			} 
//		printf("encoder_pos_1:%f\r\n",bldc_motor[1].ActVal[0]);
		};break;
		
		case 0x020*2 + 0x009:					//0x02
		{
			for(i=0;i<8;i++)
			{
				bldc_motor[2].data[i] = msg->Data[i];
			}
//		printf("encoder_pos_2:%f\r\n",bldc_motor[2].ActVal[0]);			
		};break;

		case 0x020*3 + 0x009:					//0x03
		{
			for(i=0;i<8;i++)
			{
				bldc_motor[3].data[i] = msg->Data[i];
			}
//		printf("encoder_pos_3:%f\r\n",bldc_motor[3].ActVal[0]);
		};break;
		
		case 0x020*4 + 0x009:					
		{
			for(i=0;i<8;i++)
			{
				bldc_motor[4].data[i] = msg->Data[i];
			}
		};break;
		
		case 0x020*5 + 0x009:					
		{
			for(i=0;i<8;i++)
			{
				bldc_motor[5].data[i] = msg->Data[i];
			}
		};break;
		
		case 0x020*6 + 0x009:				
		{
			for(i=0;i<8;i++)
			{
				bldc_motor[6].data[i] = msg->Data[i];
			}
		};break;
		
		case 0x020*7 + 0x009:				
		{
			for(i=0;i<8;i++)
			{
				bldc_motor[7].data[i] = msg->Data[i];
			}
		};break;
		
		case 0x020*8 + 0x009:					
		{
			for(i=0;i<8;i++)
			{
				bldc_motor[8].data[i] = msg->Data[i];
			}
		};break;
		
		case 0x020*9 + 0x009:					
		{
			for(i=0;i<8;i++)
			{
				bldc_motor[9].data[i] = msg->Data[i];
			}
		};break;
		
		case 0x020*10 + 0x009:					
		{
			for(i=0;i<8;i++)
			{
				bldc_motor[10].data[i] = msg->Data[i];
			}
		};break;

		case 0x020*11 + 0x009:				
		{
			for(i=0;i<8;i++)
			{
				bldc_motor[11].data[i] = msg->Data[i];
			}
		};break;
		
		case 0x020*12 + 0x009:					
		{
			for(i=0;i<8;i++)
			{
				bldc_motor[12].data[i] = msg->Data[i];
			}
		};break;
		
	}
}
/****************************************************************************************
                                    ��������
Get_IQ_Tx(CAN_TypeDef *CANx, u8 drive_num)

Iq Setpoint 0   �����㷢�͵ĵ���Ŀ��ֵ������Ҫ��
Iq Measured	4		������ʵ�ʵ���

����������Ϊ call & respond
�˺���Ϊcall��������Ҫ�鿴�����ĵ����ţ�����
����������can�ж��н��ж�ȡ
��������Ϊ����

drive_num   ȡֵ��Χ 1-12

*****************************************************************************************/



void Get_IQ_Tx(CAN_TypeDef *CANx, u8 drive_num)
{
    CanTxMsg tx_message;
    tx_message.StdId = (drive_num << 5) + 0x014;
    tx_message.IDE = CAN_Id_Standard;
    tx_message.RTR = CAN_RTR_Data;
    tx_message.DLC = 0x08;
    
    tx_message.Data[0] = 0;	
    tx_message.Data[1] = 0;	
    tx_message.Data[2] = 0;	
    tx_message.Data[3] = 0;	
    tx_message.Data[4] = 0;
    tx_message.Data[5] = 0;
    tx_message.Data[6] = 0;
    tx_message.Data[7] = 0;
	
		can_tx_success_flag = 0;
    CAN_Transmit(CANx,&tx_message);
		
		CAN_Time_Out = 0;
    while(can_tx_success_flag == 0)
    {
        CAN_Delay_Us(1);
        CAN_Time_Out++;
        if(CAN_Time_Out>100)
        {
            break;
        }
    }
}


/****************************************************************************************
                                    ����ָ��
Get_IQ_Rx(CanRxMsg * msg)

�˺�����can�����ж����Զ����ã�

Encoder_Estimates���������ݽṹ

bldc_motor_iq[num].Setpoint[0] Ϊnum������ֵ
bldc_motor_iq[num].Measured[1] Ϊnum�Ĳ���ֵ

num: 1-12
*****************************************************************************************/

IQ bldc_motor_iq[13];

void Get_IQ_Rx(CanRxMsg * msg)
{
	u8 i = 0;
	switch(msg->StdId)
	{
		case 0x020*1 + 0x014:					//0x01      0x020 * num +0x014
		{
			for(i=0;i<8;i++)
			{
				bldc_motor_iq[1].data[i] = msg->Data[i];
			}	
//		printf("IQ_1:%f\r\n",bldc_motor_iq[1].ActVal[0]);			
		};break;
		
		case 0x020*2 + 0x014:					//0x02
		{
			for(i=0;i<8;i++)
			{
				bldc_motor_iq[2].data[i] = msg->Data[i];
			} 
//		printf("IQ_1:%f\r\n",bldc_motor_iq[2].ActVal[0]);
		};break;

		case 0x020*3 + 0x014:					//0x03
		{
			for(i=0;i<8;i++)
			{
				bldc_motor_iq[3].data[i] = msg->Data[i];
			}
		};break;
		
		case 0x020*4 + 0x014:					
		{
			for(i=0;i<8;i++)
			{
				bldc_motor_iq[4].data[i] = msg->Data[i];
			}
		};break;
		
		case 0x020*5 + 0x014:					
		{
			for(i=0;i<8;i++)
			{
				bldc_motor_iq[5].data[i] = msg->Data[i];
			}
		};break;
		
		case 0x020*6 + 0x014:				
		{
			for(i=0;i<8;i++)
			{
				bldc_motor_iq[6].data[i] = msg->Data[i];
			}
		};break;
		
		case 0x020*7 + 0x014:				
		{
			for(i=0;i<8;i++)
			{
				bldc_motor_iq[7].data[i] = msg->Data[i];
			}
//			printf("IQ_1:%f\r\n",bldc_motor_iq[7].ActVal[0]);	
		};break;
		case 0x020*8 + 0x014:					
		{
			for(i=0;i<8;i++)
			{
				bldc_motor_iq[8].data[i] = msg->Data[i];
			}
		};break;
		
		case 0x020*9 + 0x014:					
		{
			for(i=0;i<8;i++)
			{
				bldc_motor_iq[9].data[i] = msg->Data[i];
			}
		};break;
		
		case 0x020*10 + 0x014:					
		{
			for(i=0;i<8;i++)
			{
				bldc_motor_iq[10].data[i] = msg->Data[i];
			}
		};break;

		case 0x020*11 + 0x014:				
		{
			for(i=0;i<8;i++)
			{
				bldc_motor_iq[11].data[i] = msg->Data[i];
			}
		};break;
		
		case 0x020*12 + 0x014:					
		{
			for(i=0;i<8;i++)
			{
				bldc_motor_iq[12].data[i] = msg->Data[i];
			}
		};break;
		
	}
}










void odrive_control(u8 motor_num)
{
//	Odrive_Control_pos1(CAN_TypeDef *CANx, u8 motor_num, int pos, float vel_limit, float accel_limit, float decel_limit)
	switch(motor_num)
	{
		case 1:			
		{
			Odrive_Control_pos1(CAN2,motor_num, 0, 4000*9*0.3, 4000*9*0.2, 4000*9*0.2);
		
			OSTimeDly(1000);

			Odrive_Control_pos1(CAN2,motor_num, 4000*6, 4000*9*0.3, 4000*9*0.2, 4000*9*0.2);
			
			OSTimeDly(1000);OSTimeDly(1000);

			Odrive_Control_pos1(CAN2,motor_num, 0, 4000*9*0.3, 4000*9*0.2, 4000*9*0.2);
			
      ROBOT.KICK_STATE = KICK_SUCCEED;			
		};break;
		
		case 2:					
		{
			Odrive_Control_pos1(CAN2,motor_num, 0, 4000*9*0.3, 4000*9*0.2, 4000*9*0.2);
		
			OSTimeDly(1000);

			Odrive_Control_pos1(CAN2,motor_num, 4000*6, 4000*9*0.3, 4000*9*0.2, 4000*9*0.2);
			
			OSTimeDly(1000);OSTimeDly(1000);

			Odrive_Control_pos1(CAN2,motor_num, 0, 4000*9*0.3, 4000*9*0.2, 4000*9*0.2);	
			
			ROBOT.KICK_STATE = KICK_SUCCEED;
		};break;
		
		default: 
			break;

	}

}
