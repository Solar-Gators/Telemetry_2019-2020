//File Name: motor-driver-data-module.hpp
//Description: This holds the headers for all the different types of motor driver messages

//Header Guards
#ifndef MOTOR_DRIVER_DATA_MODULE_H_
#define MOTOR_DRIVER_DATA_MODULE_H_

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
/*****************TX Classes*****************/
struct MITSUBA_DRIVER_TX_RL_DATA_PACKET
{
    bool requestFrame0;
    bool requestFrame1;
    bool requestFrame2;
};

class MITSUBA_DRIVER_TX_RL_MESSAGE final: public SUBSYSTEM_DATA_MODULE_TEMPLATE_INTERFACE<MITSUBA_DRIVER_TX_RL_MESSAGE, MITSUBA_DRIVER_TX_RL_DATA_PACKET>
{
public:
//Constructors
MITSUBA_DRIVER_TX_RL_MESSAGE(uint32_t message_id);
//Public Constants
static constexpr uint8_t NUM_BYTES = 1;
//Public Function Prototypes
/**
 * @brief This function converts @input to fill the encoded @output array
 * @param input: Data to be converted
 * @param output: Array that should be allocated at least @ARRAY_SIZE bytes
 */
static void dataPacketToArray(MITSUBA_DRIVER_TX_RL_DATA_PACKET input, uint8_t output[NUM_BYTES]);
/**
 * @brief This converts the encoded @input array to a data packet
 * @param input: Encoded array of @ARRAY_SIZE bytes
 * @retval A data packet
 */
static MITSUBA_DRIVER_TX_RL_DATA_PACKET arrayToDataPacket(uint8_t input[NUM_BYTES]);
//Public Variables
/**
 * @brief Fill this out prior to calling SendData()
 */
MITSUBA_DRIVER_TX_RL_DATA_PACKET txData;
};

/*****************RX Classes*****************/
struct MITSUBA_DRIVER_RX_FRAME_0_DATA_PACKET
{
	uint16_t battVoltage;
	uint16_t battCurrent;
	bool 	 battCurrentDir;
	uint16_t motorCurrentPkAvg;
	uint8_t  FETtemp;
	uint16_t motorRPM;
	uint16_t PWMDuty;
	uint8_t  LeadAngle;
};

class MITSUBA_DRIVER_RX_FRAME_0 final: public SUBSYSTEM_DATA_MODULE_TEMPLATE_INTERFACE<MITSUBA_DRIVER_RX_FRAME_0, MITSUBA_DRIVER_RX_FRAME_0_DATA_PACKET>
{
public:
//Constructors
MITSUBA_DRIVER_RX_FRAME_0(uint32_t message_id);
//Public Constants
static constexpr uint8_t NUM_BYTES = 8;
//Public Function Prototypes
/**
 * @brief This function converts @input to fill the encoded @output array
 * @param input: Data to be converted
 * @param output: Array that should be allocated at least @ARRAY_SIZE bytes
 */
static void dataPacketToArray(MITSUBA_DRIVER_RX_FRAME_0_DATA_PACKET input, uint8_t output[NUM_BYTES]);
/**
 * @brief This converts the encoded @input array to a data packet
 * @param input: Encoded array of @ARRAY_SIZE bytes
 * @retval A data packet
 */
static MITSUBA_DRIVER_RX_FRAME_0_DATA_PACKET arrayToDataPacket(uint8_t input[NUM_BYTES]);
//Public Variables
/**
 * @brief This variable does nothing
 */
MITSUBA_DRIVER_RX_FRAME_0_DATA_PACKET txData;
};

struct MITSUBA_DRIVER_RX_FRAME_1_DATA_PACKET
{
	bool 	 powerMode;
	bool 	 MCmode;
	uint16_t AcceleratorPosition;
	uint16_t regenVRposition;
	uint8_t	 digitSWposition;
	uint16_t outTargetVal;
	uint8_t  driveActStat;
	bool	 regenStat;
};

class MITSUBA_DRIVER_RX_FRAME_1 final: public SUBSYSTEM_DATA_MODULE_TEMPLATE_INTERFACE<MITSUBA_DRIVER_RX_FRAME_1, MITSUBA_DRIVER_RX_FRAME_1_DATA_PACKET>
{
public:
//Constructors
MITSUBA_DRIVER_RX_FRAME_1(uint32_t message_id);
//Public Constants
static constexpr uint8_t NUM_BYTES = 5;
//Public Function Prototypes
/**
 * @brief This function converts @input to fill the encoded @output array
 * @param input: Data to be converted
 * @param output: Array that should be allocated at least @ARRAY_SIZE bytes
 */
static void dataPacketToArray(MITSUBA_DRIVER_RX_FRAME_1_DATA_PACKET input, uint8_t output[NUM_BYTES]);
/**
 * @brief This converts the encoded @input array to a data packet
 * @param input: Encoded array of @ARRAY_SIZE bytes
 * @retval A data packet
 */
static MITSUBA_DRIVER_RX_FRAME_1_DATA_PACKET arrayToDataPacket(uint8_t input[NUM_BYTES]);
//Public Variables
/**
 * @brief This variable does nothing
 */
MITSUBA_DRIVER_RX_FRAME_1_DATA_PACKET txData;
};

struct MITSUBA_DRIVER_RX_FRAME_2_DATA_PACKET
{
	bool adSensorError;
	bool motorCurrSensorUError;
	bool motorCurrSensorWError;
	bool fetThermError;
	bool battVoltSensorError;
	bool battCurrSensorError;
	bool battCurrSensorAdjError;
	bool motorCurrSensorAdjError;
	bool accelPosError;
	bool contVoltSensorError;
	bool powerSystemError;
	bool overCurrError;
	bool overVoltError;
	bool overCurrLimit;
	bool motorSystemError;
	bool motorLock;
	bool hallSensorShort;
	bool hallSensorOpen;
	uint8_t overHeatLevel;
};

class MITSUBA_DRIVER_RX_FRAME_2 final: public SUBSYSTEM_DATA_MODULE_TEMPLATE_INTERFACE<MITSUBA_DRIVER_RX_FRAME_2, MITSUBA_DRIVER_RX_FRAME_2_DATA_PACKET>
{
public:
//Constructors
MITSUBA_DRIVER_RX_FRAME_2(uint32_t message_id);
//Public Constants
static constexpr uint8_t NUM_BYTES = 5;
//Public Function Prototypes
/**
 * @brief This function converts @input to fill the encoded @output array
 * @param input: Data to be converted
 * @param output: Array that should be allocated at least @ARRAY_SIZE bytes
 */
static void dataPacketToArray(MITSUBA_DRIVER_RX_FRAME_2_DATA_PACKET input, uint8_t output[NUM_BYTES]);
/**
 * @brief This converts the encoded @input array to a data packet
 * @param input: Encoded array of @ARRAY_SIZE bytes
 * @retval A data packet
 */
static MITSUBA_DRIVER_RX_FRAME_2_DATA_PACKET arrayToDataPacket(uint8_t input[NUM_BYTES]);
//Public Variables
/**
 * @brief This variable does nothing
 */
MITSUBA_DRIVER_RX_FRAME_2_DATA_PACKET txData;
};

#endif //End Header Guard
