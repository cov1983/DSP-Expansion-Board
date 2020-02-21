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
#include <stdbool.h>

#include "em_core.h"
#include "em_gpio.h"   	// emlib GPIO (general purpose I/O) functionality.

#include "buttons.h"

//==================================================================================================
//  M O D U L E   D E F I N E S
//==================================================================================================

//! Some module define

//==================================================================================================
//  M O D U L E   T Y P E S
//==================================================================================================

//! Some module type

//==================================================================================================
//  M O D U L E   V A R I A B L E S
//==================================================================================================

static bool ButtonPB1Flag = false;
static bool ButtonPB0Flag = false;

//==================================================================================================
//  M O D U L E   F U N C T I O N   P R O T O T Y P E S
//==================================================================================================
static void SetButtonPB1Flag(void);
static void SetButtonPB0Flag(void);
static void ResetButtonPB1Flag(void);
static void ResetButtonPB0Flag(void);

//==================================================================================================
//  I R Q   H A N D L E R S
//==================================================================================================

//--------------------------------------------------------------------------------------------------
// void GPIO_EVEN_IRQHandler()
//--------------------------------------------------------------------------------------------------
//! \brief	Handles GPIO events from even pin numbers.
//!
//! Handles the push button PB1 pressed event.
//! -sets the SetSelectEventFlag flag
//!
//! \param	void		input	No input arguments
//! \return	void		output	No output arguments
//--------------------------------------------------------------------------------------------------
void GPIO_EVEN_IRQHandler()
{
	// Check whether interrupt comes from PB1
	if (GPIO->IF & (1<<PB1PIN))
	{
		// Clear interrupt flag
		GPIO->IFC = (1<<PB1PIN);

		// Toggle function for button PB1 Flag
		if (ButtonPB1Flag)
		{
			// Reset the associated flag if already active (toggle)
			ResetButtonPB1Flag();
		}
		else {
			// Set the associated flag
			SetButtonPB1Flag();
		}
	}
}

//--------------------------------------------------------------------------------------------------
// void GPIO_ODD_IRQHandler()
//--------------------------------------------------------------------------------------------------
//! \brief	Handles GPIO events from odd pin numbers.
//!
//! Handles the push button PB0 pressed event.
//! -sets the SetModeEventFlag flag
//!
//! \param	void		input	No input arguments
//! \return	void		output	No output arguments
//--------------------------------------------------------------------------------------------------
void GPIO_ODD_IRQHandler()
{
	// Check whether interrupt comes from PB0
	if (GPIO->IF & (1<<PB0PIN))
	{
		// Clear interrupt flag
		GPIO->IFC = (1<<PB0PIN);


		if (ButtonPB0Flag)
		{
			// Reset the associated flag if already active (toggle)
			ResetButtonPB0Flag();
		}
		else {
			// Set the associated flag
			SetButtonPB0Flag();
		}
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

void initButtons(void)
{
	// PB0: input with pullup R
	GPIO_PinModeSet(gpioPortB, PB0PIN, gpioModeInputPull,HIGH);
	// PB1: input with pullup R
	GPIO_PinModeSet(gpioPortB, PB1PIN, gpioModeInputPull,HIGH);
	// PB0: enable interrupts on falling edge
	GPIO_IntConfig( gpioPortB, PB0PIN, false, true, true );
	// PB1: enable interrupts on falling edge
	GPIO_IntConfig( gpioPortB, PB1PIN, false, true, true );

	//Also enable GPIO interrupts on ARM CPU level
	// Note:
	//- PB0 is on an odd pin (9) it triggers thus GPIO_ODD interrupts
	//- PB1 is on an even pin (10) it triggers thus GPIO_EVEN interrupts
	// Clear pending interrupts before enabling them
	NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
	NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
	NVIC_EnableIRQ(GPIO_ODD_IRQn);
	NVIC_EnableIRQ(GPIO_EVEN_IRQn);;
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

bool GetButtonPB1Flag(void)
{
	return ButtonPB1Flag;
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

bool GetButtonPB0Flag(void)
{
	return ButtonPB0Flag;
}

//==================================================================================================
//  M O D U L E   F U N C T I O N   I M P L E M E N T A T I O N
//==================================================================================================

//--------------------------------------------------------------------------------------------------
// static void SetButtonPB1Flag(void)
//--------------------------------------------------------------------------------------------------
//! \brief	Setter function for actual state of ButtonPB1.
//!
//! This function is used to set the ButtonPB1Flag.
//! This function is called from the PB1 GPIO Interrupt routine.
//!
//! \param	void	input	No input arguments
//! \return	void	output	No input arguments
//--------------------------------------------------------------------------------------------------
static void SetButtonPB1Flag(void)
{
	ButtonPB1Flag = true;
}

//--------------------------------------------------------------------------------------------------
// static void SetButtonPB0Flag(void)
//--------------------------------------------------------------------------------------------------
//! \brief	Setter function for actual state of ButtonPB0.
//!
//! This function is used to set the ButtonPB0Flag.
//! This function is called from the PB0 GPIO Interrupt routine.
//!
//! \param	void	input	No input arguments
//! \return	void	output	No input arguments
//--------------------------------------------------------------------------------------------------
static void SetButtonPB0Flag(void)
{
	ButtonPB0Flag = true;
}

//--------------------------------------------------------------------------------------------------
// static void ResetButtonPB1Flag(void)
//--------------------------------------------------------------------------------------------------
//! \brief	Reset function for actual state of ButtonPB1.
//!
//! This function is used to set the ButtonPB1Flag.
//! This function is called from the PB1 GPIO Interrupt routine.
//!
//! \param	void	input	No input arguments
//! \return	void	output	No input arguments
//--------------------------------------------------------------------------------------------------
static void ResetButtonPB1Flag(void)
{
	ButtonPB1Flag = false;
}

//--------------------------------------------------------------------------------------------------
// static void ResetButtonPB0Flag(void)
//--------------------------------------------------------------------------------------------------
//! \brief	Setter function for actual state of ButtonPB0.
//!
//! This function is used to set the ButtonPB0Flag.
//! This function is called from the PB0 GPIO Interrupt routine.
//!
//! \param	void	input	No input arguments
//! \return	void	output	No input arguments
//--------------------------------------------------------------------------------------------------
static void ResetButtonPB0Flag(void)
{
	ButtonPB0Flag = false;
}

//==================================================================================================
//  E N D   O F   F I L E
//==================================================================================================
