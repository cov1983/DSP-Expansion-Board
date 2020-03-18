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

#include "em_device.h" 	// Includes the MCU dependent headers based on the project's MCU definition
#include "em_lcd.h"		// emblib for LCD

#include "segmentlcd.h" // Include STK3800 LCD Library

#include "system.h"		// Include System Module
#include "codec.h"		// Include CODEC Module

//==================================================================================================
//  M O D U L E   D E F I N E S
//==================================================================================================

//==================================================================================================
//  M O D U L E   T Y P E S
//==================================================================================================

//==================================================================================================
//  M O D U L E   V A R I A B L E S
//==================================================================================================

bool dspBoardActive = false;
bool i2cError = false;

bool buttonPB0once = false;

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
	// STK3800 BASIC SYSTEM INIT
	initSTK3800_Basic();


	// Initialize LCD without boost
	SegmentLCD_Init(false);
	// Show welcome message on LCD
	SegmentLCD_AllOff();
	SegmentLCD_Write("DSPDemo");
	Delay(2000);

	// Initialize STK3800
	initSTK3800_Basic();


	// ENTER INFINITE LOOP
	while (true)
	{

		if (getDSPDetectionFlag())
		{
			SegmentLCD_Write("DSP ON");
			// Call StateMachine
			// ...
		}
		else {
			SegmentLCD_Write("DSP OFF");
		}







		// Check if PB0 Button is activated
		/*
		if (getButtonPB0Flag() && (!buttonPB0once))
		{
			// Enable LED0
			enableLED0();

			// CODEC SETUP LINE IN TO HP OUT AT FS = 48Khz
			// CODEC Base Initialization (LDO Power)
			i2cError = initCODEC();
			// CODEC PLL & Clocks Initialization
			i2cError = setSampling48CODEC();
			// CODEC Configure Processing Blocks
			i2cError = setProcessingBlocksCODEC();
			// CODEC DAC Routing & Power Up
			i2cError = setDacHPCODEC();
			Delay(100);
			// CODEC ADC Routing & Power Up
			i2cError = setAdcIN2CODEC();
			// CODEC Set Default Digital Gain ADC L&R 0dB
			i2cError = setAdcDigitalGainCODEC();

			// Set flag for ButtonPB0 pressed once
			buttonPB0once = true;
		}
		else {
			// Disable LED0
			disableLED0();
		}

		// Check if PB1 Button is activated
		if (getButtonPB1Flag())
		{
			// Enable LED1
			enableLED1();
		}
		else {

			// Disable LED1
			disableLED1();
		}
		*/
	}
	return (0);
}




//==================================================================================================
//  E N D   O F   F I L E
//==================================================================================================
