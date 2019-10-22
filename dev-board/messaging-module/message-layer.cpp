//File Name:
//Description:

//Include Files
#include "message-layer.h"

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
RF_PACKET::RF_PACKET():
dataPacket{0}, numMessagesInPacket{0}, packetLength{RF_ENCODER::MIN_PACKET_LENGTH}
{
	dataPacket[0] = RF_ENCODER::START_CHAR;
	dataPacket[1] = this->numMessagesInPacket;
}

void RF_PACKET::Send()
{
	//Add the end character
	dataPacket[this->packetLength] = RF_ENCODER::END_CHAR;
	//Send out Message
	//TODO: Call transport layer send packet
	//Reset data packet
	this->packetLength = RF_ENCODER::MIN_PACKET_LENGTH;
	this->dataPacket[1] = this->numMessagesInPacket = 0;
}

bool RF_PACKET::AddToPacket(uint8_t address, uint8_t data_size, uint8_t* data)
{
	bool packetTooLarge = true;
	//Continue if the total packet length after adding 1 byte for address + 1 byte for data size + @data_size
	//bytes for this message is less than or equal to max length.
	if(this->packetLength + 2 + data_size <= RF_ENCODER::MAX_PACKET_LENGTH)
	{
		this->dataPacket[this->packetLength++] = address;
		this->dataPacket[this->packetLength++] = data_size;
		for(uint8_t i = 0; i < data_size; i++)
		{
			this->dataPacket[this->packetLength++] = data[i];
		}
		packetTooLarge = false;
	}
	return packetTooLarge;
}
