//File Name: subsystem-data-module.cpp
//Description: This implements the functionality shared amongst all subsystems for data storage

//Include Files
#include "subsystem-data-module.hpp"

//Private Constants

//Private Variables
 RX_BINARY_TREE SUBSYSTEM_DATA_MODULE::rxModulesTree{};
 CAN_HandleTypeDef* SUBSYSTEM_DATA_MODULE::hcan{nullptr};
//Public Constants

//Public Variables

//Private Function Prototypes

//Special Functions
/**
 * @brief This function is called when a rx msg is pending in can rx fifo 0
 * @param hcan: pointer to can handle
 * @important HAL_CAN_IRQHandler must be called in the CAN isr for this to be called
 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	//Get all pending messages in fifo 0 in case there is more than one
	while(HAL_CAN_GetRxFifoFillLevel(hcan, SUBSYSTEM_DATA_MODULE::CAN_RX_FIFO_NUMBER))
	{
		//Read message
		CAN_RxHeaderTypeDef pHeader;
		uint8_t aData[SUBSYSTEM_DATA_MODULE::ARRAY_SIZE];
		HAL_CAN_GetRxMessage(hcan, SUBSYSTEM_DATA_MODULE::CAN_RX_FIFO_NUMBER, &pHeader, aData);

		//Get pointer to receiving data module
		SUBSYSTEM_DATA_MODULE* receivingNode =
				SUBSYSTEM_DATA_MODULE::FindReceivingModule((pHeader.IDE == CAN_ID_STD ? pHeader.StdId : pHeader.ExtId));
		if(receivingNode != nullptr)
		{
			//Verify that the received header matches the receiving node in terms of dlc
			if(receivingNode->dataLength == pHeader.DLC)
			{
				//Store data into receive fifo
				receivingNode->addToFifo(aData);
				//Call receive callback (if it exists)
				receivingNode->CallReceiveCallback();
			}
		}
	}
}

//Private Function Definitions

//Protected Function Definitions
SUBSYSTEM_DATA_MODULE::SUBSYSTEM_DATA_MODULE(uint32_t message_id, uint8_t data_length, bool is_ext_id):
messageIdentifier{message_id}, dataLength{data_length}, isExtID{is_ext_id}, storageFifo{}, rxFuncPtr{nullptr}, isReceiving{false}
{}
//Public Function Definitions
SUBSYSTEM_DATA_MODULE* SUBSYSTEM_DATA_MODULE::FindReceivingModule(uint32_t message_id)
{
	return SUBSYSTEM_DATA_MODULE::rxModulesTree.FindElement(message_id);
}

void SUBSYSTEM_DATA_MODULE::SetupReceive(subsystemReceiveCallback rx_func_ptr)
{
    this->rxFuncPtr = rx_func_ptr;
    //Add node to receive tree if not already receiving
    if(!isReceiving)
    {
        SUBSYSTEM_DATA_MODULE::rxModulesTree.AddNode(this);
        isReceiving = true;
    } 
}

void SUBSYSTEM_DATA_MODULE::SendData(void)
{
    fillTransmitBuffer();
    sendTransmitBufferData();
}

void SUBSYSTEM_DATA_MODULE::CallReceiveCallback(void)
{
    if(this->rxFuncPtr != nullptr)
    {
        this->rxFuncPtr(this);
    }
}

void SUBSYSTEM_DATA_MODULE::StartCAN(CAN_HandleTypeDef* in_hcan)
{
	hcan = in_hcan;
	//Initialize CAN itself
	hcan->Instance = CAN;
	hcan->Init.Prescaler = 16;
	hcan->Init.Mode = CAN_MODE_NORMAL;
	hcan->Init.SyncJumpWidth = CAN_SJW_1TQ;
	hcan->Init.TimeSeg1 = CAN_BS1_1TQ;
	hcan->Init.TimeSeg2 = CAN_BS2_1TQ;
	hcan->Init.TimeTriggeredMode = DISABLE;
	hcan->Init.AutoBusOff = DISABLE;
	hcan->Init.AutoWakeUp = DISABLE;
	hcan->Init.AutoRetransmission = DISABLE;
	hcan->Init.ReceiveFifoLocked = DISABLE;
	hcan->Init.TransmitFifoPriority = DISABLE;
	if (HAL_CAN_Init(hcan) != HAL_OK)
	{
	Error_Handler();
	}

	//Initialize a hardware filter that passes everything
	CAN_FilterTypeDef sFilterConfig;
	sFilterConfig.FilterActivation = CAN_FILTER_ENABLE; /*Enable the filter*/
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK; /*Mask mode*/
	sFilterConfig.FilterMaskIdHigh = 0;
	sFilterConfig.FilterMaskIdLow = 0; /*Accept everything*/
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT; /*One 32-bit filter*/
	sFilterConfig.FilterBank = 0; /*Init bank 0*/
	sFilterConfig.FilterFIFOAssignment = 0; /*Assign to FIFO 0*/
	HAL_CAN_ConfigFilter(hcan, &sFilterConfig);

    //Set Up CAN interrupt receive callback
	HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);

	//Start the CAN bus
	HAL_CAN_Start(hcan);
}

void SUBSYSTEM_DATA_MODULE::sendTransmitBufferData(void)
{
	//Only continue if hcan has been initialized
	if(hcan != nullptr)
	{
		//Spinlock until a tx mailbox is empty
		while(!HAL_CAN_GetTxMailboxesFreeLevel(hcan));

		//Initialize Header
		uint32_t pTxMailbox;
		CAN_TxHeaderTypeDef pHeader;
		pHeader.RTR = CAN_RTR_DATA;
		pHeader.DLC = this->dataLength;
		if(this->isExtID)
		{
			pHeader.ExtId = this->messageIdentifier;
			pHeader.IDE = CAN_ID_EXT;
		}else
		{
			pHeader.StdId = this->messageIdentifier;
			pHeader.IDE = CAN_ID_STD;
		}
		//Put CAN message in tx mailbox
		HAL_CAN_AddTxMessage(hcan, &pHeader, this->transmitBuffer, &pTxMailbox);
	}
}

bool SUBSYSTEM_DATA_MODULE::isFifoEmpty(void)
{
    return this->storageFifo.IsEmpty();
}

bool SUBSYSTEM_DATA_MODULE::isFifoFull(void)
{
    return this->storageFifo.IsFull();
}

bool SUBSYSTEM_DATA_MODULE::addToFifo(uint8_t* incoming_data)
{
    bool operationSucceeded;
    this->storageFifo.PushBack(incoming_data, &operationSucceeded);
    return operationSucceeded;
}
