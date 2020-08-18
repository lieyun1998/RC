#include "includes.h"


void bsp_init()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	delay_init(168);
	uart_init(115200);
	
	Location_init();
	
	cs_GPIO_init();
	ls_GPIO_init();
	cylinder_GPIO_init();
	Key_GPIO_Init();
	
	PS2_init();

	beep_GPIO_init();
	
	can1_CAN1_init();
	
	can2_CAN2_init();
	
//	adc_adc3_init();
	
	m3508_motor_init();
	
	moving_init();
	
	Launch_Motor_init(20000-1,83);
	delay_ms(1000);delay_ms(1000);
	delay_ms(1000);delay_ms(1000);
  TIM9_PWM_Init(20000-1,83);
	
	//cd_chassis_driver_init();
	
	
	
}



