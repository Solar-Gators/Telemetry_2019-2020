//File Name: motor-driver-data-module.cpp
//Description: This implements motor driver-specific data storage functions

//Include Files
#include "motor-driver-data-module.hpp"

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
/*****************TX Classes*****************/
void MOTOR_DRIVER_TX_RL_MESSAGE::dataPacketToArray(MOTOR_DRIVER_TX_RL_DATA_PACKET input, uint8_t output[NUM_BYTES])
{
	output[0] = 0;

	output[0] |= static_cast<uint8_t>(input.requestFrame0) << 0;
	output[0] |= static_cast<uint8_t>(input.requestFrame1) << 1;
	output[0] |= static_cast<uint8_t>(input.requestFrame2) << 2;
}

MOTOR_DRIVER_TX_RL_DATA_PACKET MOTOR_DRIVER_TX_RL_MESSAGE::arrayToDataPacket(uint8_t input[NUM_BYTES])
{
	MOTOR_DRIVER_TX_RL_DATA_PACKET output;
	output.requestFrame0 = input[0] & (1 << 0);
	output.requestFrame1 = input[0] & (1 << 1);
	output.requestFrame2 = input[0] & (1 << 2);

	return output;
}

//Public Function Definitions
MOTOR_DRIVER_TX_RL_MESSAGE::MOTOR_DRIVER_TX_RL_MESSAGE():
SUBSYSTEM_DATA_MODULE_TEMPLATE_INTERFACE<MOTOR_DRIVER_TX_RL_MESSAGE, MOTOR_DRIVER_TX_RL_DATA_PACKET>{subsystem_info::MOTORTX_RL_MSG_ID,subsystem_info::MOTORTX_RL_MSG_LENGTH, true, false, false}
{}
/*****************RX Classes*****************/
//RX Frame 0
void MOTOR_DRIVER_RX_FRAME_0::dataPacketToArray(MOTOR_DRIVER_RX_FRAME_0_DATA_PACKET input, uint8_t output[NUM_BYTES])
{
	uint32_t convMotorRPM = input.motorRPM * 1;

	output[4] = (static_cast<uint32_t>(convMotorRPM) & 0x1F) << 3;
	output[5] = (static_cast<uint32_t>(convMotorRPM) & 0xFE0) >> 5;
}

MOTOR_DRIVER_RX_FRAME_0_DATA_PACKET MOTOR_DRIVER_RX_FRAME_0::arrayToDataPacket(uint8_t input[NUM_BYTES])
{
	MOTOR_DRIVER_RX_FRAME_0_DATA_PACKET output;
	uint32_t preMotorRPM = (static_cast<uint32_t>(input[5] & 0x7F) << 5) | (input[4] >> 3);
	output.motorRPM = static_cast<uint16_t>(preMotorRPM);

	return output;
}

MOTOR_DRIVER_RX_FRAME_0::MOTOR_DRIVER_RX_FRAME_0():
SUBSYSTEM_DATA_MODULE_TEMPLATE_INTERFACE<MOTOR_DRIVER_RX_FRAME_0, MOTOR_DRIVER_RX_FRAME_0_DATA_PACKET>{subsystem_info::MOTORRX0_RL_MSG_ID,subsystem_info::MOTORRX0_RL_MSG_LENGTH, true, true, false}
{}

//RX Frame 2
void MOTOR_DRIVER_RX_FRAME_2::dataPacketToArray(MOTOR_DRIVER_RX_FRAME_2_DATA_PACKET input, uint8_t output[NUM_BYTES])
{
	uint32_t convOverHeadLevel = input.overHeatLevel;

	output[0] = 0;
	output[0] |= static_cast<uint8_t>(input.adSensorError) << 0;
	output[2] = 0;
	output[2] |= static_cast<uint8_t>(input.powerSystemError) << 0;
	output[3] = 0;
	output[3] |= static_cast<uint8_t>(input.motorSystemError) << 0;
	output[4] = static_cast<uint32_t>(convOverHeadLevel) & 0x3;
}

MOTOR_DRIVER_RX_FRAME_2_DATA_PACKET MOTOR_DRIVER_RX_FRAME_2::arrayToDataPacket(uint8_t input[NUM_BYTES])
{
	MOTOR_DRIVER_RX_FRAME_2_DATA_PACKET output;
	output.adSensorError = input[0] & (1 << 0);
	output.powerSystemError = input[2] & (1 << 0);
	output.motorSystemError = input[3] & (1 << 0);
	output.overHeatLevel = input[4] & 0x3;

	return output;
}

//Public Function Definitions
MOTOR_DRIVER_RX_FRAME_2::MOTOR_DRIVER_RX_FRAME_2():
SUBSYSTEM_DATA_MODULE_TEMPLATE_INTERFACE<MOTOR_DRIVER_RX_FRAME_2, MOTOR_DRIVER_RX_FRAME_2_DATA_PACKET>{subsystem_info::MOTORRX2_RL_MSG_ID,subsystem_info::MOTORRX2_RL_MSG_LENGTH, true, true, false}
{}

