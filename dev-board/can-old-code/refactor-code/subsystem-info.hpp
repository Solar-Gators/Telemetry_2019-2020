//File Name: subsystem-info.hpp
//Description: This holds info on information for the CAN messages for each subsystem

//Header Guards
#ifndef SUBSYSTEM_INFO_HPP
#define SUBSYSTEM_INFO_HPP

//Include Files

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
    static constexpr uint8_t NUM_MESSAGES = 2;
    //Message IDs
    static constexpr uint16_t MPPT0_MSG_ID = 1024;
    static constexpr uint16_t BMS0_MSG_ID = 1025;
};

#endif //End Header Guard