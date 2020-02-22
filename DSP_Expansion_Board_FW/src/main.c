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

#include "em_device.h" 	// Includes the MCU dependent headers based on the project's MCU definition.
#include "em_chip.h"   	// emlib chip errata.

#include "clocks.h"		// Include Clocks Module
#include "buttons.h"	// Include Buttons Module
#include "i2c.h"		// Include I2C Module
#include "leds.h"		// Include LEDs Module
#include "codec.h"		// Include Codec Module


//==================================================================================================
//  M O D U L E   D E F I N E S
//==================================================================================================


//==================================================================================================
//  M O D U L E   T Y P E S
//==================================================================================================


//==================================================================================================
//  M O D U L E   V A R I A B L E S
//==================================================================================================

bool i2cRepeat = false;

bool i2cError = false;

//==================================================================================================
//  F O R W A R D   D E C L A R A T I O N S
//==================================================================================================


//==================================================================================================
//  G L O B A L   F U N C T I O N   I M P L E M E N T A T I O N
//==================================================================================================


//==================================================================================================
//  M O D U L E   F U N C T I O N   I M P L E M E N T A T I O N
//==================================================================================================

//--------------------------------------------------------------------------------------------------
// SomeModuleFunction
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

int main(void)
{
	// Apply chip errata:
	CHIP_Init();
	// Initialize Clocks
	InitClk();
	// Initialize Push Buttons
	initButtons();
	// Initialize LEDs
	initLEDS();
	// Initialize I2C
	initI2C();

	while (true)
	{
		// Check if PB0 Button is activated
		if (GetButtonPB0Flag())
		{
			// Enable HFRCO Clock on Pin PD7
			enableMCLK();
		}
		else {
			// Disable HFRCO Clock on Pin PD7
			disableMCLK();
		}

		// Check if PB1 Button is activated
		if (GetButtonPB1Flag())
		{
			// Enable LED0
			enableLED0();

			//I2c Test Transfer
			if (!i2cRepeat)
			{
				// CODEC Configuration Test Block
				i2cError = initCODEC();

				// Set Repeat Flag
				i2cRepeat = true;
			}
		}
		else {
			// Disable LED0
			disableLED0();
			// Reset i2cRepeat Flag, with the next press of PB1 a new transfer will start
			i2cRepeat = false;
		}
	}

	return (0);
}


//==================================================================================================
//  E N D   O F   F I L E
//==================================================================================================
