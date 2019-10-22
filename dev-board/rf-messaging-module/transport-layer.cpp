//File Name: transport-layer.cpp
//Description: This  handles the actual sending of messages over RF

//Include Files
#include "transport-layer.h"

//Private Constants
/*This is an example description for constants and variables. Delete this if it is unused here and copy and paste it to where it is needed. */
/**
 * @brief This is a brief description
 */
//Private Variables

//Public Constants

//Public Variables

//Private Function Prototypes
/*This is an example description for function prototypes. Delete this if it is unused here and copy and paste it to where it is needed. */
/* @brief This is a brief description
 * @param Input_Param_Name - Description of input parameter
 * @ret Description of return value
 */

//Public Function Prototypes

//Private Function Definitions

//Public Function Definitions
RF_TRANSPORT_LAYER::RF_TRANSPORT_LAYER(USART_TypeDef* uart_instance):
uartInstance{uart_instance}
{}

void sendMessage(uint8_t* data, uint16_t data_length)
{

}
