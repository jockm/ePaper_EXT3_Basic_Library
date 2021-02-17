///
/// @file       ePaper_EXT3_Basic_Library.h
/// @brief      Library header
/// @details    Driver for Pervasive Displays iTC BWR screens
/// @n
/// @n @b       Project highView Library Suite
///
/// @author     Rei Vilo
/// @author     http://embeddedcomputing.weebly.com
///
/// @date       11 Jan 2021
/// @version    release 501
///
/// @copyright  (c) Rei Vilo, 2010-2021
/// @copyright  Attribution-NonCommercial-ShareAlike 4.0 Unported (CC BY-NC-SA 4.0)
///
/// @details    The highView Library Suite is shared under the Creative Commons licence Attribution-NonCommercial-ShareAlike 4.0 Unported (CC BY-NC-SA 4.0).
/// @ see https://creativecommons.org/licenses/by-nc-sa/4.0/
///
/// * For hobbyists and for personal usage: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 Unported (CC BY-NC-SA 4.0)
///
/// * For professionals or organisations or for commercial usage: All rights reserved. Consider the advanced edition ePaper_EXT3_Advanced_Library which brings waivers for the NonCommercial ShareAlike clauses.
///
///
/// @see Sections based on https://github.com/PervasiveDisplays/ePaper_PervasiveDisplays
///


// Core library - IDE-based
#if defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#elif defined(ARDUINO) // Arduino general
#include "Arduino.h"
#else // error
#error Platform not defined
#endif // end IDE

#include "Screen_EPD_EXT3.h"
