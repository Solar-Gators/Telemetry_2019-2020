//File Name: gps-driver.h
//Description: This contains the implementation of the gps driver for receiving gps data through uart and parsing it

//Header Guards
#ifndef GPS_DRIVER_H_
#define GPS_DRIVER_H_

//Include Files
#include "main.h"

//Public Structs
typedef struct gps_data
{
	char latitude[11]; //Format for lat lon is: lat: DDMM.MMMM(N/S) lon: DDDMM.MMMM(E/W)
	char longitude[12]; //4042.6142,N 07400.4168,W. = +40  42.6142', -74  00.4168' in google maps
	char speed[10]; //This is in knots
	char trueCourse[10]; //This is in degrees
}GPS_Data_t;
//Public Constants

//Public Variables

//Public Function Prototypes
void GPS_init(UART_HandleTypeDef* uart_instance);

void GPS_startReception(void);

uint8_t GPS_isDataAvailable(void);

GPS_Data_t GPS_getLatestData(void);

#endif //End Header Guard
