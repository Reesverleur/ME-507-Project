// Includes
#include "Motor.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <numeric>

// Constructor only requires a few of the class attributes
	Motor::Motor(TIM_HandleTypeDef* htim1,TIM_HandleTypeDef* htim2,int32_t Ch1,int32_t Ch2){
		tim	  	  = htim1;
		entim	  = htim2;
		FwdCh	  = Ch1;
		RevCh     = Ch2;
		En		  = 0;
		Duty	  = 0;
		Pos		  = 0;
		Kp		  = 0;
		Ki 		  = 0;
		Kd		  = 0;
		setpoint  = 0;
		error	  = 0;
		esum	  = 0;
		derror	  = 0;
	}
// Enables/Disables the motor
	void Motor::Enable(int32_t newEn){
		En = newEn;
	}
// Sets duty cycle based off of percentage value
	void Motor::duty(int32_t newDuty){
		Duty = newDuty;
		if(Duty>=0){
			__HAL_TIM_SET_COMPARE(tim,FwdCh,En*Duty*48);
			__HAL_TIM_SET_COMPARE(tim,RevCh,0);
		}else if(Duty<0){
			__HAL_TIM_SET_COMPARE(tim,RevCh,En*-1*Duty*48);
			__HAL_TIM_SET_COMPARE(tim,FwdCh,0);
		}
	}
	void Motor::Control(int32_t newSet){
		setpoint= newSet;
		Pos = __HAL_TIM_GET_COUNTER(entim);
		derror = (setpoint-Pos)-error;
		error = error+derror;
		esum = esum+error;

		Duty = (Kp*error+Ki*esum+Kd*derror);
		if(Duty>4800){
			Duty = 4800;
		}else if(Duty<-4800){
			Duty = -4800;
		}

		if(Duty>=0){
			__HAL_TIM_SET_COMPARE(tim,FwdCh,En*Duty);
			__HAL_TIM_SET_COMPARE(tim,RevCh,0);
		}else if(Duty<0){
			__HAL_TIM_SET_COMPARE(tim,RevCh,En*-1*Duty);
			__HAL_TIM_SET_COMPARE(tim,FwdCh,0);
		}

	}
	void Motor::setGains(float nKp,float nKi, float nKd){
		Kp = nKp;
		Ki = nKi;
		Kd = nKd;
	}
	void Motor::zeroErrors(){
		error = 0;
		derror = 0;
		esum = 0;
	}





