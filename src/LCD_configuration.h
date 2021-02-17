///
/// @file		LCD_Configuration.h
/// @brief		Header
/// @details	Configuration of the options for ePaper EXT3 Basic Library
///
/// 1. CONFIGURATION_OPTION selects the hardware with pre-defined configurations.
/// 2. Based on CONFIGURATION_OPTION, GPIOs are defined.
/// 3. FONT_MODE defines the fonts used, here Terminal for the basic edition. (Advanced edition)
/// 4. MAX_FONT_SIZE sets the number of fonts, maximum 4 for the basic edition.
/// 5. SRAM_MODE sets the memory either internal MCU or external SPI. (Advanced edition)
/// 6. Set USE_LCD_SCREEN to virtual object, recommended. (Advanced edition)
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
/// @copyright  Creative Commons - Attribution-NonCommercial-ShareAlike 4.0 Unported (CC BY-NC-SA 4.0)
///
/// @details    The LCD_screen Library Suite is shared under the Creative Commons licence Attribution-NonCommercial-ShareAlike 4.0 Unported (CC BY-NC-SA 4.0).
/// @ see https://creativecommons.org/licenses/by-nc-sa/4.0/
///
/// * For hobbyists and for personal usage: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 Unported (CC BY-NC-SA 4.0)
///
/// * For professionals or organisations or for commercial usage: All rights reserved. Consider the advanced edition ePaper_EXT3_Advanced_Library which brings waivers for the NonCommercial ShareAlike clauses.
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
/// @name       1- Configuration
/// @details    Select pre-defined configurations
/// @note       Edit the pins in next section
/// @{
#define CONFIGURATION_EXT3_LAUNCHPAD 1 ///< default LaunchPad for EXT3
#define CONFIGURATION_EXT3_MSP5430FR5994 2 ///< specific MSP5430FR5994 as CGU
#define CONFIGURATION_EXT3_RASPI 3 ///< specific Raspberry Pi
#define CONFIGURATION_EXT3_REDBEAR_DUO 4 // specific Particle Photon or ReadBear Duo
#define CONFIGURATION_EXT3_CC1352 5 ///< specific CC1352
#define CONFIGURATION_EXT3_ARDUINO_ZERO 6 ///< specific Arduino Zero or M0 Pro

#define CONFIGURATION_OPTION CONFIGURATION_EXT3_RASPI ///< selected option
/// @}

///
/// @name       2- GPIOs for each configuration
/// @{
#if (CONFIGURATION_OPTION == CONFIGURATION_EXT3_LAUNCHPAD)
// --- Initial configuration, tested
// Valid for MSP430 and MSP432 LaunchPad boards
#warning Default pins for EXT3_MSP432
#define PANEL_BUSY_PIN 11   ///< EXT3 pin 3 -> 11
#define PANEL_DC_PIN 12     ///< EXT3 pin 4 -> 12
#define PANEL_RESET_PIN 13  ///< EXT3 pin 5 -> 13
#define FLASH_CS_PIN 18     ///< EXT3 pin 8 -> 18
#define PANEL_CS_PIN 19     ///< EXT3 pin 9 -> 19
// If not used, comment out
#define PANEL_CSS_PIN 39    ///< EXT3 pin 12 -> 39
#define FLASH_CSS_PIN 38    ///< EXT3 pin 20 -> 38

#elif (CONFIGURATION_OPTION == CONFIGURATION_EXT3_CC1352)
// --- CC1352 configuration, tested
#warning Default pins for CC1352
#define PANEL_BUSY_PIN 5    ///< EXT3 pin 3 -> 5
#define PANEL_DC_PIN 6      ///< EXT3 pin 4 -> 6
#define PANEL_RESET_PIN 19  ///< EXT3 pin 5 -> 19
#define FLASH_CS_PIN 24     ///< EXT3 pin 8 -> 24
#define PANEL_CS_PIN 26     ///< EXT3 pin 9 -> 26
// If not used, comment out
//#define PANEL_CSS_PIN 27    ///< EXT3 pin 12 -> NC
#define FLASH_CSS_PIN 27    ///< EXT3 pin 20 -> 27

#elif (CONFIGURATION_OPTION == CONFIGURATION_EXT3_MSP5430FR5994)
// --- MSP5430FR5994 configuration, tested
#warning Modified pins for MSP5430FR5994 as CGU
#define PANEL_BUSY_PIN 28   ///< EXT3 pin 3 -> 28
#define PANEL_DC_PIN 19     ///< EXT3 pin 4 -> 19
#define PANEL_RESET_PIN 30  ///< EXT3 pin 5 -> 30
#define FLASH_CS_PIN 18     ///< EXT3 pin 8 -> 18
#define PANEL_CS_PIN 19     ///< EXT3 pin 9 -> 19
#define PANEL_CSS_PIN 39    ///< EXT3 pin 12 -> 39
#define FLASH_CSS_PIN 38    ///< EXT3 pin 20 -> 38

