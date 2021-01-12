//
// Screen_EPD_iTC.cpp
// Library C++ code
// ----------------------------------
//
// Project      LCD_screen Library Suite
//
// Created by   Rei Vilo, 28 Jun 2016
//
//
// Copyright    © Rei Vilo, 2010-2020
// Licence      Attribution-NonCommercial-ShareAlike 4.0 Unported (CC BY-NC-SA 4.0)
//


// Library header
#include "Screen_EPD_iTC.h"

#if defined(ENERGIA)
///
/// @brief    SPI Settings for Energia
///
struct _SPISettings_s
{
    uint32_t clock; // in Hz, checked against SPI_CLOCK_MAX = 16000000
    uint8_t bitOrder; // LSBFIRST, MSBFIRST
    uint8_t dataMode; // SPI_MODE0, SPI_MODE1, SPI_MODE2, SPI_MODE3
};
///
/// @brief    SPI settings for screen
///
_SPISettings_s _settingScreen;
#else
///
/// @brief    SPI settings for screen
///
SPISettings _settingScreen;
#endif // ENERGIA


#if (CONFIGURATION_OPTION == CONFIGURATION_BOOSTERPACK)
// --- Initial configuration
#warning Default pins for BoosterPack
#define PNLON_PIN 11 // EXT2 BOARD J5 pin 11
#define CS_PIN 19    // EXT2 BOARD J5 pin 19
#define DC_PIN 9     // EXT2 BOARD J5 pin 9
#define RESET_PIN 10 // EXT2 BOARD J5 pin 10
#define BUSY_PIN 8   // EXT2 BOARD J5 pin 8
#define FLASH_CS_PIN 18 // EXT2 BOARD J5 pin 18 -> 18

#elif (CONFIGURATION_OPTION == CONFIGURATION_MSP5430FR5994)
// --- MSP5430FR5994 configuration
#warning Modified pins for MSP5430FR5994 controller
#define PNLON_PIN 11 // EXT2 BOARD J5 pin 11
#define CS_PIN 19    // EXT2 BOARD J5 pin 19
#define DC_PIN 29    // EXT2 BOARD J5 pin 9 -> 29
#define RESET_PIN 30 // EXT2 BOARD J5 pin 10 -> 30
#define BUSY_PIN 28  // EXT2 BOARD J5 pin 8 -> 28
#define FLASH_CS_PIN 18 // EXT2 BOARD J5 pin 18 -> 18

#elif (CONFIGURATION_OPTION == CONFIGURATION_RASPI)
// --- Raspberry Pi configuration
#warning Modified pins for Raspberry Pi
#define PNLON_PIN 22 // EXT2 BOARD 11 -> GPIO22 pin 15
#define CS_PIN 8     // EXT2 BOARD 19 -> GPIO8 pin 24
#define DC_PIN 25    // EXT2 BOARD 9 -> GPIO25 pin 22
#define RESET_PIN 23 // EXT2 BOARD 10 -> GPIO23 pin 16
#define BUSY_PIN 24  // EXT2 BOARD 8 -> GPIO24 pin 18
#define FLASH_CS_PIN 18 // EXT2 BOARD 18 -> GPIO18 pin 12
// EXT2 BOARD 17 -> GROUND

#elif (CONFIGURATION_OPTION == CONFIGURATION_REDBEAR_DUO)
// --- REDBEAR_DUO configuration
#warning Modified pins for RedBear Duo
#define PNLON_PIN D5 // EXT2 BOARD J5 pin 11 -> D5
#define CS_PIN D6    // EXT2 BOARD J5 pin 19 -> D6
#define DC_PIN D3    // EXT2 BOARD J5 pin 9 -> D3
#define RESET_PIN D4 // EXT2 BOARD J5 pin 10 -> D4
#define BUSY_PIN D2  // EXT2 BOARD J5 pin 8 -> D2
#define PIN_EPD_FLASH_CS D14 // EXT2 BOARD J5 pin 18 -> D14
// EXT2 BOARD 17 -> GROUND

#else
#error Invalid CONFIGURATION_OPTION
#endif

// #define BS_PIN 17 // EXT2 BOARD J5 pin 17 --- Reset on some LaunchPads

// --- Slave CSB for 9.7" and 12" screen with two sub-screens
#define CSS24_PIN 2    // EXT2 BOARD J5 pin 2 for 24-pin flat cable
#define CSS34_PIN 13   // EXT2 BOARD J5 pin 13 for bridge board and 34-pin flat cable
// ---

#ifndef SPI_CLOCK_MAX
#define SPI_CLOCK_MAX 16000000
#endif

// Class
Screen_iTC_BWR::Screen_iTC_BWR(eScreen_iTC_BWR_t eScreen_iTC_BWR)
{
    _newImage = 0;
    _eScreen_iTC_BWR = eScreen_iTC_BWR;
}

