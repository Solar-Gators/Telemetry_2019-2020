//File Name: message-layer.h
//Description: This contains the class implementation for creating rf packets and transmitting them

//Header Guards
#ifndef MESSAGE_LAYER_H_
#define MESSAGE_LAYER_H_

//Include Files
#include "main.h"

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
class RF_PACKET
{
public:
//Constructors
RF_PACKET();
//Public Function Prototypes
/**
 * @brief This sends the message that has been constructed by AddToMessage. It starts with @START_CHAR and ends
 * with @END_CHAR. The current message will be reset after this function is called.
 */
void Send();
/**
 * @brief This adds a new message to the packet.
 * @param address: The address of the message
 * @param data_size: the length in bytes of @data
 * @param data: A pointer to the data to append to the data packet
 * @retval True if there was sufficient space and the message was succesfully added, false otherwise
 */
bool AddToPacket(uint8_t address, uint8_t data_size, uint8_t* data);
//Public Constants

//Public Variable
private:
//Private Constants
/**
 * @brief These are the special characters in the packet
 */
static constexpr uint8_t START_CHAR = 0xFF;
static constexpr uint8_t END_CHAR = 0x3F;
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