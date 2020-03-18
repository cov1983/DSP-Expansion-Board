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

#ifndef SYSTEM_H
#define SYSTEM_H


//==================================================================================================
//  I N C L U D E D   F I L E S
//==================================================================================================

#include <stdbool.h>

#include "em_chip.h"   		// emlib chip errata

#include "clocks.h"			// Include Clocks Module
#include "delay.h"			// Include Delay Module
#include "digital_inputs.h"	// Include Buttons Module
#include "leds.h"			// Include LEDs Module
#include "i2c.h"			// Include I2C Module
#include "i2s.h"			// Include I2S Module

#include "ioexpander.h"		// Include IOExpander Module

//==================================================================================================
//  S U P P O R T   F O R   M I X E D   C / C + +
//==================================================================================================

#ifdef __cplusplus
extern "C" {
#endif


//==================================================================================================
//  D E F I N I T I O N S
//==================================================================================================


//==================================================================================================
//  M O D U L E   T Y P E S
//==================================================================================================


//==================================================================================================
//  G L O B A L   F U N C T I O N   D E C L A R A T I O N
//==================================================================================================

//--------------------------------------------------------------------------------------------------
// HBU_TEMPLATE_SomeGlobalFunction
//--------------------------------------------------------------------------------------------------
//! \brief	A brief explanation of this functions's functionality goes here.
//!
//! A more detailed explanation of this functions's functionality goes here,
//! which may go over several lines.
//!
//! \param	someInt		input	Description of parameter someInt
//! \param	someDouble	input	Description of parameter someDouble
//! \return	Description of the return value
//! 		-  0 = Nothing
//! 		- >0 = Number of something
//--------------------------------------------------------------------------------------------------
void initSTK3800(void);
void enableDSPInterface(void);
bool initDSPBoard(void);


#ifdef __cplusplus
}
#endif

#endif // HBU_TEMPLATE_H

//==================================================================================================
//  E N D   O F   F I L E
//==================================================================================================
