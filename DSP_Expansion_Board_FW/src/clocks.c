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

#include "em_cmu.h"    	// emlib CMU (clock management unit) functionality.
#include "clocks.h"


//==================================================================================================
//  M O D U L E   D E F I N E S
//==================================================================================================

// Assertion macro
// remains in endless loop only if expr is false
# define sysAssert(expr) ((expr) ? ({}):  ({AssertErrorLine = __LINE__; AssertErrorFile = __FILE__; while (true){}}) )


//==================================================================================================
//  M O D U L E   T Y P E S
//==================================================================================================


//==================================================================================================
//  M O D U L E   V A R I A B L E S
//==================================================================================================

// Indicates the erroneous file in case of assertion error
static char *AssertErrorFile;
// Indicates the erroneous line in case of assertion error
static int AssertErrorLine;

//==================================================================================================
//  F O R W A R D   D E C L A R A T I O N S
//==================================================================================================


//==================================================================================================
//  G L O B A L   F U N C T I O N   I M P L E M E N T A T I O N
//==================================================================================================

//--------------------------------------------------------------------------------------------------
// void InitClk()
//--------------------------------------------------------------------------------------------------
//! \brief	Initializes the uC clock system.
//!
//! - Selects HFXO as HF clock source (f=48MHz)
//!
//! \param	void		input	No input arguments
//! \return	void		output	No output arguments
//--------------------------------------------------------------------------------------------------
void InitClk(void)
{
	// Activate HFXO and use it as HF clock source
	// Enable and start crystal oscillator
	CMU_OscillatorEnable(cmuOsc_HFXO,true,true);
	// Select HFXO for HFCLK
	CMU_ClockSelectSet(cmuClock_HF,cmuSelect_HFXO);
	// Make sure selected clock source works
	sysAssert( CMU_ClockSelectGet(cmuClock_HF) == cmuSelect_HFXO);

	//Enable peripheral clocks
	CMU_ClockEnable(cmuClock_GPIO,true);
	CMU_ClockEnable(cmuClock_I2C1, true);
	CMU_ClockEnable(cmuClock_USART1, true);

	/*
	CMU_ClockEnable( cmuClock_TIMER0,true);
	CMU_ClockEnable( cmuClock_TIMER1,true);
	CMU_ClockEnable( cmuClock_ADC0,true);
	CMU_ClockEnable( cmuClock_DAC0,true);
	CMU_ClockEnable( cmuClock_PRS,true);
	*/

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

void enableMCLK(void)
{
	/* Select HFCLK/4 as source for CMU_CLK0 pin (should be 48/4 = 12Mhz) */
	CMU->CTRL =(CMU->CTRL &~_CMU_CTRL_CLKOUTSEL0_MASK)| CMU_CTRL_CLKOUTSEL0_HFCLK4;

	/* Enable routing of CMU_CLK0 on location #2 (PD7)  */
	CMU->ROUTE = CMU_ROUTE_LOCATION_LOC2 | CMU_ROUTE_CLKOUT0PEN;

	/* Configure PD7 as push-pull output */
	GPIO_PinModeSet(gpioPortD,7, gpioModePushPull ,0);
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
void disableMCLK(void)
{
	// Disable MCLK Clock
	CMU->ROUTE = CMU_ROUTE_LOCATION_DEFAULT & _CMU_ROUTE_RESETVALUE;
}

//==================================================================================================
//  M O D U L E   F U N C T I O N   I M P L E M E N T A T I O N
//==================================================================================================


//==================================================================================================
//  E N D   O F   F I L E
//==================================================================================================
