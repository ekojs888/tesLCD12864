#ifndef __TOMBOL__
#define __TOMBOL__

#include <Arduino.h>

#ifdef _BOARD_ESP32_
#define PIN_BTN1 1
#define PIN_BTN1_X 34
#define PIN_BTN1_Y 35
#define PIN_BTN1_S 32

#define POS_MOVE_NO 1800
#define POS_MOVE_UP 10
#define POS_MOVE_DOWN 4000
#define POS_MOVE_LEFT 10
#define POS_MOVE_RIGHT 4000

#endif

#ifdef _BOARD_UNO_
#define PIN_BTN1_X A1
#define PIN_BTN1_Y A2
#define PIN_BTN1_D A3

// adc value position
#define POS_MOVE_NO 1800
#define POS_MOVE_UP 10
#define POS_MOVE_DOWN 4000
#define POS_MOVE_LEFT 10
#define POS_MOVE_RIGHT 4000

#endif

#ifdef _BOARD_MEGA2560_
#define PIN_BTN1 2
#endif

#define PIN_MODE 12
#define PIN_START 11

#define PIN_BIP 10

#define TOMBOL_DELAY 500
#define BIP_DELAY 100

#define BIP_ON LOW
#define BIP_OFF HIGH

struct joystic
{
    uint16_t posx;
    uint16_t posy;
    uint8_t possw;
};

class joyPad
{
public:
    void Run();
    void Begin();
    uint8_t GetDirection();
    uint8_t GetKlick();

private:
    void getJoy();
    joystic jos;
    joystic jos_prev;
    // 1 = up, 2 up right, 3 = right, 4 = down right, 5 = down , 6 = down left, 7 = left, 8 = left up
    uint8_t posisi;
    long prevMills, prevMillsBip;
};

#endif