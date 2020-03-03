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

#include "ioexpander.h"

//==================================================================================================
//  M O D U L E   D E F I N E S
//==================================================================================================

#define I2C_IOEXP_ADDR			0x48

#define IOEXP_REG_IN_PORT0 		0x00		// Port0 Input Register Address
#define IOEXP_REG_IN_PORT1 		0x01		// Port1 Input Register Address
#define IOEXP_REG_OUT_PORT0 	0x02		// Port0 Output Register Address
#define IOEXP_REG_OUT_PORT1 	0x03		// Port1 Output Register Address
#define IOEXP_REG_POL_PORT0 	0x04		// Port0 Polarity Inversion Register Address
#define IOEXP_REG_POL_PORT1 	0x05		// Port1 Polarity Inversion Register Address
#define IOEXP_REG_CFG_PORT0 	0x06		// Port0 Configuration Register Address
#define IOEXP_REG_CFG_PORT1 	0x07		// Port1 Configuration Register Address

#define IOEXP_DIR_PORT0 		0x00		// Default Direction Value Port0 => All Outputs
#define IOEXP_DIR_PORT1 		0xe0		// Default Direction Value Port1 => P10-14 Outputs P15-17 Inputs

#define IOEXP_OUT_LOW_PORT0 	0x00		// Default Port0 Output Value => All LOW
#define IOEXP_OUT_LOW_PORT1 	0x00		// Default Port1 Output Value => All LOW

//==================================================================================================
//  M O D U L E   T Y P E S
//==================================================================================================

static uint8_t IOEXP_INIT_DIR_PORT0[]	=	{IOEXP_REG_CFG_PORT0, IOEXP_DIR_PORT0};		// Init Port0 Direction
static uint8_t IOEXP_INIT_DIR_PORT1[]	=	{IOEXP_REG_CFG_PORT1, IOEXP_DIR_PORT1};		// Init Port1 Direction

static uint8_t IOEXP_INIT_VAL_PORT0[]	=	{IOEXP_REG_OUT_PORT0, IOEXP_OUT_LOW_PORT0};	// Init Port0 Output State
static uint8_t IOEXP_INIT_VAL_PORT1[]	=	{IOEXP_REG_OUT_PORT1, IOEXP_OUT_LOW_PORT1};	// Init Port1 Output State

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
bool initIOexpander(void)
{
	static int8_t state = 0;

	static bool errorFlag = false;

	state += I2Cwrite(I2C_IOEXP_ADDR, IOEXP_INIT_DIR_PORT0, 2);
	state += I2Cwrite(I2C_IOEXP_ADDR, IOEXP_INIT_DIR_PORT1, 2);
	state += I2Cwrite(I2C_IOEXP_ADDR, IOEXP_INIT_VAL_PORT0, 2);
	state += I2Cwrite(I2C_IOEXP_ADDR, IOEXP_INIT_VAL_PORT1, 2);

	// Check if I2C Write was successful, if state not 0 -> NACK OR BUS ERROR
	if(state != 0) {errorFlag = true;}

	return errorFlag;

}


//==================================================================================================
//  M O D U L E   F U N C T I O N   I M P L E M E N T A T I O N
//==================================================================================================

//--------------------------------------------------------------------------------------------------
// static someModuleFunction(void)
//--------------------------------------------------------------------------------------------------
//! \brief	Setter function for actual state of ButtonPB1.
//!
//! This function is used to set the ButtonPB1Flag.
//! This function is called from the PB1 GPIO Interrupt routine.
//!
//! \param	void	input	No input arguments
//! \return	void	output	No input arguments
//--------------------------------------------------------------------------------------------------


//==================================================================================================
//  E N D   O F   F I L E
//==================================================================================================
