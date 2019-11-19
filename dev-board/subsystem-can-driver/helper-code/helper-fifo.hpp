//File Name: helper-fifo.hpp
//Description: This is a module for a fifo

//Header Guards
#ifndef HELPER_FIFO_H_
#define HELPER_FIFO_H_

//Include Files
#include "stdint.h" //REMOVE THIS
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
/**
 * @brief T is the data type of the fifo and DEPTH is the depth of the fifo
 */
template <class T,uint16_t DEPTH, uint16_t SIZE>
class HELPER_FIFO
{
public:
    //Constructors
    HELPER_FIFO():
    headIndex{0}, tailIndex{0}, emptyNotFull{true}
    {}
    //Public Function Definitions
    bool IsEmpty()
    {
        return (headIndex == tailIndex ? emptyNotFull : false);
    }
    bool IsFull()
    {
        return (headIndex == tailIndex ? !emptyNotFull : false);
    }

    void PushBack(T* const next_element, bool* success)
    {
        if(tailIndex == headIndex && !emptyNotFull)
        {
            //Fail to write since we are full
            if(success)
            {
                *success = false;
            }
        }else
        {
            if(success)
            {
                *success = true;
            }
            copyArrayData(headIndex,next_element);
            headIndex = (headIndex + 1)%DEPTH;
            //If head caught up to tail then we are full
            if(headIndex == tailIndex)
            {
                emptyNotFull = false;
            }
        }
    }
    T* PopFront(bool* success)
    {
    	 uint16_t prevTailIndex = 0;
        if(tailIndex == headIndex && emptyNotFull)
        {
            //Fail to read since we are empty
            if(success)
            {
                *success = false;
            }
        }else
        {
            if(success)
            {
                *success = true;
            }
            prevTailIndex = tailIndex;
            tailIndex = (tailIndex + 1)%DEPTH;
            //If tail caught up to head then we are empty
            if(tailIndex == headIndex)
            {
                emptyNotFull = true;
            }
        }
        return fifoData[prevTailIndex];
    }
    //Public Constants

    //Public Variable
private:
    //Private Variables
    T fifoData[DEPTH][SIZE];

    uint16_t headIndex;
    uint16_t tailIndex;

    bool emptyNotFull;
    //Private Function Definitions
    void copyArrayData(uint16_t index, T* const dataToCopyFrom)
    {
        for(uint16_t i = 0; i < SIZE; i++)
        {
            this->fifoData[index][i] = dataToCopyFrom[i];
        }
    }
};

#endif //End Header Guard
