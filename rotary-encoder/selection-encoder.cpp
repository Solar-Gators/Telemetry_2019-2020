//File Name: selection-encoder.cpp
//Description: This implements the functions for the state-text-box selection encoder

//Include Files
#include "selection-encoder.h"

//Private Constants

//Private Variables

//Public Constants

//Public Variables

//Private Function Prototypes
namespace
{
bool stringsEqual(const char* string1, const char* string2);
}

//Public Function Prototypes

//Private Function Definitions
namespace
{
bool stringsEqual(const char* string1, const char* string2)
{
	if(string1 == nullptr || string2 == nullptr)
	{
		return false;
	}
	while(*string1 != '\0' && *string2 != '\0' && *(string1) == *(string2))
	{
		string1++;
		string2++;
	}
	return (*string1 == *string2);
}

}

//Public Function Definitions
SELECTION_ENCODER::SELECTION_ENCODER(uint8_t ticks_per_step, TFT_TEXT_BOX* display_box,
		uint16_t font_color, uint8_t font_size, const char * const * output_text_array, uint16_t output_text_length,
		CHOSEN_STATE_TEXT_BOX* selected_states,uint8_t selected_states_length):
ROTARY_ENCODER(ticks_per_step), displayBox{display_box}, fontColor{font_color},
fontSize{font_size}, outputTextArray{output_text_array}, outputTextLength{output_text_length}, nameIndex{0},
selectedStates{selected_states}, numSelectedStates{selected_states_length}
{}

uint16_t SELECTION_ENCODER::getCurrentNameIndex(void)
{
	return this->nameIndex;
}

void SELECTION_ENCODER::setCurrentNameIndex(uint16_t index)
{
	this->nameIndex = index;
}

void SELECTION_ENCODER::printNextAvailableState(void)
{
	this->doStep(true);
}

bool SELECTION_ENCODER::stringAlreadyPresent(const char* check_string)
{
	for(uint8_t i = 0; i < this->numSelectedStates; i++)
	{
		if(stringsEqual(this->selectedStates[i].getCurrentText(), check_string))
		{
			return true;
		}
	}
	return false;
}

void SELECTION_ENCODER::doStep(bool up_not_down)
{
	bool validIndex = false;
	while(!validIndex)
	{
		if(up_not_down)
		{
			if(this->nameIndex == (this->outputTextLength - 1))
			{
				this->nameIndex = 0;
			}else{
				this->nameIndex++;
			}
		}else{
			if(this->nameIndex == 0)
			{
				this->nameIndex = this->outputTextLength - 1;
			}else{
				this->nameIndex--;
			}
		}
		validIndex = !this->stringAlreadyPresent(this->outputTextArray[this->nameIndex]);
	}
	displayBox->write(this->outputTextArray[this->nameIndex], this->fontColor, this->fontSize);
}
