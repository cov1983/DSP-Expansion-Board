//==================================================================================================
//! \brief     Simplicity Studio C/C++ Template with Doxygen integration.
//==================================================================================================
//! \verbatim
//! -----------------------------------------------------------------------------------------------
//! School   : HBU Hoehere Berufsbildung Uster
//! Subject  : DA DSP Expansion Board
//! Topic    : Topic description
//! -----------------------------------------------------------------------------------------------
//!            Date         Name			Comment
//! Created  : 2020-02-18   Thomas Cova		Created when/during ...
//! History  : &&&&-&&-&&   Thomas Cova		...
//!
//! -----------------------------------------------------------------------------------------------
//! (c) Copyright 2019-2020 Thomas Cova and HBU Hoehere Berufsbildung Uster. All Rights Reserved.
//! -----------------------------------------------------------------------------------------------
//! \endverbatim
//==================================================================================================
//! Short description of this file/module.
//==================================================================================================


//==================================================================================================
//  I N C L U D E D   F I L E S
//==================================================================================================
#include <stdio.h>

#include "i2c.h"
#include "leds.h"

//==================================================================================================
//  M O D U L E   D E F I N E S
//==================================================================================================

#define CORE_FREQUENCY		48000000
#define I2C_RXBUFFER_SIZE	10

// I2C ADRESS -> JUST FOR TESTING - STANDARD = NOT ACTIVE
#define I2C_CODEC_ADDR	0x18
#define I2C_IOEXP_ADDR	0x24

//==================================================================================================
//  M O D U L E   T Y P E S
//==================================================================================================

//==================================================================================================
//  M O D U L E   V A R I A B L E S
//==================================================================================================

// TX Test Buffer - JUST USED FOR TESTING EMBLIB
uint8_t i2c_txBuffer[] = "I2C TEST";

// TX Test Buffer Size - JUST USED FOR TESTING EMBLIB
uint8_t i2c_txBufferSize = sizeof(i2c_txBuffer);

// RX Buffer - NEEDED IF SLAVE FUNCTION IS ACTIVE
uint8_t i2c_rxBuffer[I2C_RXBUFFER_SIZE];

// RX Buffer Index - NEEDED IF SLAVE FUNCTION IS ACTIVE
uint8_t i2c_rxBufferIndex;

// Transmission Flags
volatile bool i2c_rxInProgress;
volatile bool i2c_startTx;

//==================================================================================================
//  M O D U L E   F U N C T I O N   P R O T O T Y P E S
//==================================================================================================

//==================================================================================================
//  I R Q   H A N D L E R S
//==================================================================================================

//--------------------------------------------------------------------------------------------------
// void I2C_IRQHandler()
//--------------------------------------------------------------------------------------------------
//! \brief	Handles I2C Data IN if Slave Functionality is Active.
//!
//!
//! \param	void		input	No input arguments
//! \return	void		output	No output arguments
//--------------------------------------------------------------------------------------------------
void I2C1_IRQHandler(void)
{
  int status;

  status = I2C1->IF;

  if (status & I2C_IF_ADDR)
  {
    // Address Match
    // Indicating that reception is started
    i2c_rxInProgress = true;
    I2C0->RXDATA;
    i2c_rxBufferIndex = 0;

    I2C_IntClear(I2C1, I2C_IFC_ADDR);

  } else if (status & I2C_IF_RXDATAV)
  {
    // Data received
    i2c_rxBuffer[i2c_rxBufferIndex] = I2C1->RXDATA;
    i2c_rxBufferIndex++;
  }

  if(status & I2C_IEN_SSTOP){
    // Stop received, reception is ended
    I2C_IntClear(I2C1, I2C_IEN_SSTOP);
    i2c_rxInProgress = false;
    i2c_rxBufferIndex = 0;
  }
}

//==================================================================================================
//  G L O B A L   F U N C T I O N   I M P L E M E N T A T I O N
//==================================================================================================

//--------------------------------------------------------------------------------------------------
// void initI2C(void)
//--------------------------------------------------------------------------------------------------
//! \brief	A brief explanation of this function's functionality goes here.
//!
//! A more detailed explanation of this function's functionality goes here,
//! which may go over several lines.
//!
//! \param	someInt		input	Description of parameter someInt
//! \param	someDouble	input	Description of parameter someDouble
//! \return	Description of the return value
//! 		-  0 = Nothing
//! 		- >0 = Number of something
//--------------------------------------------------------------------------------------------------
void initI2C(void)
{
  // Using default settings
  I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;
  // Use ~400khz SCK
  i2cInit.freq = I2C_FREQ_FAST_MAX;

  // Using PC4 (SDA) and PC5 (SCL)
  GPIO_PinModeSet(gpioPortC, 4, gpioModeWiredAndPullUpFilter, 1);
  GPIO_PinModeSet(gpioPortC, 5, gpioModeWiredAndPullUpFilter, 1);

  // Enable pins for I2C1 on Expansion Header as specified in Datasheet (p.403)
  I2C1->ROUTE = I2C_ROUTE_SDAPEN | I2C_ROUTE_SCLPEN;
  I2C1->ROUTE = (I2C1->ROUTE & (~_I2C_ROUTE_LOCATION_MASK)) | I2C_ROUTE_LOCATION_DEFAULT;

  // Initializing the I2C
  I2C_Init(I2C1, &i2cInit);

  // Setting the status flags and index
  i2c_rxInProgress = false;
  i2c_startTx = false;
  i2c_rxBufferIndex = 0;

  // Setting up to enable slave mode
  // NOT ACTIVE
  /*
  I2C1->SADDR = I2C_IOEXP_ADDR;
  I2C1->CTRL |= I2C_CTRL_SLAVE | I2C_CTRL_AUTOACK | I2C_CTRL_AUTOSN;
  enableI2cSlaveInterrupts();
  */
}

