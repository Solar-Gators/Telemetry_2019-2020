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
bool MPPT_MESSAGE_0::fillTransmitDataBuffer(void* subsystem_specific_data_packet)
{
    MPPT_MESSAGE_0_DATA_PACKET* myDataPacket = reinterpret_cast<MPPT_MESSAGE_0_DATA_PACKET*>(subsystem_specific_data_packet);
}
//Public Function Definitions
