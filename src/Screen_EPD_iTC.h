///
/// @file       Screen_EPD_iTC.h
/// @brief      Library header
/// @details    Driver for Pervasive Displays iTC BWR screens
/// @n
/// @n @b       Project LCD_screen Library Suite
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
/// @n Dual licence:
/// * For hobbyists and for personal usage: Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
/// * For professionals or organisations or for commercial usage: All rights reserved. Consider the advanced edition ePaper_EXT3_Advanced_Library.
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

#ifndef SCREEN_EPD_ITC_RELEASE
///
/// @brief	Library release number
///
#define SCREEN_EPD_ITC_RELEASE 501

#include "LCD_Configuration.h"

// Set parameters
// * Edit LCD_Configuration.h

// Other libraries
#include "LCD_Screen_Buffer.h"

#if LCD_SCREEN_BUFFER_RELEASE < 501
#error Required LCD_SCREEN_BUFFER_RELEASE 501
#endif

#include "SPI.h"

///
/// @name	List of supported Pervasive Displays screens
/// 
enum eScreen_iTC_BWR_t
{
    eScreen_EPD_iTC_154_BWR, ///< iTC 1.54 BWR 152 x 152 x 2
    eScreen_EPD_iTC_213_BWR, ///< iTC 2.13 BWR 104 x 212 x 2
    eScreen_EPD_iTC_266_BWR, ///< iTC 2.66 BWR 152 x 296 x 2
    eScreen_EPD_iTC_271_BWR, ///< iTC 2.71 BWR 176 x 264 x 2
    eScreen_EPD_iTC_287_BWR, ///< iTC 2.87 BWR 296 x 128 x 2
    eScreen_EPD_iTC_370_BWR, ///< iTC 3.70 BWR 416 x 240 x 2
    eScreen_EPD_iTC_420_BWR, ///< iTC 4.20 BWR 300 x 400 x 2
    eScreen_EPD_iTC_437_BWR, ///< iTC 4.37 BWR 480 x 176 x 2
    eScreen_EPD_iTC_565_BWR, ///< iTC 5.65 BWR 600 x 448 x 2
    eScreen_EPD_iTC_581_BWR, ///< iTC 5.81 BWR 720 x 256 x 2
    eScreen_EPD_iTC_740_BWR, ///< iTC 7.40 BWR 480 x 800 x 2
    eScreen_EPD_iTC_970_BWR, ///< iTC 9.70 BWR 960 x 672 x 2
    eScreen_EPD_iTC_1220_BWR, ///< iTC 12.20 BWR 960 x 768 x 2
};
/// 

///
/// @name      Frame buffer sizes
/// @details    Frame buffer size = width * height / 8 * depth, uint32_t
/// @note       Only one frame buffer is required.
/// @n          Depth = 2 for black-white-red screen
///
#define frameSize_EPD_iTC_154_BWR (uint32_t)(5776)
#define frameSize_EPD_iTC_213_BWR (uint32_t)(5512)
#define frameSize_EPD_iTC_266_BWR (uint32_t)(11248)
#define frameSize_EPD_iTC_271_BWR (uint32_t)(11616)
#define frameSize_EPD_iTC_287_BWR (uint32_t)(9472)
#define frameSize_EPD_iTC_370_BWR (uint32_t)(24960)
#define frameSize_EPD_iTC_420_BWR (uint32_t)(30000)
#define frameSize_EPD_iTC_437_BWR (uint32_t)(21120)
#define frameSize_EPD_iTC_565_BWR (uint32_t)(33600)
#define frameSize_EPD_iTC_581_BWR (uint32_t)(46080)
#define frameSize_EPD_iTC_740_BWR (uint32_t)(96000)
#define frameSize_EPD_iTC_970_BWR (uint32_t)(161280)
#define frameSize_EPD_iTC_1220_BWR (uint32_t)(184320)

