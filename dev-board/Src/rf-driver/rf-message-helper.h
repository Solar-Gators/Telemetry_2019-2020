//File Name: can-message-helper.h
//Description: This contains the class implementation for creating rf packets and transmitting them

//Header Guards
#ifndef CAN_MESSAGE_HELPER_H_
#define CAN_MESSAGE_HELPER_H_

//Include Files
//CAN include files
#include "bms-data-module.hpp"
#include "mppt-data-module.hpp"

//GPS include files
#include "gps-driver.h"

//IMU include files
#include "bno055.h"

//RF include files
#include "../rf-driver/transport-layer.h"

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
enum struct RF_ADDRESSES
{
	//Do not edit this following line
	START = -1,
	GPS,
	MPPT,
	BMS,
	IMU,
	//Do not edit this following line
	END
};

namespace CAN_TO_RF
{
	/**
	 * @brief This adds @tx_msg to @tx_packet
	 * @param tx_packet: this is a pointer to an rf packet
	 * @param rf_addr: This is a type of rf_addr between start and end
	 * @param tx_msg: this is a can-specific data message that should correspond to the rf_addr chosen
	 * @retval True on success false otherwise
	 */
    bool AddMessage(RF_PACKET* tx_packet, RF_ADDRESSES rf_addr, void* tx_msg);
}

namespace GPS_TO_RF
{
	/**
	 * @brief This adds @tx_msg to @tx_packet
	 * @param tx_packet: this is a pointer to an rf packet
	 * @param rf_addr: This is a type of rf_addr between start and end
	 * @param tx_msg: this is a pointer to data for a gps message
	 * @retval True on success false otherwise
	 */
    bool AddMessage(RF_PACKET* tx_packet, GPS_Data_t* tx_msg);
}
//Class Definitions

#endif //End Header Guard
