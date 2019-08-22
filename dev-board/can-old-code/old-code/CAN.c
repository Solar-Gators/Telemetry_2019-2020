#include "stm32f0xx.h"    
#include "CAN.h"


/**********SYSTEM GLOBAL STORAGE VARIABLES**************/
//STEPS TO ADD NEW VARIABLES
//1. Add the variable into one of the structs that already exists or create a new struct
//   for a new subsystem.
//2. If new subsystem then create a new volatile definition for the struct under
//	 SYSTEM VARIABLE DEFINITIONS
//3. Update the Storage_Packet_Init function to make sure the data_valid is initialized to
//   0 for any new data being created and update the num bytes
//4. If numbytes is greater than *2* then make sure to go to CAN.h and update the maxDataSize
//   define to the new max data size and change the number in asteriks in this step to
//   reflect that.
//5. Update the transfer to storage function
//6. Create a get(your variable name) function in this file and add it in the CAN.h file to the proper subsystem
/*****************SYSTEM VARIABLES STRUCTS*****************/
struct MPPT0_VARS
{
	StoragePacket ARRAY_VOLTAGE;
	StoragePacket ARRAY_CURRENT;
	StoragePacket BATTERY_VOLTAGE;
	StoragePacket TEMPERATURE_MPPT;
};
struct BMS0_VARS
{
	StoragePacket PACK_CURRENT;
	StoragePacket PACK_VOLTAGE;
	StoragePacket PACK_SOC;
	StoragePacket RELAY_STATE;
	StoragePacket CRC_CHECKSUM;
};
struct SPEED0_VARS
{
	StoragePacket CAR_SPEED;
};
struct TEST_VARS
{
	StoragePacket TEST_VOLTAGE;
	StoragePacket TEST_CURRENT;
	StoragePacket TEST_EFFICIENCY;
};
/***************SYSTEM VARIABLES DEFINITIONS***********/
static volatile struct MPPT0_VARS MPPT0vars;
static volatile struct BMS0_VARS BMS0vars;
static volatile struct SPEED0_VARS SPEED0vars;
static volatile struct TEST_VARS TEST0vars; 

static void Storage_Packet_Init(void)
{
	/**************MPPT**************/
	MPPT0vars.ARRAY_VOLTAGE.data_valid = 0;
	MPPT0vars.ARRAY_CURRENT.data_valid = 0;
	MPPT0vars.BATTERY_VOLTAGE.data_valid = 0;
	MPPT0vars.TEMPERATURE_MPPT.data_valid = 0;
	
	MPPT0vars.ARRAY_VOLTAGE.num_bytes = 2;
	MPPT0vars.ARRAY_CURRENT.num_bytes = 2;
	MPPT0vars.BATTERY_VOLTAGE.num_bytes = 2;
	MPPT0vars.TEMPERATURE_MPPT.num_bytes = 2;
	/************BMS***************/
	BMS0vars.PACK_CURRENT.data_valid = 0;
	BMS0vars.PACK_VOLTAGE.data_valid = 0;
	BMS0vars.PACK_SOC.data_valid = 0;
	BMS0vars.RELAY_STATE.data_valid = 0;
	BMS0vars.CRC_CHECKSUM.data_valid = 0;
	
	BMS0vars.PACK_CURRENT.num_bytes = 2; //This is unsigned
	BMS0vars.PACK_VOLTAGE.num_bytes = 2;
	BMS0vars.PACK_SOC.num_bytes = 1;
	BMS0vars.RELAY_STATE.num_bytes = 2;
	BMS0vars.CRC_CHECKSUM.num_bytes = 1;
	/************SPEED*************/
	SPEED0vars.CAR_SPEED.data_valid = 0;
	
	SPEED0vars.CAR_SPEED.num_bytes = 2;
	/************TEST*************/
	TEST0vars.TEST_VOLTAGE.data_valid = 0;
	TEST0vars.TEST_CURRENT.data_valid = 0;
	TEST0vars.TEST_EFFICIENCY.data_valid = 0;
	
	TEST0vars.TEST_VOLTAGE.num_bytes = 2;
	TEST0vars.TEST_CURRENT.num_bytes = 2;
	TEST0vars.TEST_EFFICIENCY.num_bytes = 2;
}


