//File Name: motor-driver-data-module.cpp
//Description: This implements motor driver-specific data storage functions

//Include Files
#include <mitsuba-driver-data-module.hpp>

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
void MITSUBA_DRIVER_TX_RL_MESSAGE::dataPacketToArray(MITSUBA_DRIVER_TX_RL_DATA_PACKET input, uint8_t output[NUM_BYTES])
{
	output[0] = 0;

	output[0] |= static_cast<uint8_t>(input.requestFrame0) << 0;
	output[0] |= static_cast<uint8_t>(input.requestFrame1) << 1;
	output[0] |= static_cast<uint8_t>(input.requestFrame2) << 2;
}

MITSUBA_DRIVER_TX_RL_DATA_PACKET MITSUBA_DRIVER_TX_RL_MESSAGE::arrayToDataPacket(uint8_t input[NUM_BYTES])
{
	MITSUBA_DRIVER_TX_RL_DATA_PACKET output;
	output.requestFrame0 = input[0] & (1 << 0);
	output.requestFrame1 = input[0] & (1 << 1);
	output.requestFrame2 = input[0] & (1 << 2);

	return output;
}

//Public Function Definitions
MITSUBA_DRIVER_TX_RL_MESSAGE::MITSUBA_DRIVER_TX_RL_MESSAGE(uint32_t message_id):
SUBSYSTEM_DATA_MODULE_TEMPLATE_INTERFACE<MITSUBA_DRIVER_TX_RL_MESSAGE, MITSUBA_DRIVER_TX_RL_DATA_PACKET>{message_id,subsystem_info::MOTORTX_RL_MSG_LENGTH, true, false, false}
{}
/*****************RX Classes*****************/
//RX Frame 0
void MITSUBA_DRIVER_RX_FRAME_0::dataPacketToArray(MITSUBA_DRIVER_RX_FRAME_0_DATA_PACKET input, uint8_t output[NUM_BYTES])
{
	output[0] = 0;
	output[0] |= static_cast<uint8_t>(input.battVoltage);

	output[1] = 0;
	output[1] |= static_cast<uint8_t>(input.battVoltage >> 8);
	output[1] |= static_cast<uint8_t>(static_cast<uint32_t>(input.battCurrent) << 2);

	output[2] = 0;
	output[2] |= static_cast<uint8_t>(input.battCurrent >> 6);
	output[2] |= static_cast<uint8_t>(static_cast<uint32_t>(input.battCurrentDir) << 3);
	output[2] |= static_cast<uint8_t>(input.motorCurrentPkAvg << 4);

	output[3] = 0;
	output[3] |= static_cast<uint8_t>(input.motorCurrentPkAvg >> 4);
	output[3] |= static_cast<uint8_t>(static_cast<uint32_t>(input.FETtemp) << 6);


	uint32_t convMotorRPM = input.motorRPM * 1;
	output[4] = 0;
	output[4] |= static_cast<uint8_t>(input.FETtemp >> 2);
	output[4] |= (static_cast<uint32_t>(convMotorRPM) & 0x1F) << 3;

	output[5] = 0;
	output[5] |= (static_cast<uint32_t>(convMotorRPM) & 0xFE0) >> 5;
	output[5] |= (static_cast<uint8_t>(input.PWMDuty << 7));

	output[6] = 0;
	output[6] |= static_cast<uint8_t>(input.PWMDuty >> 1);

	output[7] = 0;
	output[7] |= static_cast<uint8_t>(input.PWMDuty >> 9);
	output[7] |= static_cast<uint8_t>(static_cast<uint32_t>(input.LeadAngle) << 1);
}

