///
/// @file		LCD_configuration.h
/// @brief		Header
/// @details	Configuration of the options for ePaper EXT3 Basic Library
/// @n
/// @n @b       Project LCD_screen Library Suite
///
/// @author		Rei Vilo
/// @author		https://embeddedcomputing.weebly.com
///
/// @date       11 Jan 2021
/// @version    release 501
///
/// @copyright	(c) Rei Vilo, 2010-2021
/// @copyright  Attribution-NonCommercial-ShareAlike 4.0 Unported (CC BY-NC-SA 4.0)
///


// Core library for code-sense - IDE-based
// !!! Help: https://bit.ly/2AdU7cu
#if defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#elif defined(ARDUINO) // Arduino general
#include "Arduino.h"
#else // error
#error Platform not defined
#endif // end IDE


#ifndef LCD_CONFIGURATION_RELEASE
///
/// @brief	Release
///
#define LCD_CONFIGURATION_RELEASE 501

///
/// @brief      Set font mode
/// @details    From header files or from external flash
/// * Basic edition: Terminal font
/// * Advanced edition: DejaVu font as either header or Flash
/// @note       USE_FONT_HEADER requires addFont()
///
/// @{
#define USE_FONT_TERMINAL 0 ///< Use default Terminal fonts
#define USE_FONT_HEADER 1 ///< Use fonts from header files
#define USE_FONT_FLASH 2 ///< Use fonts from external Flash
#define USE_FONT_INTERNAL 3 ///< Use fonts from internal CGU
#define USE_FONT_MODE USE_FONT_TERMINAL ///< Selected option
/// @}

///
/// @brief      Number of fonts
/// @details    Each number includes the previous fonts
/// @note       Set number according to available Flash
///
/// Number | Font | Size | Cumulated
/// 1 | Terminal6x8e.h | 1344 | 1344
/// 2 | Terminal8x12e.h | 3584 | 4928
/// 3 | Terminal12x16e.h | 5376 | 10304
/// 4 | Terminal16x24e.h | 10752 | 21056
///
#define MAX_FONT_SIZE 4

#endif // LCD_CONFIGURATION_RELEASE
