#ifndef HSPI_H
#define HSPI_H

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif


void pullCSLow(void);
void pullCSHigh(void);
void hspi_w8(SPI_TypeDef *SPIx, uint8_t dat);
void hspi_w16(SPI_TypeDef *SPIx, uint16_t dat);
void hspi_cmd(SPI_TypeDef *SPIx, uint8_t cmd);
void sendCommand(SPI_TypeDef *SPIx, uint8_t cmd, uint8_t* data, uint8_t length);
void ili9341_hspi_init(SPI_TypeDef *SPIx);
/**
 * @brief This function resets the TFT board and starts it back up again
 */
void resetTftBoard(void);

#ifdef __cplusplus
}
#endif //End C Interface

#endif 
