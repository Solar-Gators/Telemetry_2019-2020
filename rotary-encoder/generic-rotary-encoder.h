//File Name: generic-rotary-encoder.h
//Description: This implements the driver for a generic rotary encoder which is ABC

//Header Guards
#ifndef GENERIC_ROTARY_ENCODER_H_
#define GENERIC_ROTARY_ENCODER_H_

//Include Files
#include "main.h"

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
class ROTARY_ENCODER
{
public:
//Constructors
/**
 * @brief This takes in the amount of ticks per step. Ticks are the smallest unit of turn for the rotary encoder. 
 * Steps are when something should occur. i.e. 2 ticks per step then on the second tick you might toggle an led.
 */
ROTARY_ENCODER(uint8_t ticks_per_step);
//Public Function Prototypes
/**
 * @brief This does a tick of the rotary encoder
 * @param a_state: the pin value of input a, 1 or 0
 * @param b_state the pin value of input b, 1 or 0
 */
void process(uint8_t a_state, uint8_t b_state);
//Public Constants

//Public Variable
private:
//Private Variables
uint8_t ticksPerStep;
int16_t tickCounter;
uint8_t state;
//Private Function Prototypes
virtual void doStep(bool up_not_down) = 0;
};

#endif //End Header Guard
