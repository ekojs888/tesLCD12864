#include "joyPad.h"

void joyPad::Begin()
{
    pinMode(PIN_BTN1_S, INPUT_PULLUP);
}

void joyPad::getJoy()
{
    jos.posx = analogRead(PIN_BTN1_X);
    jos.posy = analogRead(PIN_BTN1_Y);
    jos.possw = digitalRead(PIN_BTN1_S);
}

// void tombol::setBip(bool f)
// {
//     if (f)
//     {
//         bipEn = true;
//         digitalWrite(PIN_BIP, BIP_ON);
//     }
//     else
//     {
//         digitalWrite(PIN_BIP, BIP_OFF);
//     }
// }
uint8_t joyPad::GetDirection()
{
    uint8_t posi = posisi;
    posisi = 0;
    return posi;
}
uint8_t joyPad::GetKlick()
{
    return jos_prev.posy;
}

void joyPad::Run()
{
    unsigned long curMills = millis();

    // //=====BIP================================
    // if ((curMills - prevMillsBip) >= BIP_DELAY && bipEn)
    // {
    //     prevMillsBip = curMills;
    //     setBip(false);
    // }

    //======TOMBOL============================
    if ((curMills - prevMills) >= TOMBOL_DELAY)
    {
        getJoy();
        // Serial.printf("x:%d, y:%d s:%d\n", jos.posx, jos.posy, jos.possw);
        jos_prev.possw = jos.possw;
        jos_prev.posx = jos.posx;
        jos_prev.posy = jos.posy;

        uint8_t posx, posy;
        if (jos.posy <= POS_MOVE_UP)
        {

            posy = 1;
        }
        else if (jos.posy >= POS_MOVE_DOWN)
        {
            posy = 2;
        }
        else
        {
            posy = 0;
        }

        if (jos.posx <= POS_MOVE_LEFT)
        {
            posx = 1;
        }
        else if (jos.posx >= POS_MOVE_RIGHT)
        {
            posx = 2;
        }
        else
        {
            posx = 0;
        }

        if (posy == 1 && posx == 0)
        {
            Serial.println("move up");
            posisi = 1;
        }
        else if (posy == 1 && posx == 2)
        {
            Serial.println("move up right");
            posisi = 2;
        }
        else if (posy == 1 && posx == 1)
        {
            Serial.println("move up left");
            posisi = 8;
        }
        else if (posy == 0 && posx == 1)
        {
            Serial.println("move left");
            posisi = 7;
        }
        else if (posy == 2 && posx == 1)
        {
            Serial.println("move down left");
            posisi = 6;
        }
        else if (posy == 2 && posx == 0)
        {
            Serial.println("move down");
            posisi = 5;
        }
        else if (posy == 2 && posx == 2)
        {
            Serial.println("move down right");
            posisi = 4;
        }
        else if (posy == 0 && posx == 2)
        {
            Serial.println("move right");
            posisi = 3;
        }
        else
        {
            posisi = 0;
        }

        //================
        prevMills = curMills;
    }
}