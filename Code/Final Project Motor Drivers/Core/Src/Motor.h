/*
 * Motor_Driver.h
 *
 *  Created on: Jun 8, 2023
 *      Author: reesv
 */

#ifndef SRC_MOTOR_H_
#define SRC_MOTOR_H_
// Includes
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <numeric>
class Motor
{
	public:
	TIM_HandleTypeDef* 	tim;
	TIM_HandleTypeDef* 	entim;
	int32_t				FwdCh;
	int32_t				RevCh;
	int32_t				En;
	int32_t				Duty;
	int16_t				Pos;
	float				Kp;
	float				Ki;
	float				Kd;
	int16_t				setpoint;
	int32_t				error;
	int32_t				esum;
	int32_t				derror;


	Motor(TIM_HandleTypeDef* htim,TIM_HandleTypeDef* htim2,int32_t Ch1,int32_t Ch2);
	void Enable(int32_t newEn);
	void duty(int32_t newDuty);
	void Control(int32_t newSet);
	void setGains(float nKp,float nKi, float nKd);
	void zeroErrors();
};




#endif /* SRC_MOTOR_H_ */
