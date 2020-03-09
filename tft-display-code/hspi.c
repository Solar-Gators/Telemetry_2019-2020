#include "hspi.h"
#include "pin-definitions.h"

void resetTftBoard(void)
{
	TFT_RST_PORT->ODR &= ~(1 << TFT_RST_PIN);
	HAL_Delay(150);
	TFT_RST_PORT->ODR |=  (1 << TFT_RST_PIN);
	HAL_Delay(150);
}

void pullCSLow(void)
{
	SPI2_CS_PORT->ODR &= ~(1 << SPI2_CS_PIN);
}

void pullCSHigh(void)
{
	SPI2_CS_PORT->ODR |= (1 << SPI2_CS_PIN);
}

void hspi_w8(SPI_TypeDef *SPIx, uint8_t dat) {
  // Wait for TXE.
  while (!(SPIx->SR & SPI_SR_TXE)) {};
  // Send the byte.
  *(uint8_t*)&(SPIx->DR) = dat;
}

void hspi_w16(SPI_TypeDef *SPIx, uint16_t dat) {
  // Wait for TXE.
  while (!(SPIx->SR & SPI_SR_TXE)) {};
  // Send the data.
  // (Flip the bytes for the little-endian ARM core.)
  dat = (((dat & 0x00FF) << 8) | ((dat & 0xFF00) >> 8));
  *(uint16_t*)&(SPIx->DR) = dat;
}

void hspi_cmd(SPI_TypeDef *SPIx, uint8_t cmd) {
  while ((SPIx->SR & SPI_SR_BSY)) {};
  TFT_DC_PORT->ODR &= ~(1 << TFT_DC_PIN);
  hspi_w8(SPIx, cmd);
  while ((SPIx->SR & SPI_SR_BSY)) {};
  TFT_DC_PORT->ODR |=  (1 << TFT_DC_PIN);
}

void sendCommand(SPI_TypeDef *SPIx, uint8_t cmd, uint8_t* data, uint8_t length)
{
	hspi_cmd(SPIx,cmd);
	for(int i = 0; i < length; i++)
	{
		hspi_w8(SPIx, *(data++));
	}
}

void ili9341_hspi_init(SPI_TypeDef *SPIx) {
  // (Display off)
  //hspi_cmd(SPIx, 0x28);
  // Issue a series of initialization commands from the
  // Adafruit library for a simple 'known good' test.
  // (TODO: Add named macro definitions for these hex values.)
  hspi_cmd(SPIx, 0xEF);
  hspi_w8(SPIx, 0x03);
  hspi_w8(SPIx, 0x80);
  hspi_w8(SPIx, 0x02);
  hspi_cmd(SPIx, 0xCF);
  hspi_w8(SPIx, 0x00);
  hspi_w8(SPIx, 0xC1);
  hspi_w8(SPIx, 0x30);
  hspi_cmd(SPIx, 0xED);
  hspi_w8(SPIx, 0x64);
  hspi_w8(SPIx, 0x03);
  hspi_w8(SPIx, 0x12);
  hspi_w8(SPIx, 0x81);
  hspi_cmd(SPIx, 0xE8);
  hspi_w8(SPIx, 0x85);
  hspi_w8(SPIx, 0x00);
  hspi_w8(SPIx, 0x78);
  hspi_cmd(SPIx, 0xCB);
  hspi_w8(SPIx, 0x39);
  hspi_w8(SPIx, 0x2C);
  hspi_w8(SPIx, 0x00);
  hspi_w8(SPIx, 0x34);
  hspi_w8(SPIx, 0x02);
  hspi_cmd(SPIx, 0xF7);
  hspi_w8(SPIx, 0x20);
  hspi_cmd(SPIx, 0xEA);
  hspi_w8(SPIx, 0x00);
  hspi_w8(SPIx, 0x00);
  // PWCTR1
  hspi_cmd(SPIx, 0xC0);
  hspi_w8(SPIx, 0x23);
  // PWCTR2
  hspi_cmd(SPIx, 0xC1);
  hspi_w8(SPIx, 0x10);
  // VMCTR1
  hspi_cmd(SPIx, 0xC5);
  hspi_w8(SPIx, 0x3E);
  hspi_w8(SPIx, 0x28);
  // VMCTR2
  hspi_cmd(SPIx, 0xC7);
  hspi_w8(SPIx, 0x86);
  // MADCTL
  hspi_cmd(SPIx, 0x36);
  hspi_w8(SPIx, 0x48);
  // VSCRSADD
  hspi_cmd(SPIx, 0x37);
  hspi_w8(SPIx, 0x00);
  // PIXFMT
  hspi_cmd(SPIx, 0x3A);
  hspi_w8(SPIx, 0x55);
  // FRMCTR1
  hspi_cmd(SPIx, 0xB1);
  hspi_w8(SPIx, 0x00);
  hspi_w8(SPIx, 0x18);
  // DFUNCTR
  hspi_cmd(SPIx, 0xB6);
  hspi_w8(SPIx, 0x08);
  hspi_w8(SPIx, 0x82);
  hspi_w8(SPIx, 0x27);
  hspi_cmd(SPIx, 0xF2);
  hspi_w8(SPIx, 0x00);
  // GAMMASET
  hspi_cmd(SPIx, 0x26);
  hspi_w8(SPIx, 0x01);
  // (Actual gamma settings)
  hspi_cmd(SPIx, 0xE0);
  hspi_w8(SPIx, 0x0F);
  hspi_w8(SPIx, 0x31);
  hspi_w8(SPIx, 0x2B);
  hspi_w8(SPIx, 0x0C);
  hspi_w8(SPIx, 0x0E);
  hspi_w8(SPIx, 0x08);
  hspi_w8(SPIx, 0x4E);
  hspi_w8(SPIx, 0xF1);
  hspi_w8(SPIx, 0x37);
  hspi_w8(SPIx, 0x07);
  hspi_w8(SPIx, 0x10);
  hspi_w8(SPIx, 0x03);
  hspi_w8(SPIx, 0x0E);
  hspi_w8(SPIx, 0x09);
  hspi_w8(SPIx, 0x00);
  hspi_cmd(SPIx, 0xE1);
  hspi_w8(SPIx, 0x00);
  hspi_w8(SPIx, 0x0E);
  hspi_w8(SPIx, 0x14);
  hspi_w8(SPIx, 0x03);
  hspi_w8(SPIx, 0x11);
  hspi_w8(SPIx, 0x07);
  hspi_w8(SPIx, 0x31);
  hspi_w8(SPIx, 0xC1);
  hspi_w8(SPIx, 0x48);
  hspi_w8(SPIx, 0x08);
  hspi_w8(SPIx, 0x0F);
  hspi_w8(SPIx, 0x0C);
  hspi_w8(SPIx, 0x31);
  hspi_w8(SPIx, 0x36);
  hspi_w8(SPIx, 0x0F);
  // Exit sleep mode.
  hspi_cmd(SPIx, 0x11);
  HAL_Delay(150);
  // Display on.
  hspi_cmd(SPIx, 0x29);
	HAL_Delay(150);
  // 'Normal' display mode.
  hspi_cmd(SPIx, 0x13);
}