MITSUBA_DRIVER_RX_FRAME_0_DATA_PACKET MITSUBA_DRIVER_RX_FRAME_0::arrayToDataPacket(uint8_t input[NUM_BYTES])
{
	MITSUBA_DRIVER_RX_FRAME_0_DATA_PACKET output;
	uint32_t preBattVoltage = (static_cast<uint32_t>(input[1] & 3) << 8) | (input[0]);
	output.battVoltage = static_cast<uint16_t>(preBattVoltage);

	uint32_t preBattCurrent = (static_cast<uint32_t>(input[2] & 7) << 6) | (input[1] >> 2);
	output.battCurrent = static_cast<uint16_t>(preBattCurrent);

	output.battCurrentDir = static_cast<bool>(input[2] & 8);

	uint32_t preMotorCurrent = static_cast<uint32_t>((input[3] & 0x3F) << 4) | (input[2] >> 4);
	output.motorCurrentPkAvg = static_cast<uint16_t>(preMotorCurrent);

	uint32_t preFETtemp = static_cast<uint32_t>((input[4] & 7) << 2) | (input[3] >> 6);
	output.FETtemp = static_cast<uint8_t>(preFETtemp);

	uint32_t preMotorRPM = (static_cast<uint32_t>(input[5] & 0x7F) << 5) | (input[4] >> 3);
	output.motorRPM = static_cast<uint16_t>(preMotorRPM);

	uint32_t preDuty = (static_cast<uint32_t>(input[7] & 1) << 9) | (input[6] << 1) | (input[5] >> 7);
	output.PWMDuty = static_cast<uint16_t>(preDuty);

	output.LeadAngle = static_cast<uint8_t>((input[7] >> 1));

	return output;
}

MITSUBA_DRIVER_RX_FRAME_0::MITSUBA_DRIVER_RX_FRAME_0(uint32_t message_id):
SUBSYSTEM_DATA_MODULE_TEMPLATE_INTERFACE<MITSUBA_DRIVER_RX_FRAME_0, MITSUBA_DRIVER_RX_FRAME_0_DATA_PACKET>{message_id,subsystem_info::MOTORRX0_RL_MSG_LENGTH, true, true, false}
{}

//RX Frame 1
void MITSUBA_DRIVER_RX_FRAME_1::dataPacketToArray(MITSUBA_DRIVER_RX_FRAME_1_DATA_PACKET input, uint8_t output[NUM_BYTES])
{
	output[0] = 0;
	output[0] |= static_cast<uint8_t>(input.powerMode);
	output[0] |= static_cast<uint8_t>(input.MCmode) << 1;
	output[0] |= static_cast<uint8_t>(input.AcceleratorPosition << 2);

	output[1] = 0;
	output[1] |= static_cast<uint8_t>(input.AcceleratorPosition >> 6);
	output[1] |= static_cast<uint8_t>(input.regenVRposition << 4);

	output[2] = 0;
	output[2] |= static_cast<uint8_t>(input.regenVRposition >> 4);
	output[2] |= static_cast<uint8_t>(static_cast<uint32_t>(input.digitSWposition) << 6);

	output[3] = 0;
	output[3] |= static_cast<uint8_t>(input.digitSWposition >> 2);
	output[3] |= static_cast<uint8_t>(input.outTargetVal << 2);

	output[4] = 0;
	output[4] |= static_cast<uint8_t>(input.outTargetVal >> 6);
	output[4] |= static_cast<uint8_t>(input.driveActStat << 4);
	output[4] |= static_cast<uint8_t>(static_cast<uint8_t>(input.regenStat) << 6);
}

MITSUBA_DRIVER_RX_FRAME_1_DATA_PACKET MITSUBA_DRIVER_RX_FRAME_1::arrayToDataPacket(uint8_t input[NUM_BYTES])
{
	MITSUBA_DRIVER_RX_FRAME_1_DATA_PACKET output;

	output.powerMode = input[0] & 1;

	output.MCmode = (input[0] >> 1) & 1;

	uint32_t preAccelPos = static_cast<uint32_t>((input[1] & 0xF) << 6) | (input[0] >> 2);
	output.AcceleratorPosition = static_cast<uint16_t>(preAccelPos);

	uint32_t preRegenVRposition = static_cast<uint32_t>((input[2] & 0x3F) << 4) | (input[1] >> 4);
	output.regenVRposition = static_cast<uint16_t>(preRegenVRposition);

	uint32_t preDigitSWposition = static_cast<uint32_t>((input[3] & 0x3) << 2) | (input[2] >> 6);
	output.digitSWposition = static_cast<uint8_t>(preDigitSWposition);

	uint32_t preOutTargetVal = static_cast<uint32_t>((input[4] & 0xF) << 6) | (input[3] >> 2);
	output.outTargetVal = static_cast<uint16_t>(preOutTargetVal);

	output.driveActStat = static_cast<uint8_t>((input[4] >> 4) & 3);

	output.regenStat = static_cast<bool>((input[4] >> 6) & 1);

	return output;
}

