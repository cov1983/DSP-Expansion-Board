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

#include "codec.h"

//==================================================================================================
//  M O D U L E   D E F I N E S
//==================================================================================================

// I2C CODEC ADDRESS
#define I2C_CODEC_ADDR 0x30

//==================================================================================================
//  M O D U L E   T Y P E S
//==================================================================================================

//! Some module type

//==================================================================================================
//  M O D U L E   V A R I A B L E S
//==================================================================================================

// Initialize AIC3204 CODEC Block
static uint8_t AIC3204_SP0[] 		= {0, 0};			// Select page 0
static uint8_t AIC3204_RST[] 		= {1, 1};			// Reset CODEC
static uint8_t AIC3204_SP1[] 		= {0, 1};			// Select page 1
static uint8_t AIC3204_AVDD_OFF[] 	= {1, 8};			// Disable crude AVDD generation from DVDD
static uint8_t AIC3204_ANA_ON[] 	= {2, 1};			// Enable Analog Blocks, use LDO power

// CODEC Audio Interface Registers Setup
static uint8_t BCKL_WCKL[] 			= {27, 0x0D};		// BCLK and WCLK is set as output from AIC3204(Master)

// PLL & Clocks Setup Register Commands for sampling rate Fs = 48 kHz
static uint8_t PLL_CLKIN[] 			= {4, 3};			// PLL setting: PLL_CLKIN <- MCLK, CODEC_CLKIN <- PLL_CLK
static uint8_t PLL_PR[] 			= {5, 0x91};		// P = 1, R = 1 (and MSB is set to enable PLL)
static uint8_t PLL_J[]  			= {6, 7};			// J = 7
static uint8_t PLL_D_High_Byte[] 	= {7, 0x06};		// D = 1680 (decimal) or 0x0690 (hex)
static uint8_t PLL_D_Low_Byte[]  	= {8, 0x90};
static uint8_t BCLK_N_DIV[] 	   	= {30, 0x88};  		// BCLK N = 8 (decimal) or 0x08 (and MSB is set to enable divider)
static uint8_t DOSR_High_Byte[]  	= {13, 0x00};		// DOSR = 128 (decimal) or 0x0080
static uint8_t DOSR_Low_Byte[]   	= {14, 0x80};
static uint8_t AOSR[] 				= {20, 0x80};		// AOSR = 128 (decimal) or 0x80
static uint8_t NDAC[] 				= {11, 0x87};		// NDAC = 7 (decimal) or 0x07 (and MSB is set to enable divider)
static uint8_t MDAC[] 				= {12, 0x82};		// MDAC = 2 (decimal) or 0x02 (and MSB is set to enable divider)
static uint8_t NADC[] 				= {18, 0x87};		// same as NDAC
static uint8_t MADC[] 				= {19, 0x82};		// same as MDAC

// Setup Register Commands for Processing Blocks
static uint8_t PRB_P[] 				= {60, 1};			// Processing Block PRB_P1
static uint8_t PRB_R[] 				= {61, 1};			// Processing Block PRB_R1

// DAC ROUTING and Power Up
static uint8_t LDAC_HPL[] 			= {0x0c, 8};		// LDAC AFIR routed to HPL
static uint8_t RDAC_HPR[] 			= {0x0d, 8};		// LDAC AFIR routed to HPL
static uint8_t RDAC_GCTRL[] 		= {64, 2};			// Right DAC gain will be controlled by the Left DAC gain setting.  Also, unmute left and right channels
static uint8_t PWR_LRCH[] 			= {63, 0xd4};		// Power up left,right data paths and set channel
static uint8_t UNMUTE_10DB_HPL[] 	= {0x10, 10};		// Unmute HPL , 10dB gain
static uint8_t UNMUTE_10DB_HPR[] 	= {0x11, 10};		// Unmute HPR , 10dB gain
static uint8_t PWR_HPLHPR[] 		= {9, 0x30};		// Power up HPL,HPR

// ADC ROUTING and Power Up
static uint8_t IN1L_LADC_10K[] 		= {0x34, 0x40};		// IN1_L to LADC_P through 10 kOhm
static uint8_t IN1R_RADC_10K[] 		= {0x37, 0x40};		// IN1_R to RADC_P through 10 kOhm
static uint8_t CM1_LADC_10K[] 		= {0x36, 0x40};		// CM_1 (common mode) to LADC_M through 10 kohm
static uint8_t CM1_RADC_10K[] 		= {0x39, 0x40};		// CM_1 (common mode) to RADC_M through 10 kohm
static uint8_t PWR_LRADC[] 			= {0x51, 0xc0};		// Powerup Left and Right ADC
static uint8_t UNMUTE_LRADC[] 		= {0x52, 0};		// Unmute Left and Right ADC

// Setup Register Commands for ADC Digital Gain
static uint8_t Digital_ADC_Gain_L[] = {0x53, 0x00};		// ADC Digital Gain = 0dB L CHANNEL
static uint8_t Digital_ADC_Gain_R[] = {0x53, 0x00};		// ADC Digital Gain = 0dB R CHANNEL

// Flag for BiquadCoeff, standard 0 = Not loaded !
static uint8_t LoadBiquadCoeff  	= 0;				// set to 1 to load BIQUAD coefficients; else 0 (default: 0)


