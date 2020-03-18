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

#ifndef DIGITAL_INPUTS_H
#define DIGITAL_INPUTS_H


//==================================================================================================
//  I N C L U D E D   F I L E S
//==================================================================================================

#include "em_gpio.h"
#include "em_core.h"

#include <stdbool.h>

//==================================================================================================
//  S U P P O R T   F O R   M I X E D   C / C + +
//==================================================================================================

#ifdef __cplusplus
extern "C" {
#endif


//==================================================================================================
//  D E F I N I T I O N S
//==================================================================================================

#define PB0PIN 9 	// PB0 is on port B pin 9
#define PB1PIN 10	// PB1 is on port B pin 10

#define CODEC_RST_PIN 0

//==================================================================================================
//  M O D U L E   T Y P E S
//==================================================================================================

typedef enum logiclevels
{
	LOW  = 0,
	HIGH = 1
} LogicLevels_t;

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
void initSTK3800Buttons(void);
bool getButtonPB1Flag(void);
bool getButtonPB0Flag(void);

void initDSPDetection(void);
bool getDSPDetectionFlag(void);

void enableDigitalInterrupts(void);

#ifdef __cplusplus
}
#endif

#endif // HBU_TEMPLATE_H

//==================================================================================================
//  E N D   O F   F I L E
//==================================================================================================
