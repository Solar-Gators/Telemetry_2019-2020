#ifndef PIN_DEFINITIONS_H_
#define PIN_DEFINITIONS_H_

#include "main.h"

#define TFT_DC_PORT (TFT_D_C_GPIO_Port)
#define TFT_DC_PIN (TFT_D_C_Pin_Num)
#define TFT_RST_PORT (TFT_RST_GPIO_Port)
#define TFT_RST_PIN (TFT_RST_Pin_Num)

#define SPI2_MOSI_PORT (GPIOC)
#define SPI2_MOSI_PIN (3)
#define SPI2_MISO_PORT (GPIOC)
#define SPI2_MISO_PIN (2)
#define SPI2_SCK_PORT (GPIOB)
#define SPI2_SCK_PIN (10)
#define SPI2_CS_PORT (SPI2_NSS_GPIO_Port)
#define SPI2_CS_PIN (SPI2_NSS_Pin_Num)

#endif
