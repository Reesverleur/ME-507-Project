// Includes
#include "Pixy2_Driver.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <numeric>

// Constructor only requires a few of the class attributes
	Pixy2::Pixy2(SPI_HandleTypeDef* hspi,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin){
		spi	  	  = hspi;											// pointer to spi object
		SS_Port	  = GPIOx;											// pointer to ss port
		SS_Pin    = GPIO_Pin;										// pointer to ss pin

	}
// Updates block data for pixy2 object
	void Pixy2::getBlock(uint8_t sigmap,uint8_t maxblocks){
		uint8_t blocReq[] = {0xae,0xc1,32,2,sigmap,maxblocks};		// block request data
		Length = 20;												// length of response
		HAL_GPIO_WritePin(SS_Port,SS_Pin,GPIO_PIN_RESET);			// drive ss pin low to enable communication
		HAL_SPI_Transmit_IT(spi,(uint8_t*) &blocReq,6);				// transmit block request return data is put in Data
		int16_t n;
		for(n=0;n<99;n++){											// iterate over all elements in Data
			if(Data[n] == 0xaf && Data[n+1] == 0xc1){				// check for first occurrence of  0xaec1
				StartByte = n;										// set as start byte
				int16_t csum = std::accumulate(Data+StartByte+6,Data+StartByte+20,0);
				if(csum == (Data[StartByte+5]<<8)+Data[StartByte+4]){
					memcpy(&Block,&Data[n],Length);					// copy the data to Block for stability
				}
				n = 100;											// exit out of for loop early
			}
		}

	}
// Sets coordinates from last captured block
	void Pixy2::setCoords(){
		// Be sure there isn't an error state (0x0101)
		if(!(Block[8]==1 && Block[9]==1 && Block[10]==1 && Block[11]==1)){
			// If not, set coords from fetched block data
			Coords[0] = (Block[9]<<8)+Block[8];
			Coords[1] = (Block[11]<<8)+Block[10];
		} else{
			// otherwise return -1 for an error
			Coords[0] = -1;
			Coords[1] = -1;
		}
	}




	void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef* hspi){			// Transmit callback function
		if(hspi == Pixy2::spi){
			HAL_SPI_Receive_IT(hspi,(uint8_t*) &(Pixy2::Data),100);	// Start a receive command and put return data in Data
		}
	}
	void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef* hspi){			// Receive callback function
		if (hspi == Pixy2::spi){
			HAL_GPIO_WritePin(Pixy2::SS_Port,Pixy2::SS_Pin,GPIO_PIN_SET);	// Write ss pin high to disable communication
		}
	}
