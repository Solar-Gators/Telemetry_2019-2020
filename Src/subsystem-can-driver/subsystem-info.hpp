//File Name: subsystem-info.hpp
//Description: This holds info on information for the CAN messages for each subsystem

//Header Guards
#ifndef SUBSYSTEM_INFO_HPP
#define SUBSYSTEM_INFO_HPP

//Include Files
#include "main.h"
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
namespace subsystem_info
{
    /**
     * @brief This is a count of the number of messages as listed below
     * @important Must be up to date
     */
    static constexpr uint8_t NUM_MESSAGES = 7;
    //Message info
    /******************AUX MESSAGES*****************/
    static constexpr uint16_t AUX0_MSG_ID = 1023;
    static constexpr uint8_t AUX0_MSG_LENGTH = 1;
    /****************MPPT MESSAGES*****************/
    static constexpr uint16_t MPPT0_MSG_ID = 1024;
    static constexpr uint8_t MPPT0_MSG_LENGTH = 8;
    /****************BMS MESSAGES*****************/
    static constexpr uint16_t BMS0_MSG_ID = 0x6B0;
    static constexpr uint8_t BMS0_MSG_LENGTH = 8;
    /****************MOTOR DRIVER MESSAGES*****************/
    //TX Messages
    static constexpr uint32_t MOTORTX_RL_MSG_ID = 0x08F89540;
    static constexpr uint8_t MOTORTX_RL_MSG_LENGTH = 1;
    //RX Messages
    static constexpr uint32_t MOTORRX0_RL_MSG_ID = 0x08850225;
    static constexpr uint8_t MOTORRX0_RL_MSG_LENGTH = 8;

    static constexpr uint32_t MOTORRX1_RL_MSG_ID = 0x08950225;
    static constexpr uint8_t MOTORRX1_RL_MSG_LENGTH = 5;

    static constexpr uint32_t MOTORRX2_RL_MSG_ID = 0x08A50225;
    static constexpr uint8_t MOTORRX2_RL_MSG_LENGTH = 5;
    /****************RF MESSAGE IDs*****************/
    static constexpr uint8_t MPPT0 = 0;
    static constexpr uint8_t MPPT1 = 1;
    static constexpr uint8_t MPPT2 = 2;
    static constexpr uint8_t MITSUBARX0_RL = 0;
    static constexpr uint8_t MITSUBARX1_RL = 0;
    static constexpr uint8_t MITSUBARX2_RL = 0;
    static constexpr uint8_t BNO5550 = 0;

};
namespace subsystem_rf_ids
{
	/****************MPPT MESSAGE IDs*****************/
    static constexpr uint8_t MPPT0 = 0;
    static constexpr uint8_t MPPT1 = 1;
    static constexpr uint8_t MPPT2 = 2;
    /****************MOTOR MESSAGE IDs*****************/
    static constexpr uint8_t MITSUBARX0_RL = 0;
    static constexpr uint8_t MITSUBARX1_RL = 0;
    static constexpr uint8_t MITSUBARX2_RL = 0;
    /****************BMS MESSAGE IDs*****************/
    static constexpr uint8_t ORION0 = 0;
    /****************IMU MESSAGE IDs*****************/
    static constexpr uint8_t BNO5550 = 0;
    /****************GPS MESSAGE IDs*****************/
    static constexpr uint8_t GPS = 0;
}
#endif //End Header Guard
