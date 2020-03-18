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

#include "digital_inputs.h"

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

static bool DSPDetectionFlag = false;

//==================================================================================================
//  M O D U L E   F U N C T I O N   P R O T O T Y P E S
//==================================================================================================
static void setButtonPB1Flag(void);
static void setButtonPB0Flag(void);
static void resetButtonPB1Flag(void);
static void resetButtonPB0Flag(void);

static void setDSPDetectionFlag(void);
static void resetDSPDetectionFlag(void);

//==================================================================================================
//  I R Q   H A N D L E R S
//==================================================================================================

//--------------------------------------------------------------------------------------------------
// void GPIO_EVEN_IRQHandler()
//--------------------------------------------------------------------------------------------------
//! \brief	Handles GPIO events from even pin numbers.
//!
//! Handles the push button PB1 pressed event.
//! Handles the DSP Expansion Board Detection on CODEC_RST signal
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
			// Reset the associated flag if already active
			resetButtonPB1Flag();
		}
		else {
			// Set the associated flag
			setButtonPB1Flag();
		}
	}

	// Check if interrupt comes from CODEC_RST (Pin PC0)
	if (GPIO->IF & (1<<CODEC_RST_PIN))
	{
		// Clear interrupt flag
		GPIO->IFC = (1<<CODEC_RST_PIN);

		// Check if interrupt is on Rising or Falling Edge
		if (GPIO_PinInGet(gpioPortC, CODEC_RST_PIN))
		{
			// Set the associated flag
			setDSPDetectionFlag();
		}
		else {
			// Reset the associated flag
			resetDSPDetectionFlag();
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

		// Toggle function for button PB0 Flag
		if (ButtonPB0Flag)
		{
			// Reset the associated flag if already active
			resetButtonPB0Flag();
		}
		else {
			// Set the associated flag
			setButtonPB0Flag();
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

void initSTK3800Buttons(void)
{
	// PB0: input with pullup R
	GPIO_PinModeSet(gpioPortB, PB0PIN, gpioModeInputPull,HIGH);
	// PB1: input with pullup R
	GPIO_PinModeSet(gpioPortB, PB1PIN, gpioModeInputPull,HIGH);
	// PB0: enable interrupts on falling edge
	GPIO_ExtIntConfig( gpioPortB, PB0PIN, PB0PIN, false, true, true );
	// PB1: enable interrupts on falling edge
	GPIO_ExtIntConfig( gpioPortB, PB1PIN, PB0PIN, false, true, true );
}

//--------------------------------------------------------------------------------------------------
// bool GetButtonPB1Flag(void)
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

bool getButtonPB1Flag(void)
{
	return ButtonPB1Flag;
}

//--------------------------------------------------------------------------------------------------
// bool GetButtonPB0Flag(void)
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

bool getButtonPB0Flag(void)
{
	return ButtonPB0Flag;
}

//--------------------------------------------------------------------------------------------------
// void initDSPDetection(void)
//--------------------------------------------------------------------------------------------------
//! \brief	Setter function for actual state of ButtonPB1.
//!
//! This function is used to set the ButtonPB1Flag.
//! This function is called from the PB1 GPIO Interrupt routine.
//!
//! \param	void	input	No input arguments
//! \return	void	output	No input arguments
//--------------------------------------------------------------------------------------------------
void initDSPDetection(void)
{
	// PC0/CODEC_RST: input
	GPIO_PinModeSet(gpioPortC, CODEC_RST_PIN, gpioModeInputPullFilter, LOW);
	// PC0/CODEC_RST: enable interrupts on rising edge
	GPIO_ExtIntConfig(gpioPortC, CODEC_RST_PIN, CODEC_RST_PIN, true, true, true);
}

//--------------------------------------------------------------------------------------------------
// void initDSPDetection(void)
//--------------------------------------------------------------------------------------------------
//! \brief	Setter function for actual state of ButtonPB1.
//!
//! This function is used to set the ButtonPB1Flag.
//! This function is called from the PB1 GPIO Interrupt routine.
//!
//! \param	void	input	No input arguments
//! \return	void	output	No input arguments
//--------------------------------------------------------------------------------------------------
bool getDSPDetectionFlag(void)
{
	return DSPDetectionFlag;
}

//--------------------------------------------------------------------------------------------------
// void enableDigitalInterrupts(void)
//--------------------------------------------------------------------------------------------------
//! \brief	Setter function for actual state of ButtonPB1.
//!
//! This function is used to set the ButtonPB1Flag.
//! This function is called from the PB1 GPIO Interrupt routine.
//!
//! \param	void	input	No input arguments
//! \return	void	output	No input arguments
//--------------------------------------------------------------------------------------------------
void enableDigitalInterrupts(void)
{
	//Also enable GPIO interrupts on ARM CPU level
	// Clear pending interrupts before enabling them
	NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
	NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
	NVIC_EnableIRQ(GPIO_ODD_IRQn);
	NVIC_EnableIRQ(GPIO_EVEN_IRQn);
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
static void setButtonPB1Flag(void)
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
static void setButtonPB0Flag(void)
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
static void resetButtonPB1Flag(void)
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
static void resetButtonPB0Flag(void)
{
	ButtonPB0Flag = false;
}

//--------------------------------------------------------------------------------------------------
// static void setDSPDetectionFlag(void)
//--------------------------------------------------------------------------------------------------
//! \brief	Setter function for actual state of DSPDetection.
//!
//! This function is used to set the DSPDetectionFlag.
//! This function is called from the GPIO Interrupt routine.
//!
//! \param	void	input	No input arguments
//! \return	void	output	No input arguments
//--------------------------------------------------------------------------------------------------
static void setDSPDetectionFlag(void)
{
	DSPDetectionFlag = true;
}

//--------------------------------------------------------------------------------------------------
// static void resetDSPDetectionFlag(void)
//--------------------------------------------------------------------------------------------------
//! \brief	Setter function for actual state of DSPDetection.
//!
//! This function is used to set the DSPDetectionFlag.
//! This function is called from the GPIO Interrupt routine.
//!
//! \param	void	input	No input arguments
//! \return	void	output	No input arguments
//--------------------------------------------------------------------------------------------------
static void resetDSPDetectionFlag(void)
{
	DSPDetectionFlag = false;
}

//==================================================================================================
//  E N D   O F   F I L E
//==================================================================================================
