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
void BMS_MESSAGE_0::fillTransmitBuffer(void)
{
    float convArrayVoltage = this->txData.arrayVoltage * 100;
    float convArrayCurrent = this->txData.arrayCurrent * 100;
    float convBatteryVoltage = this->txData.batteryVoltage * 100;
    float convMpptTemperature = this->txData.mpptTemperature * 100;

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
BMS_MESSAGE_0::BMS_MESSAGE_0():
SUBSYSTEM_DATA_MODULE{subsystem_info::BMS0_MSG_ID,subsystem_info::BMS0_MSG_LENGTH, false}
{}

BMS_MESSAGE_0_DATA_PACKET BMS_MESSAGE_0::GetOldestDataPacket(bool* success)
{
    uint8_t* raw_data = this->storageFifo.PopFront(success);
    BMS_MESSAGE_0_DATA_PACKET returnData;

    //Only do the conversions if we successfully extracted from the fifo
    if(*success)
    {
        uint32_t preArrayVoltage = (static_cast<uint32_t>(raw_data[1]) << 8) | raw_data[0];
        uint32_t preArrayCurrent = (static_cast<uint32_t>(raw_data[3]) << 8) | raw_data[2];
        uint32_t preBatteryVoltage = (static_cast<uint32_t>(raw_data[5]) << 8) | raw_data[4];
        uint32_t preMpptTemperature = (static_cast<uint32_t>(raw_data[7]) << 8) | raw_data[6];

        returnData.arrayVoltage = static_cast<float>(preArrayVoltage)/100;
        returnData.arrayCurrent = static_cast<float>(preArrayCurrent)/100;
        returnData.batteryVoltage = static_cast<float>(preBatteryVoltage)/100;
        returnData.mpptTemperature = static_cast<float>(preMpptTemperature)/100;
    }

    return returnData;
}