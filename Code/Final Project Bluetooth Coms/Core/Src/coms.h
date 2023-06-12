/*
 * coms.h
 *
 *  Created on: Jun 12, 2023
 *      Author: reesv
 */

#ifndef SRC_COMS_H_
#define SRC_COMS_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <numeric>
class coms{
	private:
		int32_t cpr;
		float   gear;
		float   wheelrad;
		float	wheeldist;
	public:
		static UART_Handle_TypeDef 	uart;
		char 						start[5];
		char						req[4];
		static char					messbuff[10];
		int32_t						rotate;
		int32_t						translate;

	coms::coms(UART_HandleTypeDef* huart);
	void coms::begin();
	void coms::request();
	void coms::decode();
};




void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart);

#endif /* SRC_COMS_H_ */
