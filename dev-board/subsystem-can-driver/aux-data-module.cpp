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
namespace MPPT0_HELPER
{
	void dataPacketToArray(MPPT_MESSAGE_0_DATA_PACKET input, uint8_t output[ARRAY_SIZE])
	{
		assert_param(output != nullptr);

		float convArrayVoltage = input.arrayVoltage * 100;
		float convArrayCurrent = input.arrayCurrent * 100;
		float convBatteryVoltage = input.batteryVoltage * 100;
		float convMpptTemperature = input.mpptTemperature * 100;

		output[0] = static_cast<uint32_t>(convArrayVoltage) & 0xFF;
		output[1] = (static_cast<uint32_t>(convArrayVoltage) >> 8) & 0xFF;
		output[2] = static_cast<uint32_t>(convArrayCurrent) & 0xFF;
		output[3] = (static_cast<uint32_t>(convArrayCurrent) >> 8) & 0xFF;
		output[4] = static_cast<uint32_t>(convBatteryVoltage) & 0xFF;
		output[5] = (static_cast<uint32_t>(convBatteryVoltage) >> 8) & 0xFF;
		output[6] = static_cast<uint32_t>(convMpptTemperature) & 0xFF;
		output[7] = (static_cast<uint32_t>(convMpptTemperature) >> 8) & 0xFF;
	}

	MPPT_MESSAGE_0_DATA_PACKET arrayToDataPacket(uint8_t input[ARRAY_SIZE])
	{
		assert_param(input != nullptr);

		MPPT_MESSAGE_0_DATA_PACKET output;
		uint32_t preArrayVoltage = (static_cast<uint32_t>(input[1]) << 8) | input[0];
		uint32_t preArrayCurrent = (static_cast<uint32_t>(input[3]) << 8) | input[2];
		uint32_t preBatteryVoltage = (static_cast<uint32_t>(input[5]) << 8) | input[4];
		uint32_t preMpptTemperature = (static_cast<uint32_t>(input[7]) << 8) | input[6];
		output.arrayVoltage = static_cast<float>(preArrayVoltage)/100;
		output.arrayCurrent = static_cast<float>(preArrayCurrent)/100;
		output.batteryVoltage = static_cast<float>(preBatteryVoltage)/100;
		output.mpptTemperature = static_cast<float>(preMpptTemperature)/100;

		return output;
	}
}

void MPPT_MESSAGE_0::fillTransmitBuffer(void)
{
	MPPT0_HELPER::dataPacketToArray(this->txData, nullptr);
}
//Public Function Definitions
MPPT_MESSAGE_0::MPPT_MESSAGE_0():
SUBSYSTEM_DATA_MODULE{subsystem_info::MPPT0_MSG_ID,subsystem_info::MPPT0_MSG_LENGTH, false}
{}

MPPT_MESSAGE_0_DATA_PACKET MPPT_MESSAGE_0::GetOldestDataPacket(bool* success)
{
    MPPT_MESSAGE_0_DATA_PACKET returnData;
    if(success)
    {
        uint8_t* raw_data = this->storageFifo.PopFront(success);

        //Only do the conversions if we successfully extracted from the fifo
        if(*success)
        {
        	returnData = MPPT0_HELPER::arrayToDataPacket(raw_data);
        }
    }
    return returnData;
}
