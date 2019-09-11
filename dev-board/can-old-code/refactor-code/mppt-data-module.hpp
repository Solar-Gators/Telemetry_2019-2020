//File Name: subsystem-data-module.hpp
//Description: This is what each subsystem will inherit from for storage

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
class MPPT_MESSAGE_0 final: public SUBSYSTEM_DATA_MODULE
{
public:
//Constructors
MPPT_MESSAGE_0();
//Public Function Prototypes
/**
 * @brief This should be called in order to initializing reception from the calling subsystem
 */
void InitReceive(subsystemReceiveCallback rx_func_ptr);
/**
 * @brief This is called to send data on the CAN lines using the data initializes in the subsystem specific transmit packet initializer
 */
void SendData(void);
//Public Constants

//Public Variable

private:
//Private Variables
//Private Function Prototypes
};

#endif //End Header Guard