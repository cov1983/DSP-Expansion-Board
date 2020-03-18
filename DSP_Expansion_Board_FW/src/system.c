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

#include "system.h"		// Include System Module

//==================================================================================================
//  M O D U L E   D E F I N E S
//==================================================================================================


//==================================================================================================
//  M O D U L E   T Y P E S
//==================================================================================================

//! Some module type

//==================================================================================================
//  M O D U L E   V A R I A B L E S
//==================================================================================================


//==================================================================================================
//  M O D U L E   F U N C T I O N   P R O T O T Y P E S
//==================================================================================================


//==================================================================================================
//  I R Q   H A N D L E R S
//==================================================================================================



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
void initSTK3800(void)
{
	// Apply chip Errata:
	CHIP_Init();
	// Initialize Clocks
	initClk();
	// Initialize SysTick
	initSysTick();
	// Initialize Push Buttons
	initSTK3800Buttons();
	// Initialize LEDs
	initSTK3800Leds();
	// Initialize DSP Board detection
	initDSPDetection();
	// Enable digital interrupts
	enableDigitalInterrupts();
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
void enableDSPInterface(void)
{
	// Enable I2C Interface
	enableI2C();
	// Enable I2S Interface
	enableI2S();
	// Enable MCLK
	enableMCLK();
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
void disableDSPInterface(void)
{
	// Disable I2C Interface
	disableI2C();
	// Disable I2S Interface
	disableI2S();
	// Disable MCLK
	disableMCLK();
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
bool initDSPBoard(void)
{
	bool initDSPBoard = true;

	// IOexpander Initialization
	initDSPBoard = initIOexpander();

	return initDSPBoard;
}

//==================================================================================================
//  M O D U L E   F U N C T I O N   I M P L E M E N T A T I O N
//==================================================================================================


//==================================================================================================
//  E N D   O F   F I L E
//==================================================================================================