void Screen_iTC_BWR::begin()
{
    _eScreen_iTC_BWR = _eScreen_iTC_BWR;
    _pinCSS = 0;

    _screenColourBits = 2; // BWR

    switch (_eScreen_iTC_BWR)
    {
        case eScreen_EPD_iTC_154_BWR:

            _widthScreen =  152; // x = wide size
            _heightScreen = 152; // y = small size
            _screenDiagonal = 154;
            _refreshTime = 16;
            break;

        case eScreen_EPD_iTC_213_BWR:

            _widthScreen =  212; // x = wide size
            _heightScreen = 104; // y = small size
            _screenDiagonal = 213;
            _refreshTime = 15;
            break;

        case eScreen_EPD_iTC_266_BWR:

            _widthScreen =  296; // x = wide size
            _heightScreen = 152; // y = small size
            _screenDiagonal = 266;
            _refreshTime = 15;
            break;

        case eScreen_EPD_iTC_271_BWR:

            _widthScreen =  264; // x = wide size
            _heightScreen = 176; // y = small size
            _screenDiagonal = 271;
            _refreshTime = 19;
            break;

        case eScreen_EPD_iTC_287_BWR:

            _widthScreen =  296; // x = wide size
            _heightScreen = 128; // y = small size
            _screenDiagonal = 287;
            _refreshTime = 14;
            break;

        case eScreen_EPD_iTC_370_BWR:

            _widthScreen =  416; // x = wide size
            _heightScreen = 240; // y = small size
            _screenDiagonal = 370;
            _refreshTime = 15; // ?
            break;

        case eScreen_EPD_iTC_420_BWR:

            _widthScreen =  300; // x = wide size
            _heightScreen = 400; // y = small size
            _screenDiagonal = 420;
            _refreshTime = 19;
            break;

        case eScreen_EPD_iTC_437_BWR:

            _widthScreen =  480; // x = wide size
            _heightScreen = 176; // y = small size
            _screenDiagonal = 437;
            _refreshTime = 21;
            break;

        case eScreen_EPD_iTC_565_BWR:

            _widthScreen =  600; // x = wide size
            _heightScreen = 448; // y = small size
            _screenDiagonal = 565;
            _refreshTime = 32;
            break;

        case eScreen_EPD_iTC_581_BWR:

            _widthScreen =  720; // x = wide size
            _heightScreen = 256; // y = small size
            _screenDiagonal = 581;
            _refreshTime = 32;
            break;

        case eScreen_EPD_iTC_740_BWR:

            _widthScreen =  800; // x = wide size
            _heightScreen = 480; // y = small size
            _screenDiagonal = 740;
            _refreshTime = 32;
            break;

        case eScreen_EPD_iTC_970_BWR:

            _pinCSS = CSS24_PIN; // 970-specific

            _widthScreen =  672; // x = wide size
            _heightScreen = 960; // Actually, 960 = 480 x 2, y = small size
            _screenDiagonal = 970;
            _refreshTime = 45;
            break;

        case eScreen_EPD_iTC_1220_BWR:

            _pinCSS = CSS34_PIN; // 1220-specific

            _widthScreen =  768; // x = wide size
            _heightScreen = 960; // Actually, 960 = 480 x 2, y = small size
            _screenDiagonal = 1220;
            _refreshTime = 45;
            break;

        default:

            break;
    }

    _depthBuffer = _screenColourBits; // 2 colours
    _widthBuffer = _widthScreen; // x = wide size
    _heightBuffer = _heightScreen / 8; // small size 112 / 8;

    // Force conversion for two unit16_t multiplication into uint32_t.
    // Actually for 1 colour; BWR requires 2 pages.
    _sizePageColour = (uint32_t)_widthBuffer * (uint32_t)_heightBuffer;

    // Serial.print("_sizePageColour= ");
    // Serial.println(_sizePageColour);

    // _sizeFrame = _sizePageColour, except for 9.70 and 12.20
    // 9.70 and 12.20 combine two half-screens, hence two frames with adjusted size
    switch (_eScreen_iTC_BWR)
    {
        case eScreen_EPD_iTC_970_BWR:
        case eScreen_EPD_iTC_1220_BWR:

            _sizeFrame = _sizePageColour / 2;
            break;

        default:

            _sizeFrame = _sizePageColour;
            break;
    }

    if (_newImage == 0)
    {
        static uint8_t * _newFrameBuffer;
        _newFrameBuffer = new uint8_t[_sizePageColour * _depthBuffer];
        _newImage = (uint8_t *) _newFrameBuffer;
    }

    // Check FRAM
    bool flag = true;
    uint8_t count = 8;
    _newImage[1] = 0x00;
    while (flag)
    {
        _newImage[1] = 0xaa;
        if ((_newImage[1] == 0xaa) or (count == 0))
        {
            flag = false;
        }
        count--;
    }
    memset(_newImage, 0x00, _sizePageColour);

    // Initialise the screen
    // SPI speed 4 MHz max for e-paper displays
    // SPI issue fixed by release ENERGIA_MSP432_RED_EMT 5.6.2
    // #if defined(ENERGIA_ARCH_MSP432R)
    // #warning Patch for MSP432 Red LaunchPad hardware bug
    // _settingScreen = {4000000, MSBFIRST, SPI_MODE1};
    // #else
    //    _settingScreen = {4000000, MSBFIRST, SPI_MODE0};
    // Recommended 1 MHz max for e-paper displays
    _settingScreen = {1000000, MSBFIRST, SPI_MODE0};
    // #endif

#if defined(ENERGIA)
    SPI.setBitOrder(_settingScreen.bitOrder);
    SPI.setDataMode(_settingScreen.dataMode);
    SPI.setClockDivider(SPI_CLOCK_MAX / min(SPI_CLOCK_MAX, _settingScreen.clock));
#else
    SPI.beginTransaction(_settingScreen);
#endif // ENERGIA

    SPI.begin();

    pinMode(PNLON_PIN, OUTPUT);
    pinMode(CS_PIN, OUTPUT);
    digitalWrite(CS_PIN, HIGH);      // CS# = 1
    if (_pinCSS > 0)                 // for 9.7 and 12.2
    {
        pinMode(_pinCSS, OUTPUT);
        digitalWrite(_pinCSS, HIGH); // CSS# = 1
    }
    pinMode(DC_PIN, OUTPUT);
    pinMode(RESET_PIN, OUTPUT);
    pinMode(BUSY_PIN, INPUT);        // All Pins 0

    // Reset
    switch (_eScreen_iTC_BWR)
    {
        case eScreen_EPD_iTC_420_BWR:
        case eScreen_EPD_iTC_437_BWR:

            _reset(5, 5, 10, 5, 5);
            break;

        case eScreen_EPD_iTC_565_BWR:
        case eScreen_EPD_iTC_581_BWR:
        case eScreen_EPD_iTC_740_BWR:

            _reset(200, 20, 200, 50, 5);
            break;

        case eScreen_EPD_iTC_970_BWR:
        case eScreen_EPD_iTC_1220_BWR:

            _reset(200, 20, 200, 200, 5);
            break;

        default:
            _reset(5, 5, 10, 5, 5);
            break;
    }

    _screenWidth = _heightScreen;
    _screenHeigth = _widthScreen;

    // Standard
    LCD_screen_buffer::begin();

    setOrientation(0);
    if (fontMax() > 0)
    {
        selectFont(0);
    }
    invert(false);

    _penSolid = false;
    _fontSolid = false;
    _invert = false;

    clear();
}

void Screen_iTC_BWR::_reset(uint32_t ms1, uint32_t ms2, uint32_t ms3, uint32_t ms4, uint32_t ms5)
{
    digitalWrite(PNLON_PIN, HIGH);  // PANEL_ON# = 1
    delay_ms(ms1);                  // delay_ms 5ms
    digitalWrite(RESET_PIN, HIGH);  // RES# = 1
    delay_ms(ms2);                  // delay_ms 5ms
    digitalWrite(RESET_PIN, LOW);
    delay_ms(ms3);
    digitalWrite(RESET_PIN, HIGH);
    delay_ms(ms4);

    digitalWrite(CS_PIN, HIGH);     // CS# = 1
    if (_pinCSS > 0)                // for 9.7 and 12.2
    {
        digitalWrite(_pinCSS, HIGH);// CSS# = 1
    }
    delay_ms(ms5);
}

String Screen_iTC_BWR::WhoAmI()
{
    String text = "iTC ";
    text += String(_screenDiagonal / 100);
    text += ".";
    text += String(_screenDiagonal % 100);
    text += "\" BWR";

#if (USE_FONT_MODE == USE_FONT_HEADER)
    text += " (h)";
#elif (USE_FONT_MODE == USE_FONT_FLASH)
    text += " (f)";
#elif (USE_FONT_MODE == USE_FONT_TERMINAL)
    text += " (t)";
#endif
    return text;
}

