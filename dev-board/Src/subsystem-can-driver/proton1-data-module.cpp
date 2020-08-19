//File Name: mppt-data-module.cpp
//Description: This implements mppt-specific data storage functions

//Include Files
#include <proton1-data-module.hpp>

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
void PROTON1_MESSAGE_0::dataPacketToArray(PROTON1_MESSAGE_0_DATA_PACKET input, uint8_t output[NUM_BYTES])
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

PROTON1_MESSAGE_0_DATA_PACKET PROTON1_MESSAGE_0::arrayToDataPacket(uint8_t input[NUM_BYTES])
{
	assert_param(input != nullptr);

	PROTON1_MESSAGE_0_DATA_PACKET output;
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

//Public Function Definitions
PROTON1_MESSAGE_0::PROTON1_MESSAGE_0(uint16_t message_id):
SUBSYSTEM_DATA_MODULE_TEMPLATE_INTERFACE<PROTON1_MESSAGE_0, PROTON1_MESSAGE_0_DATA_PACKET>{message_id,subsystem_info::MPPT0_MSG_LENGTH, false, false, true}
{}
