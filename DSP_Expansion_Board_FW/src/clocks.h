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

#ifndef CLOCKS_H
#define CLOCKS_H


//==================================================================================================
//  I N C L U D E D   F I L E S
//==================================================================================================

#include "em_cmu.h"

//==================================================================================================
//  S U P P O R T   F O R   M I X E D   C / C + +
//==================================================================================================

#ifdef __cplusplus
extern "C" {
#endif


//==================================================================================================
//  G L O B A L   D E F I N I T I O N S
//==================================================================================================

//! Some global define
#define HBU_TEMPLATE_SOME_GLOBAL_DEFINE 0


//==================================================================================================
//  G L O B A L   T Y P E S
//==================================================================================================

//! Some global type
typedef enum {
	HBU_TEMPLATE_SomeGlobalEnum_E1,		//!< Description of enum entry 1
	HBU_TEMPLATE_SomeGlobalEnum_E2,		//!< Description of enum entry 2
	HBU_TEMPLATE_SomeGlobalEnum_E3,		//!< Description of enum entry 3
} HBU_TEMPLATE_SomeGlobalEnum_T;


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
void InitClk(void);

void enableMCLK(void);
void disableMCLK(void);


#ifdef __cplusplus
}
#endif

#endif // HBU_TEMPLATE_H

//==================================================================================================
//  E N D   O F   F I L E
//==================================================================================================