// Objects
//
///
/// @name   List of supported screens
/// @n      All screens are iTC and BWR or BWY
///
/// Screen |  ms  |  s | Buffer size | Link
/// ----  |  ----  |  ---- |  ---- |  ----
/// 1.54 BWR | 15781 | 16 | 5776 | https://www.pervasivedisplays.com/product/1-54-e-ink-display-spectra-e4/
/// 1.54 BWY | 35470 | 36 | 5776 | https://www.pervasivedisplays.com/product/1-54-e-ink-display-yellow/
/// 2.13 BWR | 12504 | 13 | 5512 | https://www.pervasivedisplays.com/product/2-13-e-ink-display-spectra-e4/
/// 2.13 BWY | 34207 | 35 | 5512 | https://www.pervasivedisplays.com/product/2-13-e-ink-display-yellow/
/// 2.66 BWR | 18833 | 19 | 11248 | https://www.pervasivedisplays.com/product/2-66-e-ink-display-spectra-e4/
/// 2.66 BWY | 31011 | 32 | 11248 | https://www.pervasivedisplays.com/product/2-66-e-ink-display-yellow/
/// 2.71 BWR | 14372 | 15 | 11616 | https://www.pervasivedisplays.com/product/2-71-e-ink-display-spectra-e4/
/// 2.71 BWY |  |  | 11616 | http://www.pervasivedisplays.com/products/271i
/// 2.87 BWR | 13201 | 14 | 9472 | https://www.pervasivedisplays.com/product/2-87-e-ink-display-spectra-e4/
/// 2.87 BWY |  |  | 9472 |
/// 3.70 BWR | 19626 | 20 | 24960 | https://www.pervasivedisplays.com/product/3-7-e-ink-display/
/// 4.20 BWR | 18872 | 19 | 30000 | https://www.pervasivedisplays.com/product/4-2-e-ink-display-spectra-e4/
/// 4.20 BWY | 31497 | 32 | 30000 | https://www.pervasivedisplays.com/product/4-2-e-ink-display-yellow/
/// 4.37 BWR | 20248 | 21 | 21120 | https://www.pervasivedisplays.com/product/4-37-e-ink-display-spectra-e4/
/// 4.37 BWY | 30101 | 31 | 21120 | https://www.pervasivedisplays.com/product/4-37-e-ink-display-yellow/
/// 5.65 BWR | | | 33600 |
/// 5.81 BWR | 62666 | 63 | 46080 | https://www.pervasivedisplays.com/product/5-8-e-ink-display-spectra-e4/
/// 7.40 BWR | 35379 | 32 | 96000 | https://www.pervasivedisplays.com/product/7-4-e-ink-display-spectra-e4/
/// 7.40 BWY | 48736 | 49 | 96000 |https://www.pervasivedisplays.com/product/7-4-e-ink-display-yellow/
/// 9.70 BWR | 55663 | 46 | 161280 | https://www.pervasivedisplays.com/product/9-7-e-ink-display-spectra-e4/
/// 12.20 BWR | 44426 | 45 | 184320 | https://www.pervasivedisplays.com/product/12-2-e-ink-display-spectra-e4/
/// 12.20 BWY | 55475 | 56 | 184320 | https://www.pervasivedisplays.com/product/12-2-e-ink-display-yellow/
///

///
/// @brief      Class for Pervasive Displays iTC BWR screens
/// @details    Screen controllers
/// * LCD: propietary, SPI
///
/// @note Contrary to eTC, only one frame-buffer is required for iTC BWR.
///
/// @n  All commands work on the frame-buffer,
///     to be displayed on screen with flush()
///
class Screen_iTC_BWR : public LCD_Screen_Buffer
{
  public:
    ///
    /// @brief  Constructor with default pins
    /// @param  eScreen_iTC_BWR size and model of the e-screen
    /// @note   To be used with begin() with no parameter
    ///
    Screen_iTC_BWR(eScreen_iTC_BWR_t eScreen_iTC_BWR);

    ///
    /// @brief  Initialisation
    /// @note   Frame-buffer generated internally
    ///
    void begin();

    ///
    /// @brief  Who Am I
    /// @return Who Am I string
    ///
    String WhoAmI();

    ///
    /// @brief  Clear the screen
    /// @param  colour default=white
    /// @note   Clear next frame-buffer
    ///
    void clear(uint16_t colour = myColours.white);

    ///
    /// @brief  Invert screen
    /// @param  flag true to invert, false for normal screen
    ///
    void invert(bool flag);

    ///
    /// @brief  Update the display
    /// @note   Display next frame-buffer on screen,
    ///         and copy next frame-buffer into old frame-buffer
    ///
    void flush();

    ///
    /// @brief  Draw pixel
    /// @param  x1 point coordinate, x-axis
    /// @param  y1 point coordinate, y-axis
    /// @param  colour 16-bit colour
    ///
    /// @n @b   More: @ref Coordinate, @ref Colour
    ///
    void point(uint16_t x1, uint16_t y1, uint16_t colour);

