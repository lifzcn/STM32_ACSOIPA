#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "stm32f1xx_hal.h"
#include "main.h"

#define MOTOR_1_H HAL_GPIO_WritePin(SM_IN1_GPIO_Port, SM_IN1_Pin, GPIO_PIN_SET)
#define MOTOR_1_L HAL_GPIO_WritePin(SM_IN1_GPIO_Port, SM_IN1_Pin, GPIO_PIN_RESET)

#define MOTOR_2_H HAL_GPIO_WritePin(SM_IN2_GPIO_Port, SM_IN2_Pin, GPIO_PIN_SET)
#define MOTOR_2_L HAL_GPIO_WritePin(SM_IN2_GPIO_Port, SM_IN2_Pin, GPIO_PIN_RESET)

#define MOTOR_3_H HAL_GPIO_WritePin(SM_IN3_GPIO_Port, SM_IN3_Pin, GPIO_PIN_SET)
#define MOTOR_3_L HAL_GPIO_WritePin(SM_IN3_GPIO_Port, SM_IN3_Pin, GPIO_PIN_RESET)

#define MOTOR_4_H HAL_GPIO_WritePin(SM_IN4_GPIO_Port, SM_IN4_Pin, GPIO_PIN_SET)
#define MOTOR_4_L HAL_GPIO_WritePin(SM_IN4_GPIO_Port, SM_IN4_Pin, GPIO_PIN_RESET)

void MOTOR_CONTROL(uint8_t direction);
void StepMotor_Start(uint16_t angle, uint8_t direction);
void StepMotor_Stop(void);

#endif
