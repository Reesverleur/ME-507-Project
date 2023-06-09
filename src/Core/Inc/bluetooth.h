#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H

#include <string.h>

class bluetooth
{
private:
	UART_HandleTypeDef* huartX;		// Holds pointer to UART handle
	char sentMsg[100];				// Holds the last message sent over bluetooth
	char receivedMsg[100];			// Holds the last received message over bluetooth
	char msg_buff[100] = {0};		// Message buffer for sending messages using AL_UART_Transmit_IT
public:
	bluetooth(void);				// Prototype for default constructor
	bluetooth(UART_HandleTypeDef* _huartX);	// Prototype for initializing constructor
	char get_sentMsg(void);			// Prototype for sentMsg getter function
	char get_receivedMsg(void);		// Prototype for receivedMsg getter function
	void send(const char* _message);	// Prototype for sending a message
	void callback(void);			// Prototype for receiving messages during a callback
};

#endif // __BLUETOOTH_H
