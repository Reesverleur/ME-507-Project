/*
 * Pixy2_Driver.h
 *
 *  Created on: May 25, 2023
 *      Author: reesv
 */

#ifndef SRC_PIXY2_DRIVER_H_
#define SRC_PIXY2_DRIVER_H_
// Includes
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <numeric>
// Class Declaration
class Pixy2
{

	private:								// Private variables
		int StartByte = 0;					// Start index of requested data
		int Length = 0;						// Length of expected response
	public:									// Public variables
		uint8_t Block[40] = {0};			// Block response data
		static SPI_HandleTypeDef* spi;		// pointer to spi object
		static GPIO_TypeDef* SS_Port;		// pointer to ss port
		static uint16_t SS_Pin;				// pointer to ss pin
		int Coords[2] = {0};				// coordinates of block
		static uint8_t Data[100];			// Raw Data from response

		// Constructor
		Pixy2(SPI_HandleTypeDef* hspi,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
		// Function to get new block data
		void getBlock(uint8_t sigmap,uint8_t maxblocks);
		// Function to set coords from current block data
		void setCoords();
};

// Callback functions for SPI object
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef* hspi);
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef* hspi);


#endif /* SRC_PIXY2_DRIVER_H_ */
