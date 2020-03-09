//File Name: generic-rotary-encoder.cpp
//Description: This defines the base functions for the generic rotary encoder ABC

//Include Files
#include "generic-rotary-encoder.h"

//Private Constants

//Private Variables
// Use the full-step state table (emits a code at 00 only)
#define DIR_CW 0x10
#define DIR_CCW 0x20

#define R_START 0x0
#define R_CW_FINAL 0x1
#define R_CW_BEGIN 0x2
#define R_CW_NEXT 0x3
#define R_CCW_BEGIN 0x4
#define R_CCW_FINAL 0x5
#define R_CCW_NEXT 0x6

static const uint8_t ttable[7][4] = {
  // R_START
  {R_START,    R_CW_BEGIN,  R_CCW_BEGIN, R_START},
  // R_CW_FINAL
  {R_CW_NEXT,  R_START,     R_CW_FINAL,  R_START | DIR_CW},
  // R_CW_BEGIN
  {R_CW_NEXT,  R_CW_BEGIN,  R_START,     R_START},
  // R_CW_NEXT
  {R_CW_NEXT,  R_CW_BEGIN,  R_CW_FINAL,  R_START},
  // R_CCW_BEGIN
  {R_CCW_NEXT, R_START,     R_CCW_BEGIN, R_START},
  // R_CCW_FINAL
  {R_CCW_NEXT, R_CCW_FINAL, R_START,     R_START | DIR_CCW},
  // R_CCW_NEXT
  {R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START},
};

//Public Constants

//Public Variables

//Private Function Prototypes

//Public Function Prototypes

//Private Function Definitions

//Public Function Definitions
ROTARY_ENCODER::ROTARY_ENCODER(uint8_t ticks_per_step):
ticksPerStep{ticks_per_step}, tickCounter{0}, state{R_START}
{}

void ROTARY_ENCODER::process(uint8_t a_state, uint8_t b_state)
{
	state = ttable[state & 0xF][((a_state & 0x1) << 1) | (b_state & 0x1)];
	if(state & (DIR_CCW | DIR_CW))
	{
	    if(state & DIR_CW)
	    {
	    	//Reset tick counter if we were in the middle of turning it one way and we start turning it the other way
	    	if(this->tickCounter < 0)
	    	{
	    		this->tickCounter = 0;
	    	}
	        this->tickCounter++;
	    }else{
	    	//Reset tick counter if we were in the middle of turning it one way and we start turning it the other way
	    	if(this->tickCounter > 0)
	    	{
	    		this->tickCounter = 0;
	    	}
	        this->tickCounter--;
	    }

	    uint16_t tempCounter = (this->tickCounter < 0) ? this->tickCounter * -1 : this->tickCounter;
	    if(tempCounter >= this->ticksPerStep)
	    {
	    	this->doStep(state & DIR_CW);
	    	this->tickCounter = 0;
	    }
	}
}
