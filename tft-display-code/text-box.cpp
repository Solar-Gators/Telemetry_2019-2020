//File Name: text-box.cpp
//Description: This implements functions necessary to use a text box

//Include Files
#include "text-box.h"

//Private Constants

//Private Variables

//Public Constants

//Public Variables

//Private Function Prototypes

//Public Function Prototypes

//Private Function Definitions

//Public Function Definitions
TFT_TEXT_BOX::TFT_TEXT_BOX(TFT_GFX* display, uint16_t bg_color, uint16_t x_pos, uint16_t y_pos, int16_t x_edge, bool is_centered):
main_display{display}, xPos{x_pos}, yPos{y_pos}, prevMaxX{x_pos}, prevMaxY{y_pos}, bgColor{bg_color}, isCentered{is_centered}
{
	if(x_edge <= x_pos || x_edge > display->width())
	{
		this->wrapXEdge = display->width();
	}else{
		this->wrapXEdge = x_edge;
	}
}

TFT_TEXT_BOX::TFT_TEXT_BOX(void):
main_display{nullptr}, xPos{0}, yPos{0}, prevMaxX{0}, prevMaxY{0}, bgColor{0},wrapXEdge{0}, isCentered{0}
{}

uint16_t TFT_TEXT_BOX::write(const char* string, uint16_t font_color, uint8_t font_size)
{
    //First clear previous text
    this->clear();
    //Then draw new text
	std::pair<uint16_t, uint16_t> drawStringRet = this->main_display->drawString(this->xPos, this->yPos, string, font_color, font_color, font_size, font_size, this->wrapXEdge, this->isCentered);
	this->prevMaxX = drawStringRet.first;
	this->prevMaxY = drawStringRet.second;
	return this->prevMaxY;
}

void TFT_TEXT_BOX::clear(void)
{
    this->main_display->writeFillRect(this->xPos, this->yPos, this->prevMaxX - this->xPos, this->prevMaxY - this->yPos, this->bgColor);
}
