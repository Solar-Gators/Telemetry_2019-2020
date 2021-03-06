//File Name: can-message-helper.h
//Description: This contains the class implementation for creating rf packets and transmitting them

//Header Guards
#ifndef CAN_MESSAGE_HELPER_H_
#define CAN_MESSAGE_HELPER_H_

//Include Files
//CAN include files
#include <orion-data-module.hpp>
#include <proton1-data-module.hpp>
#include <mitsuba-driver-data-module.hpp>
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
enum struct RF_TYPES
{
	//Do not edit this following line
	START = -1,
	GPS,
	PROTON1,
	ORION,
	IMU,
	MITSUBA_FRAME0,
	MITSUBA_FRAME1,
	MITSUBA_FRAME2,
	//Do not edit this following line
	END
};

namespace IMU_TO_RF
{
	/**
	 * @brief This adds @tx_msg to @tx_packet
	 * @param tx_packet: this is a pointer to an rf packet
	 * @param tx_msg: pointer to imu message
	 * @retval True on success false otherwise
	 */
	bool AddMessage(RF_PACKET* tx_packet, uint8_t rf_id, IMU_DATA_t* tx_msg);
}

namespace CAN_TO_RF
{
	/**
	 * @brief This adds @tx_msg to @tx_packet
	 * @param tx_packet: this is a pointer to an rf packet
	 * @param rf_addr: This is a type of rf_addr between start and end
	 * @param tx_msg: this is a can-specific data message that should correspond to the rf_addr chosen
	 * @retval True on success false otherwise
	 */
    bool AddMessage(RF_PACKET* tx_packet, RF_TYPES rf_addr, uint8_t rf_id, void* tx_msg);
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
    bool AddMessage(RF_PACKET* tx_packet, uint8_t rf_id, GPS_Data_t* tx_msg);
}
//Class Definitions

#endif //End Header Guard
