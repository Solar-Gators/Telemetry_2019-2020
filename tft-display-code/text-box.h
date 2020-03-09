//File Name: text-box.h
//Description: This contains the declarations of the class used for a text box

//Header Guards
#ifndef TEXT_BOX_H_
#define TEXT_BOX_H_

//Include Files
#include "gfx.h"

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
class TFT_TEXT_BOX
{
public:
	//Constructors
	/**
	 * @brief Constructor to initialize x and y position as well as pass spi instance
	 * @param SPIx: Spi instance
	 * @param bg_color: This is the background color this text box will be on top of
	 * @param x_pos: x position of bottom left corner of text box
	 * @param y_pos: y position of bottom left corner of text box
	 * @param x_edge: This is the x_edge used for screen wrapping. If -1 this is just the edge of the screen.
	 */
	TFT_TEXT_BOX(TFT_GFX* display, uint16_t bg_color, uint16_t x_pos, uint16_t y_pos, int16_t x_edge = -1, bool is_centered = false);
	/**
	 * @brief Default constructor
	 */
	TFT_TEXT_BOX(void);
	//Public Function Prototypes
	/**
	 * @brief Writes a null terminated string in the text box
	 * @param string: Null terminated string to write
	 * @param font_size: Size of the font
	 * @retval Returns the y position of the bottom of the text box.
	 */
	uint16_t write(const char* string, uint16_t font_color, uint8_t font_size);
	/**
	 * @brief This clears the text box
	 */
	void clear(void);
	//Public Constants

	//Public Variable
private:
	//Private Variables
	/**
	 * @brief This holds a pointer to the main display for GFX
	 */
	TFT_GFX* main_display;
	/**
	 * @brief This is the x and y pos
	 */
	uint16_t xPos;
	uint16_t yPos;
	/**
	 * @brief This tracks the X bound of the previous string so we know how much to erase
	 */
	uint16_t prevMaxX;
	/**
	 * @brief This tracks the Y bound of the previous string so we know how much to erase
	 */
	uint16_t prevMaxY;
	/**
	 * @brief This is the color of the background which the text box lies on top of. Used for clear
	 */
	uint16_t bgColor;
	/**
	 * @brief This is the x edge used for wrapping text
	 */
	uint16_t wrapXEdge;
	/**
	 * @brief This is true if this text box should be centered false if not
	 */
	bool isCentered;
	//Private Function Prototypes
};

#endif //End Header Guard
