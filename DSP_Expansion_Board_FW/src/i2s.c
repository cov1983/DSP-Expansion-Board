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

#include "i2s.h"
#include "processing.h"

//==================================================================================================
//  M O D U L E   D E F I N E S
//==================================================================================================

#define SPK_I2S_FORMAT          usartI2sFormatW32D16			// Sets I2S Format Word = 32bit Data = 16bit
#define I2S_USART_UART          USART1							// Selects USART1
#define I2S_USART_LOCATION      USART_ROUTE_LOCATION_LOC1		// Selects USART Pinout for Expansion Header (Datasheet p.407)
#define I2S_USART_TXPORT        gpioPortD						// USART_TX => PortD0
#define I2S_USART_TXPIN         0
#define I2S_USART_RXPORT        gpioPortD						// USART_RX => PortD1
#define I2S_USART_RXPIN         1
#define I2S_USART_CLKPORT       gpioPortD						// USART_CLK => PortD2
#define I2S_USART_CLKPIN        2
#define I2S_USART_WSPORT        gpioPortD						// USART_WS => PortD3
#define I2S_USART_WSPIN         3

//==================================================================================================
//  M O D U L E   T Y P E S
//==================================================================================================


//==================================================================================================
//  M O D U L E   V A R I A B L E S
//==================================================================================================
static AudioSample audioSampleIN;
static AudioSample audioSampleOUT;

//==================================================================================================
//  M O D U L E   F U N C T I O N   P R O T O T Y P E S
//==================================================================================================
static void enableUSARTinterrupts(void);
static void disableUSARTinterrupts(void);

//==================================================================================================
//  I R Q   H A N D L E R S
//==================================================================================================

//--------------------------------------------------------------------------------------------------
// void USART1_RX_IRQHandler()
//--------------------------------------------------------------------------------------------------
//! \brief	Handles USART1_RX events.
//!
//!
//! \param	void		input	No input arguments
//! \return	void		output	No output arguments
//--------------------------------------------------------------------------------------------------
void USART1_RX_IRQHandler()
{
	// Check whether RX Data Valid Interrupt is active
	if(USART1->IF & (USART_IF_RXFULL))
	{
		// Clear interrupt Flag
		USART1->IFC = USART_IFC_RXFULL;

		// Check if RXDATA are Right Data
		if(USART1->STATUS & (USART_STATUS_RXDATAVRIGHT))
		{
			// Get Right Sample from USART1/I2S RX Buffer
			audioSampleIN.right = (uint16_t)((USART1->RXDOUBLE) & 0xFFFF);
		}
		else {

			// Get Left Sample from USART1/I2S RX Buffer
			audioSampleIN.left = (uint16_t)((USART1->RXDOUBLE) & 0xFFFF);
		}
		// Call processing function here & get samples back
		audioSampleOUT = bypass(audioSampleIN);
	}
}

//--------------------------------------------------------------------------------------------------
// void USART1_RX_IRQHandler()
//--------------------------------------------------------------------------------------------------
//! \brief	Handles USART1_RX events.
//!
//!
//! \param	void		input	No input arguments
//! \return	void		output	No output arguments
//--------------------------------------------------------------------------------------------------
void USART1_TX_IRQHandler(void)
{

  if(USART1->STATUS & (USART_STATUS_TXBDRIGHT))
  {
	  USART1->TXDOUBLE = (uint32_t)(audioSampleOUT.right);
  }
  else {
	  USART1->TXDOUBLE = (uint32_t)(audioSampleOUT.left);
  }

}

//==================================================================================================
//  G L O B A L   F U N C T I O N   I M P L E M E N T A T I O N
//==================================================================================================

