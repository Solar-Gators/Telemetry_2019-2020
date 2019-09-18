#ifndef CAN_H
#define CAN_H
#include "stm32f0xx.h"
#include "stdint.h"



/*************Defines*************/

//Uncomment for debugging purposes
#define DEBUG

//Only uncomment the line that corresponds to your subsystem

//#define MPPT_DEF //This is for MPPT
//#define BMS_DEF //This is for BMS
//#define SPEED_DEF //This is for the speed sensor
#define RF_DEF //This is for the RF transmitter on the car

//This is the false value for if data is invalid when returning
#define falseValue 0xFFEE
//This is the maximum data size of all the above variables in bytes
#define maxDataSize 2


/*********TypeDefs**********/
typedef enum mailbox{NONE,mailbox0,mailbox1,mailbox0_and_1} Mailbox;
//This is the msgid's for each message
typedef enum msgid{MPPT0_MSGID = 0x600,
									 TEST_MSGID = 10,
									BMS0_MSGID = 1023,
									SPEED_MSGID = 1025
									}MSGID;							
									
/*************Storage TypeDefs***************/								
//New struct for data + what that data is (variable_name)
typedef struct StoragePacket
{
	uint8_t data[maxDataSize];
	uint8_t num_bytes;
	uint8_t data_valid;
}StoragePacket;

//New struct to easily send data
typedef struct TransmitPacket
{
	MSGID message_identifier;
	uint8_t data[8];
	uint8_t num_bytes;
}TransmitPacket;
/********************************************/



/***********Functions***********/

//This handles the setup of the CAN bus
void CAN_Setup(void);
//This is for the receive interrupt
void CEC_CAN_IRQHandler(void); 
//This is to check if the data we receive is valid
#define isInvalid(a) (a == falseValue)

//These functions are for receiving and sending
//Certain functions are only accessible by certain subsystems
#if defined(MPPT_DEF)

#elif defined(BMS_DEF)

#elif defined(RF_DEF)
#ifdef DEBUG
void Send_Test_Message(float V_in, float I_in, float efficiency_in);
float getTest_Voltage(void);
float getTest_Current(void);
float getTest_Efficiency(void);
#endif
//These are from the MPPT
void Send_RTRtoMPPT (void);
float getArrayVoltage(void);
float getArrayCurrent(void);
float getBatteryVoltage(void);
float getTemperature_MPPT(void);
//These are from the BMS
float getPackCurrent(void);
float getPackVoltage(void);
float getPackSOC(void);
uint16_t getRelayState(void);
uint16_t getCRCChecks(void); //This is the checksum
//This is from the Speed
float getSpeed(void);

#elif defined(SPEED_DEF)
void Send_SPEED_Message(float speed);

#endif


#endif
