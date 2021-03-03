///
/// @file		ePaper_EXT3_Forms.ino
/// @brief		Example of features for basic edition
///
/// @image html T2_FORMS.PDF
/// @image latex T2_FORMS.PDF width=10cm
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
#else // Arduino general
#include "Arduino.h"
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
/// @brief    Basic forms test screen
/// @param    flag true=default=perform flush, otherwise no
///
/// @image html T2_FORMS.PDF
/// @image latex T2_FORMS.PDF width=10cm
///
void displayForms(bool flag = true)
{
    Serial.print(1);
    myScreen.setOrientation(7);
    Serial.print(2);

    uint16_t x = myScreen.screenSizeX();
    uint16_t y = myScreen.screenSizeY();
    uint16_t z = min(x, y);

    myScreen.setPenSolid(false);
    myScreen.dRectangle(0, 0, x, y, myColours.black);
    myScreen.dLine(0, 0, x, y, myColours.red);
    Serial.print(4);

    myScreen.setPenSolid(true);
    myScreen.circle(x/3, y/3, z / 4, myColours.grey);
    // myScreen.triangle(x*2/3, y/3, x/2, y*2/3, x*3/4, y*2/3-10, myColours.black);
    myScreen.triangle(x*2/3, y/3, x*3/4, y*2/3-10, x-10, 10, myColours.black);
    myScreen.dRectangle(x/3, y*2/3, x/3, y/4, myColours.red);
    Serial.print(6);
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

    Serial.print("Forms... ");
    myScreen.clear();
    displayForms();
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