    ///
    /// @brief  Read pixel colour
    /// @param  x1 point coordinate, x-axis
    /// @param  y1 point coordinate, y-axis
    /// @return 16-bit colour, bits 15-11 red, bits 10-5 green, bits 4-0 blue
    ///
    /// @n @b   More: @ref Coordinate, @ref Colour
    ///
    uint16_t readPixel(uint16_t x1, uint16_t y1);

    ///
    /// @brief  Screen refresh time for the BWR screens
    /// @return Estimated refresh time in seconds
    ///
    uint8_t getRefreshTime();

    ///
    /// @brief  Get the details of the selected font
    /// @return font_s structure
    ///
    font_s getFontDetails();

  protected:
    /// @cond

    ///
    /// @brief  General reset
    /// @param  ms1 delay after PNLON_PIN, ms
    /// @param  ms2 delay after RESET_PIN HIGH, ms
    /// @param  ms3 delay after RESET_PIN LOW, ms
    /// @param  ms4 delay after RESET_PIN HIGH, ms
    /// @param  ms5 delay after CS_PIN CSS_PIN HIGH, ms
    ///
    void _reset(uint32_t ms1, uint32_t ms2, uint32_t ms3, uint32_t ms4, uint32_t ms5);

    // * Virtual =0 compulsory functions
    // Screen-specific
    ///
    /// @brief  Send data through SPI
    /// @param  index register
    /// @param  data data
    /// @param  len number of bytes
    /// @note   Valid for all screens except 12.20"
    ///
    void _sendIndexData(uint8_t index, const uint8_t *data, uint32_t len);

    ///
    /// @brief  Send data through SPI to first half of 12.2" screen
    /// @param  index register
    /// @param  data data
    /// @param  len number of bytes
    /// @note   Valid only for 12.20" screen
    ///
    void _sendIndexDataMaster(uint8_t index, const uint8_t *data, uint32_t len);

    /// @brief  Send data through SPI to second half of 12.2" screen
    /// @param  index register
    /// @param  data data
    /// @param  len number of bytes
    /// @note   Valid only for 12.20" screen
    ///
    void _sendIndexDataSlave(uint8_t index, const uint8_t *data, uint32_t len);

    // Orientation
    ///
    /// @brief    Set orientation
    /// @param    orientation 1..3, 6, 7
    ///
    void _setOrientation(uint8_t orientation) ; // compulsory

    ///
    /// @brief  Check and orient coordinates
    /// @param  x x-axis coordinate, modified
    /// @param  y y-axis coordinate, modified
    /// @return false=success, true=error
    ///
    bool _orientCoordinates(uint16_t &x, uint16_t &y) ; // compulsory

    // Position

    // Write and Read
    /// @brief    Set point
    /// @param    x1 x coordinate
    /// @param    y1 y coordinate
    /// @param    colour 16-bit colour
    /// @n @b More: @ref Colour, @ref Coordinate
    ///
    void _setPoint(uint16_t x1, uint16_t y1, uint16_t colour);

    /// @brief    Get point
    /// @param    x1 x coordinate
    /// @param    y1 y coordinate
    /// @return   colour 16-bit colour
    /// @n @b More: @ref Colour, @ref Coordinate
    ///
    uint16_t _getPoint(uint16_t x1, uint16_t y1);

    ///
    /// @brief  Convert
    /// @param  x1 x-axis coordinate
    /// @param  y1 y-axis coordinate
    /// @return index for _newImage[]
    ///
    uint32_t _getZ(uint16_t x1, uint16_t y1);

    // Touch
    // No touch

    // Energy
    // LPM4 mode on MSP430

    // * Other functions specific to the screen

    // Screen independent variables
    uint8_t * _newImage;
    bool _invert;
    uint16_t _widthScreen, _heightScreen;

    // Screen dependent variables
    bool _flagBeginDone;
    uint8_t _pinCSS;
    eScreen_iTC_BWR_t _eScreen_iTC_BWR;
    uint16_t _widthBuffer, _heightBuffer, _depthBuffer, _numberBuffer;
    uint32_t _sizePageColour, _sizeFrame;
    uint8_t _refreshTime;
    /// @endcond
};

#endif // SCREEN_EPD_ITC_RELEASE
