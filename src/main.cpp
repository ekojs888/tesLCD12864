#include "main.h"

// 'TheOffice', 128x64px
// static const unsigned char myBitmap[] PROGMEM = {};
// static const unsigned char bm_bits[] PROGMEM = {};

// void draw(void)
// {
//     u8g2.drawXBMP(0, 0, 128, 64, bm_bits);
// }

void setup(void)
{
    Serial.begin(9600);

    Tombol.Begin();
    Framex.Begin();

    // Framex.SetSubValue(1, 7, 15, "Volt : 10", 0);

    delay(1000);

    // u8g2.clearBuffer();
    // u8g2.drawFrame(0, 0, 128, 64);
    // u8g2.drawFrame(5, 5, 50, 12);
    // u8g2.setFont(u8g2_font_helvR08_tr);
    // u8g2.setCursor(7, 15);
    // u8g2.print("Volt : 12");
    // u8g2.sendBuffer();

    // delay(5000);

    // u8g2.clearBuffer();
    // u8g2.setFont(u8g2_font_ncenB14_tr);
    // u8g2.drawStr(0, 20, "Hello World!");
    // u8g2.sendBuffer();

    // delay(2000);

    // u8g2.clearBuffer();
    // u8g2.setFont(u8g2_font_ncenB14_tr);
    // u8g2.drawStr(0, 20, "Ika....");
    // u8g2.sendBuffer();

    // delay(1000);

    // u8g2.clearBuffer();

    // u8g2.setFont(u8g2_font_ncenB14_tr);
    // u8g2.drawStr(0, 20, "Ravin....");
    // u8g2.drawStr(0, 40, "Nila....");
    // u8g2.sendBuffer();

    // delay(1000);
    // u8g2.clearBuffer();
}

// void WriteVolume(uint8_t v)
// {
//     String ab = "Volt : ";
//     char tes_str[3];
//     strcpy(tes_str, u8x8_u8toa(v, 2));
//     u8g2.clearBuffer();
//     u8g2.drawFrame(0, 0, 128, 64);
//     u8g2.drawFrame(5, 5, 50, 12);
//     u8g2.setFont(u8g2_font_helvR08_tr);
//     u8g2.setCursor(7, 15);
//     u8g2.print(ab);
//     u8g2.print(tes_str);
//     u8g2.sendBuffer();
// }

// uint8_t m = 24;
// uint8_t tes = 0;
void loop(void)
{
    Tombol.Run();
    Framex.Run();
    uint8_t t = Tombol.GetDirection();
    if (t == 1)
    {
        Framex.KursonPrev();
    }
    else if (t == 5)
    {
        Framex.KursonNext();
    }

    if (!Tombol.GetKlick())
    {
        Framex.GoToPageSelect();
        Serial.println("klik:");
    }

    // char m_str[3];
    // strcpy(m_str, u8x8_u8toa(m, 2)); /* convert m to a string with two digits */
    // u8g2.firstPage();
    // do
    // {
    //     u8g2.setFont(u8g2_font_logisoso62_tn);
    //     u8g2.drawStr(0, 63, "8");
    //     u8g2.drawStr(33, 63, ":");
    //     u8g2.drawStr(50, 63, m_str);
    // } while (u8g2.nextPage());
    // delay(1000);
    // m++;
    // if (m == 60)
    //     m = 0;
}