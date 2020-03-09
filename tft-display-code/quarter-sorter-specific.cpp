//File Name: quarter-sorter-specific.c
//Description: This contains any misc. quarter-sorter implementations

//Include Files
#include "quarter-sorter-specific.h"
#include "selection-encoder.h"

//Private Constants

//Private Variables

//Public Constants

//Public Variables

//Private Function Prototypes

//Public Function Prototypes

//Private Function Definitions

//Public Function Definitions
namespace UI_API
{
void enableEncoder(uint16_t encA_pin, uint16_t encb_pin)
{
	EXTI->IMR |= encA_pin | encb_pin;
}
void disableEncoder(uint16_t encA_pin, uint16_t encb_pin)
{
	EXTI->IMR &= ~(encA_pin | encb_pin);
}
}//namespace UI_API

namespace GUI_API
{
void resetSelectionGUI(TFT_GFX& tftDisplay, TFT_TEXT_BOX& instructionBox, TFT_TEXT_BOX& mainTitle, TFT_TEXT_BOX& stateSelector, CHOSEN_STATE_TEXT_BOX chosenStates[NUM_BOXES],
		const uint16_t backgroundColor,const uint16_t fontColor,const uint16_t lineColor,const uint16_t lineThickness,const uint8_t stateSelectorFontSize,
		uint8_t& statesSelected, SELECTION_ENCODER* encoder_ptr)
{
	//Clear the chosen states
	for(uint8_t i = 0; i < NUM_BOXES; i++)
	{
		chosenStates[i].clearCurrentText();
	}
	encoder_ptr->setCurrentNameIndex(0);
	statesSelected = 0;
	drawSelectionLines(tftDisplay, backgroundColor, fontColor, lineColor, lineThickness);
	writeSelectionWords(instructionBox, mainTitle, stateSelector, fontColor, stateSelectorFontSize);
}

void drawSelectionLines(TFT_GFX& tftDisplay,const uint16_t backgroundColor,const uint16_t fontColor,const uint16_t lineColor,const uint16_t lineThickness)
{

	//for the love of god don't touch these plz

	//Set background to correct color and add outline
	tftDisplay.writeFillRect(0, 0, tftDisplay.width(), tftDisplay.height(), lineColor);
	tftDisplay.writeFillRect(lineThickness, lineThickness, tftDisplay.width() - lineThickness * 2, tftDisplay.height() - lineThickness * 2, backgroundColor);

	//Upper Left Border Box
	tftDisplay.writeFillRect(lineThickness, lineThickness, tftDisplay.width()/2, tftDisplay.height()/2, lineColor);
	tftDisplay.writeFillRect(lineThickness, lineThickness, tftDisplay.width()/2-lineThickness, tftDisplay.height()/2-lineThickness, backgroundColor);

	//Bottom Right Border Box
	tftDisplay.writeFillRect(tftDisplay.width()/2, tftDisplay.height()/2, tftDisplay.width(), tftDisplay.height(), lineColor);
	tftDisplay.writeFillRect(tftDisplay.width()/2+lineThickness, tftDisplay.height()/2+lineThickness, (tftDisplay.width() / 2 ) - (2 * lineThickness), (tftDisplay.height() / 2 ) - (2 * lineThickness), backgroundColor);




	//	for(uint16_t i = 1; i < NUM_BOXES; i++)
	//	{
	//	  tftDisplay.writeFillRect(0, tftDisplay.height()/2 + i*(tftDisplay.height()/(2 *NUM_BOXES)) - lineThickness/2, tftDisplay.width(), lineThickness, lineColor);
	//	}

	//Draw Segment Lines

	//	tftDisplay.writeFillRect(tftDisplay.width()/2, tftDisplay.height(), lineThickness, tftDisplay.height(), lineColor);
}

void writeSelectionWords(TFT_TEXT_BOX& instructionBox, TFT_TEXT_BOX& mainTitle, TFT_TEXT_BOX& stateSelector,const uint16_t fontColor,
		const uint8_t stateSelectorFontSize)
{
	instructionBox.write("*Hold OK button for 3 seconds to confirm selection.", fontColor, 1);
	mainTitle.write("State Selection: ", fontColor, 2);
	stateSelector.write(stateNames[0], fontColor, stateSelectorFontSize);
}

void printCurrentState(CHOSEN_STATE_TEXT_BOX chosenStates[NUM_BOXES], uint8_t& statesSelected,SELECTION_ENCODER* encoderPtr)
{
	//Stay at the last state box
	if(statesSelected == NUM_BOXES)
	{
		statesSelected--;
	}
	chosenStates[statesSelected++].printState(stateNames[encoderPtr->getCurrentNameIndex()]);
	encoderPtr->printNextAvailableState();
}

void clearCurrentState(CHOSEN_STATE_TEXT_BOX chosenStates[NUM_BOXES], uint8_t& statesSelected)
{
	if(statesSelected > 0)
	{
		chosenStates[--statesSelected].clear();
		chosenStates[statesSelected].clearCurrentText();
	}
}

void displayInProgress(TFT_GFX& tftDisplay, TFT_TEXT_BOX& instructionBox, const uint16_t lineThickness, const uint16_t lineColor, const uint16_t backgroundColor, const uint16_t fontColor)
{
	tftDisplay.writeFillRect(0, 0, tftDisplay.width(), tftDisplay.height(), lineColor);
	tftDisplay.writeFillRect(lineThickness, lineThickness, tftDisplay.width() - lineThickness * 2, tftDisplay.height() - lineThickness * 2, backgroundColor);
	TFT_TEXT_BOX statusBox{&tftDisplay,backgroundColor, lineThickness, (uint16_t)(tftDisplay.height()/3.0f),(int16_t)(tftDisplay.width() - lineThickness),true};
	statusBox.write("Scan in Progress!", fontColor, 4);
	instructionBox.write("*Press cancel to quit the current operation and go back to selecting states.", fontColor, 1);
}

void addConfirmQuit(TFT_GFX& tftDisplay, const uint16_t lineThickness,const uint16_t fontColor,const uint16_t backgroundColor)
{
	TFT_TEXT_BOX confirmQuit{&tftDisplay, backgroundColor, lineThickness + 8, (uint16_t)(3*tftDisplay.height()/5.0f),(int16_t)(tftDisplay.width() - lineThickness - 8), true};
	uint16_t bottomConfirmQuit = confirmQuit.write("*Are you sure you want to quit?*", fontColor, 2);
	TFT_TEXT_BOX confirmQuitInstructions{&tftDisplay, backgroundColor, lineThickness + 8, (uint16_t)(bottomConfirmQuit + 10),(int16_t)(tftDisplay.width() - lineThickness - 8), true};
	confirmQuitInstructions.write("Hold cancel for 3 seconds to confirm quit, tap to cancel.", fontColor, 1);
}

void removeConfirmQuit(TFT_GFX& tftDisplay, const uint16_t lineThickness, const uint16_t backgroundColor)
{
	uint16_t yVal = (uint16_t)(3*tftDisplay.height()/5.0f);
	tftDisplay.writeFillRect(lineThickness, yVal, tftDisplay.width() - (lineThickness * 2),tftDisplay.height() - lineThickness - yVal , backgroundColor);
}

}//namespace GUI_API

CHOSEN_STATE_TEXT_BOX::CHOSEN_STATE_TEXT_BOX(uint8_t text_box_number, uint16_t font_color,
		uint8_t font_size, const TFT_TEXT_BOX& general_text_box):
						TFT_TEXT_BOX(general_text_box),currentText{nullptr}, textBoxNumber{text_box_number}, fontColor{font_color}, fontSize{font_size}
						{}

						CHOSEN_STATE_TEXT_BOX::CHOSEN_STATE_TEXT_BOX(void):
						TFT_TEXT_BOX(),currentText{nullptr}, textBoxNumber{0}, fontColor{0}, fontSize{0}
						{}

						void CHOSEN_STATE_TEXT_BOX::printState(const char* state_name)
						{
							this->currentText = state_name;
							char outputString[STATE_MAX_CHARS + 3 + 1];
							sprintf(outputString, "%d: %s",this->textBoxNumber,state_name);
							this->write(outputString, this->fontColor, this->fontSize);
						}

						const char* CHOSEN_STATE_TEXT_BOX::getCurrentText(void)
						{
							return this->currentText;
						}

						void CHOSEN_STATE_TEXT_BOX::clearCurrentText(void)
						{
							this->currentText = nullptr;
						}
