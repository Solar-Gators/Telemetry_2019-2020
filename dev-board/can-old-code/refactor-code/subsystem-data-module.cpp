//File Name: subsystem-data-module.cpp
//Description: This implements the functionality shared amongst all subsystems for data storage

//Include Files
#include "subsystem-data-module.hpp"

//Private Constants

//Private Variables
 uint8_t SUBSYSTEM_DATA_MODULE::lastMailboxSelected = 0;
 RX_BINARY_TREE SUBSYSTEM_DATA_MODULE::rxModulesTree{};
//Public Constants

//Public Variables

//Private Function Prototypes

//Private Function Definitions

//Protected Function Definitions
SUBSYSTEM_DATA_MODULE::SUBSYSTEM_DATA_MODULE(uint32_t message_id, uint8_t data_length):
messageIdentifier{message_id}, dataLength{data_length}, storageFifo{}, rxFuncPtr{nullptr}, isReceiving{false}
{}
//Public Function Definitions
void SUBSYSTEM_DATA_MODULE::SetupReceive(subsystemReceiveCallback rx_func_ptr)
{
    this->rxFuncPtr = rx_func_ptr;
    //Add node to receive tree if not already receiving
    if(!isReceiving)
    {
        SUBSYSTEM_DATA_MODULE::rxModulesTree.AddNode(this);
        isReceiving = true;
    } 
}

void SUBSYSTEM_DATA_MODULE::StartReception(void)
{
    //Start CAN receiving
}

void SUBSYSTEM_DATA_MODULE::SendData(void* subsystem_specific_data_packet)
{
    if(this->fillTransmitDataBuffer(subsystem_specific_data_packet))
    {
        //Send transmitData over CAN if we succeed in filling the transmit buffer
    }
}
