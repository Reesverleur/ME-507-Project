#include "bluetooth.h"


// Implementation of default constructor
bluetooth::bluetooth(void)
{

}


// Implementation of initializing constructor
bluetooth:bluetooth( UART_HandleTypeDef* _huartX)
		:huartX(_huartX)
{

}

void bluetooth::send(const char* _message)
{
	strcpy(sentMsg, _message);
	int32_t len = sprintf(msg_buff, sentMsg);
	HAL_UART_Transmit_IT(&huart1, (uint8_t*) msg_buff, len);
}

void bluetooth::callback(void)
{

}
