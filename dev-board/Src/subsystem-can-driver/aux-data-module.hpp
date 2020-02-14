//File Name: aux-data-module.hpp
//Description: This holds aux-specific data storage implementation

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
struct AUX_MESSAGE_0_DATA_PACKET
{
	bool cplusOn;
	bool cminusOn;
	bool hornOn;
	bool regenOn;
	bool hazardsOn;
	bool leftOn;
	bool rightOn;
	bool headlightsOn;
};


class AUX_MESSAGE_0 final: public SUBSYSTEM_DATA_MODULE_TEMPLATE_INTERFACE<AUX_MESSAGE_0, AUX_MESSAGE_0_DATA_PACKET>
{
public:
//Constructors
AUX_MESSAGE_0();
//Public Constants
static constexpr uint8_t NUM_BYTES = 1;
//Public Function Prototypes
/**
 * @brief This function converts @input to fill the encoded @output array
 * @param input: Data to be converted
 * @param output: Array that should be allocated at least @ARRAY_SIZE bytes
 */
static void dataPacketToArray(AUX_MESSAGE_0_DATA_PACKET input, uint8_t output[NUM_BYTES]);
/**
 * @brief This converts the encoded @input array to a data packet
 * @param input: Encoded array of @ARRAY_SIZE bytes
 * @retval A data packet
 */
static AUX_MESSAGE_0_DATA_PACKET arrayToDataPacket(uint8_t input[NUM_BYTES]);
//Public Variables
/**
 * @brief Fill this out prior to calling SendData()
 */
AUX_MESSAGE_0_DATA_PACKET txData;
};

#endif //End Header Guard
