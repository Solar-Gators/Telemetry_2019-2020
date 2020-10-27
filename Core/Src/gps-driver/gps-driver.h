//File Name: gps-driver.h
//Description: This contains the implementation of the gps driver for receiving gps data through uart and parsing it

//Header Guards
#ifndef GPS_DRIVER_H_
#define GPS_DRIVER_H_

//Include Files
#include "main.h"
//Public Constants
#define GPS_LATITUDE_BYTES 11
#define GPS_LONGITUDE_BYTES 12
#define GPS_SPEED_BYTES 10
#define GPS_TRUECOURSE_BYTES 10
#define GPS_MSG_MAX_BYTES (GPS_LATITUDE_BYTES + GPS_LONGITUDE_BYTES + GPS_SPEED_BYTES + GPS_TRUECOURSE_BYTES)
//Public Structs
typedef struct gps_data
{
	char latitude[GPS_LATITUDE_BYTES]; //Format for lat lon is: lat: DDMM.MMMM(N/S) lon: DDDMM.MMMM(E/W)
	char longitude[GPS_LONGITUDE_BYTES]; //4042.6142,N 07400.4168,W. = +40  42.6142', -74  00.4168' in google maps
	char speed[GPS_SPEED_BYTES]; //This is in knots
	char trueCourse[GPS_TRUECOURSE_BYTES]; //This is in degrees
}GPS_Data_t;
//Public Variables

//Public Function Prototypes
void GPS_init(USART_TypeDef* uart_instance);

void GPS_startReception(void);

bool GPS_isDataAvailable(void);

GPS_Data_t GPS_getLatestData(void);

#endif //End Header Guard
