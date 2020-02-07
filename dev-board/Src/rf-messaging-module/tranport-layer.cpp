//File Name: transport-layer.cpp
//Description: This implements the overall transmission and construction of an RF packet.

//Include Files
#include "transport-layer.h"

//Private Constants
/*This is an example description for constants and variables. Delete this if it is unused here and copy and paste it to where it is needed. */
/**
 * @brief This is a brief description
 */
//Private Variables

//Public Constants

//Public Variables

//Private Function Prototypes
/*This is an example description for function prototypes. Delete this if it is unused here and copy and paste it to where it is needed. */
/* @brief This is a brief description
 * @param Input_Param_Name - Description of input parameter
 * @ret Description of return value
 */

//Public Function Prototypes

//Private Function Definitions

//Public Function Definitions
RF_PACKET::RF_PACKET(USART_TypeDef* uart_instance):
RF_TRANSPORT_LAYER{uart_instance} ,dataPacket{0}, numMessagesInPacket{0}, packetLength{RF_PACKET::MIN_PACKET_LENGTH}
{
	dataPacket[0] = RF_TRANSPORT_LAYER::START_CHAR;
	dataPacket[1] = this->numMessagesInPacket;
}

void RF_PACKET::Send()
{
	//Set the num messages in packet
	this->dataPacket[1] = this->numMessagesInPacket;
	//Add the end character
	this->dataPacket[this->packetLength - 1] = RF_TRANSPORT_LAYER::END_CHAR;
	//Send out Message
	this->sendMessage(this->dataPacket, this->packetLength);
	//Reset data packet
	this->ClearPacket();
}

bool RF_PACKET::AddToPacket(uint8_t address, uint8_t data_size, uint8_t* data)
{
	bool packetSmallEnough = false;
	//Continue only if data size isn't 0
	if(data_size != 0)
	{
		//Continue if the total packet length after adding 1 byte for address + 1 byte for data size + @data_size
		//bytes for this message is less than or equal to max length.
		if(this->packetLength + 2 + data_size <= RF_PACKET::MAX_PACKET_LENGTH)
		{
			this->dataPacket[(this->packetLength++) - 1] = address;
			this->dataPacket[(this->packetLength++) - 1] = data_size;
			for(uint8_t i = 0; i < data_size; i++)
			{
				this->dataPacket[(this->packetLength++) - 1] = data[i];
			}
			packetSmallEnough = true;
			this->numMessagesInPacket++;
		}
	}
	return packetSmallEnough;
}

void RF_PACKET::ClearPacket(void)
{
	this->packetLength = RF_PACKET::MIN_PACKET_LENGTH;
	this->numMessagesInPacket = 0;
}
