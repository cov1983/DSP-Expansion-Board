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

#include "mclk.h"

//==================================================================================================
//  M O D U L E   D E F I N E S
//==================================================================================================

//! Some module define
#define M_SOME_MODULE_DEFINE 0


//==================================================================================================
//  M O D U L E   T Y P E S
//==================================================================================================

//! Some module type
typedef enum {
	SomeModuleEnum_E1,		//!< Description of enum entry 1
	SomeModuleEnum_E2,		//!< Description of enum entry 2
	SomeModuleEnum_E3,		//!< Description of enum entry 3
} SomeModuleEnum_T;


//==================================================================================================
//  M O D U L E   V A R I A B L E S
//==================================================================================================

static int m_someModuleVariable = 0;	//!< Description of this variable


//==================================================================================================
//  F O R W A R D   D E C L A R A T I O N S
//==================================================================================================

static int SomeModuleFunction(int someInt, double someDouble);


//==================================================================================================
//  G L O B A L   F U N C T I O N   I M P L E M E N T A T I O N
//==================================================================================================

int HBU_TEMPLATE_SomeGlobalFunction(int someInt, double someDouble)
{
	return (SomeModuleFunction(someInt, someDouble));
}


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

void initMCLK(void)
{

}


//==================================================================================================
//  E N D   O F   F I L E
//==================================================================================================
