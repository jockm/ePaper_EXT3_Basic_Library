//
// Screen_EPD_EXT3.cpp
// Library C++ code
// ----------------------------------
//
// Project      LCD_screen Library Suite
//
// Created by   Rei Vilo, 28 Jun 2016
//
//
// Copyright    © Rei Vilo, 2010-2020
// Licence      Creative Commons Attribution-NonCommercial-ShareAlike 4.0 Unported (CC BY-NC-SA 4.0)
//


// Library header
#include "Screen_EPD_EXT3.h"

#if defined(ENERGIA)
///
/// @brief      Proxy for SPISettings
/// @details    Not implemented in Energia
/// @see https://www.arduino.cc/en/Reference/SPISettings
///
struct _SPISettings_s
{
    uint32_t clock; ///< in Hz, checked against SPI_CLOCK_MAX = 16000000
    uint8_t bitOrder; ///< LSBFIRST, MSBFIRST
    uint8_t dataMode; ///< SPI_MODE0, SPI_MODE1, SPI_MODE2, SPI_MODE3
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


#ifndef SPI_CLOCK_MAX
#define SPI_CLOCK_MAX 16000000
#endif

// Class
Screen_EPD_EXT3::Screen_EPD_EXT3(eScreen_EPD_EXT3_t eScreen_EPD_EXT3)
{
    _newImage = 0;
    _eScreen_EPD_EXT3 = eScreen_EPD_EXT3;
}

void Screen_EPD_EXT3::begin()
{
    _eScreen_EPD_EXT3 = _eScreen_EPD_EXT3;
    _pinCSS = 0;

    _screenColourBits = 2; // BWR

    switch (_eScreen_EPD_EXT3)
    {
        case eScreen_EPD_EXT3_154_BWR:

            _widthScreen =  152; // x = wide size
            _heightScreen = 152; // y = small size
            _screenDiagonal = 154;
            _refreshTime = 16;
            break;

        case eScreen_EPD_EXT3_213_BWR:

            _widthScreen =  212; // x = wide size
            _heightScreen = 104; // y = small size
            _screenDiagonal = 213;
            _refreshTime = 15;
            break;

        case eScreen_EPD_EXT3_266_BWR:

            _widthScreen =  296; // x = wide size
            _heightScreen = 152; // y = small size
            _screenDiagonal = 266;
            _refreshTime = 15;
            break;

        case eScreen_EPD_EXT3_271_BWR:

            _widthScreen =  264; // x = wide size
            _heightScreen = 176; // y = small size
            _screenDiagonal = 271;
            _refreshTime = 19;
            break;

        case eScreen_EPD_EXT3_287_BWR:

            _widthScreen =  296; // x = wide size
            _heightScreen = 128; // y = small size
            _screenDiagonal = 287;
            _refreshTime = 14;
            break;

        case eScreen_EPD_EXT3_370_BWR:

            _widthScreen =  416; // x = wide size
            _heightScreen = 240; // y = small size
            _screenDiagonal = 370;
            _refreshTime = 15; // ?
            break;

        case eScreen_EPD_EXT3_420_BWR:

            _widthScreen =  300; // x = wide size
            _heightScreen = 400; // y = small size
            _screenDiagonal = 420;
            _refreshTime = 19;
            break;

        case eScreen_EPD_EXT3_437_BWR:

            _widthScreen =  480; // x = wide size
            _heightScreen = 176; // y = small size
            _screenDiagonal = 437;
            _refreshTime = 21;
            break;

        case eScreen_EPD_EXT3_565_BWR:

            _widthScreen =  600; // x = wide size
            _heightScreen = 448; // y = small size
            _screenDiagonal = 565;
            _refreshTime = 32;
            break;

        case eScreen_EPD_EXT3_581_BWR:

            _widthScreen =  720; // x = wide size
            _heightScreen = 256; // y = small size
            _screenDiagonal = 581;
            _refreshTime = 32;
            break;

        case eScreen_EPD_EXT3_740_BWR:

            _widthScreen =  800; // x = wide size
            _heightScreen = 480; // y = small size
            _screenDiagonal = 740;
            _refreshTime = 32;
            break;

        case eScreen_EPD_EXT3_970_BWR:

            _widthScreen =  672; // x = wide size
            _heightScreen = 960; // Actually, 960 = 480 x 2, y = small size
            _screenDiagonal = 970;
            _refreshTime = 45;
            break;

        case eScreen_EPD_EXT3_1220_BWR:

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
    switch (_eScreen_EPD_EXT3)
    {
        case eScreen_EPD_EXT3_970_BWR:
        case eScreen_EPD_EXT3_1220_BWR:

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

    // Initialise the /CS pins
    // pinMode(PNLON_PIN, OUTPUT);
    pinMode(PANEL_CS_PIN, OUTPUT);
    digitalWrite(PANEL_CS_PIN, HIGH); // CS# = 1

    // New generic solution

    pinMode(PANEL_DC_PIN, OUTPUT);
    pinMode(PANEL_RESET_PIN, OUTPUT);
    pinMode(PANEL_BUSY_PIN, INPUT); // All Pins 0

    // Initialise Flash /CS as HIGH
#if defined(FLASH_CS_PIN)
#if (FLASH_CS_PIN > 0)
    pinMode(FLASH_CS_PIN, OUTPUT);
    digitalWrite(FLASH_CS_PIN, HIGH);
#endif // FLASH_CS_PIN
#endif // FLASH_CS_PIN

    // Initialise slave panel /CS as HIGH
#if defined(PANEL_CSS_PIN)
#if (PANEL_CSS_PIN > 0)
    pinMode(PANEL_CSS_PIN, OUTPUT);
    digitalWrite(PANEL_CSS_PIN, HIGH);
#endif // PANEL_CSS_PIN
#endif // PANEL_CSS_PIN

    // Initialise slave Flash /CS as HIGH
#if defined(FLASH_CSS_PIN)
#if (FLASH_CSS_PIN > 0)
    pinMode(FLASH_CSS_PIN, OUTPUT);
    digitalWrite(FLASH_CSS_PIN, HIGH);
#endif // FLASH_CSS_PIN
#endif // FLASH_CSS_PIN

    // Initialise SD-card /CS as HIGH
#if defined(SD_CARD_CS_PIN)
#if (SD_CARD_CS_PIN > 0)
    pinMode(SD_CARD_CS_PIN, OUTPUT);
    digitalWrite(SD_CARD_CS_PIN, HIGH);
#endif // SD_CARD_CS_PIN
#endif // SD_CARD_CS_PIN

    // Initialise SPI
    _settingScreen = {4000000, MSBFIRST, SPI_MODE0 };
    // _settingScreen = {1000000, MSBFIRST, SPI_MODE0 };

#if defined(ENERGIA)
    SPI.begin();
    SPI.setBitOrder(_settingScreen.bitOrder);
    SPI.setDataMode(_settingScreen.dataMode);
    SPI.setClockDivider(SPI_CLOCK_MAX / min(SPI_CLOCK_MAX, _settingScreen.clock));

#else
    //    SPI.setBitOrder(MSBFIRST);
    //    SPI.setDataMode(SPI_MODE0);
    //    SPI.setClockDivider(SPI_CLOCK_DIV32);
    SPI.beginTransaction(_settingScreen);
    SPI.begin();
#endif // ENERGIA

    // Reset
    switch (_eScreen_EPD_EXT3)
    {
        case eScreen_EPD_EXT3_420_BWR:
        case eScreen_EPD_EXT3_437_BWR:

            _reset(5, 5, 10, 5, 5);
            break;

        case eScreen_EPD_EXT3_565_BWR:
        case eScreen_EPD_EXT3_581_BWR:
        case eScreen_EPD_EXT3_740_BWR:

            _reset(200, 20, 200, 50, 5);
            break;

        case eScreen_EPD_EXT3_970_BWR:
        case eScreen_EPD_EXT3_1220_BWR:

            _reset(200, 20, 200, 200, 5);
            break;

        default:

            _reset(5, 5, 10, 5, 5);
            break;
    }

    _screenWidth = _heightScreen;
    _screenHeigth = _widthScreen;

    // Standard
    LCD_Screen_Buffer::begin();

    setOrientation(0);
    if (_f_fontMax() > 0)
    {
        _f_selectFont(0);
    }
    _f_fontSolid = false;

    _penSolid = false;
    _invert = false;

    clear();
}

void Screen_EPD_EXT3::_reset(uint32_t ms1, uint32_t ms2, uint32_t ms3, uint32_t ms4, uint32_t ms5)
{
    // digitalWrite(PNLON_PIN, HIGH);  // PANEL_ON# = 1
    delay_ms(ms1);                  // delay_ms 5ms
    digitalWrite(PANEL_RESET_PIN, HIGH);  // RES# = 1
    delay_ms(ms2);                  // delay_ms 5ms
    digitalWrite(PANEL_RESET_PIN, LOW);
    delay_ms(ms3);
    digitalWrite(PANEL_RESET_PIN, HIGH);
    delay_ms(ms4);

    digitalWrite(PANEL_CS_PIN, HIGH);     // CS# = 1

    // For 9.7 and 12.2 panels
    if ((_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_970_BWR) or (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_1220_BWR))
    {
#if defined(PANEL_CSS_PIN)
#if (PANEL_CSS_PIN > 0)
        digitalWrite(PANEL_CSS_PIN, HIGH);// CSS# = 1
#endif // PANEL_CSS_PIN
#endif // PANEL_CSS_PIN
    }
    delay_ms(ms5);
}

String Screen_EPD_EXT3::WhoAmI()
{
    String text = "iTC ";
    text += String(_screenDiagonal / 100);
    text += ".";
    text += String(_screenDiagonal % 100);
    text += "\" BWR";

#if (FONT_MODE == USE_FONT_HEADER)
    text += " (h)";
#elif (FONT_MODE == USE_FONT_FLASH)
    text += " (f)";
#elif (FONT_MODE == USE_FONT_TERMINAL)
    text += " (t)";
#endif
    return text;
}

void Screen_EPD_EXT3::flush()
{
    uint8_t * blackBuffer = _newImage;
    uint8_t * redBuffer = _newImage + _sizePageColour;

    // Three groups:
    // + small: up to 4.37
    // + medium: 5.65, 5.81 and 7.4
    // + large: 9.7 and 12.2
    // switch..case doesn't allow variable declarations
    //
    if ((_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_565_BWR) or (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_581_BWR) or (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_740_BWR))
    {
        _reset(200, 20, 200, 50, 5);

        // Send image data
        if (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_565_BWR)
        {
            uint8_t data1_565[] = {0x00, 0x37, 0x00, 0x00, 0x57, 0x02 }; // DUW
            _sendIndexData(0x13, data1_565, 6); // DUW
            uint8_t data2_565[] = {0x00, 0x37, 0x00, 0x97 }; // DRFW
            _sendIndexData(0x90, data2_565, 4); // DRFW
            uint8_t data3_565[] = {0x37, 0x00, 0x14 }; // RAM_RW
            _sendIndexData(0x12, data3_565, 3); // RAM_RW
    }
        else if (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_581_BWR)
    {
            uint8_t data1_565[] = {0x00, 0x1f, 0x50, 0x00, 0x1f, 0x03}; // DUW
            _sendIndexData(0x13, data1_565, 6); // DUW
            uint8_t data2_565[] = {0x00, 0x1f, 0x00, 0xc9}; // DRFW
            _sendIndexData(0x90, data2_565, 4); // DRFW
            uint8_t data3_565[] = {0x1f, 0x50, 0x14}; // RAM_RW
            _sendIndexData(0x12, data3_565, 3); // RAM_RW
    }
        else if (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_740_BWR)
    {
            uint8_t data1_565[] = {0x00, 0x3b, 0x00, 0x00, 0x1f, 0x03}; // DUW
        _sendIndexData(0x13, data1_565, 6); // DUW
            uint8_t data2_565[] = {0x00, 0x3b, 0x00, 0xc9}; // DRFW
        _sendIndexData(0x90, data2_565, 4); // DRFW
            uint8_t data3_565[] = {0x3b, 0x00, 0x14}; // RAM_RW
        _sendIndexData(0x12, data3_565, 3); // RAM_RW
        }

        _sendIndexData(0x10, blackBuffer, _sizeFrame); // First frame

        if (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_565_BWR)
        {
            uint8_t data3_565[] = {0x37, 0x00, 0x14 }; // RAM_RW
            _sendIndexData(0x12, data3_565, 3); // RAM_RW
        }
        else if (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_581_BWR)
        {
            uint8_t data3_565[] = {0x1f, 0x50, 0x14}; // RAM_RW
            _sendIndexData(0x12, data3_565, 3); // RAM_RW
        }
        else if (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_740_BWR)
        {
            uint8_t data3_565[] = {0x3b, 0x00, 0x14}; // RAM_RW
        _sendIndexData(0x12, data3_565, 3); // RAM_RW
        }
        _sendIndexData(0x11, redBuffer, _sizeFrame); // Second frame

        // Initial COG
        uint8_t data4_565[] = {0x7d};
        _sendIndexData(0x05, data4_565, 1);
        delay_ms(200);
        uint8_t data5_565[] = {0x00};
        _sendIndexData(0x05, data5_565, 1);
        delay_ms(10);
        uint8_t data6_565[] = {0x3f};
        _sendIndexData(0xc2, data6_565, 1);
        delay_ms(1);
        uint8_t data7_565[] = {0x00};
        _sendIndexData(0xd8, data7_565, 1); // MS_SYNC mtp_0x1d
        uint8_t data8_565[] = {0x00};
        _sendIndexData(0xd6, data8_565, 1); // BVSS mtp_0x1e
        uint8_t data9_565[] = {0x10};
        _sendIndexData(0xa7, data9_565, 1);
        delay_ms(100);
        _sendIndexData(0xa7, data5_565, 1);
        delay_ms(100);
        //        uint8_t data10_565[] = {0x00, 0x02 };
        if (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_565_BWR)
        {
            uint8_t data10_565[] = {0x00, 0x02}; // OSC
            _sendIndexData(0x03, data10_565, 2); // OSC mtp_0x12
        }
        else if (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_581_BWR)
        {
            uint8_t data10_565[] = {0x00, 0x01}; // OSC
            _sendIndexData(0x03, data10_565, 2); // OSC mtp_0x12
        }
        else if (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_740_BWR)
        {
            uint8_t data10_565[] = {0x00, 0x01}; // OSC
        _sendIndexData(0x03, data10_565, 2); // OSC mtp_0x12
        }
        _sendIndexData(0x44, data5_565, 1);
        uint8_t data11_565[] = {0x80 };
        _sendIndexData(0x45, data11_565, 1);
        _sendIndexData(0xa7, data9_565, 1);
        delay_ms(100);
        _sendIndexData(0xa7, data7_565, 1);
        delay_ms(100);
        uint8_t data12_565[] = {0x06 };
        _sendIndexData(0x44, data12_565, 1);
        uint8_t data13_565[] = {0x82 };
        _sendIndexData(0x45, data13_565, 1); // Temperature 0x82@25C
        _sendIndexData(0xa7, data9_565, 1);
        delay_ms(100);
        _sendIndexData(0xa7, data7_565, 1);
        delay_ms(100);
        uint8_t data14_565[] = {0x25 };
        _sendIndexData(0x60, data14_565, 1); // TCON mtp_0x0b
        // uint8_t data15_565[] = {0x01 };
        if (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_565_BWR)
        {
            uint8_t data15_565[] = {0x01}; // STV_DIR
        _sendIndexData(0x61, data15_565, 1); // STV_DIR mtp_0x1c
        }
        else if (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_581_BWR)
        {
            uint8_t data15_565[] = {0x00}; // STV_DIR
            _sendIndexData(0x61, data15_565, 1); // STV_DIR mtp_0x1c
        }
        else if (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_740_BWR)
        {
            uint8_t data15_565[] = {0x00}; // STV_DIR
            _sendIndexData(0x61, data15_565, 1); // STV_DIR mtp_0x1c
        }
        uint8_t data16_565[] = {0x00 };
        _sendIndexData(0x01, data16_565, 1); // DCTL mtp_0x10
        uint8_t data17_565[] = {0x00 };
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

        // Display Refresh Start
        while (digitalRead(PANEL_BUSY_PIN) != HIGH);
        uint8_t data18_565[] = {0x3c };
        _sendIndexData(0x15, data18_565, 1); //Display Refresh
        delay_ms(5);

        // DC-DC off
        while (digitalRead(PANEL_BUSY_PIN) != HIGH);
        uint8_t data19_565[] = {0x7f };
        _sendIndexData(0x09, data19_565, 1);
        uint8_t data20_565[] = {0x7d };
        _sendIndexData(0x05, data20_565, 1);
        _sendIndexData(0x09, data5_565, 1);
        delay_ms(200);

        while (digitalRead(PANEL_BUSY_PIN) != HIGH);
        digitalWrite(PANEL_DC_PIN, LOW);
        digitalWrite(PANEL_CS_PIN, LOW);
        digitalWrite(PANEL_RESET_PIN, LOW);
        // digitalWrite(PNLON_PIN, LOW); // PANEL_OFF# = 0
        }
    else if ((_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_970_BWR) or (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_1220_BWR))
    {
        _reset(200, 20, 200, 200, 5);

        // Send image data
        if (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_970_BWR)
        {
            uint8_t data1_970[] = {0x00, 0x3b, 0x00, 0x00, 0x9f, 0x02}; // DUW
            _sendIndexData(0x13, data1_970, 6); // DUW for Both Master and Slave
            uint8_t data2_970[] = {0x00, 0x3b, 0x00, 0xa9}; // DRFW
            _sendIndexData(0x90, data2_970, 4); // DRFW for Both Master and Slave
    }
        else if (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_1220_BWR)
    {
            uint8_t data1_970[] = {0x00, 0x3b, 0x00, 0x00, 0x1f, 0x03}; // DUW
        _sendIndexData(0x13, data1_970, 6); // DUW for Both Master and Slave
            uint8_t data2_970[] = {0x00, 0x3b, 0x00, 0xc9}; // DRFW
        _sendIndexData(0x90, data2_970, 4); // DRFW for Both Master and Slave
        }

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
        // uint8_t data10_970[] = {0x00, 0x11}; // --- 9.7 specific
        if (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_970_BWR)
        {
            uint8_t data10_970[] = {0x00, 0x11}; // OSC
            _sendIndexData(0x03, data10_970, 2); // OSC
        }
        else if (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_1220_BWR)
        {
            uint8_t data10_970[] = {0x00, 0x12}; // OSC
        _sendIndexData(0x03, data10_970, 2); // OSC
        }

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
        //        uint8_t data13_970[] = {getTemperature(0x50, 0x82) };
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
        while (digitalRead(PANEL_BUSY_PIN) != HIGH);
        uint8_t data18_970[] = {0x3c};
        _sendIndexData(0x15, data18_970, 1); // Display Refresh
        delay_ms(5);

        // DC/DC off
        while (digitalRead(PANEL_BUSY_PIN) != HIGH);
        uint8_t data19_970[] = {0x7f};
        _sendIndexData(0x09, data19_970, 1);
        uint8_t data20_970[] = {0x7d};
        _sendIndexData(0x05, data20_970, 1);
        _sendIndexData(0x09, data5_970, 1);
        delay_ms(200);
        while (digitalRead(PANEL_BUSY_PIN) != HIGH);
        digitalWrite(PANEL_DC_PIN, LOW);
        digitalWrite(PANEL_CS_PIN, LOW);

#if defined(PANEL_CSS_PIN)
#if (PANEL_CSS_PIN > 0)
        digitalWrite(PANEL_CSS_PIN, LOW);
#endif // PANEL_CSS_PIN
#endif // PANEL_CSS_PIN

        digitalWrite(PANEL_RESET_PIN, LOW);
        // digitalWrite(PNLON_PIN, LOW);   // PANEL_OFF# = 0

#if defined(PANEL_CSS_PIN)
#if (PANEL_CSS_PIN > 0)
        digitalWrite(PANEL_CSS_PIN, HIGH); // CSS# = 1
#endif // PANEL_CSS_PIN
#endif // PANEL_CSS_PIN
    }
    else // including 420 and 437
    {
        _reset(5, 5, 10, 5, 5);

        uint8_t data9[] = {0x0e};
        _sendIndexData(0x00, data9, 1); // Soft-reset
        delay_ms(5);

        uint8_t data7[] = {0x19};
        // uint8_t data7[] = {getTemperature() };
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

        while (digitalRead(PANEL_BUSY_PIN) != HIGH);
        _sendIndexData(0x12, data8, 1); // Display Refresh
        delay_ms(5);

        while (digitalRead(PANEL_BUSY_PIN) != HIGH);

        _sendIndexData(0x02, data8, 1); // Turn off DC/DC
        while (digitalRead(PANEL_BUSY_PIN) != HIGH);
        digitalWrite(PANEL_DC_PIN, LOW);
        digitalWrite(PANEL_CS_PIN, LOW);

        digitalWrite(PANEL_RESET_PIN, LOW);
        // digitalWrite(PNLON_PIN, LOW);
    }
    digitalWrite(PANEL_CS_PIN, HIGH); // CS# = 1
}

void Screen_EPD_EXT3::clear(uint16_t colour)
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

void Screen_EPD_EXT3::invert(bool flag)
{
    _invert = flag;
}

void Screen_EPD_EXT3::_setPoint(uint16_t x1, uint16_t y1, uint16_t colour)
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

void Screen_EPD_EXT3::_setOrientation(uint8_t orientation)
{
    _orientation = orientation % 4;
}

bool Screen_EPD_EXT3::_orientCoordinates(uint16_t &x, uint16_t &y)
{
    bool flag = true; // false=success, true=error
    switch (_orientation)
    {
        case 3: // checked, previously 1

            if ((x < _widthScreen) and (y < _heightScreen))
            {
                x = _widthScreen - 1 - x ;
                flag = false;
            }
            break;

        case 2: // checked

            if ((x < _heightScreen) and (y < _widthScreen))
            {
                x = _heightScreen - 1 - x;
                y = _widthScreen  - 1 - y;
                flag = false;
            }
            swap(x, y);
            break;

        case 1: // checked, previously 3

            if ((x < _widthScreen) and (y < _heightScreen))
            {
                y = _heightScreen  - 1 - y;
                flag = false;
            }
            break;

        default: // checked

            if ((x < _heightScreen) and (y < _widthScreen))
            {
                swap(x, y);
                flag = false;
            }
            break;
    }

    return flag;
}

uint32_t Screen_EPD_EXT3::_getZ(uint16_t x1, uint16_t y1)
{
    uint32_t z1 = 0;
    // According to 12.2 inch Spectra Application Note
    // at http:// www.pervasivedisplays.com/LiteratureRetrieve.aspx?ID=245146
    if ((_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_970_BWR) or (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_1220_BWR))
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

uint16_t Screen_EPD_EXT3::_getPoint(uint16_t x1, uint16_t y1)
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

            result = myColours.black;
            break;

        case 0x01:

            result = myColours.red;
            break;

        default:

            result = myColours.white;
            break;
    }

    return result;
}

void Screen_EPD_EXT3::point(uint16_t x1, uint16_t y1, uint16_t colour)
{
    _setPoint(x1, y1, colour);
}

uint16_t Screen_EPD_EXT3::readPixel(uint16_t x1, uint16_t y1)
{
    return _getPoint(x1, y1);
}

// Utilities
void Screen_EPD_EXT3::_sendIndexData(uint8_t index, const uint8_t *data, uint32_t len)
{
    digitalWrite(PANEL_DC_PIN, LOW); // DC Low
    digitalWrite(PANEL_CS_PIN, LOW); // CS Low
    if ((_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_970_BWR) or (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_1220_BWR))
    {
#if defined(PANEL_CSS_PIN)
#if (PANEL_CSS_PIN > 0)
        digitalWrite(PANEL_CSS_PIN, LOW);
        delayMicroseconds(450); // 450 + 50 = 500
#endif // PANEL_CSS_PIN
#endif // PANEL_CSS_PIN
    }
    delayMicroseconds(50);
    SPI.transfer(index);
    delayMicroseconds(50);
    if ((_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_970_BWR) or (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_1220_BWR))
    {
#if defined(PANEL_CSS_PIN)
#if (PANEL_CSS_PIN > 0)
        delayMicroseconds(450); // 450 + 50 = 500
        digitalWrite(PANEL_CSS_PIN, HIGH);
#endif // PANEL_CSS_PIN
#endif // PANEL_CSS_PIN
    }
    digitalWrite(PANEL_CS_PIN, HIGH); // CS High
    digitalWrite(PANEL_DC_PIN, HIGH); // DC High
    digitalWrite(PANEL_CS_PIN, LOW); // CS Low
    if ((_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_970_BWR) or (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_1220_BWR))
    {
#if defined(PANEL_CSS_PIN)
#if (PANEL_CSS_PIN > 0)
        digitalWrite(PANEL_CSS_PIN, LOW); // CSS Low
        delayMicroseconds(450); // 450 + 50 = 500
#endif // PANEL_CSS_PIN
#endif // PANEL_CSS_PIN
    }
    delayMicroseconds(50);
    for (uint32_t i = 0; i < len; i++)
    {
        SPI.transfer(data[i]);
    }
    delayMicroseconds(50);
    if ((_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_970_BWR) or (_eScreen_EPD_EXT3 == eScreen_EPD_EXT3_1220_BWR))
    {
#if defined(PANEL_CSS_PIN)
#if (PANEL_CSS_PIN > 0)
        delayMicroseconds(450); // 450 + 50 = 500
        digitalWrite(PANEL_CSS_PIN, HIGH);
#endif // PANEL_CSS_PIN
#endif // PANEL_CSS_PIN
    }
    digitalWrite(PANEL_CS_PIN, HIGH); // CS High
}

// Software SPI Master protocol setup
void Screen_EPD_EXT3::_sendIndexDataMaster(uint8_t index, const uint8_t *data, uint32_t len)
{
#if defined(PANEL_CSS_PIN)
#if (PANEL_CSS_PIN > 0)
    digitalWrite(PANEL_CSS_PIN, HIGH); // CS slave HIGH
#endif // PANEL_CSS_PIN
#endif // PANEL_CSS_PIN
    digitalWrite(PANEL_DC_PIN, LOW); // DC Low
    digitalWrite(PANEL_CS_PIN, LOW); // CS Low
    delayMicroseconds(500);
    SPI.transfer(index);
    delayMicroseconds(500);
    digitalWrite(PANEL_CS_PIN, HIGH); // CS High
    digitalWrite(PANEL_DC_PIN, HIGH); // DC High
    digitalWrite(PANEL_CS_PIN, LOW);  // CS Low
    delayMicroseconds(500);
    for (uint32_t i = 0; i < len; i++)
    {
        SPI.transfer(data[ i ]);
    }
    delayMicroseconds(500);
    digitalWrite(PANEL_CS_PIN, HIGH); // CS High
}

// Software SPI Slave protocol setup
void Screen_EPD_EXT3::_sendIndexDataSlave(uint8_t index, const uint8_t *data, uint32_t len)
{
    digitalWrite(PANEL_CS_PIN, HIGH); // CS Master High
    digitalWrite(PANEL_DC_PIN, LOW);  // DC Low
#if defined(PANEL_CSS_PIN)
#if (PANEL_CSS_PIN > 0)
    digitalWrite(PANEL_CSS_PIN, LOW); // CS slave LOW
#endif // PANEL_CSS_PIN
#endif // PANEL_CSS_PIN
    delayMicroseconds(500);
    SPI.transfer(index);
    delayMicroseconds(500);
#if defined(PANEL_CSS_PIN)
#if (PANEL_CSS_PIN > 0)
    digitalWrite(PANEL_CSS_PIN, HIGH); // CS slave HIGH
#endif // PANEL_CSS_PIN
#endif // PANEL_CSS_PIN
    digitalWrite(PANEL_DC_PIN, HIGH);  // DC HIGH
#if defined(PANEL_CSS_PIN)
#if (PANEL_CSS_PIN > 0)
    digitalWrite(PANEL_CSS_PIN, LOW); // CS slave LOW
#endif // PANEL_CSS_PIN
#endif // PANEL_CSS_PIN
    delayMicroseconds(500);

    for (uint32_t i = 0; i < len; i++)
    {
        SPI.transfer(data[ i ]);
    }
    delayMicroseconds(500);
#if defined(PANEL_CSS_PIN)
#if (PANEL_CSS_PIN > 0)
    digitalWrite(PANEL_CSS_PIN, HIGH); // CS slave HIGH
#endif // PANEL_CSS_PIN
#endif // PANEL_CSS_PIN
}

uint8_t Screen_EPD_EXT3::getRefreshTime()
{
    return _refreshTime;
}

font_s Screen_EPD_EXT3::getFontDetails()
{
    return _f_font;
}