#elif (CONFIGURATION_OPTION == CONFIGURATION_EXT3_RASPI)
// --- Raspberry Pi configuration, tested
#warning Modified pins for Raspberry Pi
#define PANEL_BUSY_PIN 7    ///< EXT3 pin 3 -> GPIO7 pin 6
#define PANEL_DC_PIN 8      ///< EXT3 pin 4 -> GPIO8 pin 24
#define PANEL_RESET_PIN 25  ///< EXT3 pin 5 -> GPIO25 pin 8
#define FLASH_CS_PIN 22     ///< EXT3 pin 8 -> GPIO22 pin 15
#define PANEL_CS_PIN 27     ///< EXT3 pin 9 -> GPIO27 pin 13
// If not used, comment out
#define PANEL_CSS_PIN 23    ///< EXT3 pin 12 -> GPIO23 pin 16
#define FLASH_CSS_PIN 24    ///< EXT3 pin 20 -> GPIO24 pin 18

#elif (CONFIGURATION_OPTION == CONFIGURATION_EXT3_REDBEAR_DUO)
// --- REDBEAR_DUO configuration, tested
#warning Modified pins for Particle Photon or ReadBear Duo
#define PANEL_BUSY_PIN D5   ///< EXT3 pin 3 -> D5
#define PANEL_DC_PIN D4     ///< EXT3 pin 4 -> D4
#define PANEL_RESET_PIN D3  ///< EXT3 pin 5 -> D3
#define FLASH_CS_PIN D2     ///< EXT3 pin 8 -> D2
#define PANEL_CS_PIN D1     ///< EXT3 pin 9 -> D1
// If not used, comment out
#define PANEL_CSS_PIN D6    ///< EXT3 pin 12 -> D6
#define FLASH_CSS_PIN D0    ///< EXT3 pin 20 -> D0

#elif (CONFIGURATION_OPTION == CONFIGURATION_EXT3_ARDUINO_ZERO)
// --- ARDUINO_ZERO configuration, tested
#warning Default pins for ARDUINO_ZERO
#define PANEL_BUSY_PIN 4    ///< EXT3 pin 3 -> 4
// On Arduino Zero, pins D4 and D2 are reversed
#define PANEL_DC_PIN 5      ///< EXT3 pin 4 -> 5
#define PANEL_RESET_PIN 6   ///< EXT3 pin 5 -> 6
#define FLASH_CS_PIN 7      ///< EXT3 pin 8 -> 7
#define PANEL_CS_PIN 8      ///< EXT3 pin 9 -> 8
// If not used, comment out
#define PANEL_CSS_PIN 9     ///< EXT3 pin 12 -> 9
#define FLASH_CSS_PIN 10    ///< EXT3 pin 20 -> 10

// In case of use of SERCOM
#define SPI_CLOCK_PIN 13    ///< EXT3 pin 2 -> 13
#define SPI_CLOCK_MISO 11   ///< EXT3 pin 6 -> 11
#define SPI_CLOCK_MOSI 12   ///< EXT3 pin 7 -> 12

#else
#error Invalid CONFIGURATION_OPTION
#endif
/// @}

///
/// @name       3- Set font mode
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
#define FONT_MODE USE_FONT_TERMINAL ///< Selected option
/// @}

///
/// @brief      4- Maximum number of fonts
/// @details    With MCU Flash, based on available memory, check performed at compilation
/// * USE_FONT_TERMINAL: 1..4
/// * USE_FONT_HEADER: 1..64
///
/// Number | Font | Size | Cumulated
/// 1 | Terminal6x8e.h | 1344 | 1344
/// 2 | Terminal8x12e.h | 3584 | 4928
/// 3 | Terminal12x16e.h | 5376 | 10304
/// 4 | Terminal16x24e.h | 10752 | 21056
///
#define MAX_FONT_SIZE 4

///
/// @name       5- Set SRAM memory
/// @details    From internal MCU or external SPI
/// * Basic edition: MCU internal SRAM
/// * Advanced edition: MCU internal or SPI External SRAM
///

///
/// @name       6. Use virtual object
/// @details    From LCD_Screen_Virtual.h for extended compability
/// @note       If USE_LCD_SCREEN_SELF, declare additional variables
/// @n Virtual object requires ~1 kB bytes.
/// * Basic edition: self option
/// * Advanced edition: self and virtual options
///

#endif // LCD_CONFIGURATION_RELEASE
