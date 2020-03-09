//File Name: sw-debounce.h
//Description: This implements the generic debouncing for a switch

//Header Guards
#ifndef SW_DEBOUNCE_H_
#define SW_DEBOUNCE_H_

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
enum struct SWITCH_STATE
{
	NO_PRESS,
	SHORT_PRESS,
	THREE_SECOND_PRESS = 3000,
};
//Class Definitions
class SW_DEBOUNCE
{
public:
//Constructors
/**
 * @brief This takes in the initialized-as-input gpio pin
 * @param gpio_port: port of switch
 * @param gpio_pin: pin of switch
 * @param timer_period_ms: The amount of time between timer interrupts in ms at which @process should be called.
 * @param ms_for_valid_press: This should be a multiple of @timer_period_ms and (1 << MS_FOR_VALID_PRESS/timer_period_ms)
 * @param timer_instance: This should be the instance of the timer that interrupts @timer_period_ms. You should start the timer after all debounce switches
 * are constructed.
 */
SW_DEBOUNCE(GPIO_TypeDef* gpio_port, uint16_t gpio_pin, uint32_t timer_period_ms, uint8_t ms_for_valid_press, TIM_TypeDef* timer_instance);
//Public Function Prototypes
/**
 * @brief This should be called once every @timer_period_ms milliseconds.
 */
void process(void);
/**
 * @brief This gets the current debounced state of the switch
 * @retval the debounced state of the switch
 */
SWITCH_STATE getCurrentState(void);
//Public Constants
//Public Variable
private:
enum struct SW_STATE_MACHINE
{
	SWITCH_OPEN,
	VALID_PRESS_DETECTED,
	SWITCH_RELEASED
};
//Private Constants
static constexpr uint8_t SWITCH_OPEN_BIT_SEQUENCE = 0xFF;
//Private Variables
GPIO_TypeDef* gpioPort;
uint16_t gpioPin;
SWITCH_STATE debouncedState;
/**
 * @brief This stores the last 8 values of the switch value
 */
uint8_t switchBitSequence;
SW_STATE_MACHINE stateMachineState;
const uint8_t validPressBitSequence;
/**
 * @brief This is how many ms's the button has been held
 */
uint32_t msHeldCounter;
const uint32_t timerPeriodMs;
const uint8_t msForValidPress;
TIM_TypeDef* timerInstance;
//Private Function Prototypes
inline void startCriticalSection(void);
inline void stopCriticalSection(void);
};

#endif //End Header Guard