/************Static Function Prototypes***********/

//This demasks the CAN messages and places the correct data into the correct storage packet
static void Transfer_To_Storage(MSGID identifier, uint8_t* data);
//This is to send data on the CAN bus
static void CAN_Transmit(TransmitPacket newMessage);
// function for transmitting an RTR message
static void CAN_Transmit_RTR(TransmitPacket newMessage);



/************Function Definitions************/
		
static void Transfer_To_Storage(MSGID identifier, uint8_t* data)
{
	if(identifier == MPPT0_MSGID)
	{
		MPPT0vars.ARRAY_VOLTAGE.data[0] = data[0];
		MPPT0vars.ARRAY_VOLTAGE.data[1] = data[1];
		MPPT0vars.ARRAY_VOLTAGE.data_valid = 1;
		MPPT0vars.ARRAY_CURRENT.data[0] = data[2];
		MPPT0vars.ARRAY_CURRENT.data[1] = data[3];
		MPPT0vars.ARRAY_CURRENT.data_valid = 1;
		MPPT0vars.BATTERY_VOLTAGE.data[0] = data[4];
		MPPT0vars.BATTERY_VOLTAGE.data[1] = data[5];
		MPPT0vars.BATTERY_VOLTAGE.data_valid = 1;
		MPPT0vars.TEMPERATURE_MPPT.data[0] = data[6];
		MPPT0vars.TEMPERATURE_MPPT.data[1] = data[7];
		MPPT0vars.TEMPERATURE_MPPT.data_valid = 1;
	}else if(identifier == BMS0_MSGID)
	{
		BMS0vars.PACK_CURRENT.data[0] = data[0];
		BMS0vars.PACK_CURRENT.data[1] = data[1];
		BMS0vars.PACK_CURRENT.data_valid = 1;
		BMS0vars.PACK_VOLTAGE.data[0] = data[2];
		BMS0vars.PACK_VOLTAGE.data[1] = data[3];
		BMS0vars.PACK_VOLTAGE.data_valid = 1;
		BMS0vars.PACK_SOC.data[0] = data[4];
		BMS0vars.PACK_SOC.data_valid = 1;
		BMS0vars.RELAY_STATE.data[0] = data[5];
		BMS0vars.RELAY_STATE.data[1] = data[6];
		BMS0vars.RELAY_STATE.data_valid = 1;
		BMS0vars.CRC_CHECKSUM.data[0] = data[7];
		BMS0vars.CRC_CHECKSUM.data_valid = 1;
	}else if(identifier == SPEED_MSGID)
	{
		SPEED0vars.CAR_SPEED.data[0] = data[0];
		SPEED0vars.CAR_SPEED.data[1] = data[1];
		SPEED0vars.CAR_SPEED.data_valid = 1;
	}else if(identifier == TEST_MSGID)
	{
		TEST0vars.TEST_VOLTAGE.data[0] = data[0];
		TEST0vars.TEST_VOLTAGE.data[1] = data[1];
		TEST0vars.TEST_VOLTAGE.data_valid = 1;
		TEST0vars.TEST_CURRENT.data[0] = data[2];
		TEST0vars.TEST_CURRENT.data[1] = data[3];
		TEST0vars.TEST_CURRENT.data_valid = 1;
		TEST0vars.TEST_EFFICIENCY.data[0] = data[4];
		TEST0vars.TEST_EFFICIENCY.data[1] = data[5];
		TEST0vars.TEST_EFFICIENCY.data_valid = 1;
	}
}