void Screen_iTC_BWR::flush()
{
    SPI.end();
#if defined(ENERGIA)
    SPI.setBitOrder(_settingScreen.bitOrder);
    SPI.setDataMode(_settingScreen.dataMode);
    SPI.setClockDivider(SPI_CLOCK_MAX / min(SPI_CLOCK_MAX, _settingScreen.clock));
#else
    SPI.beginTransaction(_settingScreen);
#endif // ENERGIA

    SPI.begin();

    uint8_t * blackBuffer = _newImage;
    uint8_t * redBuffer = _newImage + _sizePageColour;

    // switch..case doesn't allow variable declarations
    //
    if (_eScreen_iTC_BWR == eScreen_EPD_iTC_420_BWR)
    {
        // Serial.println("eScreen_EPD_iTC_420_BWR 1");
        _reset(5, 5, 10, 5, 5);

        uint8_t data9_420[] = { 0x0e };
        _sendIndexData(0x00, data9_420, 1); // Soft-reset
        delay_ms(5);

        uint8_t data7_420[] = {0x19};
        // uint8_t data7_420[] = { getTemperature() };
        _sendIndexData(0xe5, data7_420, 1); // Input Temperature: 0°C = 0x00, 22°C = 0x16, 25°C = 0x19
        uint8_t data6_420[] = {0x02};
        _sendIndexData(0xe0, data6_420, 1); // Active Temperature

        // Serial.println("eScreen_EPD_iTC_420_BWR 3");
        uint8_t data1_420[] = {0x0f};
        _sendIndexData(0x00, data1_420, 1); // Panel Setting
        uint8_t data2_420[] = {0x17, 0x17, 0x27};
        _sendIndexData(0x06, data2_420, 3); // Booster soft start setting
        uint8_t data3_420[] = {0x01, 0x90, 0x01, 0x2c};
        _sendIndexData(0x61, data3_420, 4); // Resolution setting
        uint8_t data4_420[] = {0x87};
        _sendIndexData(0x50, data4_420, 1); // Vcom and data interval setting
        uint8_t data5_420[] = {0x88};
        _sendIndexData(0xe3, data5_420, 1); // Power Saving

        // Send image data
        // Serial.println("eScreen_EPD_iTC_420_BWR 4");
        _sendIndexData(0x10, blackBuffer, _sizeFrame);  // First frame
        _sendIndexData(0x13, redBuffer, _sizeFrame);    // Second frame

        // Serial.println("eScreen_EPD_iTC_420_BWR 5");
        delay_ms(50);
        uint8_t data8_420[] = {0x00};
        _sendIndexData(0x04, data8_420, 1); // Power on
        delay_ms(5);

        // Serial.println("eScreen_EPD_iTC_420_BWR 6");
        while (digitalRead(BUSY_PIN) != HIGH);

        _sendIndexData(0x12, data8_420, 1); // Display Refresh
        delay_ms(5);

        // Serial.println("eScreen_EPD_iTC_420_BWR 7");
        while (digitalRead(BUSY_PIN) != HIGH);

        _sendIndexData(0x02, data8_420, 1); // Turn off DC/DC
        while (digitalRead(BUSY_PIN) != HIGH);
        digitalWrite(DC_PIN, LOW);
        digitalWrite(CS_PIN, LOW);

        digitalWrite(RESET_PIN, LOW);
        digitalWrite(PNLON_PIN, LOW);
        // Serial.println("eScreen_EPD_iTC_420_BWR 8");
    }
    else if (_eScreen_iTC_BWR == eScreen_EPD_iTC_437_BWR)
    {
        _reset(5, 5, 10, 5, 5);

        uint8_t data9_437[] = { 0x0e };
        _sendIndexData(0x00, data9_437, 1); // Soft-reset
        delay_ms(5);

        uint8_t data7_437[] = { 0x19 };
        _sendIndexData(0xe5, data7_437, 1); // Input Temperature: 25C
        uint8_t data6_437[] = { 0x02 };
        _sendIndexData(0xe0, data6_437, 1); // Active Temperature

        // Send image data
        // Serial.println("2");
        _sendIndexData(0x10, blackBuffer, _sizeFrame); // First frame
        _sendIndexData(0x13, redBuffer, _sizeFrame); // Second frame

        // Serial.println("3");
        delay_ms(50);
        uint8_t data8_437[] = { 0x00 };
        _sendIndexData(0x04, data8_437, 1); // Power on
        delay_ms(5);
        while (digitalRead(BUSY_PIN) != HIGH);
        _sendIndexData(0x12, data8_437, 1); // Display Refresh
        delay_ms(5);
        while (digitalRead(BUSY_PIN) != HIGH);
        _sendIndexData(0x02, data8_437, 1); // Turn off DC/DC
        while (digitalRead(BUSY_PIN) != HIGH);
        digitalWrite(DC_PIN, LOW);
        digitalWrite(CS_PIN, LOW);

        digitalWrite(RESET_PIN, LOW);
        digitalWrite(PNLON_PIN, LOW); // PANEL_OFF# = 0
        // Serial.println("4");
    }
    else if (_eScreen_iTC_BWR == eScreen_EPD_iTC_565_BWR)
    {
        // Send image data
        uint8_t data1_565[] = { 0x00, 0x37, 0x00, 0x00, 0x57, 0x02 };
        _sendIndexData(0x13, data1_565, 6); // DUW
        uint8_t data2_565[] = { 0x00, 0x37, 0x00, 0x97 };
        _sendIndexData(0x90, data2_565, 4); // DRFW
        uint8_t data3_565[] = { 0x37, 0x00, 0x14 };
        _sendIndexData(0x12, data3_565, 3); // RAM_RW
        _sendIndexData(0x10, blackBuffer, _sizeFrame); // First frame
        _sendIndexData(0x12, data3_565, 3); // RAM_RW
        _sendIndexData(0x11, redBuffer, _sizeFrame); // Second frame

        // Initial COG
        uint8_t data4_565[] = { 0x7d};
        _sendIndexData(0x05, data4_565, 1);
        delay_ms(200);
        uint8_t data5_565[] = { 0x00};
        _sendIndexData(0x05, data5_565, 1);
        delay_ms(10);
        uint8_t data6_565[] = { 0x3f};
        _sendIndexData(0xc2, data6_565, 1);
        delay_ms(1);
        uint8_t data7_565[] = { 0x00};
        _sendIndexData(0xd8, data7_565, 1); // MS_SYNC mtp_0x1d
        uint8_t data8_565[] = { 0x00};
        _sendIndexData(0xd6, data8_565, 1); // BVSS mtp_0x1e
        uint8_t data9_565[] = { 0x10};
        _sendIndexData(0xa7, data9_565, 1);
        delay_ms(100);
        _sendIndexData(0xa7, data5_565, 1);
        delay_ms(100);
        uint8_t data10_565[] = { 0x00, 0x02 };
        _sendIndexData(0x03, data10_565, 2); // OSC mtp_0x12
        _sendIndexData(0x44, data5_565, 1);
        uint8_t data11_565[] = { 0x80 };
        _sendIndexData(0x45, data11_565, 1);
        _sendIndexData(0xa7, data9_565, 1);
        delay_ms(100);
        _sendIndexData(0xa7, data7_565, 1);
        delay_ms(100);
        uint8_t data12_565[] = { 0x06 };
        _sendIndexData(0x44, data12_565, 1);
        uint8_t data13_565[] = { 0x82 };
        _sendIndexData(0x45, data13_565, 1); // Temperature 0x82@25C
        _sendIndexData(0xa7, data9_565, 1);
        delay_ms(100);
        _sendIndexData(0xa7, data7_565, 1);
        delay_ms(100);
        uint8_t data14_565[] = { 0x25 };
        _sendIndexData(0x60, data14_565, 1); // TCON mtp_0x0b
        uint8_t data15_565[] = { 0x01 };
        _sendIndexData(0x61, data15_565, 1); // STV_DIR mtp_0x1c
        uint8_t data16_565[] = { 0x00 };
        _sendIndexData(0x01, data16_565, 1); // DCTL mtp_0x10
        uint8_t data17_565[] = { 0x00 };
        _sendIndexData(0x02, data17_565, 1); // VCOM mtp_0x11

        // DC-DC soft-start
        uint8_t  index51_565[] = {0x50, 0x01, 0x0a, 0x01};
        _sendIndexData(0x51, &index51_565[0], 2);
        uint8_t  index09_565[] = {0x1f, 0x9f, 0x7f, 0xff};

        for (int value = 1; value <= 4; value++)
        {
            _sendIndexData(0x09, &index09_565[0], 1);
            index51_565[1] = value;
            _sendIndexData(0x51, &index51_565[0], 2);
            _sendIndexData(0x09, &index09_565[1], 1);
            delay_ms(2);
        }

        for (int value = 1; value <= 10; value++)
        {
            _sendIndexData(0x09, &index09_565[0], 1);
            index51_565[3] = value;
            _sendIndexData(0x51, &index51_565[2], 2);
            _sendIndexData(0x09, &index09_565[1], 1);
            delay_ms(2);
        }
        for (int value = 3; value <= 10; value++)
        {
            _sendIndexData(0x09, &index09_565[2], 1);
            index51_565[3] = value;
            _sendIndexData(0x51, &index51_565[2], 2);
            _sendIndexData(0x09, &index09_565[3], 1);
            delay_ms(2);
        }
        for (int value = 9; value >= 2; value--)
        {
            _sendIndexData(0x09, &index09_565[2], 1);
            index51_565[2] = value;
            _sendIndexData(0x51, &index51_565[2], 2);
            _sendIndexData(0x09, &index09_565[3], 1);
            delay_ms(2);
        }
        _sendIndexData(0x09, &index09_565[3], 1);
        delay_ms(10);
        Serial.println("3");

        // Display Refresh Start
        while (digitalRead(BUSY_PIN) != HIGH);
        uint8_t data18_565[] = { 0x3c };
        _sendIndexData(0x15, data18_565, 1); //Display Refresh
        delay_ms(5);

        // DC-DC off
        while (digitalRead(BUSY_PIN) != HIGH);
        uint8_t data19_565[] = { 0x7f };
        _sendIndexData(0x09, data19_565, 1);
        uint8_t data20_565[] = { 0x7d };
        _sendIndexData(0x05, data20_565, 1);
        _sendIndexData(0x09, data5_565, 1);
        delay_ms(200);

        while (digitalRead(BUSY_PIN) != HIGH);
        digitalWrite(DC_PIN, LOW);
        digitalWrite(CS_PIN, LOW);

        digitalWrite(RESET_PIN, LOW);
        digitalWrite(PNLON_PIN, LOW); // PANEL_OFF# = 0
    }
    else if (_eScreen_iTC_BWR == eScreen_EPD_iTC_581_BWR)
    {
        // Send image data
        uint8_t data1_581[] = { 0x00, 0x1f, 0x50, 0x00, 0x1f, 0x03 };
        _sendIndexData(0x13, data1_581, 6); // DUW 0x16 ~ 0x1B of MTP
        uint8_t data2_581[] = { 0x00, 0x1f, 0x00, 0xc9 };
        _sendIndexData(0x90, data2_581, 4); // DRFW 0x0C ~ 0x0F of MTP
        uint8_t data3_581[] = { 0x1f, 0x50, 0x14 };
        _sendIndexData(0x12, data3_581, 3); // RAM_RW 0x13 ~ 0x15 of MTP
        _sendIndexData(0x10, blackBuffer, _sizeFrame); // First frame
        _sendIndexData(0x12, data3_581, 3); // RAM_RW
        _sendIndexData(0x11, redBuffer, _sizeFrame); // Second frame

        // Initial COG
        uint8_t data4_581[] = { 0x7d};
        _sendIndexData(0x05, data4_581, 1);
        delay_ms(200);
        uint8_t data5_581[] = { 0x00};
        _sendIndexData(0x05, data5_581, 1);
        delay_ms(10);
        uint8_t data6_581[] = { 0x3f};
        _sendIndexData(0xc2, data6_581, 1);
        delay_ms(1);
        uint8_t data7_581[] = { 0x00};
        _sendIndexData(0xd8, data7_581, 1); // MS_SYNC 0x1D of MTP
        uint8_t data8_581[] = { 0x00};
        _sendIndexData(0xd6, data8_581, 1); // BVSS 0x1E of MTP
        uint8_t data9_581[] = { 0x10};
        _sendIndexData(0xa7, data9_581, 1);
        delay_ms(100);
        _sendIndexData(0xa7, data5_581, 1);
        delay_ms(100);
        uint8_t data10_581[] = { 0x00, 0x01 };
        _sendIndexData(0x03, data10_581, 2); // OSC 0x12 of MTP
        _sendIndexData(0x44, data5_581, 1);
        uint8_t data11_581[] = { 0x80 };
        _sendIndexData(0x45, data11_581, 1);
        _sendIndexData(0xa7, data9_581, 1);
        delay_ms(100);
        _sendIndexData(0xa7, data7_581, 1);
        delay_ms(100);
        uint8_t data12_581[] = { 0x06 };
        _sendIndexData(0x44, data12_581, 1);
        uint8_t data13_581[] = { 0x82 };
        _sendIndexData(0x45, data13_581, 1); // Temperature 0x82@25C
        _sendIndexData(0xa7, data9_581, 1);
        delay_ms(100);
        _sendIndexData(0xa7, data7_581, 1);
        delay_ms(100);
        uint8_t data14_581[] = { 0x25 };
        _sendIndexData(0x60, data14_581, 1); // TCON 0x0B of MTP
        uint8_t data15_581[] = { 0x00 };
        _sendIndexData(0x61, data15_581, 1); // STV_DIR 0x1C of MTP
        uint8_t data16_581[] = { 0x00 };
        _sendIndexData(0x01, data16_581, 1); // DCTL 0x10 of MTP
        uint8_t data17_581[] = { 0x00 };
        _sendIndexData(0x02, data17_581, 1); // VCOM 0x11 of MTP

        // DC-DC soft-start
        uint8_t  index51_581[] = {0x50, 0x01, 0x0a, 0x01};
        _sendIndexData(0x51, &index51_581[0], 2);
        uint8_t  index09_581[] = {0x1f, 0x9f, 0x7f, 0xff};

        for (int value = 1; value <= 4; value++)
        {
            _sendIndexData(0x09, &index09_581[0], 1);
            index51_581[1] = value;
            _sendIndexData(0x51, &index51_581[0], 2);
            _sendIndexData(0x09, &index09_581[1], 1);
            delay_ms(2);
        }
        // *
        for (int value = 1; value <= 10; value++)
        {
            _sendIndexData(0x09, &index09_581[0], 1);
            index51_581[3] = value;
            _sendIndexData(0x51, &index51_581[2], 2);
            _sendIndexData(0x09, &index09_581[1], 1);
            delay_ms(2);
        }
        for (int value = 3; value <= 10; value++)
        {
            _sendIndexData(0x09, &index09_581[2], 1);
            index51_581[3] = value;
            _sendIndexData(0x51, &index51_581[2], 2);
            _sendIndexData(0x09, &index09_581[3], 1);
            delay_ms(2);
        }
        for (int value = 9; value >= 2; value--)
        {
            _sendIndexData(0x09, &index09_581[2], 1);
            index51_581[2] = value;
            _sendIndexData(0x51, &index51_581[2], 2);
            _sendIndexData(0x09, &index09_581[3], 1);
            delay_ms(2);
        }
        _sendIndexData(0x09, &index09_581[3], 1);
        delay_ms(10);
        // Serial.println("3");

        // Display Refresh Start
        while (digitalRead(BUSY_PIN) != HIGH);
        uint8_t data18_581[] = { 0x3c };
        _sendIndexData(0x15, data18_581, 1); // Display Refresh
        delay_ms(5);

        // DC-DC off
        while (digitalRead(BUSY_PIN) != HIGH);
        uint8_t data19_581[] = { 0x7f };
        _sendIndexData(0x09, data19_581, 1);
        uint8_t data20_581[] = { 0x7d };
        _sendIndexData(0x05, data20_581, 1);
        _sendIndexData(0x09, data5_581, 1);
        delay_ms(200);
        while (digitalRead(BUSY_PIN) != HIGH);
        digitalWrite(DC_PIN, LOW);
        digitalWrite(CS_PIN, LOW);

        digitalWrite(RESET_PIN, LOW);
        digitalWrite(PNLON_PIN, LOW); // PANEL_OFF# = 0
    }
    else if (_eScreen_iTC_BWR == eScreen_EPD_iTC_740_BWR)
    {
        _reset(200, 20, 200, 50, 5);

        // Send image data
        uint8_t data1_740[] = {0x00, 0x3b, 0x00, 0x00, 0x1f, 0x03};
        _sendIndexData(0x13, data1_740, 6); // DUW
        uint8_t data2_740[] = {0x00, 0x3b, 0x00, 0xc9};
        _sendIndexData(0x90, data2_740, 4); // DRFW
        uint8_t data3_740[] = {0x3b, 0x00, 0x14};
        _sendIndexData(0x12, data3_740, 3); // RAM_RW
        _sendIndexData(0x10, blackBuffer, _sizeFrame); // First frame
        _sendIndexData(0x12, data3_740, 3); // RAM_RW
        _sendIndexData(0x11, redBuffer, _sizeFrame); // Second frame

        // Initial COG
        uint8_t data4_740[] = {0x7d};
        _sendIndexData(0x05, data4_740, 1);
        delay_ms(200);
        uint8_t data5_740[] = {0x00};
        _sendIndexData(0x05, data5_740, 1);
        delay_ms(10);
        uint8_t data6_740[] = {0x3f};
        _sendIndexData(0xc2, data6_740, 1);
        delay_ms(1);
        uint8_t data7_740[] = {0x00};
        _sendIndexData(0xd8, data7_740, 1); // MS_SYNC
        uint8_t data8_740[] = {0x00};
        _sendIndexData(0xd6, data8_740, 1); // BVSS
        uint8_t data9_740[] = {0x10};
        _sendIndexData(0xa7, data9_740, 1);
        delay_ms(100);
        _sendIndexData(0xa7, data5_740, 1);
        delay_ms(100);
        uint8_t data10_740[] = {0x00, 0x01};
        _sendIndexData(0x03, data10_740, 2); // OSC
        _sendIndexData(0x44, data5_740, 1);
        uint8_t data11_740[] = {0x80};
        _sendIndexData(0x45, data11_740, 1);
        _sendIndexData(0xa7, data9_740, 1);
        delay_ms(100);
        _sendIndexData(0xa7, data7_740, 1);
        delay_ms(100);
        uint8_t data12_740[] = {0x06};
        _sendIndexData(0x44, data12_740, 1);
        uint8_t data13_740[] = {0x82};
        //        uint8_t data13_740[] = { getTemperature(0x50, 0x82) };
        _sendIndexData(0x45, data13_740, 1); // Temperature 0x82@25C   0°C = 0x50, 25°C = 0x82
        _sendIndexData(0xa7, data9_740, 1);
        delay_ms(100);
        _sendIndexData(0xa7, data7_740, 1);
        delay_ms(100);
        uint8_t data14_740[] = {0x25};
        _sendIndexData(0x60, data14_740, 1); // TCON
        uint8_t data15_740[] = {0x00};
        _sendIndexData(0x61, data15_740, 1); // STV_DIR
        uint8_t data16_740[] = {0x00};
        _sendIndexData(0x01, data16_740, 1); // DCTL
        uint8_t data17_740[] = {0x00};
        _sendIndexData(0x02, data17_740, 1); // VCOM

        // DC-DC soft-start
        uint8_t  index51b_data_740[] = {0x50, 0x01, 0x0a, 0x01};
        _sendIndexData(0x51, &index51b_data_740[0], 2);
        uint8_t  index09b_data_740[] = {0x1f, 0x9f, 0x7f, 0xff};

        for (int value = 1; value <= 4; value++)
        {
            _sendIndexData(0x09, &index09b_data_740[0], 1);
            index51b_data_740[1] = value;
            _sendIndexData(0x51, &index51b_data_740[0], 2);
            _sendIndexData(0x09, &index09b_data_740[1], 1);
            delay_ms(2);
        }
        // *
        for (int value = 1; value <= 10; value++)
        {
            _sendIndexData(0x09, &index09b_data_740[0], 1);
            index51b_data_740[3] = value;
            _sendIndexData(0x51, &index51b_data_740[2], 2);
            _sendIndexData(0x09, &index09b_data_740[1], 1);
            delay_ms(2);
        }
        for (int value = 3; value <= 10; value++)
        {
            _sendIndexData(0x09, &index09b_data_740[2], 1);
            index51b_data_740[3] = value;
            _sendIndexData(0x51, &index51b_data_740[2], 2);
            _sendIndexData(0x09, &index09b_data_740[3], 1);
            delay_ms(2);
        }
        for (int value = 9; value >= 2; value--)
        {
            _sendIndexData(0x09, &index09b_data_740[2], 1);
            index51b_data_740[2] = value;
            _sendIndexData(0x51, &index51b_data_740[2], 2);
            _sendIndexData(0x09, &index09b_data_740[3], 1);
            delay_ms(2);
        }
        _sendIndexData(0x09, &index09b_data_740[3], 1);
        delay_ms(10);

        // Display Refresh Start
        while (digitalRead(BUSY_PIN) != HIGH);
        uint8_t data18_740[] = {0x3c};
        _sendIndexData(0x15, data18_740, 1); // Display Refresh
        delay_ms(5);

        // DC-DC off
        while (digitalRead(BUSY_PIN) != HIGH);
        uint8_t data19_740[] = {0x7f};
        _sendIndexData(0x09, data19_740, 1);
        uint8_t data20_740[] = {0x7d};
        _sendIndexData(0x05, data20_740, 1);
        _sendIndexData(0x09, data5_740, 1);
        delay_ms(200);
        while (digitalRead(BUSY_PIN) != HIGH);
        digitalWrite(DC_PIN, LOW);
        digitalWrite(CS_PIN, LOW);

        digitalWrite(RESET_PIN, LOW);
        digitalWrite(PNLON_PIN, LOW); // PANEL_OFF# = 0
    }
    else if (_eScreen_iTC_BWR == eScreen_EPD_iTC_970_BWR)
    {
        _reset(200, 20, 200, 200, 5);

        // Send image data
        uint8_t data1_970[] = {0x00, 0x3b, 0x00, 0x00, 0x9f, 0x02}; // --- 9.7 specific
        _sendIndexData(0x13, data1_970, 6); // DUW for Both Master and Slave
        uint8_t data2_970[] = {0x00, 0x3b, 0x00, 0xa9}; // --- 9.7 specific
        _sendIndexData(0x90, data2_970, 4); // DRFW for Both Master and Slave
        uint8_t data3_970[] = {0x3b, 0x00, 0x14};

        // Master
        _sendIndexDataMaster(0x12, data3_970, 3); // RAM_RW
        _sendIndexDataMaster(0x10, blackBuffer, _sizeFrame); // First frame
        _sendIndexDataMaster(0x12, data3_970, 3); // RAM_RW
        _sendIndexDataMaster(0x11, redBuffer, _sizeFrame); // Second frame

        // Slave
        _sendIndexDataSlave(0x12, data3_970, 3); // RAM_RW
        _sendIndexDataSlave(0x10, blackBuffer + _sizeFrame, _sizeFrame); // First frame
        _sendIndexDataSlave(0x12, data3_970, 3); // RAM_RW
        _sendIndexDataSlave(0x11, redBuffer + _sizeFrame, _sizeFrame); // Second frame

        // Initial COG
        uint8_t data4_970[] = {0x7d};
        _sendIndexData(0x05, data4_970, 1);
        delay_ms(200);
        uint8_t data5_970[] = {0x00};
        _sendIndexData(0x05, data5_970, 1);
        delay_ms(10);
        uint8_t data6_970[] = {0x3f};
        _sendIndexData(0xc2, data6_970, 1);
        delay_ms(1);
        uint8_t data7_970[] = {0x80};
        _sendIndexData(0xd8, data7_970, 1); // MS_SYNC
        uint8_t data8_970[] = {0x00};
        _sendIndexData(0xd6, data8_970, 1); // BVSS
        uint8_t data9_970[] = {0x10};
        _sendIndexData(0xa7, data9_970, 1);
        delay_ms(100);
        _sendIndexData(0xa7, data5_970, 1);
        delay_ms(100);
        uint8_t data10_970[] = {0x00, 0x11}; // --- 9.7 specific
        _sendIndexData(0x03, data10_970, 2); // OSC
        _sendIndexDataMaster(0x44, data5_970, 1); // Master
        uint8_t data11_970[] = {0x80};
        _sendIndexDataMaster(0x45, data11_970, 1); // Master
        _sendIndexDataMaster(0xa7, data9_970, 1); // Master
        delay_ms(100);
        _sendIndexDataMaster(0xa7, data5_970, 1); // Master
        delay_ms(100);
        uint8_t data12_970[] = {0x06};
        _sendIndexDataMaster(0x44, data12_970, 1); // Master
        uint8_t data13_970[] = {0x82};
        //        uint8_t data13_970[] = { getTemperature(0x50, 0x82) };
        _sendIndexDataMaster(0x45, data13_970, 1); // Temperature 0x82@25C   0°C = 0x50, 25°C = 0x82
        _sendIndexDataMaster(0xa7, data9_970, 1); // Master
        delay_ms(100);
        _sendIndexDataMaster(0xa7, data5_970, 1); // Master
        delay_ms(100);

        _sendIndexDataSlave(0x44, data5_970, 1); // Slave
        _sendIndexDataSlave(0x45, data11_970, 1); // Slave
        _sendIndexDataSlave(0xa7, data9_970, 1); // Slave
        delay_ms(100);
        _sendIndexDataSlave(0xa7, data5_970, 1); // Slave
        delay_ms(100);
        _sendIndexDataSlave(0x44, data12_970, 1); // Slave
        _sendIndexDataSlave(0x45, data13_970, 1); // Temperature 0x82@25C   0°C = 0x50, 25°C = 0x82
        _sendIndexDataSlave(0xa7, data9_970, 1); // Slave
        delay_ms(100);
        _sendIndexDataSlave(0xa7, data5_970, 1); // Master
        delay_ms(100);

        uint8_t data14_970[] = {0x25};
        _sendIndexData(0x60, data14_970, 1); // TCON
        uint8_t data15_970[] = {0x01};
        _sendIndexDataMaster(0x61, data15_970, 1); // STV_DIR for Master
        uint8_t data16_970[] = {0x00};
        _sendIndexData(0x01, data16_970, 1); // DCTL
        uint8_t data17_970[] = {0x00};
        _sendIndexData(0x02, data17_970, 1); // VCOM

        // DC-DC soft-start
        uint8_t  index51_970[] = {0x50, 0x01, 0x0a, 0x01};
        _sendIndexData(0x51, &index51_970[0], 2);
        uint8_t  index09_970[] = {0x1f, 0x9f, 0x7f, 0xff};

        for (int value = 1; value <= 4; value++)
        {
            _sendIndexData(0x09, &index09_970[0], 1);
            index51_970[1] = value;
            _sendIndexData(0x51, &index51_970[0], 2);
            _sendIndexData(0x09, &index09_970[1], 1);
            delay_ms(2);
        }
        for (int value = 1; value <= 10; value++)
        {
            _sendIndexData(0x09, &index09_970[0], 1);
            index51_970[3] = value;
            _sendIndexData(0x51, &index51_970[2], 2);
            _sendIndexData(0x09, &index09_970[1], 1);
            delay_ms(2);
        }
        for (int value = 3; value <= 10; value++)
        {
            _sendIndexData(0x09, &index09_970[2], 1);
            index51_970[3] = value;
            _sendIndexData(0x51, &index51_970[2], 2);
            _sendIndexData(0x09, &index09_970[3], 1);
            delay_ms(2);
        }
        for (int value = 9; value >= 2; value--)
        {
            _sendIndexData(0x09, &index09_970[2], 1);
            index51_970[2] = value;
            _sendIndexData(0x51, &index51_970[2], 2);
            _sendIndexData(0x09, &index09_970[3], 1);
            delay_ms(2);
        }
        _sendIndexData(0x09, &index09_970[3], 1);
        delay_ms(10);

        // Display Refresh Start
        while (digitalRead(BUSY_PIN) != HIGH);
        uint8_t data18_970[] = {0x3c};
        _sendIndexData(0x15, data18_970, 1); // Display Refresh
        delay_ms(5);

        // DC/DC off
        while (digitalRead(BUSY_PIN) != HIGH);
        uint8_t data19_970[] = {0x7f};
        _sendIndexData(0x09, data19_970, 1);
        uint8_t data20_970[] = {0x7d};
        _sendIndexData(0x05, data20_970, 1);
        _sendIndexData(0x09, data5_970, 1);
        delay_ms(200);
        while (digitalRead(BUSY_PIN) != HIGH);
        digitalWrite(DC_PIN, LOW);
        digitalWrite(CS_PIN, LOW);
        digitalWrite(_pinCSS, LOW);

        digitalWrite(RESET_PIN, LOW);
        digitalWrite(PNLON_PIN, LOW);   // PANEL_OFF# = 0
        digitalWrite(_pinCSS, HIGH);    // CSS# = 1
    }
    else if (_eScreen_iTC_BWR == eScreen_EPD_iTC_1220_BWR)
    {
        _reset(200, 20, 200, 200, 5);

        // Send image data
        uint8_t data1_1220[] = {0x00, 0x3b, 0x00, 0x00, 0x1f, 0x03}; // --- 12.2 specific
        _sendIndexData(0x13, data1_1220, 6); // DUW for Both Master and Slave
        uint8_t data2_1220[] = {0x00, 0x3b, 0x00, 0xc9}; // --- 12.2 specific
        _sendIndexData(0x90, data2_1220, 4); // DRFW for Both Master and Slave
        uint8_t data3_1220[] = {0x3b, 0x00, 0x14};

        // Master
        _sendIndexDataMaster(0x12, data3_1220, 3); // RAM_RW
        _sendIndexDataMaster(0x10, blackBuffer, _sizeFrame); // First frame
        _sendIndexDataMaster(0x12, data3_1220, 3); // RAM_RW
        _sendIndexDataMaster(0x11, redBuffer, _sizeFrame);   // Second frame

        // Slave
        _sendIndexDataSlave(0x12, data3_1220, 3); // RAM_RW
        _sendIndexDataSlave(0x10, blackBuffer + _sizeFrame, _sizeFrame); // First frame
        _sendIndexDataSlave(0x12, data3_1220, 3); // RAM_RW
        _sendIndexDataSlave(0x11, redBuffer + _sizeFrame, _sizeFrame); // Second frame

        // Initial COG
        uint8_t data4_1220[] = {0x7d};
        _sendIndexData(0x05, data4_1220, 1);
        delay_ms(200);
        uint8_t data5_1220[] = {0x00};
        _sendIndexData(0x05, data5_1220, 1);
        delay_ms(10);
        uint8_t data6_1220[] = {0x3f};
        _sendIndexData(0xc2, data6_1220, 1);
        delay_ms(1);
        uint8_t data7_1220[] = {0x80};
        _sendIndexData(0xd8, data7_1220, 1); // MS_SYNC
        uint8_t data8_1220[] = {0x00};
        _sendIndexData(0xd6, data8_1220, 1); // BVSS
        uint8_t data9_1220[] = {0x10};
        _sendIndexData(0xa7, data9_1220, 1);
        delay_ms(100);
        _sendIndexData(0xa7, data5_1220, 1);
        delay_ms(100);
        uint8_t data10_1220[] = {0x00, 0x12}; // --- 12.2 specific
        _sendIndexData(0x03, data10_1220, 2); // OSC
        _sendIndexDataMaster(0x44, data5_1220, 1); // Master
        uint8_t data11_1220[] = {0x80};
        _sendIndexDataMaster(0x45, data11_1220, 1); // Master
        _sendIndexDataMaster(0xa7, data9_1220, 1); // Master
        delay_ms(100);
        _sendIndexDataMaster(0xa7, data5_1220, 1); // Master
        delay_ms(100);
        uint8_t data12_1220[] = {0x06};
        _sendIndexDataMaster(0x44, data12_1220, 1); // Master
        uint8_t data13_1220[] = {0x82};
        //        uint8_t data13_1220[] = { getTemperature(0x50, 0x82) };
        _sendIndexDataMaster(0x45, data13_1220, 1); // Temperature 0x82@25C   0°C = 0x50, 25°C = 0x82
        _sendIndexDataMaster(0xa7, data9_1220, 1); // Master
        delay_ms(100);
        _sendIndexDataMaster(0xa7, data5_1220, 1); // Master
        delay_ms(100);

        _sendIndexDataSlave(0x44, data5_1220, 1); // Slave
        _sendIndexDataSlave(0x45, data11_1220, 1); // Slave
        _sendIndexDataSlave(0xa7, data9_1220, 1); // Slave
        delay_ms(100);
        _sendIndexDataSlave(0xa7, data5_1220, 1); // Slave
        delay_ms(100);
        _sendIndexDataSlave(0x44, data12_1220, 1); // Slave
        _sendIndexDataSlave(0x45, data13_1220, 1); // Temperature 0x82@25C   0°C = 0x50, 25°C = 0x82
        _sendIndexDataSlave(0xa7, data9_1220, 1); // Slave
        delay_ms(100);
        _sendIndexDataSlave(0xa7, data5_1220, 1); // Master
        delay_ms(100);

        uint8_t data14_1220[] = {0x25};
        _sendIndexData(0x60, data14_1220, 1); // TCON
        uint8_t data15_1220[] = {0x01};
        _sendIndexDataMaster(0x61, data15_1220, 1); // STV_DIR for Master
        uint8_t data16_1220[] = {0x00};
        _sendIndexData(0x01, data16_1220, 1); // DCTL
        uint8_t data17_1220[] = {0x00};
        _sendIndexData(0x02, data17_1220, 1); // VCOM

        // DC-DC soft-start
        uint8_t  index51_1220[] = {0x50, 0x01, 0x0a, 0x01};
        _sendIndexData(0x51, &index51_1220[0], 2);
        uint8_t  index09_1220[] = {0x1f, 0x9f, 0x7f, 0xff};

        for (int value = 1; value <= 4; value++)
        {
            _sendIndexData(0x09, &index09_1220[0], 1);
            index51_1220[1] = value;
            _sendIndexData(0x51, &index51_1220[0], 2);
            _sendIndexData(0x09, &index09_1220[1], 1);
            delay_ms(2);
        }
        for (int value = 1; value <= 10; value++)
        {
            _sendIndexData(0x09, &index09_1220[0], 1);
            index51_1220[3] = value;
            _sendIndexData(0x51, &index51_1220[2], 2);
            _sendIndexData(0x09, &index09_1220[1], 1);
            delay_ms(2);
        }
        for (int value = 3; value <= 10; value++)
        {
            _sendIndexData(0x09, &index09_1220[2], 1);
            index51_1220[3] = value;
            _sendIndexData(0x51, &index51_1220[2], 2);
            _sendIndexData(0x09, &index09_1220[3], 1);
            delay_ms(2);
        }
        for (int value = 9; value >= 2; value--)
        {
            _sendIndexData(0x09, &index09_1220[2], 1);
            index51_1220[2] = value;
            _sendIndexData(0x51, &index51_1220[2], 2);
            _sendIndexData(0x09, &index09_1220[3], 1);
            delay_ms(2);
        }
        _sendIndexData(0x09, &index09_1220[3], 1);
        delay_ms(10);

        // Display Refresh Start
        while (digitalRead(BUSY_PIN) != HIGH);
        uint8_t data18_1220[] = {0x3c};
        _sendIndexData(0x15, data18_1220, 1); // Display Refresh
        delay_ms(5);

        // DC/DC off
        while (digitalRead(BUSY_PIN) != HIGH);
        uint8_t data19_1220[] = {0x7f};
        _sendIndexData(0x09, data19_1220, 1);
        uint8_t data20_1220[] = {0x7d};
        _sendIndexData(0x05, data20_1220, 1);
        _sendIndexData(0x09, data5_1220, 1);
        delay_ms(200);
        while (digitalRead(BUSY_PIN) != HIGH);
        digitalWrite(DC_PIN, LOW);
        digitalWrite(CS_PIN, LOW);
        digitalWrite(_pinCSS, LOW);

        digitalWrite(RESET_PIN, LOW);
        digitalWrite(PNLON_PIN, LOW);   // PANEL_ON# = 1
        digitalWrite(_pinCSS, HIGH);    // CSS# = 1
    }
    else
    {
        _reset(5, 5, 10, 5, 5);

        uint8_t data9[] = {0x0e};
        _sendIndexData(0x00, data9, 1); // Soft-reset
        delay_ms(5);

        uint8_t data7[] = {0x19};
        //        uint8_t data7[] = { getTemperature() };
        _sendIndexData(0xe5, data7, 1);                 // Input Temperature 0°C = 0x00, 22°C = 0x16, 25°C = 0x19
        uint8_t data6[] = {0x02};
        _sendIndexData(0xe0, data6, 1); // Active Temperature

        // Send image data
        _sendIndexData(0x10, blackBuffer, _sizeFrame); // First frame
        _sendIndexData(0x13, redBuffer, _sizeFrame);   // Second frame

        delay_ms(50);
        uint8_t data8[] = {0x00};
        _sendIndexData(0x04, data8, 1); // Power on
        delay_ms(5);

        while (digitalRead(BUSY_PIN) != HIGH);
        _sendIndexData(0x12, data8, 1); // Display Refresh
        delay_ms(5);

        while (digitalRead(BUSY_PIN) != HIGH);

        _sendIndexData(0x02, data8, 1); // Turn off DC/DC
        while (digitalRead(BUSY_PIN) != HIGH);
        digitalWrite(DC_PIN, LOW);
        digitalWrite(CS_PIN, LOW);

        digitalWrite(RESET_PIN, LOW);
        digitalWrite(PNLON_PIN, LOW);
    }
    digitalWrite(CS_PIN, HIGH); // CS# = 1
    SPI.end();
}

