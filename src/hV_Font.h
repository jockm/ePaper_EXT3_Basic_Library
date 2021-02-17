///
/// @file       hV_Font.h
/// @brief      Header
/// @details    Font structure
/// @n
/// @n @b       Project highView Library Suite
/// @n @a       Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author     Rei Vilo
/// @author     https://embeddedcomputing.weebly.com
///
/// @date       19 Mar 2019
/// @version    504
///
/// @copyright  (c) Rei Vilo, 2013-2020
/// @copyright  All rights reserved
///
/// @see        ReadMe.txt for references
///


// Core library - IDE-based
#if defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#elif defined(ARDUINO) // Arduino 1.0 and 1.5 specific
#include "Arduino.h"
#else // error
#error Platform not defined
#endif // end IDE

#ifndef hV_FONT_HEADER_STRUCTURE_RELEASE
///
/// @brief    hV_Font release number
///
#define hV_FONT_HEADER_STRUCTURE_RELEASE 401

#include "hV_Configuration.h"

// The Arduino IDE doesn't allow to select the libraries, hence this condition.
#if (FONT_MODE == USE_FONT_TERMINAL)

///
/// @brief      Structure for character width
///
struct width_s
{
    uint16_t pixel; ///< width in pixel
    uint16_t index; ///< relative address
};

///
/// @brief    Structure for font
/// @note
///     * Kind of font: see details below
///     * Height: set during font generation
///     * Width: *width array: characters index and length
///     * maxWidth: to be calculated
///     * Bytes per character: see *width array
///     * Character definition: see *table array
///
/// @n Font kind
///     * 0x4-..0x1- 0b7654
///         - b7 = 0x8- = high definition, 2 bits per pixel
///         - b6 = 0x4- = Monospace
///         - b5 = 0x2- = Sans Serif
///         - b4 = 0x1- = Serif
///     * 0x-1..0x-f 0b3210
///         - b3 = 0x-8 = d8 = italic
///         - b2 = 0x-4 = d4 = bold
///         - b10 = 0x-0..0x-3 = d0..d3 = variant number
///
/// @bug    font_s.table needs to be uint8_t instead of unsigned short
/// @n      Otherwise on TM4C129, font_s.table written as uint16_t
///
struct font_s
{
    uint8_t kind;       ///< font description
    uint8_t height;     ///< general height in pixels
    uint8_t maxWidth;   ///< maximum width in pixels from *width array
    uint8_t first;      ///< number of first character, usually 32
    uint8_t number;     ///< number of characters, usually 96 or 224
};

#endif // USE_FONT_TERMINAL

#endif // hV_FONT_HEADER_STRUCTURE_RELEASE