void CAN_Setup(void)
{
	//Clock for CAN setup
	RCC->APB1ENR |= RCC_APB1ENR_CANEN;
	//GPIO setup for CAN Tx and Rx
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; //Enable the GPIOB clock
	GPIOB->AFR[1] |= (0b0100 << GPIO_AFRH_AFSEL8_Pos) | (0b0100 << GPIO_AFRH_AFSEL9_Pos); //Set PB8 and PB9 to AF4 for CAN
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_8 | GPIO_OTYPER_OT_9); //Set PB8 and PB9 to push pull
	GPIOB->OSPEEDR |= (0b01 << GPIO_OSPEEDR_OSPEEDR8_Pos) | (0b01 << GPIO_OSPEEDR_OSPEEDR9_Pos); //Set PB8 and PB9 to medium speed
	GPIOB->MODER |= (0b10 << GPIO_MODER_MODER8_Pos) | (0b10 << GPIO_MODER_MODER9_Pos); //Set PB8 and PB9 to alternate function mode
	//Initialize our data structure
	Storage_Packet_Init();
	//General CAN setup
	CAN->MCR |= CAN_MCR_RESET; //Master reset
	while((CAN->MSR & CAN_MSR_SLAK) != CAN_MSR_SLAK); //Wait til we enter sleep mode
	CAN->MCR |= CAN_MCR_INRQ; //Initialization mode
	while((CAN->MSR & CAN_MSR_INAK) != CAN_MSR_INAK); //Wait til we enter initialization mode
	CAN->MCR &= ~CAN_MCR_SLEEP;
	while((CAN->MSR & CAN_MSR_SLAK) == CAN_MSR_SLAK); //Wait til we exit sleep mode
	CAN->BTR |= 0x001C0003; //This sets the bit rate to 125kbits/s and segment 1 to 13 tq, segment 2 to 2 tq and the sync_seg to 1 tq.
	#ifdef DEBUG
	//CAN->BTR |= CAN_BTR_LBKM; //Enable loop back mode
	//CAN->MCR |= CAN_MCR_NART | CAN_MCR_ABOM; //Enable no automatic retransmission and automatic bus-off management
	#endif
	CAN->IER |= CAN_IER_FMPIE0 | CAN_IER_FMPIE1; //Enable interrupts	
	
	
	#if defined(MPPT_DEF) 
	
	#elif defined(BMS_DEF)
	
	#elif defined(SPEED_DEF)	
	
	#elif defined(RF_DEF)
	//Filter Setup
	CAN->FMR |= CAN_FMR_FINIT; //Enter filter initialization mode
	CAN->FA1R = 0; //Disable all filters
	CAN->FM1R &= ~(CAN_FM1R_FBM0 | CAN_FM1R_FBM1); //This sets which of the 14 filter banks are are in identifier mask mode
	CAN->FS1R &= ~(CAN_FS1R_FSC0 | CAN_FS1R_FSC1); //Clear the bits of the filters we are using to set them into 16 -bit mode for more filters
	CAN->FFA1R |= ((0x0 << 0) | (0x1 << 1)); //Choose which mailbox the filter will route to
	//We are using 16 bit filters, so the we need to set half of FR1 and FR2 to the identifier we want
	 //Here we set the identifier that we want to allow, the array goes from 0 to 28 but that seems wrong
	CAN->sFilterRegister[0].FR1 = ((MPPT0_MSGID << 5)) | (0xFF70U << 16); //Only mask the identifier
	CAN->sFilterRegister[0].FR2 = ((BMS0_MSGID << 5)) | (0xFF70U << 16); //Only mask the identifier
	CAN->sFilterRegister[1].FR1 = ((SPEED_MSGID << 5)) | (0xFF70U << 16); //Only mask the identifier
	CAN->sFilterRegister[1].FR2 = ((TEST_MSGID << 5)) | (0xFF70U << 16); //Only mask the identifier
	CAN->FA1R |= (CAN_FA1R_FACT0 | CAN_FA1R_FACT1); //Enable the filters we want
	CAN->FMR &= ~CAN_FMR_FINIT; //Exit filter initialization mode
	//Interrupt stuff
	EXTI->IMR |= EXTI_IMR_IM27; //This unmasks the CAN interrupts
	NVIC_SetPriority(CEC_CAN_IRQn,1); //This sets the priority for CAN interrupts 0 is highest priority 3 is lowest
	NVIC_EnableIRQ(CEC_CAN_IRQn); //This enables the can interrupt
	#endif
	
	//More General CAN setup
	CAN->MCR &= ~CAN_MCR_INRQ; //Exit initialization mode
	while((CAN->MSR & CAN_MSR_INAK) == CAN_MSR_INAK); //Wait til we exit initialization mode
}