void Screen_iTC_BWR::clear(uint16_t colour)
{
    if (colour == myColours.red)
    {
        // physical red 01
        memset(_newImage, 0x00, _sizePageColour);
        memset(_newImage + _sizePageColour, 0xff, _sizePageColour);
    }
    else if (colour == myColours.grey)
    {
        for (uint16_t i = 0; i < _widthBuffer; i++)
        {
            uint16_t pattern = (i % 2) ? 0b10101010 : 0b01010101;
            for (uint16_t j = 0; j < _heightBuffer; j++)
            {
                _newImage[i * _heightBuffer + j] = pattern;
            }
        }
        memset(_newImage + _sizePageColour, 0x00, _sizePageColour);
    }
    else if (colour == myColours.darkRed)
    {
        // red = 0-1, black = 1-0, white 0-0
        for (uint16_t i = 0; i < _widthBuffer; i++)
        {
            uint16_t pattern1 = (i % 2) ? 0b10101010 : 0b01010101; // black
            uint16_t pattern2 = (i % 2) ? 0b01010101 : 0b10101010; // red
            for (uint16_t j = 0; j < _heightBuffer; j++)
            {
                _newImage[i * _heightBuffer + j] = pattern1;
                _newImage[i * _heightBuffer + j + _sizePageColour] = pattern2;
            }
        }
    }
    else if (colour == myColours.lightRed)
    {
        // red = 0-1, black = 1-0, white 0-0
        for (uint16_t i = 0; i < _widthBuffer; i++)
        {
            uint16_t pattern1 = (i % 2) ? 0b00000000 : 0b00000000; // white
            uint16_t pattern2 = (i % 2) ? 0b01010101 : 0b10101010; // red
            for (uint16_t j = 0; j < _heightBuffer; j++)
            {
                _newImage[i * _heightBuffer + j] = pattern1;
                _newImage[i * _heightBuffer + j + _sizePageColour] = pattern2;
            }
        }
    }
    else if ((colour == myColours.white) xor _invert)
    {
        // physical black 00
        memset(_newImage, 0x00, _sizePageColour);
        memset(_newImage + _sizePageColour, 0x00, _sizePageColour);
    }
    else
    {
        // physical white 10
        memset(_newImage, 0xff, _sizePageColour);
        memset(_newImage + _sizePageColour, 0x00, _sizePageColour);
    }
}

