//File Name: can-message-helper.cpp
//Description: This  handles the actual sending of messages over RF

//Include Files
#include "../rf-driver/rf-message-helper.h"

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
    bool AddMessage(RF_PACKET* tx_packet, RF_ADDRESSES rf_addr, void* tx_msg)
    {
        bool success = false;
        if(tx_packet != nullptr && tx_msg != nullptr)
        {
            if(rf_addr > RF_ADDRESSES::START && rf_addr < RF_ADDRESSES::END)
            {
            	bool msgValid = true;
                static constexpr uint8_t MAX_CAN_MSG_SIZE = 8;
                uint8_t convertedData[MAX_CAN_MSG_SIZE];
                uint8_t actualMessageSize = 0;
                switch(rf_addr)
                {
                    case RF_ADDRESSES::MPPT:
                    {
                        actualMessageSize = MPPT0_HELPER::ARRAY_SIZE;
                        MPPT0_HELPER::dataPacketToArray(*static_cast<MPPT_MESSAGE_0_DATA_PACKET*>(tx_msg), convertedData);
                        break;
                    }
                    case RF_ADDRESSES::BMS:
                    {
                        actualMessageSize = BMS0_HELPER::ARRAY_SIZE;
                        BMS0_HELPER::dataPacketToArray(*static_cast<BMS_MESSAGE_0_DATA_PACKET*>(tx_msg), convertedData);
                        break;
                    }
                    default:
                    {
                    	msgValid = false;
                    	break;
                    }
                }
                if(msgValid)
                {
                    success = tx_packet->AddToPacket((uint8_t)rf_addr, actualMessageSize, convertedData);
                }
            }
        }
        return success;
    }
}

namespace GPS_TO_RF
{
	bool AddMessage(RF_PACKET* tx_packet, GPS_Data_t* tx_msg)
	{
		bool success = false;
        if(tx_packet != nullptr && tx_msg != nullptr)
        {
			//Add 3 for the 3 commas
			char convertedData[GPS_MSG_MAX_BYTES + 3];
			//4 is the amount of parameters to send: lat, lon, speed, trueCourse
			uint8_t index = 0;
			//Define lambda to convert parameter string to data
			auto addToConvertedData = [&index](char* convertedData, char* parameterString) -> void {
				uint8_t parameterIndex = 0;
				while(parameterString[parameterIndex])
				{
					convertedData[index++] = parameterString[parameterIndex++];
				}
			};
			//Add all of the parameters to the converted data
			addToConvertedData(convertedData, tx_msg->latitude);
			convertedData[index++] = ',';
			addToConvertedData(convertedData, tx_msg->longitude);
			convertedData[index++] = ',';
			addToConvertedData(convertedData, tx_msg->speed);
			convertedData[index++] = ',';
			addToConvertedData(convertedData, tx_msg->trueCourse);
			//Add RF packet
			success = tx_packet->AddToPacket((uint8_t)RF_ADDRESSES::GPS, index, (uint8_t*)convertedData);
        }
        return success;
	}
}
