#pragma once
#include <Arduino.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#include <lcdFrame.h>

#include <joyPad.h>

#ifdef _BOARD_ESP32_
#define PIN_LCD_CLK 18
#define PIN_LCD_DATA 23
#define PIN_LCD_CS 4
#define PIN_LCD_RST 5
#endif

#ifdef _BOARD_UNO_
#define PIN_LCD_CLK 8
#define PIN_LCD_DATA 9
#define PIN_LCD_CS 10
#define PIN_LCD_RST 11

#endif

#ifdef _BOARD_MEGA2560_
#define PIN_LCD_CLK 18
#define PIN_LCD_DATA 23
#define PIN_LCD_CS 4
#define PIN_LCD_RST 5
#endif

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0,
                                 /* clock=*/PIN_LCD_CLK,
                                 /* data=*/PIN_LCD_DATA,
                                 /* CS=*/PIN_LCD_CS,
                                 /* reset=*/PIN_LCD_RST);

joyPad Tombol;
lcdFrame Framex(u8g2);