void Screen_iTC_BWR::invert(bool flag)
{
    _invert = flag;
}

void Screen_iTC_BWR::_setPoint(uint16_t x1, uint16_t y1, uint16_t colour)
{
    // Orient and check coordinates are within screen
    // _orientCoordinates() returns false=success, true=error
    if (_orientCoordinates(x1, y1))
    {
        return;
    }

    uint32_t z1 = _getZ(x1, y1);

    // Convert combined colours into basic colours
    bool flagOdd = ((x1 + y1) % 2 == 0);

    if (colour == myColours.darkRed)
    {
        if (flagOdd)
        {
            colour = myColours.red; // red
        }
        else
        {
            colour = _invert ? myColours.white : myColours.black; // white
        }
    }
    else if (colour == myColours.lightRed)
    {
        if (flagOdd)
        {
            colour = myColours.red; // red
        }
        else
        {
            colour = _invert ? myColours.black : myColours.white; // black
        }
    }
    else if (colour == myColours.grey)
    {
        if (flagOdd)
        {
            colour = myColours.black; // black
        }
        else
        {
            colour = myColours.white; // white
        }
    }

    // Basic colours
    if (colour == myColours.red)
    {
        // physical red 01
        bitClear(_newImage[z1], 7 - (y1 % 8));
        bitSet(_newImage[_sizePageColour + z1], 7 - (y1 % 8));
    }
    else if ((colour == myColours.white) xor _invert)
    {
        // physical black 00
        bitClear(_newImage[z1], 7 - (y1 % 8));
        bitClear(_newImage[_sizePageColour + z1], 7 - (y1 % 8));
    }
    else if ((colour == myColours.black) xor _invert)
    {
        // physical white 10
        bitSet(_newImage[z1], 7 - (y1 % 8));
        bitClear(_newImage[_sizePageColour + z1], 7 - (y1 % 8));
    }
}

