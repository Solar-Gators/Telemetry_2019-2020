//File Name: selection-encoder.h
//Description: This implements the driver for a rotary encoder used for selecting the text to be displayed for the
//state text box.

//Header Guards
#ifndef SELECTION_ENCODER_H_
#define SELECTION_ENCODER_H_

//Include Files
#include "generic-rotary-encoder.h"
#include "text-box.h"
#include "quarter-sorter-specific.h"

//C Interface
#ifdef __cplusplus
extern "C" {
#endif
//C Public Constants

//C Public Variables

//C Public Function Prototypes


#ifdef __cplusplus
}
#endif //End C Interface

//C++ Interface
//Class Definitions
class SELECTION_ENCODER: public ROTARY_ENCODER
{
public:
//Constructors
/**
 * @brief This takes in the amount of ticks per step. Ticks are the smallest unit of turn for the rotary encoder. 
 * Steps are when something should occur. i.e. 2 ticks per step then on the second tick you might toggle an led.
 */
SELECTION_ENCODER(uint8_t ticks_per_step, TFT_TEXT_BOX* display_box,
		uint16_t font_color, uint8_t font_size, const char * const * output_text_array, uint16_t output_text_length,
		CHOSEN_STATE_TEXT_BOX* selected_states,uint8_t selected_states_length);
//Public Function Prototypes
uint16_t getCurrentNameIndex(void);
void setCurrentNameIndex(uint16_t index);
/**
 * @brief This should be used upon selecting a state to print the next available state in the main text box
 */
void printNextAvailableState(void);
//Public Constants

//Public Variable
private:
//Private Variables
TFT_TEXT_BOX* displayBox;
uint16_t fontColor;
uint8_t fontSize;
const char * const * outputTextArray;
uint16_t outputTextLength;
//Index to keep track of what state we are on
uint16_t nameIndex;
//Array of selected states so that we don't show any already selected states
CHOSEN_STATE_TEXT_BOX* selectedStates;
uint8_t numSelectedStates;
//Private Function Prototypes
void doStep(bool up_not_down) override;
/*
 * @brief This checks if @check_string is already being displayed in our selected_states.
 * @param check_string: The string to check
 * @retval Bool if already being displayed false otherwise.
 */
bool stringAlreadyPresent(const char* check_string);
};

#endif //End Header Guard
