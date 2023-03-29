#include "motor.h"

void MOTOR_CONTROL(uint8_t direction) //控制函数
{
	static uint8_t step = 0;
	if (direction == 1) //反转
	{
		if (step == 0)
		{
			step = 8;
		}
		else
		{
			step--;
		}
	}
	switch (step)
	{
	case 0:
		MOTOR_1_H;
		MOTOR_2_L;
		MOTOR_3_L;
		MOTOR_4_L;
		break;
	case 1:
		MOTOR_1_H;
		MOTOR_2_H;
		MOTOR_3_L;
		MOTOR_4_L;
		break;
	case 2:
		MOTOR_1_L;
		MOTOR_2_H;
		MOTOR_3_L;
		MOTOR_4_L;
		break;
	case 3:
		MOTOR_1_L;
		MOTOR_2_H;
		MOTOR_3_H;
		MOTOR_4_L;
		break;
	case 4:
		MOTOR_1_L;
		MOTOR_2_L;
		MOTOR_3_H;
		MOTOR_4_L;
		break;
	case 5:
		MOTOR_1_L;
		MOTOR_2_L;
		MOTOR_3_H;
		MOTOR_4_H;
		break;
	case 6:
		MOTOR_1_L;
		MOTOR_2_L;
		MOTOR_3_L;
		MOTOR_4_H;
		break;
	case 7:
		MOTOR_1_H;
		MOTOR_2_L;
		MOTOR_3_L;
		MOTOR_4_H;
		break;
	default:
		break;
	}
	if (direction == 0) //正转
	{
		step++;
		if (8 == step)
		{
			step = 0;
		}
	}
}

void StepMotor_Start(uint16_t angle, uint8_t direction) //驱动函数
{
	int i = 0;
	int pulse = (int)((double)(angle / 5.625) * 64);
	for (i = 0; i < pulse; i++)
	{
		MOTOR_CONTROL(direction);
		HAL_Delay(1);
	}
}

void StepMotor_Stop(void) //停止函数
{
	MOTOR_1_L;
	MOTOR_2_L;
	MOTOR_3_L;
	MOTOR_4_L;
}