static void CAN_Transmit(TransmitPacket newMessage)
{
	//This is for transmission, the array is for elements 0-2
	uint8_t n, all_full = 1;
	//find an empty mailbox
	while(all_full == 1){
		if ((CAN->TSR & CAN_TSR_TME0) == CAN_TSR_TME0) {
			n = 0; //mailbox 0 is empty
			all_full = 0;
		}else if ((CAN->TSR & CAN_TSR_TME1) == CAN_TSR_TME1) {
			n = 1; //mailbox 1 is empty
			all_full = 0;
		}else if ((CAN->TSR & CAN_TSR_TME2) == CAN_TSR_TME2) {
			n = 2; //mailbox 2 is empty
			all_full = 0;
		}
	}
	//Zero the TDLR and TDHR registers
	CAN->sTxMailBox[n].TDLR = 0;
	CAN->sTxMailBox[n].TDHR = 0;
	CAN->sTxMailBox[n].TDTR = newMessage.num_bytes & 0xF;//Here we set the DLC for the # of bytes
	
	//load data registers
	for (int i = 0; i < newMessage.num_bytes; i++) {
		if (i <= 3){
			CAN->sTxMailBox[n].TDLR |= (newMessage.data[i] << 8*i);//Byte 3-0 of the message, byte 0 comes first
		}else {		
			CAN->sTxMailBox[n].TDHR |= (newMessage.data[i] << 8*(i-4));//Byte 7-4 of the message
		}
	}
	
	//Here is where we set the identifier and transmission request.
	//mailbox n is ready to transmit
	CAN->sTxMailBox[n].TIR = 0;
	CAN->sTxMailBox[n].TIR |= ((uint32_t)newMessage.message_identifier << 21) | CAN_TI0R_TXRQ;
}
// function for transmitting an RTR message
static void CAN_Transmit_RTR(TransmitPacket newMessage)
{
	//This is for transmission, the array is for elements 0-2
	uint8_t n, all_full = 1;
	//find an empty mailbox
	while(all_full == 1){
		if ((CAN->TSR & CAN_TSR_TME0) == CAN_TSR_TME0) {
			n = 0; //mailbox 0 is empty
			all_full = 0;
		}else if ((CAN->TSR & CAN_TSR_TME1) == CAN_TSR_TME1) {
			n = 1; //mailbox 1 is empty
			all_full = 0;
		}else if ((CAN->TSR & CAN_TSR_TME2) == CAN_TSR_TME2) {
			n = 2; //mailbox 2 is empty
			all_full = 0;
		}
	}
	//Zero the TDLR and TDHR registers
	CAN->sTxMailBox[n].TDLR = 0;
	CAN->sTxMailBox[n].TDHR = 0;
	CAN->sTxMailBox[n].TDTR = newMessage.num_bytes & 0xF;//Here we set the DLC for the # of bytes
		
	//Here is where we set the identifier and transmission request.
	//mailbox n is ready to transmit
	CAN->sTxMailBox[n].TIR = 0;
	CAN->sTxMailBox[n].TIR |= ((uint32_t)newMessage.message_identifier << 21) | CAN_TI0R_RTR | CAN_TI0R_TXRQ;
}


