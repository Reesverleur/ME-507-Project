/*
 * coms.cpp
 *
 *  Created on: Jun 12, 2023
 *      Author: reesv
 */
#include "coms.h"

coms::coms(UART_HandleTypeDef* huart){
	uart = huart;
	start = "begin";
	req = "data";
	rotate = 0;
	translate = 0;

	cpr = 24;
	gear = 46.85;
	wheeldist = 150;
	wheelrad = 30;
}

void coms::begin(){
	HAL_UART_Transmit_IT(uart,(uint8_t*) &start,5);

}

void coms::request(){
	HAL_UART_Transmit_IT(uart,(uint8_t*) &req,4);
}

void coms::decode(){
	if(messbuff[0] == 'R' && messbuff[4] = 'T'){
		rotate = (messbuff[1]-'0')*100+(messbuff[2]-'0')*10+(messbuff[3]-'0')*1;
		translate = (messbuff[5]-'0')*1000+(messbuff[6]-'0')*100+(messbuff[7]-'0')*10+(messbuff[8]-'0')*1;

	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart){
	if(huart == coms::uart){
		HAL_UART_Receive_IT(coms::uart,(uint8_t*) &(coms::messbuff),10);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart){
	if(huart == coms::uart){
		if(coms::messbuff == "stop000000"){
			//Handle E-stop condition
		}
	}
}
