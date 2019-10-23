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

//Public Function Definitions
RF_TRANSPORT_LAYER::RF_TRANSPORT_LAYER(USART_TypeDef* uart_instance):
uartInstance{uart_instance}
{}

void RF_TRANSPORT_LAYER::sendMessage(uint8_t* data, uint16_t data_length)
{
	for(uint16_t i = 0; i < data_length; i++)
	{
		while(!(this->uartInstance->ISR & USART_ISR_TXE));
		this->uartInstance->TDR = data[i];
	}
}
