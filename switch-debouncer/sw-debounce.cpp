//File Name: sw-debounce.cpp
//Description: This implements the functions for the state-text-box selection encoder

//Include Files
#include "sw-debounce.h"

//Private Constants

//Private Variables

//Public Constants

//Public Variables

//Private Function Prototypes

//Public Function Prototypes

//Private Function Definitions
inline void SW_DEBOUNCE::startCriticalSection(void)
{
	this->timerInstance->DIER &= ~TIM_DIER_UIE;
}
inline void SW_DEBOUNCE::stopCriticalSection(void)
{
	this->timerInstance->DIER |= TIM_DIER_UIE;
}
//Public Function Definitions
SW_DEBOUNCE::SW_DEBOUNCE(GPIO_TypeDef* gpio_port, uint16_t gpio_pin, uint32_t timer_period_ms, uint8_t ms_for_valid_press, TIM_TypeDef* timer_instance):
gpioPort{gpio_port}, gpioPin{gpio_pin}, debouncedState{SWITCH_STATE::NO_PRESS},
switchBitSequence{0xFF},stateMachineState{SW_STATE_MACHINE::SWITCH_OPEN}, validPressBitSequence{static_cast<uint8_t>(1 << static_cast<uint8_t>(ms_for_valid_press/timer_period_ms))},
msHeldCounter{0}, timerPeriodMs{timer_period_ms}, msForValidPress{ms_for_valid_press} , timerInstance{timer_instance}
{}

void SW_DEBOUNCE::process(void)
{
	this->switchBitSequence = (this->switchBitSequence << 1) | ((this->gpioPort->IDR & this->gpioPin) != 0);
	if(this->stateMachineState == SW_STATE_MACHINE::SWITCH_OPEN)
	{
		if((this->switchBitSequence & (this->validPressBitSequence | (this->validPressBitSequence - 1))) == this->validPressBitSequence)
		{
			this->stateMachineState = SW_STATE_MACHINE::VALID_PRESS_DETECTED;
			this->msHeldCounter = this->msForValidPress;
			//Reset the bit sequence to only count held time now
			this->switchBitSequence = 0;
		}
	//Make all the bits above valid_press_detected be don't cares
	}else if(this->stateMachineState == SW_STATE_MACHINE::VALID_PRESS_DETECTED)
	{
		//If the bit sequence is all 0's then the switch is being held closed
		if(!this->switchBitSequence)
		{
			this->msHeldCounter+= this->timerPeriodMs;
		}else{
			//If there is a 1 in the bit sequence than the switch was released
			this->stateMachineState = SW_STATE_MACHINE::SWITCH_RELEASED;
			//Check current ms to see what the state should be
			if(this->msHeldCounter >= static_cast<uint32_t>(SWITCH_STATE::THREE_SECOND_PRESS))
			{
				this->debouncedState = SWITCH_STATE::THREE_SECOND_PRESS;
			}else{
				this->debouncedState = SWITCH_STATE::SHORT_PRESS;
			}
			this->msHeldCounter = 0;
		}
	}else if(this->stateMachineState == SW_STATE_MACHINE::SWITCH_RELEASED)
	{
		if(this->switchBitSequence == SW_DEBOUNCE::SWITCH_OPEN_BIT_SEQUENCE)
		{
			this->stateMachineState = SW_STATE_MACHINE::SWITCH_OPEN;
		}
	}
}

SWITCH_STATE SW_DEBOUNCE::getCurrentState(void)
{
	this->startCriticalSection();
	SWITCH_STATE temp = this->debouncedState;
	this->debouncedState = SWITCH_STATE::NO_PRESS;
	this->stopCriticalSection();
	return temp;
}
