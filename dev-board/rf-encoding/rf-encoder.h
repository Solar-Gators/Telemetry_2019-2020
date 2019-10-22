//File Name: rf-encoder.h
//Description: This contains the class implementation for encoding for rf transmissions

//Header Guards
#ifndef RF_ENCODER_H_
#define RF_ENCODER_H_

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
enum struct RF_ADDRESS: uint8_t
{
	GPS = 0,
	MPPT,
	NUM_ADDRESSES
};
//Class Definitions
class RF_ENCODER
{
public:
//Constructors
RF_ENCODER();
//Public Function Prototypes
void Send();
bool AddToMessage(RF_ADDRESS data_address, void* data);
//Public Constants

//Public Variable
private:
//Private Constants
static constexpr uint8_t START_CHAR = 0xFF;
static constexpr uint8_t END_CHAR = 0x3F;
//Private Variables

//Private Function Prototypes
};

#endif //End Header Guard
