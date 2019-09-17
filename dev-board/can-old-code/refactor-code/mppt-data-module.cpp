//File Name: mppt-data-module.cpp
//Description: This implements mppt-specific data storage functions

//Include Files
#include "mppt-data-module.hpp"

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
void MPPT_MESSAGE_0::fillTransmitBuffer(const void* data_packet)
{
    const MPPT_MESSAGE_0_DATA_PACKET* mpptDataPacket = static_cast<const MPPT_MESSAGE_0_DATA_PACKET*>(data_packet);

    float convArrayVoltage = mpptDataPacket->arrayVoltage * 100;
    float convArrayCurrent = mpptDataPacket->arrayCurrent * 100;
    float convBatteryVoltage = mpptDataPacket->batteryVoltage * 100;
    float convMpptTemperature = mpptDataPacket->mpptTemperature * 100;

    this->transmitBuffer[0] = static_cast<uint32_t>(convArrayVoltage) & 0xFF;
    this->transmitBuffer[1] = (static_cast<uint32_t>(convArrayVoltage) >> 8) & 0xFF;
    this->transmitBuffer[2] = static_cast<uint32_t>(convArrayCurrent) & 0xFF;
    this->transmitBuffer[3] = (static_cast<uint32_t>(convArrayCurrent) >> 8) & 0xFF;
    this->transmitBuffer[4] = static_cast<uint32_t>(convBatteryVoltage) & 0xFF;
    this->transmitBuffer[5] = (static_cast<uint32_t>(convBatteryVoltage) >> 8) & 0xFF;
    this->transmitBuffer[6] = static_cast<uint32_t>(convMpptTemperature) & 0xFF;
    this->transmitBuffer[7] = (static_cast<uint32_t>(convMpptTemperature) >> 8) & 0xFF;
}
//Public Function Definitions
MPPT_MESSAGE_0::MPPT_MESSAGE_0():
SUBSYSTEM_DATA_MODULE{subsystem_info::MPPT0_MSG_ID,subsystem_info::MPPT0_MSG_LENGTH}
{}
void MPPT_MESSAGE_0::SendData(const MPPT_MESSAGE_0_DATA_PACKET& tx_packet)
{
    fillTransmitBuffer(&tx_packet);
    sendTransmitBufferData();
}