//File Name: transport-layer.h
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
RF_TRANSPORT_LAYER(UART_THING);
//Protected Function Prototypes
void sendMessage(uint8_t* data, uint16_t data_length);
private:
//Private Variables
UART_THING;
//Private Function Prototypes
};

#endif //End Header Guard