void Screen_iTC_BWR::_setOrientation(uint8_t orientation)
{
    _orientation = orientation % 4;
}

bool Screen_iTC_BWR::_orientCoordinates(uint16_t &x, uint16_t &y)
{
    bool flag = false; // false=success, true=error
    switch (_orientation)
    {
        case 1: // checked

            if ((x < _widthScreen) and (y < _heightScreen))
            {
                x = _widthScreen - 1 - x ;
            }
            else
            {
                flag = true;
            }

            break;

        case 2: // checked

            if ((x < _heightScreen) and (y < _widthScreen))
            {
                x = _heightScreen - 1 - x;
                y = _widthScreen  - 1 - y;
            }
            else
            {
                flag = true;
            }

            swap(x, y);
            break;

        case 3: // checked

            if ((x < _widthScreen) and (y < _heightScreen))
            {
                y = _heightScreen  - 1 - y;
            }
            else
            {
                flag = true;
            }
            break;

        default: // checked

            if ((x < _heightScreen) and (y < _widthScreen))
            {
                swap(x, y);
            }
            else
            {
                flag = true;
            }
            break;
    }

    return flag;
}

uint32_t Screen_iTC_BWR::_getZ(uint16_t x1, uint16_t y1)
{
    uint32_t z1 = 0;
    // According to 12.2 inch Spectra Application Note
    // at http:// www.pervasivedisplays.com/LiteratureRetrieve.aspx?ID=245146
    if ((_eScreen_iTC_BWR == eScreen_EPD_iTC_970_BWR) or (_eScreen_iTC_BWR == eScreen_EPD_iTC_1220_BWR))
        // if (_pinCSS > 0)
    {
        if (y1 >= (_heightScreen >> 1))
        {
            y1 -= (_heightScreen >> 1); // rebase y1
            z1 += (_sizePageColour >> 1); // buffer second half
        }
        z1 += (uint32_t)x1 * (_heightBuffer  >> 1) + (y1 >> 3);
    }
    else
    {
        z1 = (uint32_t)x1 * _heightBuffer + (y1 >> 3);
    }
    return z1;
}

