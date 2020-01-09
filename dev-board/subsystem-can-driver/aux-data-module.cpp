//File Name: aux-data-module.cpp
//Description: This implements aux-specific data storage functions

//Include Files
#include "aux-data-module.hpp"

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

//Protected Function Definitions
namespace AUX0_HELPER
{
	void dataPacketToArray(AUX_MESSAGE_0_DATA_PACKET input, uint8_t output[ARRAY_SIZE])
	{
		assert_param(output != nullptr);
		output[0] = 0;

		output[0] |= static_cast<uint32_t>(input.hazardsOn) << 0;
		output[0] |= static_cast<uint32_t>(input.headlightsOn) << 1;
		output[0] |= static_cast<uint32_t>(input.leftOn) << 2;
		output[0] |= static_cast<uint32_t>(input.rightOn) << 3;
	}

	AUX_MESSAGE_0_DATA_PACKET arrayToDataPacket(uint8_t input[ARRAY_SIZE])
	{
		assert_param(input != nullptr);

		AUX_MESSAGE_0_DATA_PACKET output;
		output.hazardsOn = input[0] & (1 << 0);
		output.headlightsOn = input[0] & (1 << 1);
		output.leftOn = input[0] & (1 << 2);
		output.rightOn = input[0] & (1 << 3);

		return output;
	}
}

void AUX_MESSAGE_0::fillTransmitBuffer(void)
{
	AUX0_HELPER::dataPacketToArray(this->txData, this->transmitBuffer);
}
//Public Function Definitions
AUX_MESSAGE_0::AUX_MESSAGE_0():
SUBSYSTEM_DATA_MODULE{subsystem_info::AUX0_MSG_ID,subsystem_info::AUX0_MSG_LENGTH, false}
{}

AUX_MESSAGE_0_DATA_PACKET AUX_MESSAGE_0::GetOldestDataPacket(bool* success)
{
	AUX_MESSAGE_0_DATA_PACKET returnData;
    if(success)
    {
        uint8_t* raw_data = this->storageFifo.PopFront(success);

        //Only do the conversions if we successfully extracted from the fifo
        if(*success)
        {
        	returnData = AUX0_HELPER::arrayToDataPacket(raw_data);
        }
    }
    return returnData;
}
