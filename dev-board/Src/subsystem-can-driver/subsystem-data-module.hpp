//File Name: subsystem-data-module.hpp
//Description: This is what each subsystem will inherit from for storage

//Header Guards
#ifndef SUBSYSTEM_DATA_MODULE_H_
#define SUBSYSTEM_DATA_MODULE_H_

//Include Files
#include "subsystem-info.hpp"
#include "helper-code/helper-fifo.hpp"
#include "helper-code/rx-module-binary-tree.hpp"
#include "main.h" //TODO MAKE MORE SPECIFIC
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
void SetupReceive(subsystemReceiveCallback rx_func_ptr);
/**
 * @brief This function is used to take in a mppt data packet and send it over CAN.
 */
void SendData(void);
/**
 * @brief This calls the callback set up for receiving if there was one otherwise it does nothing.
 */
void CallReceiveCallback(void);
/**
 * @brief This returns if the fifo is empty
 */
bool isFifoEmpty(void);
/**
 * @brief This returns if the fifo is full
 */
bool isFifoFull(void);
/**
 * @brief This adds incoming data to the rx fifo
 * @param incoming_data: A pointer to data of length ARRAY_SIZE
 * @return false if the fifo was full when attempting this and true if was successfully added
 */
bool addToFifo(uint8_t* incoming_data);
/**
 * @brief This function starts CAN and must be called prior to any messages being sent or received.
 * @note This function should be called after all the SetupReceive()'s have been called
 * @IMPORTANT You must implement HAL_CAN_MspInit yourself. You must also implement
 * CEC_CAN_IRQHandler yourself and have it call HAL_CAN_IRQHandler.
 */
static void StartCAN(void);
/**
 * @brief This searches for modules that have been initialized for receiving
 * @param message_id: The CAN message id corresponding to the message
 * @return A pointer to the module's base class
 */
static SUBSYSTEM_DATA_MODULE* FindReceivingModule(uint32_t message_id);
//Public Constants
static constexpr uint8_t FIFO_DEPTH = 3;
static constexpr uint8_t ARRAY_SIZE = 8;
/**
 * @brief This is the fifo number all receive messages will be mapped to
 */
static constexpr uint32_t CAN_RX_FIFO_NUMBER = 0;
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
 * @brief This is true if the id is an extended id false otherwise
 */
const bool isExtID;
/**
 * @brief This is the instance of the CAN handle needed to use the HAL CAN operations
 */
static CAN_HandleTypeDef hcan;
protected:
//Protected Constructor
SUBSYSTEM_DATA_MODULE(uint32_t message_id, uint8_t data_length, bool is_ext_id);
//Protected Function Prototypes
/**
 * @brief This fills the transmit buffer using the subsystem specific txData
 */
virtual void fillTransmitBuffer(void) = 0;
/**
 * @brief This is called to send data on the CAN lines using the txDataPacket
 */
void sendTransmitBufferData(void);
//Protected Variables
/**
 * @brief This holds the data to be transmitted directly over CAN
 */
uint8_t transmitBuffer[ARRAY_SIZE];
/**
 * @brief This is the storage fifo which can be used to store and retrieve data
 */
HELPER_FIFO<uint8_t,FIFO_DEPTH,ARRAY_SIZE> storageFifo;
private:
//Private Variables
/**
 * @brief This is the callback which will be called when the corresponding subsystem receives a message
 * @param SUBSYSTEM_DATA_MODULE*: This is a pointer to this object aka the subsystem specific data module
 */
subsystemReceiveCallback rxFuncPtr;
/**
 * @brief This holds if this particular module is initialized for receiving or not
 */
bool isReceiving;
/**
 * @brief This is a binary tree of pointers to all the objects initialized for receiving
 */
static RX_BINARY_TREE rxModulesTree;
//Private Function Prototypes
};

/**
 * @brief This is a templated middleman class. The SUBSYSTEM_DATA_MODULE class isn't a template because it would be wasting program memory
 * since only two of the functions need to be function templates.
 */
template <typename CHILD_OBJ, typename CHILD_DATA>
class SUBSYSTEM_DATA_MODULE_TEMPLATE_INTERFACE: public SUBSYSTEM_DATA_MODULE
{
public:
	/**
	 * @brief This is used to get the first received data packet
	 * @param success: returns true if there was data to get, false if the fifo was empty. You must pass in a value.
	 * @return Corresponding Data Packet of Child Data Type
	 */
	CHILD_DATA GetOldestDataPacket(bool* success)
	{
		CHILD_DATA returnData;
	    if(success)
	    {
	        uint8_t* raw_data = this->storageFifo.PopFront(success);

	        //Only do the conversions if we successfully extracted from the fifo
	        if(*success)
	        {
	        	returnData = static_cast<CHILD_OBJ*>(this)->arrayToDataPacket(raw_data);
	        }
	    }
	    return returnData;
	}
protected:
	SUBSYSTEM_DATA_MODULE_TEMPLATE_INTERFACE(uint32_t message_id, uint8_t data_length, bool is_ext_id):
		SUBSYSTEM_DATA_MODULE{message_id, data_length, is_ext_id}
		{}
private:
	virtual void fillTransmitBuffer(void) override
	{
		static_cast<CHILD_OBJ*>(this)->dataPacketToArray(static_cast<CHILD_OBJ*>(this)->txData, this->transmitBuffer);
	}
};

#endif //End Header Guard