uint16_t Screen_iTC_BWR::_getPoint(uint16_t x1, uint16_t y1)
{
    // Orient and check coordinates are within screen
    // _orientCoordinates() returns false=success, true=error
    if (_orientCoordinates(x1, y1))
    {
        return 0;
    }

    uint16_t result = 0;
    uint8_t value = 0;

    uint32_t z1 = _getZ(x1, y1);
    value = bitRead(_newImage[z1], 7 - (y1 % 8));
    value <<= 4;
    value |= bitRead(_newImage[_sizePageColour + z1], 7 - (y1 % 8));

    // red = 0-1, black = 1-0, white 0-0
    switch (value)
    {
        case 0x10:

            result = myColours.white;
            break;

        case 0x01:

            result = myColours.red;
            break;

        default:

            result = myColours.black;
            break;
    }

    return result;
}

void Screen_iTC_BWR::point(uint16_t x1, uint16_t y1, uint16_t colour)
{
    _setPoint(x1, y1, colour);
}

uint16_t Screen_iTC_BWR::readPixel(uint16_t x1, uint16_t y1)
{
    return _getPoint(x1, y1);
}

// Utilities
void Screen_iTC_BWR::_sendIndexData(uint8_t index, const uint8_t *data, uint32_t len)
{
    digitalWrite(DC_PIN, LOW); // DC Low
    digitalWrite(CS_PIN, LOW); // CS Low
    // _pinCSS as a proxy for eScreen_EPD_iTC_970_BWR and eScreen_EPD_iTC_1220_BWR
    // as _pinCSS is > 0 for those screens only
    // if ((_eScreen_iTC_BWR == eScreen_EPD_iTC_970_BWR) or (_eScreen_iTC_BWR == eScreen_EPD_iTC_1220_BWR))
    if (_pinCSS > 0)
    {
        digitalWrite(_pinCSS, LOW); // CSS Low
        delayMicroseconds(450); // 450 + 50 = 500
    }
    delayMicroseconds(50);
    SPI.transfer(index);
    delayMicroseconds(50);
    // if ((_eScreen_iTC_BWR == eScreen_EPD_iTC_970_BWR) or (_eScreen_iTC_BWR == eScreen_EPD_iTC_1220_BWR))
    if (_pinCSS > 0)
    {
        delayMicroseconds(450); // 450 + 50 = 500
        digitalWrite(_pinCSS, HIGH); // CSS HIGH
    }
    digitalWrite(CS_PIN, HIGH); // CS High
    digitalWrite(DC_PIN, HIGH); // DC High
    digitalWrite(CS_PIN, LOW); // CS Low
    // if ((_eScreen_iTC_BWR == eScreen_EPD_iTC_970_BWR) or (_eScreen_iTC_BWR == eScreen_EPD_iTC_1220_BWR))
    if (_pinCSS > 0)
    {
        digitalWrite(_pinCSS, LOW); // CSS Low
        delayMicroseconds(450); // 450 + 50 = 500
    }
    delayMicroseconds(50);
    for (uint32_t i = 0; i < len; i++)
    {
        SPI.transfer(data[i]);
    }
    delayMicroseconds(50);
    // if ((_eScreen_iTC_BWR == eScreen_EPD_iTC_970_BWR) or (_eScreen_iTC_BWR == eScreen_EPD_iTC_1220_BWR))
    if (_pinCSS > 0)
    {
        delayMicroseconds(450); // 450 + 50 = 500
        digitalWrite(_pinCSS, HIGH); // CSS HIGH
    }
    digitalWrite(CS_PIN, HIGH); // CS High
}