//==================================================================================================
//  M O D U L E   F U N C T I O N   P R O T O T Y P E S
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
bool pingCODEC(void)
{
	static int8_t state = 0;

	static bool pingPassed = true;

	// Select Page 0 Register Command for CODEC
	state = I2Cwrite(I2C_CODEC_ADDR, AIC3204_SP0 , 2);

	if(state != 0) {pingPassed = false;}

	return pingPassed;
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
bool initCODEC(void)
{
	static int8_t state = 0;

	static bool errorFlag = false;

	state += I2Cwrite(I2C_CODEC_ADDR, AIC3204_SP0 , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, AIC3204_RST , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, AIC3204_SP1 , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, AIC3204_AVDD_OFF , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, AIC3204_ANA_ON , 2);

	// Check if I2C Write was successful, if state not 0 -> NACK OR BUS ERROR
	if(state != 0) {errorFlag = true;}

	return errorFlag;
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
bool setSampling48CODEC(void)
{
	static int8_t state = 0;

	static bool errorFlag = false;

	// PLL and Clocks Configuration and Power Up
	state += I2Cwrite(I2C_CODEC_ADDR, AIC3204_SP0 , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, BCKL_WCKL , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, PLL_CLKIN , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, PLL_J , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, PLL_D_High_Byte , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, PLL_D_Low_Byte , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, BCLK_N_DIV , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, PLL_PR , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, DOSR_High_Byte , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, DOSR_Low_Byte , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, AOSR , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, NDAC , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, MDAC , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, NADC , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, MADC , 2);

	// Check if I2C Write was successful, if state not 0 -> NACK OR BUS ERROR
	if(state != 0) {errorFlag = true;}

	return errorFlag;
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
bool setProcessingBlocksCODEC(void)
{
	static int8_t state = 0;

	static bool errorFlag = false;

	// Configure Processing Blocks
	state += I2Cwrite(I2C_CODEC_ADDR, AIC3204_SP0 , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, PRB_P , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, PRB_R , 2);

	// Check if I2C Write was successful, if state not 0 -> NACK OR BUS ERROR
	if(state != 0) {errorFlag = true;}

	return errorFlag;
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
bool setDacHPCODEC(void)
{
	static int8_t state = 0;

	static bool errorFlag = false;

	// DAC ROUTING and Power Up
	state += I2Cwrite(I2C_CODEC_ADDR, AIC3204_SP1 , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, LDAC_HPL , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, RDAC_HPR , 2);

	state += I2Cwrite(I2C_CODEC_ADDR, AIC3204_SP0 , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, RDAC_GCTRL , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, PWR_LRCH , 2);

	state += I2Cwrite(I2C_CODEC_ADDR, AIC3204_SP1 , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, UNMUTE_10DB_HPL , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, UNMUTE_10DB_HPR , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, PWR_HPLHPR , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, AIC3204_SP0 , 2);

	// Check if I2C Write was successful, if state not 0 -> NACK OR BUS ERROR
	if(state != 0) {errorFlag = true;}

	return errorFlag;
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
bool setAdcIN2CODEC(void)
{
	static int8_t state = 0;

	static bool errorFlag = false;

	// ADC ROUTING and Power Up
	state += I2Cwrite(I2C_CODEC_ADDR, AIC3204_SP1 , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, IN1L_LADC_10K , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, IN1R_RADC_10K , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, CM1_LADC_10K , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, CM1_RADC_10K , 2);

	state += I2Cwrite(I2C_CODEC_ADDR, AIC3204_SP0 , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, PWR_LRADC , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, UNMUTE_LRADC , 2);

	// Check if I2C Write was successful, if state not 0 -> NACK OR BUS ERROR
	if(state != 0) {errorFlag = true;}

	return errorFlag;
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
bool setAdcDigitalGainCODEC(void)
{
	static int8_t state = 0;

	static bool errorFlag = false;

	// set digital gain
	state += I2Cwrite(I2C_CODEC_ADDR, AIC3204_SP0 , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, Digital_ADC_Gain_L , 2);
	state += I2Cwrite(I2C_CODEC_ADDR, Digital_ADC_Gain_R , 2);

	// Check if I2C Write was successful, if state not 0 -> NACK OR BUS ERROR
	if(state != 0) {errorFlag = true;}

	return errorFlag;
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
bool enableCodecLINtoHPplayback(void)
{
	static bool errorFlag = false;
	static bool doneConfig = false;

	// CODEC SETUP LINE IN TO HP OUT AT FS = 48KHZ

	while (!doneConfig)
	{
		// CODEC Base Initialization (LDO Power)
		if(!initCODEC()){errorFlag = true; break;}
		// CODEC PLL & Clocks Initialization
		if(!setSampling48CODEC()){errorFlag = true; break;}
		// CODEC Configure Processing Blocks
		if(!setProcessingBlocksCODEC()){errorFlag = true; break;}
		// CODEC DAC Routing & Power Up
		if(!setDacHPCODEC()){errorFlag = true; break;}
		// CODEC ADC Routing & Power Up
		if(!setAdcIN2CODEC()){errorFlag = true; break;}
		// CODEC Set Default Digital Gain ADC L&R 0dB
		if(!setAdcDigitalGainCODEC()){errorFlag = true; break;}

		// Set donConfig flag
		doneConfig = true;
	}
	return errorFlag;
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

//==================================================================================================
//  E N D   O F   F I L E
//==================================================================================================
