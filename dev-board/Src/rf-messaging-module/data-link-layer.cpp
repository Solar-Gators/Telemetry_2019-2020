//File Name: data-link-layer-layer.cpp
//Description: This  handles the actual sending of messages over RF

//Include Files
#include "data-link-layer.h"

//Private Constants

//Private Variables

//Public Constants

//Public Variables

//Private Function Prototypes

//Public Function Prototypes

//Private Function Definitions
inline void RF_DATA_LINK_LAYER::handleByteStuff(uint8_t data, uint16_t index, uint16_t message_length)
{
	if(index != 0 && index != (message_length - 1))
	{
		if(data == RF_DATA_LINK_LAYER::START_CHAR || data == RF_DATA_LINK_LAYER::END_CHAR || data == RF_DATA_LINK_LAYER::ESC_CHAR)
		{
			sendData(RF_DATA_LINK_LAYER::ESC_CHAR);
		}
	}
}

inline void RF_DATA_LINK_LAYER::sendData(uint8_t data)
{
	while(!(this->uartInstance->ISR & USART_ISR_TXE));
	this->uartInstance->TDR = data;
}
//Public Function Definitions
RF_DATA_LINK_LAYER::RF_DATA_LINK_LAYER(USART_TypeDef* uart_instance):
uartInstance{uart_instance}
{}

void RF_DATA_LINK_LAYER::sendMessage(uint8_t* data, uint16_t data_length)
{
	for(uint16_t i = 0; i < data_length; i++)
	{
		handleByteStuff(data[i], i, data_length);
		sendData(data[i]);
	}
}
