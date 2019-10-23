//File Name: can-message-helper.cpp
//Description: This  handles the actual sending of messages over RF

//Include Files
#include "can-message-helper.h"

//Private Constants

//Private Variables

//Public Constants

//Public Variables

//Private Function Prototypes

//Public Function Prototypes

//Private Function Definitions

//Public Function Definitions
namespace CAN_TO_RF
{
    bool AddMessage(RF_PACKET* tx_packet, CAN_MSG_RF_ADDR rf_addr, void* tx_msg)
    {
        bool success = false;
        if(tx_packet != nullptr && tx_msg != nullptr)
        {
            if(rf_addr > CAN_MSG_RF_ADDR::START && rf_addr < CAN_MSG_RF_ADDR::END)
            {
                static constexpr uint8_t MAX_CAN_MSG_SIZE = 8;
                uint8_t convertedData[MAX_CAN_MSG_SIZE];
                uint8_t actualMessageSize = 0;
                switch(rf_addr)
                {
                    case CAN_MSG_RF_ADDR::MPPT:
                    {
                        actualMessageSize = MPPT0_HELPER::ARRAY_SIZE;
                        MPPT0_HELPER::dataPacketToArray(*static_cast<MPPT_MESSAGE_0_DATA_PACKET*>(tx_msg), convertedData);
                        break;
                    }
                    case CAN_MSG_RF_ADDR::BMS:
                    {
                        actualMessageSize = BMS0_HELPER::ARRAY_SIZE;
                        BMS0_HELPER::dataPacketToArray(*static_cast<BMS_MESSAGE_0_DATA_PACKET*>(tx_msg), convertedData);
                        break;
                    }
                }
                //If rf_addr doesn't map then we will send a message of 0 size which will fail
                success = tx_packet->AddToPacket((uint8_t)rf_addr, actualMessageSize, convertedData);
            }
        }
        return success;
    }
}
