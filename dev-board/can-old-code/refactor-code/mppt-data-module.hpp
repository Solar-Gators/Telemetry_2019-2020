//File Name: subsystem-data-module.hpp
//Description: This holds mppt-specific data storage implementation

//Header Guards
#ifndef MPPT_DATA_MODULE_H_
#define MPPT_DATA_MODULE_H_

//Include Files
#include "subsystem-data-module.hpp"
//C Interface
#ifdef __cplusplus
extern "C" {
#endif
//C Public Constants
/*This is an example description for constants and variables. Delete this if it is unused here and copy and paste it to where it is needed. */
/**
 * @brief This is a brief description
 */

//C Public Variables

//C Public Function Prototypes
/*This is an example description for function prototypes. Delete this if it is unused here and copy and paste it to where it is needed. */
/**
 * @brief This is a brief description
 * @param Input_Param_Name - Description of input parameter
 * @ret Description of return value
 */


#ifdef __cplusplus
}
#endif //End C Interface

//C++ Interface
//Class Definitions
struct MPPT_MESSAGE_0_DATA_PACKET
{
    float arrayVoltage;
    float arrayCurrent;
    float batteryVoltage;
    float mpptTemperature;
};

class MPPT_MESSAGE_0 final: public SUBSYSTEM_DATA_MODULE
{
public:
//Constructors
MPPT_MESSAGE_0();
//Public Function Prototypes
/**
 * @brief This function is used to take in a mppt data packet and send it over CAN.
 * @param tx_packet: Packet to be sent out.
 */
void SendData(const MPPT_MESSAGE_0_DATA_PACKET& tx_packet);
/**
 * @brief This is used to convert the CAN data into the mppt data packet
 */
MPPT_MESSAGE_0_DATA_PACKET GetDataPacket(uint8_t* raw_data);
//Public Constants

//Public Variable
private:
//Private Constants
//Private Variables
//Private Function Prototypes
void fillTransmitBuffer(const void* data_packet) override;
};

#endif //End Header Guard