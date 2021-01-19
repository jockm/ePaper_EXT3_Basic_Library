///
/// @file		ePaper_EXT3_Characters.ino
/// @brief		Example of features for basic edition
///
/// @details    Library for Pervasive Displays EXT3 - Basic level
/// @n @a		Developed with [embedXcode+](https://embedXcode.weebly.com)
///
/// @author		Rei Vilo
/// @author		https://embeddedcomputing.weebly.com
/// @date       31 Dec 2020
/// @version    release 501
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
#include "LCD_Utilities.h"

// Define structures and classes


// Define variables and constants
// === Pervasive Displays iTC
#include "ePaper_EXT3_Basic_Library.h"
//Screen_iTC_BWR myScreen(eScreen_EPD_iTC_154_BWR);
//Screen_iTC_BWR myScreen(eScreen_EPD_iTC_213_BWR);
Screen_iTC_BWR myScreen(eScreen_EPD_iTC_271_BWR);
//Screen_iTC_BWR myScreen(eScreen_EPD_iTC_287_BWR);
//Screen_iTC_BWR myScreen(eScreen_EPD_iTC_266_BWR);
//Screen_iTC_BWR myScreen(eScreen_EPD_iTC_370_BWR);
//Screen_iTC_BWR myScreen(eScreen_EPD_iTC_420_BWR);
//Screen_iTC_BWR myScreen(eScreen_EPD_iTC_437_BWR);
//Screen_iTC_BWR myScreen(eScreen_EPD_iTC_565_BWR);
//Screen_iTC_BWR myScreen(eScreen_EPD_iTC_581_BWR);
//Screen_iTC_BWR myScreen(eScreen_EPD_iTC_740_BWR);
//Screen_iTC_BWR myScreen(eScreen_EPD_iTC_970_BWR);
//Screen_iTC_BWR myScreen(eScreen_EPD_iTC_1220_BWR);


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
/// @brief    Characters test screen
/// @param    flag true=default=perform flush, otherwise no
///
/// @image html T2_CHARA.PDF
/// @image latex T2_CHARA.PDF width=10cm
///
void displayCharacters(bool flag = true)
{
    myScreen.setOrientation(7);
    uint16_t x = myScreen.screenSizeX(); // 17
    uint16_t y = myScreen.screenSizeY(); // 14

// #if (USE_FONT_MODE == USE_FONT_TERMINAL)
    myScreen.selectFont(Font_Terminal8x12);
// #elif (USE_FONT_MODE == USE_FONT_HEADER)
//
// #elif (USE_FONT_MODE == USE_FONT_FLASH)
//
// #else
// #error USE_FONT_MODE not defined
// #endif

    uint8_t k;
    String text;
    uint16_t dx;

    for (uint8_t i = 1; i < 17; i++)
    {
        myScreen.gText(i * x / 17, 0, formatString(".%x", (i - 1)), myColours.red);
    }
    for (uint8_t j = 2; j < 16; j++)
    {
        myScreen.gText(0, (j - 1)*y / 15, formatString("%x.", (j)), myColours.red);
    }

    for (uint16_t i = 1; i < 17; i++)
    {
        for (uint8_t j = 2; j < 16; j++)
        {
            k = (i - 1) + j * 16;

            text = (String)char(k);
            dx = i * x / 17 + (x / 17 - myScreen.stringSizeX(text)) / 2;
            myScreen.gText(dx, (j - 1)*y / 15, text, myColours.black);
        }
    }

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

    Serial.print("Characters... ");
    myScreen.clear();
    displayCharacters();
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