//--------------------------------------------------------------------------------------------------
// void performI2CTransfer(void)
//--------------------------------------------------------------------------------------------------
//! \brief	Handles I2C Data Bidirectional Transfer [MASTER <-> SLAVE].
//!
//! A more detailed explanation of this function's functionality goes here,
//! which may go over several lines.
//!
//! \param	someInt		input	Description of parameter someInt
//! \param	someDouble	input	Description of parameter someDouble
//! \return	Description of the return value
//! 		-  0 = Nothing
//! 		- >0 = Number of something
//--------------------------------------------------------------------------------------------------
void performI2CTransfer(void)
{
  // Transfer structure
  I2C_TransferSeq_TypeDef i2cTransfer;
  I2C_TransferReturn_TypeDef result;

  // Setting LED1 to indicate transfer
  enableLED1();

  // Initializing I2C transfer
  i2cTransfer.addr          = I2C_IOEXP_ADDR;
  i2cTransfer.flags         = I2C_FLAG_WRITE;
  i2cTransfer.buf[0].data   = i2c_txBuffer;
  i2cTransfer.buf[0].len    = i2c_txBufferSize;
  i2cTransfer.buf[1].data   = i2c_rxBuffer;
  i2cTransfer.buf[1].len    = I2C_RXBUFFER_SIZE;
  result = I2C_TransferInit(I2C1, &i2cTransfer);

  // Sending data
  while (result == i2cTransferInProgress)
  {
    result = I2C_Transfer(I2C1);
  }

  // Clearing LED1 to indicate end of transfer
  disableLED1();
  // NOT USED NOW -> JUST TRANSFER TEST !
  //enableI2cSlaveInterrupts();
}

//--------------------------------------------------------------------------------------------------
// int8_t I2Cwrite(uint8_t addr, uint8_t* data, uint8_t len)
//--------------------------------------------------------------------------------------------------
//! \brief	A brief explanation of this function's functionality goes here.
//!
//! A more detailed explanation of this function's functionality goes here,
//! which may go over several lines.
//!
//! \param	someInt		input	Description of parameter someInt
//! \param	someDouble	input	Description of parameter someDouble
//! \return	Description of the return value
//! 		-  0 = Nothing
//! 		- >0 = Number of something
//--------------------------------------------------------------------------------------------------
int8_t I2Cwrite(uint8_t addr, uint8_t* data, uint8_t len)
{
	// Transfer structure
	I2C_TransferSeq_TypeDef i2cWrite;
	I2C_TransferReturn_TypeDef i2cState;

	// Setting LED1 to indicate transfer
	enableLED1();

	// Initializing I2C transfer
	i2cWrite.addr          = addr;
	i2cWrite.flags         = I2C_FLAG_WRITE;
	i2cWrite.buf[0].data   = data;
	i2cWrite.buf[0].len    = len;
	i2cWrite.buf[1].data   = i2c_rxBuffer;
	i2cWrite.buf[1].len    = I2C_RXBUFFER_SIZE;
	i2cState = I2C_TransferInit(I2C1, &i2cWrite);

	// Sending data, as long i2cState is 1 = in progress
	while (i2cState == i2cTransferInProgress)
	{
	  i2cState = I2C_Transfer(I2C1);
	}

	// Clearing LED1 to indicate end of transfer
	disableLED1();

	// Return i2cState after Transfer
	//  0 = DONE
	// -1 = NACK
	// -2 = BUS ERROR
	return i2cState;
}

//--------------------------------------------------------------------------------------------------
// void enableI2cSlaveInterrupts(void)
//--------------------------------------------------------------------------------------------------
//! \brief	Enable I2C Data IN Interrupts for Slave Functionality.
//!
//! A more detailed explanation of this function's functionality goes here,
//! which may go over several lines.
//!
//! \param	someInt		input	Description of parameter someInt
//! \param	someDouble	input	Description of parameter someDouble
//! \return	Description of the return value
//! 		-  0 = Nothing
//! 		- >0 = Number of something
//--------------------------------------------------------------------------------------------------
void enableI2cSlaveInterrupts(void)
{
  I2C_IntClear(I2C0, I2C_IEN_ADDR | I2C_IEN_RXDATAV | I2C_IEN_SSTOP);
  I2C_IntEnable(I2C0, I2C_IEN_ADDR | I2C_IEN_RXDATAV | I2C_IEN_SSTOP);
  NVIC_EnableIRQ(I2C0_IRQn);
}

//--------------------------------------------------------------------------------------------------
// void disableI2cSlaveInterrupts(void)
//--------------------------------------------------------------------------------------------------
//! \brief	Disable I2C Data IN Interrupts for Slave Functionality.
//!
//! A more detailed explanation of this function's functionality goes here,
//! which may go over several lines.
//!
//! \param	someInt		input	Description of parameter someInt
//! \param	someDouble	input	Description of parameter someDouble
//! \return	Description of the return value
//! 		-  0 = Nothing
//! 		- >0 = Number of something
//--------------------------------------------------------------------------------------------------
void disableI2cSlaveInterrupts(void)
{
  NVIC_DisableIRQ(I2C0_IRQn);
  I2C_IntDisable(I2C0, I2C_IEN_ADDR | I2C_IEN_RXDATAV | I2C_IEN_SSTOP);
  I2C_IntClear(I2C0, I2C_IEN_ADDR | I2C_IEN_RXDATAV | I2C_IEN_SSTOP);
}

//==================================================================================================
//  E N D   O F   F I L E
//==================================================================================================
