//File Name: bms-data-module.cpp
//Description: This implements bms-specific data storage functions

//Include Files
#include "bms-data-module.hpp"

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
namespace BMS0_HELPER
{
	void dataPacketToArray(BMS_MESSAGE_0_DATA_PACKET input, uint8_t output[ARRAY_SIZE])
	{
		float convLowCellVoltage = input.lowCellVoltage * 10000;
		float convHighCellVoltage = input.highCellVoltage * 10000;
		float convAvgCellVoltage = input.avgCellVoltage * 10000;
		float convPackSummedVoltage = input.packSummedVoltage * 100;

		output[0] = static_cast<uint32_t>(convLowCellVoltage) & 0xFF;
		output[1] = (static_cast<uint32_t>(convLowCellVoltage) >> 8) & 0xFF;
		output[2] = static_cast<uint32_t>(convHighCellVoltage) & 0xFF;
		output[3] = (static_cast<uint32_t>(convHighCellVoltage) >> 8) & 0xFF;
		output[4] = static_cast<uint32_t>(convAvgCellVoltage) & 0xFF;
		output[5] = (static_cast<uint32_t>(convAvgCellVoltage) >> 8) & 0xFF;
		output[6] = static_cast<uint32_t>(convPackSummedVoltage) & 0xFF;
		output[7] = (static_cast<uint32_t>(convPackSummedVoltage) >> 8) & 0xFF;
	}

	BMS_MESSAGE_0_DATA_PACKET arrayToDataPacket(uint8_t input[ARRAY_SIZE])
	{
		BMS_MESSAGE_0_DATA_PACKET output;
		uint32_t preLCV = (static_cast<uint32_t>(input[1]) << 8) | input[0];
		uint32_t preHCV = (static_cast<uint32_t>(input[3]) << 8) | input[2];
		uint32_t preACV = (static_cast<uint32_t>(input[5]) << 8) | input[4];
		uint32_t prePCV = (static_cast<uint32_t>(input[7]) << 8) | input[6];
		output.lowCellVoltage = static_cast<float>(preLCV)/10000;
		output.highCellVoltage = static_cast<float>(preHCV)/10000;
		output.avgCellVoltage = static_cast<float>(preACV)/10000;
		output.packSummedVoltage = static_cast<float>(prePCV)/100;

		return output;
	}
}

void BMS_MESSAGE_0::fillTransmitBuffer(void)
{
	BMS0_HELPER::dataPacketToArray(this->txData, this->transmitBuffer);
}
//Public Function Definitions
BMS_MESSAGE_0::BMS_MESSAGE_0():
SUBSYSTEM_DATA_MODULE{subsystem_info::BMS0_MSG_ID,subsystem_info::BMS0_MSG_LENGTH, false}
{}

BMS_MESSAGE_0_DATA_PACKET BMS_MESSAGE_0::GetOldestDataPacket(bool* success)
{
	BMS_MESSAGE_0_DATA_PACKET returnData;
    if(success)
    {
        uint8_t* raw_data = this->storageFifo.PopFront(success);

        //Only do the conversions if we successfully extracted from the fifo
        if(*success)
        {
        	returnData = BMS0_HELPER::arrayToDataPacket(raw_data);
        }
    }
    return returnData;
}
