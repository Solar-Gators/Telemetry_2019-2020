//File Name: subsystem-data-module.hpp
//Description: This holds bms-specific data storage implementation

//Header Guards
#ifndef BMS_DATA_MODULE_H_
#define BMS_DATA_MODULE_H_

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
struct BMS_MESSAGE_0_DATA_PACKET
{
    float arrayVoltage;
    float arrayCurrent;
    float batteryVoltage;
    float mpptTemperature;
};

class BMS_MESSAGE_0 final: public SUBSYSTEM_DATA_MODULE
{
public:
//Constructors
BMS_MESSAGE_0();
//Public Function Prototypes
/**
 * @brief This is used to get the first in data packet.
 * @param success: returns true if there was data to get, false if the fifo was empty
 * @return Corresponding mppt data packet
 */
BMS_MESSAGE_0_DATA_PACKET GetOldestDataPacket(bool* success);
//Public Constants

//Public Variables
/**
 * @brief Fill this out prior to calling SendData()
 */
BMS_MESSAGE_0_DATA_PACKET txData;
private:
//Private Constants
//Private Variables
//Private Function Prototypes
void fillTransmitBuffer(void) override;
};

#endif //End Header Guard