//File Name: gps-driver.cpp
//Description: This implements the definition of the gps driver

//Include Files
#include "main.h"
#include "gps-driver.h"
#include "helper-code/helper-fifo.hpp"
#include <string.h>

//Private Constants
#define FIFO_DEPTH 5
#define RX_MESSAGE_MAX_SIZE 100
//Private Variables
static UART_HandleTypeDef* uartInstance;
static HELPER_FIFO<GPS_Data_t,FIFO_DEPTH,1> dataFIFO;
static char rxMessage[RX_MESSAGE_MAX_SIZE];
static uint8_t messageStart = 0;
static uint16_t rxMessageIndex = 0;
//Public Constants

//Public Variables

//Private Function Prototypes
static uint8_t parseRMCString(const char* input, GPS_Data_t* output);
//Public Function Prototypes

//Private Function Definitions

//Public Function Definitions
void GPS_init(UART_HandleTypeDef* uart_instance)
{
	uartInstance = uart_instance;
	//GPRMC only
	const char options[] = "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n";
	HAL_UART_Transmit(uartInstance, (uint8_t *)options , sizeof(options), HAL_MAX_DELAY);
	memset(rxMessage,0, RX_MESSAGE_MAX_SIZE);
}

void GPS_startReception(void)
{
	//Enable interrupts
	uartInstance->Instance->CR1 |= USART_CR1_RXNEIE;
}

uint8_t GPS_isDataAvailable(void)
{
	return !dataFIFO.IsEmpty();
}

GPS_Data_t GPS_getLatestData(void)
{
	bool success;
	return *dataFIFO.PopFront(&success);
}

extern "C"
void GPS_RxCpltCallback(void)
{
	char rxChar = (char)uartInstance->Instance->RDR;
	if(rxChar == '$')
	{
	  messageStart = 1;
	  rxMessageIndex = 0;
	}
	if(messageStart)
	{
	  rxMessage[rxMessageIndex++] = rxChar;
	}
	if(rxChar == '\n')
	{
	  rxMessage[rxMessageIndex] = '\0';
	  messageStart = 0;
	  GPS_Data_t parsedMessage;
	  if(parseRMCString(rxMessage, &parsedMessage))
	  {
		  bool success;
		  dataFIFO.PushBack(&parsedMessage, &success);
	  }
	}
}

static uint8_t parseRMCString(const char* input, GPS_Data_t* output)
{
	if(!strstr(input, "$GPRMC"))
	{
		return 0;
	}
	const char* p = input;
	p = strchr(p, ',') + 1; //Skip header
	p = strchr(p, ',') + 1; //Skip date
	//V == invalid
	if(p[0] == 'V')
	{
		return 0;
	}
	//Handle Latitude
	p = strchr(p, ',') + 1; //Go to lat
	strncpy(output->latitude, p, 9);
	p = strchr(p, ',') + 1; //Go to lat-dir
	strncpy(output->latitude + 9, p, 1);
	*(output->latitude + 10) = '\0';
	//Handle Longitude
	p = strchr(p, ',') + 1; //Go to lon
	strncpy(output->longitude, p, 10);
	p = strchr(p, ',') + 1; //Go to lon-dir
	strncpy(output->longitude + 10, p, 1);
	*(output->longitude + 11) = '\0';
	//Handle speed
	p = strchr(p, ',') + 1; //Go to speed
	uint8_t speedDigits = 0;
	speedDigits = strcspn(p, ",");
	strncpy(output->speed, p, speedDigits); //Copy to speed
	output->speed[speedDigits] = '\0';
	//Handle true course
	p = strchr(p, ',') + 1; //Go to true course
	uint8_t trueCourseDigits = 0;
	trueCourseDigits = strcspn(p, ",");
	strncpy(output->trueCourse, p, trueCourseDigits); //Copy to true course
	output->trueCourse[trueCourseDigits] = '\0';
	return 1;
}