void CEC_CAN_IRQHandler(void)
{
	GPIOA->ODR ^= GPIO_ODR_5;
	//These variables are for data storage 
	uint8_t CAN_numBytes[2];
	uint8_t CAN_data[2][8];
	MSGID CAN_identifier[2];
	Mailbox CAN_validMailbox = NONE; //Default if no message was received
	
	//These if statements determine which mailbox received a message, or if both
	uint8_t mailboxnum;
	int	x = 0;
	//Essentially mailboxnum: which mailbox? , x: one or both?
	if ((CAN->RF0R & CAN_RF0R_FMP0) > 0) {
		mailboxnum = 0; 	// Mailbox 0 is used
		CAN_validMailbox = mailbox0;
	}
	if ((CAN->RF1R & CAN_RF1R_FMP1) > 0) {
		mailboxnum = 1;		// Mailbox 1 is used
		//In case of both, mailboxnum = 1 entering the for loop
		CAN_validMailbox = mailbox1;
	}
	// Check if both (x = 0 by default)
	if (((CAN->RF0R & CAN_RF0R_FMP0) > 0)&&((CAN->RF1R & CAN_RF1R_FMP1) > 0)) {
		x = 1; // Increase x to 1 to make the following for loop run twice in order to service each mailbox
		CAN_validMailbox = mailbox0_and_1;
	}	
	
	// Next loop to handle message(s) 
	// When x = 0, only one mailbox is serviced; when x = 1, both are serviced
	// If x = 1, mailboxnum = 1, so at the end of the loop mailboxnum is dec to = 0 for next iteration
	// In case of both, 1 is serviced first, then 0 on second iteration
	
	for (; x >= 0; x--) {
		
		CAN_identifier[mailboxnum] = (CAN->sFIFOMailBox[mailboxnum].RIR & CAN_RI0R_STID) >> CAN_RI0R_STID_Pos; //This sets the identifier
		
		uint32_t dlcControlReg = CAN->sFIFOMailBox[mailboxnum].RDTR;	// store entire DLC control register 
		CAN_numBytes[mailboxnum] = dlcControlReg & CAN_RDT0R_DLC; // then extract number of bytes of data to receive		
	 
		// loop stores each byte of data necessary into intermediate array "databytes" then distributes appropriately
		for (int i = 0;i < CAN_numBytes[mailboxnum]; i++) {
			if (i < 4) {
				// 0 <= i <= 3 means pull from Low Data Receive reg
				CAN_data[mailboxnum][i] = (CAN->sFIFOMailBox[mailboxnum].RDLR & (0xFFU << i*8)) >> i*8 ;
			}	else {			
				// 4 <= i <= 7 means pull from High Data Receive reg
				CAN_data[mailboxnum][i] = (CAN->sFIFOMailBox[mailboxnum].RDHR & (0xFFU << (i-4)*8)) >> (i-4)*8 ;
			}
		}	
		mailboxnum--; // if loop needs to run twice this is set to 0 so mailbox zero can be serviced next
	}
	
	//Here we store the data we received into its appropriate storage block
	if(CAN_validMailbox == mailbox0)
	{
		Transfer_To_Storage(CAN_identifier[0], CAN_data[0]);
		CAN->RF0R = CAN_RF0R_RFOM0 | CAN_RF0R_FOVR0 | CAN_RF0R_FULL0; //Release the mailbox 0 and don't clear the other flags
	}else if(CAN_validMailbox == mailbox1)
	{
		Transfer_To_Storage(CAN_identifier[1], CAN_data[1]);
		CAN->RF1R = CAN_RF1R_RFOM1 | CAN_RF1R_FOVR1 | CAN_RF1R_FULL1; //Release the mailbox 1 and don't clear the other flags
	}else if(CAN_validMailbox == mailbox0_and_1)
	{
		Transfer_To_Storage(CAN_identifier[0], CAN_data[0]);
		CAN->RF0R = CAN_RF0R_RFOM0 | CAN_RF0R_FOVR0 | CAN_RF0R_FULL0; //Release the mailbox 0 and don't clear the other flags
		Transfer_To_Storage(CAN_identifier[1], CAN_data[1]);
		CAN->RF1R = CAN_RF1R_RFOM1 | CAN_RF1R_FOVR1 | CAN_RF1R_FULL1; //Release the mailbox 1 and don't clear the other flags
	}
}
// function for sending an RTR message to the Photon MPPT:
void Send_RTRtoMPPT (void){
	// define packet
	TransmitPacket RTRmessage;
	// set identifier
	RTRmessage.message_identifier = MPPT0_MSGID;
	// DLC is zero 
	RTRmessage.num_bytes = 0; //potentially change this to the number of bytes we are requesting(8)
	// transmit packet
	CAN_Transmit_RTR(RTRmessage);
}