MITSUBA_DRIVER_RX_FRAME_1::MITSUBA_DRIVER_RX_FRAME_1(uint32_t message_id):
SUBSYSTEM_DATA_MODULE_TEMPLATE_INTERFACE<MITSUBA_DRIVER_RX_FRAME_1, MITSUBA_DRIVER_RX_FRAME_1_DATA_PACKET>{message_id,subsystem_info::MOTORRX1_RL_MSG_LENGTH, true, true, false}
{}

//RX Frame 2
void MITSUBA_DRIVER_RX_FRAME_2::dataPacketToArray(MITSUBA_DRIVER_RX_FRAME_2_DATA_PACKET input, uint8_t output[NUM_BYTES])
{
	uint32_t convOverHeadLevel = input.overHeatLevel;

	output[0] = 0;
	output[0] |= static_cast<uint8_t>(input.adSensorError) << 0;
	output[0] |= static_cast<uint8_t>(input.motorCurrSensorUError) << 1;
	output[0] |= static_cast<uint8_t>(input.motorCurrSensorWError) << 2;
	output[0] |= static_cast<uint8_t>(input.fetThermError) << 3;
	output[0] |= static_cast<uint8_t>(input.battVoltSensorError) << 5;
	output[0] |= static_cast<uint8_t>(input.battCurrSensorError) << 6;
	output[0] |= static_cast<uint8_t>(input.battCurrSensorAdjError) << 7;

	output[1] = 0;
	output[1] |= static_cast<uint8_t>(input.motorCurrSensorAdjError) << 0;
	output[1] |= static_cast<uint8_t>(input.accelPosError) << 1;
	output[1] |= static_cast<uint8_t>(input.contVoltSensorError) << 3;

	output[2] = 0;
	output[2] |= static_cast<uint8_t>(input.powerSystemError) << 0;
	output[2] |= static_cast<uint8_t>(input.overCurrError) << 1;
	output[2] |= static_cast<uint8_t>(input.overVoltError) << 3;
	output[2] |= static_cast<uint8_t>(input.overCurrLimit) << 5;

	output[3] = 0;
	output[3] |= static_cast<uint8_t>(input.motorSystemError) << 0;
	output[3] |= static_cast<uint8_t>(input.motorLock) << 1;
	output[3] |= static_cast<uint8_t>(input.hallSensorShort) << 2;
	output[3] |= static_cast<uint8_t>(input.hallSensorOpen) << 3;

	output[4] = static_cast<uint32_t>(convOverHeadLevel) & 0x3;
}

MITSUBA_DRIVER_RX_FRAME_2_DATA_PACKET MITSUBA_DRIVER_RX_FRAME_2::arrayToDataPacket(uint8_t input[NUM_BYTES])
{
	MITSUBA_DRIVER_RX_FRAME_2_DATA_PACKET output;

	output.adSensorError 			= input[0] & (1 << 0);
	output.motorCurrSensorUError 	= input[0] & (1 << 1);
	output.motorCurrSensorWError 	= input[0] & (1 << 2);
	output.fetThermError 			= input[0] & (1 << 3);
	output.battVoltSensorError 		= input[0] & (1 << 5);
	output.battCurrSensorError 		= input[0] & (1 << 6);
	output.battCurrSensorAdjError 	= input[0] & (1 << 7);

	output.motorCurrSensorAdjError	= input[1] & (1 << 0);
	output.accelPosError			= input[1] & (1 << 1);
	output.contVoltSensorError		= input[1] & (1 << 3);

	output.powerSystemError 		= input[2] & (1 << 0);
	output.overCurrError			= input[2] & (1 << 1);
	output.overVoltError			= input[2] & (1 << 3);
	output.overCurrLimit			= input[2] & (1 << 5);

	output.motorSystemError 		= input[3] & (1 << 0);
	output.motorLock		 		= input[3] & (1 << 1);
	output.hallSensorShort			= input[3] & (1 << 2);
	output.hallSensorOpen			= input[3] & (1 << 3);

	output.overHeatLevel			= input[4] & 0x3;

	return output;
}

//Public Function Definitions
MITSUBA_DRIVER_RX_FRAME_2::MITSUBA_DRIVER_RX_FRAME_2(uint32_t message_id):
SUBSYSTEM_DATA_MODULE_TEMPLATE_INTERFACE<MITSUBA_DRIVER_RX_FRAME_2, MITSUBA_DRIVER_RX_FRAME_2_DATA_PACKET>{message_id,subsystem_info::MOTORRX2_RL_MSG_LENGTH, true, true, false}
{}

