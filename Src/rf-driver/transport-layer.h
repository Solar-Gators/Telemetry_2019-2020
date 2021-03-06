//File Name: transport-layer.h
//Description: This contains the class implementation for creating rf packets and transmitting them

//Header Guards
#ifndef RF_MESSAGE_LAYER_H_
#define RF_MESSAGE_LAYER_H_

//Include Files
#include "main.h"

#include "../rf-driver/data-link-layer.h"

//C Interface
#ifdef __cplusplus
extern "C" {
#endif
//C Public Constants

//C Public Variables

//C Public Function Prototypes

#ifdef __cplusplus
}
#endif //End C Interface

//C++ Interface
//Class Definitions
class RF_PACKET: private RF_DATA_LINK_LAYER
{
public:
//Constructors
/**
 * @brief Simple constructor that takes in an initialized uart_instance
 * @param uart_instance: Initialized uart_instance that will be used for communication
 */
RF_PACKET(USART_TypeDef* uart_instance);
//Public Function Prototypes
/**
 * @brief This sends the message that has been constructed by AddToMessage. It starts with @START_CHAR and ends
 * with @END_CHAR. The current message will be reset after this function is called.
 */
void Send();
/**
 * @brief This adds a new message to the packet.
 * @param address: The address of the message used in decoding on the pit side
 * @param id: The identifier for which instance the data is from
 * @param data_size: the length in bytes of @data
 * @param data: A pointer to the data to append to the data packet
 * @retval True if there was sufficient space and the message was succesfully added, false otherwise
 */
bool AddToPacket(uint8_t address, uint8_t id, uint8_t data_size, uint8_t* data);
/**
 * @brief This clears the current packet and resets the data
 */
void ClearPacket(void);
/*
 * @brief This checks to see if there are no messages in the packet
 * @retval True if packet is empty
 */
bool isPacketEmpty(void);
//Public Constants

//Public Variable
private:
//Private Constants
/**
 * @brief This is the max bytes in a packet
 */
static constexpr uint16_t MAX_PACKET_LENGTH = 200;
/**
 * @brief This is the min packet size. It contains the start and end character and the num messages byte.
 */
static constexpr uint16_t MIN_PACKET_LENGTH = 3;
//Private Variables
/**
 * @brief This holds the message
 */
uint8_t dataPacket[MAX_PACKET_LENGTH];
/**
 * @brief This is the number of messages in the packet and is the second element in the array.
 */
uint8_t numMessagesInPacket;
/**
 * @brief This is the amount of bytes that the current packet contains.
 */
uint8_t packetLength;

//Private Function Prototypes
};

#endif //End Header Guard