// Software SPI Master protocl setup
void Screen_iTC_BWR::_sendIndexDataMaster(uint8_t index, const uint8_t *data, uint32_t len)
{
    digitalWrite(_pinCSS, HIGH); // CSS slave High
    digitalWrite(DC_PIN, LOW); // DC Low
    digitalWrite(CS_PIN, LOW); // CS Low
    delayMicroseconds(500);
    SPI.transfer(index);
    delayMicroseconds(500);
    digitalWrite(CS_PIN, HIGH); // CS High
    digitalWrite(DC_PIN, HIGH); // DC High
    digitalWrite(CS_PIN, LOW);  // CS Low
    delayMicroseconds(500);
    for (uint32_t i = 0; i < len; i++)
    {
        SPI.transfer(data[ i ]);
    }
    delayMicroseconds(500);
    digitalWrite(CS_PIN, HIGH); // CS High
}

// Software SPI Slave protocol setup
void Screen_iTC_BWR::_sendIndexDataSlave(uint8_t index, const uint8_t *data, uint32_t len)
{
    digitalWrite(CS_PIN, HIGH); // CS Master High
    digitalWrite(DC_PIN, LOW);  // DC Low
    digitalWrite(_pinCSS, LOW); // CS slave Low
    delayMicroseconds(500);
    SPI.transfer(index);
    delayMicroseconds(500);
    digitalWrite(_pinCSS, HIGH); // CS slave High
    digitalWrite(DC_PIN, HIGH);  // DC High
    digitalWrite(_pinCSS, LOW);  // CS slave Low
    delayMicroseconds(500);

    for (uint32_t i = 0; i < len; i++)
    {
        SPI.transfer(data[ i ]);
    }
    delayMicroseconds(500);
    digitalWrite(_pinCSS, HIGH); // CS slave High
}

uint8_t Screen_iTC_BWR::getRefreshTime()
{
    return _refreshTime;
}

font_s Screen_iTC_BWR::getFontDetails()
{
    return _font;
}
