///
/// @file       LCD_documentation.h
/// @brief      Documentation for the ePaper EXT3 Basic Library
/// @details    Additional documentation on coordinates, fonts and colours
///
/// @n The ePaper_EXT3_Basic_Library is a special edition of the LCD_screen Library Suite for the Pervasive Displays e-paper screens and EXT3 extension board.
///
/// @n @a   Member of LCD_screen Library Suite
/// @n      For Arduino and Energia
///
///
/// @author     Rei Vilo
/// @author     https://embeddedcomputing.weebly.com
///
/// @date       11 Jan 2021
/// @version    release 501
/// 
/// @copyright  (c) Rei Vilo, 2010-2021
/// @copyright  CC BY-NC-SA 4.0
///
/// @n Licence:
/// * For hobbyists and for personal usage: [Attribution-NonCommercial-ShareAlike 4.0 Unported (CC BY-NC-SA 4.0)](https://creativecommons.org/licenses/by-nc-sa/4.0/)
/// * For professionals or organisations or for commercial usage: All rights reserved. Consider the ePaper_EXT3_Advanced_Library
///

///
/// @mainpage  EPD EXT3 BWR eScreen Basic Library
/// @details The ePaper_EXT3_Basic_Library is a special edition of the LCD_screen Library Suite for the Pervasive Displays e-paper screens and EXT3 extension board.
///
/// The ePaper_EXT3_Basic_Example.ino example showcases the features the library and how to use it.
///
/// Use LCD_configuration.h to select the configuration for GPIOs and SPI bus.
/// 
///
/// @author     Rei Vilo
/// @author     https://embeddedcomputing.weebly.com
///
/// @date       11 Jan 2021
/// @version    release 501
///
/// @copyright  (c) Rei Vilo, 2010-2021
/// @copyright  Attribution-NonCommercial-ShareAlike 4.0 Unported (CC BY-NC-SA 4.0)
///
/// @b Licence:
/// * For hobbyists and for personal usage: Attribution-NonCommercial-ShareAlike 4.0 Unported (CC BY-NC-SA 4.0)
/// * For professionals or organisations or for commercial usage: All rights reserved. Consider the ePaper_EXT3_Advanced_Library
///


