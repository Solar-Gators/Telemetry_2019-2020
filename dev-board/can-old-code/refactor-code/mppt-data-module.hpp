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
MPPT_MESSAGE_0() = default;
//Public Function Prototypes
//Public Constants

//Public Variable
protected:
bool fillTransmitDataBuffer(void* subsystem_specific_data_packet) override;
private:
//Private Constants
//Private Variables
//Private Function Prototypes
};

#endif //End Header Guard