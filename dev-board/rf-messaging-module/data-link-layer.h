//File Name: data-link-layer-layer.h
//Description: This contains the declarations for the actual transmission over rf

//Header Guards
#ifndef RF_TRANSPORT_LAYER_H_
#define RF_TRANSPORT_LAYER_H_

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
class RF_TRANSPORT_LAYER
{
public:
//Delete all public constructors as this will be an inherited class only
RF_TRANSPORT_LAYER() = delete;
RF_TRANSPORT_LAYER(const RF_TRANSPORT_LAYER&) = delete;
RF_TRANSPORT_LAYER(const RF_TRANSPORT_LAYER&&) = delete;
RF_TRANSPORT_LAYER& operator=(const RF_TRANSPORT_LAYER&) = delete;
RF_TRANSPORT_LAYER& operator=(const RF_TRANSPORT_LAYER&&) = delete;
//Public Function Prototypes

//Public Constants

//Public Variable
protected:
//Protected Constructor
/**
 * @brief This takes in the initialized uart instance to use for communicating information
 * @param @uart_instance: initialized uart instance
 */
RF_TRANSPORT_LAYER(USART_TypeDef* uart_instance);
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
};

#endif //End Header Guard
