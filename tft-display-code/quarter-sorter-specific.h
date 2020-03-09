//File Name: quarter-sorter-specific.h
//Description: This contains any misc. quarter-sorter info

//Header Guards
#ifndef QUARTER_SORTER_SPECIFIC_H_
#define QUARTER_SORTER_SPECIFIC_H_

//Include Files
#include "text-box.h"
#include "gfx.h"

//C Interface
#ifdef __cplusplus
extern "C" {
#endif
//C Structs
//C Public Constants
static constexpr uint8_t NUM_NAMES = 50;
static constexpr uint8_t STATE_MAX_CHARS = 14;
static constexpr uint16_t NUM_BOXES = 5;
//C Public Variables
const char* const stateNames[NUM_NAMES] = {"Alabama", "Alaska", "Arizona", "Arkansas", "California", "Colorado",
		"Connecticut", "Delaware", "Florida", "Georgia", "Hawaii", "Idaho", "Illinois", "Indiana",
		"Iowa", "Kansas", "Kentucky", "Louisiana", "Maine", "Maryland", "Massachusetts", "Michigan",
		"Minnesota", "Mississippi", "Missouri", "Montana", "Nebraska", "Nevada", "New Hampshire",
		"New Jersey", "New Mexico", "New York", "North Carolina", "North Dakota", "Ohio", "Oklahoma",
		"Oregon", "Pennsylvania", "Rhode Island", "South Carolina", "South Dakota", "Tennessee", "Texas",
		"Utah", "Vermont", "Virginia", "Washington", "West Virginia", "Wisconsin", "Wyoming"};
//C Public Function Prototypes
#ifdef __cplusplus
}
#endif //End C Interface

//C++ Interface
class CHOSEN_STATE_TEXT_BOX;
class SELECTION_ENCODER;
//Enums
enum struct OVERALL_STATES: uint8_t
{
	SELECTING,
	SORTING,
	FINISHED
};
enum struct SORTING_STATES: uint8_t
{
	TAKE_PICTURES,
	MOVE_BASE_MOTOR,
};
enum struct CANCEL_STATES: uint8_t
{
	CONFIRM_CANCEL,
	NO_CANCEL,
};
//Public Functions
namespace UI_API
{
	void enableEncoder(uint16_t encA_pin, uint16_t encb_pin);
	void disableEncoder(uint16_t encA_pin, uint16_t encb_pin);
}//namespace UI_API
namespace GUI_API
{
/**
 * @brief This does an entire reset of the GUI where we are selecting states
 */
void resetSelectionGUI(TFT_GFX& tftDisplay, TFT_TEXT_BOX& instructionBox, TFT_TEXT_BOX& mainTitle, TFT_TEXT_BOX& stateSelector, CHOSEN_STATE_TEXT_BOX chosenStates[NUM_BOXES],
		const uint16_t backgroundColor,const uint16_t fontColor,const uint16_t lineColor,const uint16_t lineThickness,const uint8_t stateSelectorFontSize,
		uint8_t& statesSelected,SELECTION_ENCODER* encoder_ptr);
/**
 * @brief This draws the background color and lines that make up the selecting states gui
 */
void drawSelectionLines(TFT_GFX& tftDisplay,const uint16_t backgroundColor,const uint16_t fontColor,const uint16_t lineColor,const uint16_t lineThickness);
/**
 * @brief This fills in all the text boxes for a reset of the selecting states gui
 */
void writeSelectionWords(TFT_TEXT_BOX& instructionBox, TFT_TEXT_BOX& mainTitle, TFT_TEXT_BOX& stateSelector,const uint16_t fontColor,
		const uint8_t stateSelectorFontSize);
/**
 * @brief This is to print the current state into the current chosen state text box
 */
void printCurrentState(CHOSEN_STATE_TEXT_BOX chosenStates[NUM_BOXES], uint8_t& statesSelected,SELECTION_ENCODER* encoderPtr);
/**
 * @brief This removes the most recent state from the most recent chosen state text box
 */
void clearCurrentState(CHOSEN_STATE_TEXT_BOX chosenStates[NUM_BOXES], uint8_t& statesSelected);
/**
 * @brief This displays the in-progress screen for after the user has finished selecting their states.
 */
void displayInProgress(TFT_GFX& tftDisplay, TFT_TEXT_BOX& instructionBox, const uint16_t lineThickness, const uint16_t lineColor, const uint16_t backgroundColor, const uint16_t fontColor);
/**
 * @brief This adds in the prompt for if you're sure you want to stop sorting
 */
void addConfirmQuit(TFT_GFX& tftDisplay, const uint16_t lineThickness,const uint16_t fontColor,const uint16_t backgroundColor);
/**
 * @brief This removes the prompt for confirming if you are quitting the sorting
 */
void removeConfirmQuit(TFT_GFX& tftDisplay, const uint16_t lineThickness, const uint16_t backgroundColor);
}//namespace GUI_API
//Class Definitions
class CHOSEN_STATE_TEXT_BOX: public TFT_TEXT_BOX
{
public:
//Constructors
CHOSEN_STATE_TEXT_BOX(uint8_t text_box_number, uint16_t font_color, uint8_t font_size, const TFT_TEXT_BOX& general_text_box);
//Default constructor for mass initialization
CHOSEN_STATE_TEXT_BOX(void);
//Public Function Prototypes
void printState(const char* state_name);
const char* getCurrentText(void);
void clearCurrentText(void);
//Public Constants

//Public Variable
private:
//Private Variables
const char* currentText;
uint8_t textBoxNumber;
uint16_t fontColor;
uint8_t fontSize;
//Private Function Prototypes
};


#endif //End Header Guard
