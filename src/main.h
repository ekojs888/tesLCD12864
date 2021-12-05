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

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/18, /* data=*/23, /* CS=*/4, /* reset=*/5);

joyPad Tombol;
lcdFrame Framex(u8g2);

// static const modelText menuATS[] PROGMEM = {
//     {0, "Menu", 10, 61, 1, true, false, 1, 1},
//     {1, "Setting", 10, 22, 1, true, false, 1, 2},
//     {1, "Menu Utama", 10, 35, 1, true, false, 1, 0},
//     {2, "Pompa", 10, 22, 1, true, false, 0, 1},
//     {2, "ATS", 10, 35, 1, true, false, 1, 3},
//     {2, "Kembali", 10, 48, 1, true, false, 1, 1},
//     {3, "On/Off", 10, 22, 1, true, false, 2, 1},
//     {3, "Ups/Pln", 10, 35, 1, true, false, 2, 2},
//     {3, "Back", 10, 48, 1, true, false, 1, 2},
// };
// static const modelGrafik menuGATS[] PROGMEM = {
//     {0, "garis", 0, 10, 128, 10},
// };
// static const modelLogo menuLogo[] PROGMEM = {
//     {0, 64, 0, 64, 64, 0},
// };
