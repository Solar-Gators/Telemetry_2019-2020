//File Name: gfx.h
//Description: This defines the interface for the graphic fx library

//Header Guards
#ifndef GFX_H_
#define GFX_H_

//Include Files
#include "main.h"
#include <utility>
//C Interface
#ifdef __cplusplus
extern "C" {
#endif
//Public Defines
#define ILI9341_TFTWIDTH   240      ///< ILI9341 max TFT width
#define ILI9341_TFTHEIGHT  320      ///< ILI9341 max TFT height

#define ILI9341_MADCTL     0x36     ///< Memory Access Control
#define MADCTL_MY  0x80  ///< Bottom to top
#define MADCTL_MX  0x40  ///< Right to left
#define MADCTL_MV  0x20  ///< Reverse Mode
#define MADCTL_ML  0x10  ///< LCD refresh Bottom to top
#define MADCTL_RGB 0x00  ///< Red-Green-Blue pixel order
#define MADCTL_BGR 0x08  ///< Blue-Green-Red pixel order
#define MADCTL_MH  0x04  ///< LCD refresh right to left
// Color definitions
#define ILI9341_DARK_ORANGE 0xfc60  ///< 255, 140, 0
#define ILI9341_GOLD_ROD	0xdd24	///< 218, 165, 32
#define ILI9341_BLACK       0x0000  ///<   0,   0,   0
#define ILI9341_NAVY        0x000F  ///<   0,   0, 123
#define ILI9341_DARKGREEN   0x03E0  ///<   0, 125,   0
#define ILI9341_DARKCYAN    0x03EF  ///<   0, 125, 123
#define ILI9341_MAROON      0x7800  ///< 123,   0,   0
#define ILI9341_PURPLE      0x780F  ///< 123,   0, 123
#define ILI9341_OLIVE       0x7BE0  ///< 123, 125,   0
#define ILI9341_LIGHTGREY   0xC618  ///< 198, 195, 198
#define ILI9341_DARKGREY    0x7BEF  ///< 123, 125, 123
#define ILI9341_BLUE        0x001F  ///<   0,   0, 255
#define ILI9341_GREEN       0x07E0  ///<   0, 255,   0
#define ILI9341_CYAN        0x07FF  ///<   0, 255, 255
#define ILI9341_RED         0xF800  ///< 255,   0,   0
#define ILI9341_MAGENTA     0xF81F  ///< 255,   0, 255
#define ILI9341_YELLOW      0xFFE0  ///< 255, 255,   0
#define ILI9341_WHITE       0xFFFF  ///< 255, 255, 255
#define ILI9341_ORANGE      0xFD20  ///< 255, 165,   0
#define ILI9341_GREENYELLOW 0xAFE5  ///< 173, 255,  41
#define ILI9341_PINK        0xFC18  ///< 255, 130, 198
#define ILI9341_SADDLEBROWN 0x8A22  ///< 139, 69, 19
#define ILI9341_LIGHTGREEN 	0x4FC7  ///< 139, 69, 19
//C Public Constants

//C Public Variables

//C Public Function Prototypes

#ifdef __cplusplus
}
#endif //End C Interface

