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

    // Home Page ===
    Framex.SetPage(0, {
                          {
                              {{"Menu", 10, 61, 1}, true, true, 1, 1},
                          },
                          {
                              {"ATS RAVIN V.001", 2, 9, 1},
                          },
                          {
                              {"garis", 0, 10, 128, 10},
                              {"logo0", 64, 11, 64, 64},
                          },
                      });
    // Menu Page ====
    Framex.SetPage(1, {
                          {
                              {{"ATS", 10, 22, 1}, true, true, 1, 2},
                              {{"PH", 10, 35, 1}, true, false, 1, 0},
                              {{"PPM", 10, 48, 1}, true, false, 1, 1},
                              {{"Back", 10, 61, 1}, true, false, 1, 0},
                          },
                          {
                              {"Menu", 2, 9, 1},
                          },
                          {
                              {"garis", 0, 10, 128, 10},
                          },
                      });

    // ATS PAGE====
    Framex.SetPage(2, {
                          {
                              {{"ON", 10, 22, 1}, true, true, 2, 1},
                              {{"PLN", 10, 35, 1}, true, false, 2, 2},
                              {{"Back", 10, 48, 1}, true, false, 1, 1},
                              {{"Home", 10, 61, 1}, true, false, 1, 0},
                          },
                          {
                              {"ATS", 2, 9, 1},
                          },
                          {
                              {"garis", 0, 10, 128, 10},
                          },
                      });

    delay(1000);
}

struct menus
{
    uint8_t ATS_ONOFF;
    uint8_t ATS_PLNUPS;
};
menus M;
void loop(void)
{
    Tombol.Run();
    Framex.Run();
    uint8_t t = Tombol.GetDirection();
    if (t == 1)
    {
        Framex.SetPrevSelect();
    }
    else if (t == 5)
    {
        Framex.SetNextSelect();
    }

    if (!Tombol.GetKlick())
    {
        Framex.SetKlikMenu();

#ifdef _BOARD_ESP32_
        Serial.printf("h: %d, m: %d, o: %d, e: %d \n",
                      Framex.Out.Hal,
                      Framex.Out.Menu,
                      Framex.Out.ExcSts,
                      Framex.Out.idProg);
#endif
#ifdef _BOARD_UNO_
        Serial.print("h: ");
        Serial.print(Framex.Out.Hal);
        Serial.print("m: ");
        Serial.print(Framex.Out.Menu);
        Serial.print("o: ");
        Serial.print(Framex.Out.ExcSts);
        Serial.print("e: ");
        Serial.print(Framex.Out.idProg);
#endif
        if (Framex.Out.ExcSts == 2)
        {
            switch (Framex.Out.idProg)
            {
            case 1: // onoff ATS
                if (M.ATS_ONOFF == 0)
                {
                    Framex.SetRenameMenu("OFF");
                    M.ATS_ONOFF = 1;
                }
                else
                {
                    Framex.SetRenameMenu("ON");
                    M.ATS_ONOFF = 0;
                }
                break;

            case 2: // ups or pln ATS
                if (M.ATS_PLNUPS == 0)
                {
                    Framex.SetRenameMenu("UPS");
                    M.ATS_PLNUPS = 1;
                }
                else
                {
                    Framex.SetRenameMenu("PLN");
                    M.ATS_PLNUPS = 0;
                }
                break;
            default:
                break;
            }
        }
    }
}