void Send_Test_Message(float V_in, float I_in, float efficiency_in){
	// convert from floats
	uint16_t v_tosend = (int) (V_in * 100);	
	uint16_t i_tosend = (int) (I_in * 100);	
	uint16_t eff_tosend = (int) (efficiency_in * 100);	

	// define packet
	TransmitPacket messageOut;
	//msgid
	messageOut.message_identifier = TEST_MSGID;
	//number of bytes
	messageOut.num_bytes = TEST0vars.TEST_VOLTAGE.num_bytes + TEST0vars.TEST_CURRENT.num_bytes + TEST0vars.TEST_EFFICIENCY.num_bytes;
	// package V_in
	messageOut.data[0] = (uint8_t) (v_tosend & 0xFF);
	messageOut.data[1] = (uint8_t) ((v_tosend >> 8) & 0xFF);
	// package I_in
	messageOut.data[2] = (uint8_t) (i_tosend & 0xFF);
	messageOut.data[3] = (uint8_t) ((i_tosend >> 8) & 0xFF);
	// package Power_in
	messageOut.data[4] = (uint8_t) (eff_tosend & 0xFF);
	messageOut.data[5] = (uint8_t) ((eff_tosend >> 8) & 0xFF);
	// send packet
	CAN_Transmit(messageOut);
}

float getArrayVoltage(void) {
	// check if data is valid
	if(MPPT0vars.ARRAY_VOLTAGE.data_valid) {
		//change this data type for each get function
		uint16_t data_for_return = 0;
		for(int i = 0; i < MPPT0vars.ARRAY_VOLTAGE.num_bytes; i++){
			data_for_return = data_for_return | (MPPT0vars.ARRAY_VOLTAGE.data[i] << 8*i);
		}
		float float_data_for_return = (data_for_return) / 100.0f;
		//This corrects for if we accidentally return a false value which should never happen anyways
		if(isInvalid(float_data_for_return))
			float_data_for_return += 0.1;
		return float_data_for_return;
	}else {
		return falseValue;
	}	
}

float getArrayCurrent(void) {
	// check if data is valid
	if(MPPT0vars.ARRAY_CURRENT.data_valid) {
		//change this data type for each get function
		uint16_t data_for_return = 0;
		for(int i = 0; i < MPPT0vars.ARRAY_CURRENT.num_bytes; i++){
			data_for_return = data_for_return | (MPPT0vars.ARRAY_CURRENT.data[i] << 8*i);
		}
		float float_data_for_return = (data_for_return) / 1000.0f;
		//This corrects for if we accidentally return a false value which should never happen anyways
		if(isInvalid(float_data_for_return))
			float_data_for_return += 0.1;
		return float_data_for_return;
	}else {
		return falseValue;
	}	
}

float getBatteryVoltage(void) {
	// check if data is valid
	if(MPPT0vars.BATTERY_VOLTAGE.data_valid) {
		//change this data type for each get function
		uint16_t data_for_return = 0;
		for(int i = 0; i < MPPT0vars.BATTERY_VOLTAGE.num_bytes; i++){
			data_for_return = data_for_return | (MPPT0vars.BATTERY_VOLTAGE.data[i] << 8*i);
		}
		float float_data_for_return = (data_for_return) / 100.0f;
		//This corrects for if we accidentally return a false value which should never happen anyways
		if(isInvalid(float_data_for_return))
			float_data_for_return += 0.1;
		return float_data_for_return;
	}else {
		return falseValue;
	}	
}