//C++ Interface
//Class Definitions
class TFT_GFX
{
public:
//Constructors
TFT_GFX(SPI_TypeDef *SPIx);
//Delete all other constructors
TFT_GFX(void) = delete;
TFT_GFX(const TFT_GFX&) = delete;
TFT_GFX(const TFT_GFX&&) = delete;
TFT_GFX& operator=(const TFT_GFX&) = delete;
TFT_GFX& operator=(const TFT_GFX&&) = delete;
//Public Function Prototypes
/**************************************************************************/
/*!
    @brief   Set the "address window" - the rectangle we will write to RAM with the next chunk of 
    SPI data writes. The ILI9341 will automatically wrap the data as each row is filled
    @param   x1  TFT memory 'x' origin
    @param   y1  TFT memory 'y' origin
    @param   w   Width of rectangle
    @param   h   Height of rectangle
*/
/**************************************************************************/
void setAddrWindow(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h);
/*!
    @brief  Draw a single pixel to the display at requested coordinates.
            Not self-contained; should follow a startWrite() call.
    @param  x      Horizontal position (0 = left).
    @param  y      Vertical position   (0 = top).
    @param  color  16-bit pixel color in '565' RGB format.
*/
void writePixel(int16_t x, int16_t y, uint16_t color);
/*!
    @brief  Draw a filled rectangle to the display. Not self-contained;
            should follow startWrite(). Typically used by higher-level
            graphics primitives; user code shouldn't need to call this and
            is likely to use the self-contained fillRect() instead.
            writeFillRect() performs its own edge clipping and rejection;
            see writeFillRectPreclipped() for a more 'raw' implementation.
    @param  x      Horizontal position of first corner.
    @param  y      Vertical position of first corner.
    @param  w      Rectangle width in pixels (positive = right of first
                   corner, negative = left of first corner).
    @param  h      Rectangle height in pixels (positive = below first
                   corner, negative = above first corner).
    @param  color  16-bit fill color in '565' RGB format.
    @note   Written in this deep-nested way because C by definition will
            optimize for the 'if' case, not the 'else' -- avoids branches
            and rejects clipped rectangles at the least-work possibility.
*/
void writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
/*!
    @brief  A lower-level version of writeFillRect(). This version requires
            all inputs are in-bounds, that width and height are positive,
            and no part extends offscreen. NO EDGE CLIPPING OR REJECTION IS
            PERFORMED. If higher-level graphics primitives are written to
            handle their own clipping earlier in the drawing process, this
            can avoid unnecessary function calls and repeated clipping
            operations in the lower-level functions.
    @param  x      Horizontal position of first corner. MUST BE WITHIN
                   SCREEN BOUNDS.
    @param  y      Vertical position of first corner. MUST BE WITHIN SCREEN
                   BOUNDS.
    @param  w      Rectangle width in pixels. MUST BE POSITIVE AND NOT
                   EXTEND OFF SCREEN.
    @param  h      Rectangle height in pixels. MUST BE POSITIVE AND NOT
                   EXTEND OFF SCREEN.
    @param  color  16-bit fill color in '565' RGB format.
    @note   This is a new function, no graphics primitives besides rects
            and horizontal/vertical lines are written to best use this yet.
*/
inline void writeFillRectPreclipped(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
/*!
    @brief  Issue a series of pixels, all the same color. Not self-
            contained; should follow startWrite() and setAddrWindow() calls.
    @param  color  16-bit pixel color in '565' RGB format.
    @param  len    Number of pixels to draw.
*/
void writeColor(uint16_t color, uint32_t len);
/*!
    @brief  Draw a vertical line on the display. Performs edge clipping and
            rejection. Not self-contained; should follow startWrite().
            Typically used by higher-level graphics primitives; user code
            shouldn't need to call this and is likely to use the self-
            contained drawFastVLine() instead.
    @param  x      Horizontal position of first point.
    @param  y      Vertical position of first point.
    @param  h      Line height in pixels (positive = below first point,
                   negative = above first point).
    @param  color  16-bit line color in '565' RGB format.
*/
void inline writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
/*!
    @brief  Draw a horizontal line on the display. Performs edge clipping
            and rejection. Not self-contained; should follow startWrite().
            Typically used by higher-level graphics primitives; user code
            shouldn't need to call this and is likely to use the self-
            contained drawFastHLine() instead.
    @param  x      Horizontal position of first point.
    @param  y      Vertical position of first point.
    @param  w      Line width in pixels (positive = right of first point,
                   negative = point of first corner).
    @param  color  16-bit line color in '565' RGB format.
*/
void inline writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
/**************************************************************************/
/*!
   @brief   Draw a single character
    @param    x   Bottom left corner x coordinate
    @param    y   Bottom left corner y coordinate
    @param    c   The 8-bit font-indexed character (likely ascii)
    @param    color 16-bit 5-6-5 Color to draw chraracter with
    @param    bg 16-bit 5-6-5 Color to fill background with (if same as color, no background)
    @param    size_x  Font magnification level in X-axis, 1 is 'original' size
    @param    size_y  Font magnification level in Y-axis, 1 is 'original' size
*/
/**************************************************************************/
void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size_x, uint8_t size_y);
/**************************************************************************/
/*!
   @brief   Draw a single character
    @param    init_x   Bottom left corner x coordinate of first char
    @param    init_y   Bottom left corner y coordinate of first char
    @param    s   Null-terminated ASCII string (max length is MAX_STRING_LENGTH characters)
    @param    color 16-bit 5-6-5 Color to draw chraracter with
    @param    bg 16-bit 5-6-5 Color to fill background with (if same as color, no background)
    @param    size_x  Font magnification level in X-axis, 1 is 'original' size
    @param    size_y  Font magnification level in Y-axis, 1 is 'original' size
    @param	  x_edge   This is the edge of the text string for wrapping and centering
    @param	  do_center	  True to center text false if not
    @retval   Returns the bound of the string in the x direction in first and the bound of the string in the y direction in second
*/
/**************************************************************************/
std::pair<uint16_t, uint16_t> drawString(int16_t init_x, int16_t init_y, const char* s, uint16_t color, uint16_t bg, uint8_t size_x, uint8_t size_y, uint16_t x_edge, bool do_center = false);
/**************************************************************************/
/*!
    @brief   Set origin of (0,0) and orientation of TFT display
    @param   m  The index for rotation, from 0-3 inclusive
*/
/**************************************************************************/
void setRotation(uint8_t m);
/**
 * @brief Gets the current width of the TFT display
 */
uint16_t width(void);
/**
 * @brief Gets the current height of the TFT display
 */
uint16_t height(void);
//Public Constants
//Public Variable
private:
//Private Constants
static constexpr uint8_t MAX_STRING_LENGTH = 100;
//Private Variables
SPI_TypeDef* spiInstance;
//This is not the same as TFT_WIDTH and TFT_HEIGHT due to the fact we can rotate the screen
uint16_t _width;
uint16_t _height;
//Private Function Prototypes
/**
 * @brief This returns the size of the current word pointed to be string
 * @param A null-terminated or space-terminated string
 * @retval The amount of characters in the word pointed to be string. 0 if string points to a space or null character.
 */
uint8_t getWordSize(const char* string);
/**
 * @brief This returns the expected size of the line
 * @param string: A null-terminated string
 * @param max_chars_in_line: The maximum number of characters in one line
 * @retval The number of characters that will fit onto this line
 */
uint8_t getLineSize(const char* string, uint8_t max_chars_in_line);
/**
 * @brief This returns the total characters in a string
 * @param string: A null-terminated string
 * @retval The number of characters in string, disregarding the null character
 */
uint8_t getStringSize(const char* string);
};

#endif //End Header Guard
