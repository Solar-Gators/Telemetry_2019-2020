//File Name: subsystem-data-module.hpp
//Description: This is what each subsystem will inherit from for storage

//Header Guards
#ifndef SUBSYSTEM_DATA_MODULE_H_
#define SUBSYSTEM_DATA_MODULE_H_

//Include Files
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
//Typedefs
typedef void (*subsystemReceiveCallback)(SUBSYSTEM_DATA_MODULE*);
//Class Definitions
class SUBSYSTEM_DATA_MODULE 
{
public:
//Constructors
//Public Function Prototypes
/**
 * @brief This should be called in order to initializing reception from the calling subsystem
 * @param rx_func_ptr: This is the function pointer that will be called (if not nullptr) on reception of data packet from
 * this specific subsystem.
 */
void InitReceive(subsystemReceiveCallback rx_func_ptr);
/**
 * @brief This is called to send data on the CAN lines using the txDataPacket
 */
void SendData(void);
//Public Constants

//Public Variable
protected:
//Protected Constructor
SUBSYSTEM_DATA_MODULE();
//Protected Structs
struct TRANSMIT_PACKET
{
    uint16_t identifier;
    uint8_t length;
    uint8_t* const data;
}; 
//Protected Variables
/**
 * @brief This is the callback which will be called when the corresponding subsystem receives a message
 * @param SUBSYSTEM_DATA_MODULE*: This is a pointer to this object aka the subsystem specific data module
 */
subsystemReceiveCallback rxFuncPtr;
/**
 * @brief This holds the generic transmit packet which will be sent using the SendData() command
 */
TRANSMIT_PACKET txDataPacket;
private:
//Private Variables
/**
 * @brief This holds the count of the amount of messages routed to mailbox 0
 */
static uint8_t mailbox0Count;
/**
 * @brief This holds the count of the amount of messages routed to mailbox 1
 */
static uint8_t mailbox1Count;
//Private Function Prototypes
};

#endif //End Header Guard