float getTemperature_MPPT(void) {
	// check if data is valid
	if(MPPT0vars.TEMPERATURE_MPPT.data_valid) {
		//change this data type for each get function
		uint16_t data_for_return = 0;
		for(int i = 0; i < MPPT0vars.TEMPERATURE_MPPT.num_bytes; i++){
			data_for_return = data_for_return | (MPPT0vars.TEMPERATURE_MPPT.data[i] << 8*i);
		}
		float float_data_for_return = (data_for_return) / 100.0f;
		//This corrects for if we accidentally return a false value which should never happen anyways
		if(isInvalid(float_data_for_return))
			float_data_for_return += 0.1;
		return float_data_for_return;
	}else {
		return falseValue;
	}	
}

float getTest_Voltage(void) {
	// check if data is valid
	if(TEST0vars.TEST_VOLTAGE.data_valid) {
		//change this data type for each get function
		uint16_t data_for_return = 0;
		for(int i = 0; i < TEST0vars.TEST_VOLTAGE.num_bytes; i++){
			data_for_return = data_for_return | (TEST0vars.TEST_VOLTAGE.data[i] << 8*i);
		}
		float float_data_for_return = (data_for_return) / 100.0f;
		//This corrects for if we accidentally return a false value which should never happen anyways
		if(isInvalid(float_data_for_return))
			float_data_for_return += 0.1;
		return float_data_for_return;
	}else {
		return falseValue;
	}	
}

float getTest_Current(void) {
	// check if data is valid
	if(TEST0vars.TEST_CURRENT.data_valid) {
		//change this data type for each get function
		uint16_t data_for_return = 0;
		for(int i = 0; i < TEST0vars.TEST_CURRENT.num_bytes; i++){
			data_for_return = data_for_return | (TEST0vars.TEST_CURRENT.data[i] << 8*i);
		}
		float float_data_for_return = (data_for_return) / 100.0f;
		//This corrects for if we accidentally return a false value which should never happen anyways
		if(isInvalid(float_data_for_return))
			float_data_for_return += 0.1;
		return float_data_for_return;
	}else {
		return falseValue;
	}	
}

float getTest_Efficiency(void) {
	// check if data is valid
	if(TEST0vars.TEST_EFFICIENCY.data_valid) {
		//change this data type for each get function
		uint16_t data_for_return = 0;
		for(int i = 0; i < TEST0vars.TEST_EFFICIENCY.num_bytes; i++){
			data_for_return = data_for_return | (TEST0vars.TEST_EFFICIENCY.data[i] << 8*i);
		}
		float float_data_for_return = (data_for_return) / 100.0f;
		//This corrects for if we accidentally return a false value which should never happen anyways
		if(isInvalid(float_data_for_return))
			float_data_for_return += 0.1;
		return float_data_for_return;
	}else {
		return falseValue;
	}	
}
//Pack current is unsigned
float getPackCurrent(void) {
	// check if data is valid
	if(BMS0vars.PACK_CURRENT.data_valid) {
		//change this data type for each get function
		uint16_t data_for_return = 0;
		for(int i = 0; i < BMS0vars.PACK_CURRENT.num_bytes; i++){
			data_for_return = data_for_return | (BMS0vars.PACK_CURRENT.data[i] << 8*i);
		}
		float float_data_for_return = (data_for_return - 32767) / 10.0f;//Not sure if I should do subtraction before or after
		//This corrects for if we accidentally return a false value which should never happen anyways
		if(isInvalid(float_data_for_return))
			float_data_for_return += 0.1;
		return float_data_for_return;
	}else {
		return falseValue;
	}	
}