///
/// @page       Documentation Additional documentation
/// @details    This section includes additional documentation on copyright and licence, structure, initialisation, coordinates, colour, SD-card and resources
///
/// @section    Copyright Copyright and licence
/// @details    The LCD_screen Library Suite is shared under dual licence:
/// * For hobbyists and for personal usage: Attribution-NonCommercial-ShareAlike 4.0 Unported (CC BY-NC-SA 4.0)
/// * For professionals or organisations or for commercial usage: All rights reserved. Consider the ePaper_EXT3_Advanced_Library
///
/// @section    Structure Library structure
/// @details    The LCD_screen Library Suite contains three layers:
/// * top level end-user libraries like GUI.h with label, button, dialog, menu or slider with, and Graphics.h with  graphics.
/// * intermediate level screen-specific libraries, ie. ePaper_EXT3_Basic_Library.h
/// * low level virtual classes, ie. LCD_screen_buffer or LCD_Font_Terminal.h
///
///
/// @section    Version Version management
/// @brief      This section details the management and control of each library part of the Serial_LCD Library Suite.
/// @details    Each library has a release number to be checked at pre-processing.
///
/// Each library has its own release number.
/// @code {.cpp}
///  #define LCD_FONT_RELEASE 105
/// @endcode
///
/// The release number is checked at pre-processing
/// @code {.cpp}
///  #include "LCD_screen_font.h"
///
///  #if LCD_FONT_RELEASE < 106
///  #error Required LCD_FONT_RELEASE 106
///  #endif
/// @endcode
///
/// In this example, if the LCD_screen_font library release  is 105, the pre-processor prompts an error message:
/// @code {.cpp}
///  #error Required LCD_FONT_RELEASE 106
/// @endcode
///
///
/// @section    Screen Screens
/// @brief      This section explains the different screen features exposed by the library.
/// @details    Each screen is driven by a controller, and each controller provides different features.
///
/// @n A readable screen allows to get the colour of one specific pixel.
/// @code {.cpp}
///     uint16_t colour;
///     if (myScreen.isReadable()) {
///         colour = myScreen.readPixel(10, 10);
///     }
/// @endcode
///
/// If the screen isn't readable, LCD_screen::isReadable() is false and LCD_screen::readPixel() returns 0.
/// @n The LCD_screen::readPixel() function is required by the LCD_screen::copyPasteArea() and LCD_screen::copyArea() functions.
///
///
/// @section    Storage Storage
/// @brief      This section explains the different kinds of storage used used by the library.
/// @details    The GUI library saves the initial screen before displaying a dialog box, a menu or a slider, to restore it afterwards.
///
/// A storage can be:
/// * external SRAM
/// * SD-card
///
/// The function LCD_screen::isStorage() returns true is a storage is available.
///
/// The storage is required by the LCD_screen::copyArea() and LCD_screen::pasteArea() functions.
/// * LCD_screen::copyArea() copies an area from the screen and saves it to the SRAM or SD-card
/// * LCD_screen::pasteArea() reads an area from the SRAM or SD-card and pastes it to the screen
///
/// The MCU SRAM is used for the LCD_screen::copyPasteArea() function.
///
///
/// @section    Coordinate Coordinates systems
/// @brief      This section explains the rectangle and vector coordinates systems.
/// @details    Two systems of coordinates are used, rectangle and vector coordinates.
///
/// @b Rectangle coordinates include two points P1 and P2.
/// * P1 is a pixel on the top left, with (x1, y1) coordinates.
/// * P2 is a pixel on the bottom right, with (x2, y2) coordinates.
///
/// @a  Example rectangle (0, 0) - (319, 239)
///
/// @b Vector coordinates include one point P0 and one distance.
/// * P0 is a pixel and the origin, with (x0, y0) coordinates.
/// * The distance (dx, dy) is specified for the horizontal and the vertical axis.
///
/// @a Example vector (0, 0) - (320, 240)
/// @n Going from pixel 0 to pixel 319 represents 320 pixels in total
///
///
/// @section    Fonts   Fonts
/// @brief      This section explains how to use the fonts.
/// @details    Starting release 226, LCD_screen includes fixed and variable sized fonts.
///
/// The basic edition supplies four extended fonts:
///
/// Font | Name | Size | Bytes | Cumulated
/// --- | --- | --- | --- | ---
/// 0 | Terminal6x8e | 6 x 8 | 1344 | 1344
/// 1 | Terminal8x12e | 8 x 12 | 3584 | 4928
/// 2 | Terminal12x16e | 12 x 16 | 5376 | 10304
/// 3 | Terminal16x24e | 16 x 24 | 10752 | 21056
///
/// The advanced edition brings fixed Mono and variable Serif and Sans Serif based on the DejaVu font.
///
/// * All the fonts include the extended characters 0x80~0xff corresponding to the ISO-8859-1 fonts page.
/// * To convert UTF-8 strings to ISO-8859-1 strings, use the utf2iso() utility.
///
///
/// @section    Value Values using integer numbers
/// @brief      This section explains how values are coded using integer numbers only.
/// @details    Using integers only allows to avoid loading the library for real numbers, which requires 6 KB of memory.
///
/// A value are coded using two numbers:
/// * a significand, int32_t number, already multiplied by unit
/// * plus a multiplier, int32_t unit, with default=1, 10 or 100
///
/// value = number / unit = significand / multiplier
///
/// The unit provides the scale of the degrees passed.
///
/// The following calls of the draw() function are equivalent:
///
/// @code{.cpp}
///     draw(90);        // = 90 / 1
///     draw(90, 1);     // = 90 / 1
///     draw(9000, 100); // = 9000 / 100
/// @endcode
///
/// Functions like cos32x100 and sin32x100 receive and return values multiplied by 100.
/// The unit is set at 100.
/// * int32_t cos32x100(int32_t degreesX100)
/// * int32_t sin32x100(int32_t degreesX100)
///
/// int32_t are used instead of int64_t because some platforms don't manage 64-bit numbers.
///
/// @see
/// * Wikipedia on Floating points and Significand
/// @n https://en.wikipedia.org/wiki/Floating_point and https://en.wikipedia.org/wiki/Significand
///
///
/// @section    Colour Colours
/// @brief      This section explains how the colours are coded in 16-bit colours and 8-bits Red-Green-Blue components.
/// @details    Colours are coded internally on 16 bits, with 5 bits for red, 6 bits for green and 5 bits for blue, or called RGB565.
///
/// The Red-Green-Blue components are 8-bit sized and 0x00..0xff scaled.
///
/// The BW e-paper screens provides 2 basic colours. Combining those 2 basic colours gives an additional shade, totaling 3 colours.
///
/// * white: basic colour
/// * black: basic colour
/// * grey: combined colour, one dot black, another dot white
///
/// The BWR e-paper screens provides 3 basic colours. Combining those 3 basic colours gives two additional shades, totaling 6 colours.
///
/// * white: basic colour
/// * black: basic colour
/// * grey: combined colour, one dot black, another dot white
/// * red: basic colour
/// * light red: combined colour, one dot red, another dot white
/// * dark red: combined colour, one dot red, another dot black
///
///
/// @section    Port Porting to another SDK
/// When porting the example to another SDK,
/// define main() and call setup() and loop() as follow:
///
/// @code
/// // Prototypes
/// void setup();
/// void loop();
///
/// int main(void)
/// {
///     setup();
///
///     while (1)
///     {
///         loop();
///     }
///     return 0;
/// }
/// @endcode
///
///
/// @section    Resource Other resources
/// @brief      More resources are available online.
/// @details    The LCD_screen Library Suite is supported by the dedicated Embedded Computing website at https://embeddedcomputing.weebly.com
///
/// @see from Embedded Computing website:
/// * [Main page](https://embeddedcomputing.weebly.com/serial-lcd.html)
/// * [Download](https://embeddedcomputing.weebly.com/download.html)
/// * Former [Tutorials](https://embeddedcomputing.weebly.com/tutorials.html)
/// * Former [Examples](https://embeddedcomputing.weebly.com/examples.html)
/// * Former [Tutorial 3: FAQ](https://embeddedcomputing.weebly.com/tutorial-3-faq.html)
/// * Former [LCD_screen Library Suite](https://embeddedcomputing.weebly.com/lcd_screen-library-suite.html)
/// * [Fonts and font generator](http://www.mikroe.com)
/// * [DejaVu Fonts](http://dejavu-fonts.org/wiki/Main_Page)
///

