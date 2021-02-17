///
/// @file		ePaper_EXT3_Fonts.ino
/// @brief		Example of features for basic edition
///
/// @image html T2_FONTS.PDF
/// @image latex T2_FONTS.PDF width=10cm
///
/// @details    Library for Pervasive Displays EXT3 - Basic level
///
/// @author		Rei Vilo
/// @author		https://embeddedcomputing.weebly.com
/// @date       31 Dec 2020
/// @version    release 503
///
/// @copyright	(c) Rei Vilo, 2020
/// @copyright	CC = BY SA NC
///
/// @see		ReadMe.txt for references
/// @n
///


// Core library for code-sense - IDE-based
// !!! Help: https://bit.ly/2AdU7cu
#if defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#elif defined(ARDUINO) // Arduino 1.0 and 1.5 specific
#include "Arduino.h"
#else // error
#error Platform not defined
#endif // end IDE


// Set parameters


// Include application, user and local libraries
// !!! Help https://bit.ly/2CL22Qp
#include "SPI.h"
#include "hV_Configuration.h"
#include "hV_Colours565.h"
#include "hV_Utilities.h"

// Define structures and classes


// Define variables and constants
// === Pervasive Displays iTC
#include "ePaper_EXT3_Basic_Library.h"
//Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_154_BWR);
//Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_213_BWR);
Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_271_BWR);
//Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_287_BWR);
//Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_266_BWR);
//Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_370_BWR);
//Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_420_BWR);
//Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_437_BWR);
//Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_565_BWR);
//Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_581_BWR);
//Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_740_BWR);
//Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_970_BWR);
//Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_1220_BWR);


// Prototypes
// !!! Help: https://bit.ly/2TAbgoI


// Utilities
///
/// @brief    Wait with countdown
/// @param    second duration, s
///
void wait(uint8_t second)
{
    for (uint8_t i = second; i > 0; i--)
    {
        Serial.print(formatString(" > %i  \r", i));
        delay(1000);
    }
    Serial.print("         \r");
}

///
/// @brief    Flush screen and display time
///
void flush_ms()
{
    uint32_t chrono = (uint32_t)millis();
    myScreen.flush();
    Serial.print(millis() - chrono);
    Serial.println(" ms");
}

// Functions
///
/// @brief    Fonts test screen
/// @param    flag true=default=perform flush, otherwise no
///
/// @image html T2_FONTS.PDF
/// @image latex T2_FONTS.PDF width=10cm
///
void displayFonts(bool flag = true)
{
    uint16_t y = 10;
    myScreen.setOrientation(7);

// #if (USE_FONT_MODE == USE_FONT_TERMINAL)
    myScreen.selectFont(Font_Terminal12x16);

    myScreen.gText(10, y, myScreen.WhoAmI(), myColours.red);
    y += myScreen.characterSizeY();
    myScreen.gText(10, y, formatString("%i x %i", myScreen.screenSizeX(), myScreen.screenSizeY()), myColours.red);
    y += myScreen.characterSizeY();
    y += myScreen.characterSizeY();

    myScreen.selectFont(Font_Terminal6x8);
    myScreen.gText(10, y, "Terminal6x8");
    y += myScreen.characterSizeY();

    myScreen.selectFont(Font_Terminal8x12);
    myScreen.gText(10, y, "Terminal8x12");
    y += myScreen.characterSizeY();

    myScreen.selectFont(Font_Terminal12x16);
    myScreen.gText(10, y, "Terminal12x16");
    y += myScreen.characterSizeY();

    myScreen.selectFont(Font_Terminal16x24);
    myScreen.gText(10, y, "Terminal16x24");
    y += myScreen.characterSizeY();

// #elif (USE_FONT_MODE == USE_FONT_HEADER)
//
// #elif (USE_FONT_MODE == USE_FONT_FLASH)
//
// #else
// #error USE_FONT_MODE not defined
// #endif

    if (flag)
    {
        flush_ms();
    }
}

// Add setup code
// !!! Help: https://bit.ly/2BmKRzI
///
/// @brief    Setup
///
void setup()
{
    pinMode(38, OUTPUT);
    digitalWrite(38, HIGH);

    Serial.begin(115200);
    delay(500);
    Serial.println();
    Serial.println("=== " __FILE__);
    Serial.println("=== " __DATE__ " " __TIME__);

#if defined(ARDUINO_ARCH_PIDUINO)
    pinMode(21, OUTPUT);
    digitalWrite(21, LOW);
    Serial.println("Launch in 8 s");
    wait(8);
    digitalWrite(21, HIGH);
#endif

    Serial.print("begin... ");
    myScreen.begin();
    Serial.println(formatString("%s %ix%i", myScreen.WhoAmI().c_str(), myScreen.screenSizeX(), myScreen.screenSizeY()));

    Serial.print("Fonts... ");
    myScreen.clear();
    displayFonts();
    wait(8);

    Serial.print("White... ");
    myScreen.clear();
    flush_ms();

    Serial.println("=== ");
    Serial.println();

#if defined(ARDUINO_ARCH_PIDUINO)
    digitalWrite(21, LOW);
    exit(0);
#endif
}

// Add loop code
///
/// @brief    Loop, empty
///
void loop()
{
    delay(1000);
}
