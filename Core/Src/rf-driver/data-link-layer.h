//File Name: data-link-layer-layer.h
//Description: This contains the declarations for the actual transmission over rf

//Header Guards
#ifndef RF_DATA_LINK_LAYER_H_
#define RF_DATA_LINK_LAYER_H_

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
class RF_DATA_LINK_LAYER
{
public:
//Delete all public constructors as this will be an inherited class only
RF_DATA_LINK_LAYER() = delete;
RF_DATA_LINK_LAYER(const RF_DATA_LINK_LAYER&) = delete;
RF_DATA_LINK_LAYER(const RF_DATA_LINK_LAYER&&) = delete;
RF_DATA_LINK_LAYER& operator=(const RF_DATA_LINK_LAYER&) = delete;
RF_DATA_LINK_LAYER& operator=(const RF_DATA_LINK_LAYER&&) = delete;
//Public Function Prototypes

//Public Constants

//Public Variable
protected:
//Protected Constants
/**
 * @brief These are the special characters in the packet
 */
static constexpr uint8_t START_CHAR = 0xFF;
static constexpr uint8_t ESC_CHAR = 0x2F;
static constexpr uint8_t END_CHAR = 0x3F;
//Protected Constructor
/**
 * @brief This takes in the initialized uart instance to use for communicating information
 * @param @uart_instance: initialized uart instance
 */
RF_DATA_LINK_LAYER(USART_TypeDef* uart_instance);
//Protected Function Prototypes
/**
 * @brief This sends a message pointed to be @data of @data_length length
 * @param data: Pointer to data to send
 * @param data_length: Amount of bytes to send
 */
void sendMessage(uint8_t* data, uint16_t data_length);
private:
//Private Variables
USART_TypeDef* uartInstance;
//Private Function Prototypes
/**
 * @brief This function checks if data is one of the special characters and if so, it escapes it. Should be called before sending the data.
 * @param data - This is the data to be send
 * @param index - The current index of the data to be sent
 * @param message_length - the total size in bytes of the message to be sent
 */
inline void handleByteStuff(uint8_t data, uint16_t index, uint16_t message_length);
/**
 * @brief This sends data through UART
 */
inline void sendData(uint8_t data);
};

#endif //End Header Guard
