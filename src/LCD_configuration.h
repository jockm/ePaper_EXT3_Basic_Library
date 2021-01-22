///
/// @file		LCD_Configuration.h
/// @brief		Header
/// @details	Configuration of the options for ePaper EXT3 Basic Library
/// 
/// 1. CONFIGURATION_OPTION selects the hardware with pre-defined configurations.
/// 2. Based on CONFIGURATION_OPTION, GPIOs are defined.
/// 3. Large screens 9.7 and 12.2 require additional CSS24_PIN and CSS34_PIN
/// 4. USE_FONT_MODE defines the fonts used, here Terminal for the basic edition.
/// 5. MAX_FONT_SIZE sets the number of fonts, maximum 4 for the basic edition.
/// 
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
/// @name       Configuration
/// @details    Select pre-defined configurations
/// @note       Edit the pins in next section
/// @{
#define CONFIGURATION_BOOSTERPACK_EXT2 1 ///< default BoosterPack EXT3
#define CONFIGURATION_MSP5430FR5994 2 ///< specific MSP5430FR5994 as CGU
#define CONFIGURATION_RASPI 3 ///< specific Raspberry Pi
#define CONFIGURATION_REDBEAR_DUO 4 // specific REDBEAR_DUO
#define CONFIGURATION_CC1352 5 ///< specific CC1352

#define CONFIGURATION_OPTION CONFIGURATION_BOOSTERPACK_EXT3 ///< selected option
/// @}

///
/// @name       GPIOs for each configuration
/// @{
#if (CONFIGURATION_OPTION == CONFIGURATION_BOOSTERPACK_EXT2)
// --- Initial configuration
#warning Default pins for BoosterPack
#define PNLON_PIN 11 ///< EXT3 BOARD J5 pin 11
#define CS_PIN 19    ///< EXT3 BOARD J5 pin 19
#define DC_PIN 9     ///< EXT3 BOARD J5 pin 9
#define RESET_PIN 10 ///< EXT3 BOARD J5 pin 10
#define BUSY_PIN 8   ///< EXT3 BOARD J5 pin 8
#define FLASH_CS_PIN 18 ///< EXT3 BOARD J5 pin 18
// EXT3 BOARD 17 -> GROUND

#elif (CONFIGURATION_OPTION == CONFIGURATION_CC1352)
// --- CC1352 configuration
#warning Default pins for CC1352
#define PNLON_PIN 2  ///< EXT3 BOARD J5 pin 11 -> 2
#define CS_PIN 19    ///< EXT3 BOARD J5 pin 19
#define DC_PIN 9     ///< EXT3 BOARD J5 pin 9
#define RESET_PIN 10 ///< EXT3 BOARD J5 pin 10
#define BUSY_PIN 8   ///< EXT3 BOARD J5 pin 8
#define FLASH_CS_PIN 18 ///< EXT3 BOARD J5 pin 18
// EXT3 BOARD 17 -> GROUND

#elif (CONFIGURATION_OPTION == CONFIGURATION_MSP5430FR5994)
// --- MSP5430FR5994 configuration
#warning Modified pins for MSP5430FR5994 as CGU
#define PNLON_PIN 11 ///< EXT3 BOARD J5 pin 11
#define CS_PIN 19    ///< EXT3 BOARD J5 pin 19
#define DC_PIN 29    ///< EXT3 BOARD J5 pin 9 -> 29
#define RESET_PIN 30 ///< EXT3 BOARD J5 pin 10 -> 30
#define BUSY_PIN 28  ///< EXT3 BOARD J5 pin 8 -> 28
#define FLASH_CS_PIN 18 ///< EXT3 BOARD J5 pin 18 -> 18
// EXT3 BOARD 17 -> GROUND

#elif (CONFIGURATION_OPTION == CONFIGURATION_RASPI)
// --- Raspberry Pi configuration
#warning Modified pins for Raspberry Pi
#define PNLON_PIN 22 ///< EXT3 BOARD 11 -> GPIO22 pin 15
#define CS_PIN 8     ///< EXT3 BOARD 19 -> GPIO8 pin 24
#define DC_PIN 25    ///< EXT3 BOARD 9 -> GPIO25 pin 22
#define RESET_PIN 23 ///< EXT3 BOARD 10 -> GPIO23 pin 16
#define BUSY_PIN 24  ///< EXT3 BOARD 8 -> GPIO24 pin 18
#define FLASH_CS_PIN 18 ///< EXT3 BOARD 18 -> GPIO18 pin 12
// EXT3 BOARD 17 -> GROUND

#elif (CONFIGURATION_OPTION == CONFIGURATION_REDBEAR_DUO)
// --- REDBEAR_DUO configuration
#warning Modified pins for RedBear Duo
#define PNLON_PIN D5 ///< EXT3 BOARD J5 pin 11 -> D5
#define CS_PIN D6    ///< EXT3 BOARD J5 pin 19 -> D6
#define DC_PIN D3    ///< EXT3 BOARD J5 pin 9 -> D3
#define RESET_PIN D4 ///< EXT3 BOARD J5 pin 10 -> D4
#define BUSY_PIN D2  ///< EXT3 BOARD J5 pin 8 -> D2
#define PIN_EPD_FLASH_CS D14 ///< EXT3 BOARD J5 pin 18 -> D14
// EXT3 BOARD 17 -> GROUND

#else
#error Invalid CONFIGURATION_OPTION
#endif
/// @}

///
/// @name       Slave /CS for large screens
/// @details    9.7" and 12" screens have two sub-screens
///
/// @{
#define CSS24_PIN 2    ///< EXT3 BOARD J5 pin 2 for 24-pin flat cable
#define CSS34_PIN 13   ///< EXT3 BOARD J5 pin 13 for bridge board and 34-pin flat cable
/// @}

///
/// @name       Set font mode
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