//--------------------------------------------------------------------------------------------------
// SomeGlobalFunction
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
void enableI2S(void)
{
  USART_InitI2s_TypeDef init = USART_INITI2S_DEFAULT;

  GPIO_PinModeSet(I2S_USART_TXPORT, I2S_USART_TXPIN, gpioModeInput, 0);
  GPIO_PinModeSet(I2S_USART_RXPORT, I2S_USART_RXPIN, gpioModePushPull, 0);
  GPIO_PinModeSet(I2S_USART_CLKPORT, I2S_USART_CLKPIN, gpioModeInput, 0);
  GPIO_PinModeSet(I2S_USART_WSPORT, I2S_USART_WSPIN, gpioModeInput, 0);


  /* Configure USART for I2S slave. */
  init.sync.enable = usartEnable;
  init.sync.master = false;
  init.mono = false;
  init.format = SPK_I2S_FORMAT;

  // Enable USART1 configured as I2S above
   USART_InitI2s(I2S_USART_UART, &init);

  /* Enable pins at location. */
  I2S_USART_UART->ROUTE = USART_ROUTE_TXPEN
                        | USART_ROUTE_RXPEN
                        | USART_ROUTE_CSPEN
                        | USART_ROUTE_CLKPEN
                        | I2S_USART_LOCATION;

  // Enable USART RX and TX Interrupts
  enableUSARTinterrupts();
}

//--------------------------------------------------------------------------------------------------
// SomeGlobalFunction
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
void disableI2S(void)
{
	// Disable USART Interrupts
	disableUSARTinterrupts();

	// Disable USART Interface
	USART_Enable(I2S_USART_UART, usartDisable);

	// Disable USART Pins
	GPIO_PinModeSet(I2S_USART_TXPORT, I2S_USART_TXPIN, gpioModeDisabled, 0);
	GPIO_PinModeSet(I2S_USART_RXPORT, I2S_USART_RXPIN, gpioModeDisabled, 0);
	GPIO_PinModeSet(I2S_USART_CLKPORT, I2S_USART_CLKPIN, gpioModeDisabled, 0);
	GPIO_PinModeSet(I2S_USART_WSPORT, I2S_USART_WSPIN, gpioModeDisabled, 0);
}

//==================================================================================================
//  M O D U L E   F U N C T I O N   I M P L E M E N T A T I O N
//==================================================================================================

//--------------------------------------------------------------------------------------------------
// static void enableIntUSART(void)
//--------------------------------------------------------------------------------------------------
//! \brief	Setter function for actual state of ButtonPB1.
//!
//! This function is used to set the ButtonPB1Flag.
//! This function is called from the PB1 GPIO Interrupt routine.
//!
//! \param	void	input	No input arguments
//! \return	void	output	No input arguments
//--------------------------------------------------------------------------------------------------
static void enableUSARTinterrupts(void)
{
	// Enable USART1 RX Interrupts
	USART_IntClear(USART1, USART_IF_RXDATAV);
	USART_IntEnable(USART1, USART_IF_RXDATAV);
	NVIC_ClearPendingIRQ(USART1_RX_IRQn);
	NVIC_EnableIRQ(USART1_RX_IRQn);

	// Enable USART1 TX Interrupts
	// If there is room in the transmit buffer
	// This should immediately trigger to load the first frame of TX buffer
	USART_IntClear(USART1, USART_IF_TXBL);
	USART_IntEnable(USART1, USART_IF_TXBL);
	NVIC_ClearPendingIRQ(USART1_TX_IRQn);
	NVIC_EnableIRQ(USART1_TX_IRQn);
}

//--------------------------------------------------------------------------------------------------
// static void enableIntUSART(void)
//--------------------------------------------------------------------------------------------------
//! \brief	Setter function for actual state of ButtonPB1.
//!
//! This function is used to set the ButtonPB1Flag.
//! This function is called from the PB1 GPIO Interrupt routine.
//!
//! \param	void	input	No input arguments
//! \return	void	output	No input arguments
//--------------------------------------------------------------------------------------------------
static void disableUSARTinterrupts(void)
{
	// Disable USART1 RX Interrupts
	USART_IntClear(USART1, USART_IF_RXDATAV);
	USART_IntDisable(USART1, USART_IF_RXDATAV);
	NVIC_ClearPendingIRQ(USART1_RX_IRQn);
	NVIC_DisableIRQ(USART1_RX_IRQn);

	// Disable USART1 TX Interrupts
	USART_IntClear(USART1, USART_IF_TXBL);
	USART_IntDisable(USART1, USART_IF_TXBL);
	NVIC_ClearPendingIRQ(USART1_TX_IRQn);
	NVIC_DisableIRQ(USART1_TX_IRQn);
}

//==================================================================================================
//  E N D   O F   F I L E
//==================================================================================================
