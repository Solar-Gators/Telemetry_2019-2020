//File Name: subsystem-data-module.hpp
//Description: This is what each subsystem will inherit from for storage

//Header Guards
#ifndef SUBSYSTEM_DATA_MODULE_H_
#define SUBSYSTEM_DATA_MODULE_H_

//Include Files
#include "subsystem-info.hpp"
#include "helper-fifo.hpp"
#include "stdint.h" //REMOVE THIS
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
static constexpr uint8_t FIFO_DEPTH = 3;
static constexpr uint8_t ARRAY_SIZE = 8;
//Public Variables
/**
 * @brief This is the message identifier for the subsystem-specific CAN message
 * @note This is public for easy access
 */
const uint32_t messageIdentifier;
/**
 * @brief This is the length of data which is specific to each subsystem
 */
const uint8_t dataLength;
/**
 * @brief This is the storage fifo which can be used to store and retrieve data
 */
HELPER_FIFO<uint8_t,FIFO_DEPTH,ARRAY_SIZE> storageFifo;
/**
 * @brief This is the callback which will be called when the corresponding subsystem receives a message
 * @param SUBSYSTEM_DATA_MODULE*: This is a pointer to this object aka the subsystem specific data module
 */
subsystemReceiveCallback rxFuncPtr;
/**
 * @brief This holds the data to be transmitted directly over CAN
 */
uint8_t transmitData[ARRAY_SIZE];
protected:
//Protected Constructor
SUBSYSTEM_DATA_MODULE();
private:
//Private Variables
/**
 * @brief This holds the value of the last mailbox selected.
 * @note Possible values are 0 to 1
 */
static uint8_t lastMailboxSelected;
/**
 * @brief This is the table of pointers to all the objects initialized for receiving
 */
static SUBSYSTEM_DATA_MODULE* receiveModulesTable[subsystem_info::NUM_MESSAGES];
//Private Function Prototypes
};

#endif //End Header Guard