float getPackVoltage(void) {
	// check if data is valid
	if(BMS0vars.PACK_VOLTAGE.data_valid) {
		//change this data type for each get function
		uint16_t data_for_return = 0;
		for(int i = 0; i < BMS0vars.PACK_VOLTAGE.num_bytes; i++){
			data_for_return = data_for_return | (BMS0vars.PACK_VOLTAGE.data[i] << 8*i);
		}
		float float_data_for_return = (data_for_return) / 10.0f;
		//This corrects for if we accidentally return a false value which should never happen anyways
		if(isInvalid(float_data_for_return))
			float_data_for_return += 0.1;
		return float_data_for_return;
	}else {
		return falseValue;
	}	
}

float getPackSOC(void) {
	// check if data is valid
	if(BMS0vars.PACK_SOC.data_valid) {
		//change this data type for each get function
		uint8_t data_for_return = 0;
		for(int i = 0; i < BMS0vars.PACK_SOC.num_bytes; i++){
			data_for_return = data_for_return | (BMS0vars.PACK_SOC.data[i] << 8*i);
		}
		float float_data_for_return = (data_for_return) / 2.0f;
		//This corrects for if we accidentally return a false value which should never happen anyways
		if(isInvalid(float_data_for_return))
			float_data_for_return += 0.1;
		return float_data_for_return;
	}else {
		return falseValue;
	}	
}

uint16_t getRelayState(void) {
	// check if data is valid
	if(BMS0vars.RELAY_STATE.data_valid) {
		//change this data type for each get function
		uint16_t data_for_return = 0;
		for(int i = 0; i < BMS0vars.RELAY_STATE.num_bytes; i++){
			data_for_return = data_for_return | (BMS0vars.RELAY_STATE.data[i] << 8*i);
		}
		//This corrects for if we accidentally return a false value which should never happen anyways
		if(isInvalid(data_for_return))
			data_for_return += 1;
		return data_for_return;
	}else {
		return falseValue;
	}	
}


uint16_t getCRCChecks(void) {
	// check if data is valid
	if(BMS0vars.CRC_CHECKSUM.data_valid) {
		//change this data type for each get function
		uint16_t data_for_return = 0;
		for(int i = 0; i < BMS0vars.CRC_CHECKSUM.num_bytes; i++){
			data_for_return = data_for_return | (BMS0vars.CRC_CHECKSUM.data[i] << 8*i);
		}
		//This corrects for if we accidentally return a false value which should never happen anyways
		if(isInvalid(data_for_return))
			data_for_return += 1;
		return data_for_return;
	}else {
		return falseValue;
	}	
}

float getSpeed(void)
{
	// check if data is valid
	if(SPEED0vars.CAR_SPEED.data_valid) {
		//change this data type for each get function
		uint16_t data_for_return = 0;
		for(int i = 0; i < SPEED0vars.CAR_SPEED.num_bytes; i++){
			data_for_return = data_for_return | (SPEED0vars.CAR_SPEED.data[i] << 8*i);
		}
		float float_data_for_return = (data_for_return) / 10.0f;
		//This corrects for if we accidentally return a false value which should never happen anyways
		if(isInvalid(float_data_for_return))
			float_data_for_return += 0.1;
		return float_data_for_return;
	}else {
		return falseValue;
	}	
}

void Send_SPEED_Message(float speed)
{
	// convert from floats
	uint16_t speed_tosend = (int) (speed * 10); //One decimal point of precision
	// define packet
	TransmitPacket messageOut;
	//msgid
	messageOut.message_identifier = SPEED_MSGID;
	//number of bytes
	messageOut.num_bytes = SPEED0vars.CAR_SPEED.num_bytes;
	// package Speed
	messageOut.data[0] = (uint8_t) (speed_tosend & 0xFF);
	messageOut.data[1] = (uint8_t) ((speed_tosend >> 8) & 0xFF);
	// send packet
	CAN_Transmit(messageOut);
}

