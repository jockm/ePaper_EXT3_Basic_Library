///
/// @file		LCD_colours565.h
/// @brief  	Class library header
/// @details	Library for 5-6-5 coded colours
/// 
/// @n @b		Project LCD_screen Library Suite
///
/// @author		Rei Vilo
/// @author		https://embeddedcomputing.weebly.com
///
/// @date       11 Jan 2021
/// @version    release 501
///
/// @copyright    (c) Rei Vilo, 2010-2021
/// @copyright  Attribution-NonCommercial-ShareAlike 4.0 Unported (CC BY-NC-SA 4.0)
///


// Core library - IDE-based
#if defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#elif defined(ARDUINO) // Arduino general
#include "Arduino.h"
#else // error
#error Platform not defined
#endif // end IDE

#ifndef LCD_COLOURS_RELEASE
///
/// @brief  Library release number
///
#define LCD_COLOURS_RELEASE 501


///
/// @class      LCD_colours565
/// @brief      for 5-6-5 coded colours = 64K colours
/// @details    red: 5 bits, green: 6 bits, blue: 5 bits
///
class LCD_colours565
{
  public:
    ///
    /// @brief  Constructor
    ///
    LCD_colours565();

    ///
    /// @name   Colours constants
    /// @note   Both syntaxes are valid
    /// * myColours.black and
    /// * LCD_colours565::black
    /// with extern LCD_colours565 myColours; declared below
    ///
    // Colours RGB=565                 Red  Green Blue
    //                                 4321054321043210
    /// @{

    static const uint16_t black    = 0b0000000000000000; ///< black
    static const uint16_t white    = 0b1111111111111111; ///< white
    static const uint16_t red      = 0b1111100000000000; ///< red
    static const uint16_t green    = 0b0000011111100000; ///< green
    static const uint16_t blue     = 0b0000000000011111; ///< blue
    static const uint16_t yellow   = 0b1111111111100000; ///< yellow
    static const uint16_t cyan     = 0b0000011111111111; ///< cyan
    static const uint16_t orange   = 0b1111101111100000; ///< orange
    static const uint16_t magenta  = 0b1111100000001111; ///< magenta
    static const uint16_t violet   = 0b1111100000011111; ///< violet
    static const uint16_t grey     = 0b0111101111101111; ///< grey
    static const uint16_t darkGrey = 0b0011100111100111; ///< dark grey
    static const uint16_t brown    = 0b0111100000000000; ///< brown

    /// American-English variants
    static const uint16_t gray     = 0b0111101111101111; ///< American-English variant for grey
    static const uint16_t darkGray = 0b0011100111100111; ///< American-English variant for dark grey

    // e-Paper specific colours
    static const uint16_t darkRed  = 0b0011100000000000; ///<   dark red for BWR e-paper screens
    static const uint16_t lightRed = 0b1111100011100011; ///<   light red for BWR e-paper screens

    /// @}
};

///
/// @brief      Instantiated object
/// @details    myColours
///
extern LCD_colours565 myColours;

#endif // LCD_COLOURS_RELEASE