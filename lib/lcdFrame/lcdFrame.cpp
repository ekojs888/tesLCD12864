#include "lcdFrame.h"
lcdFrame::lcdFrame(U8G2 &u)
{
    ugs = u;
}

void lcdFrame::Begin()
{
    ugs.begin();

    uint8_t numy = 9;

    setText(0, 1, 0, numy, "Menu");
    setGrafikGaris(0, 0, 10, 128, 10);

    String menua[] = {"Setting", "Kembali", "", ""};
    setMenu(0, 10, numy, 13, menua);

    setText(1, 1, 0, 10, "Hallow EEE");
    setGrafikGaris(1, 0, 20, 128, 20);
    setGrafikLogo0(1, 0, 0, 64, 64);
}

void lcdFrame::setMenu(int hal, uint8_t x, uint8_t y, uint8_t spasi, String menu[4])
{
    // uint8_t numx = x;
    uint8_t numy = y;
    for (uint8_t a = 0; a < 4; a++)
    {
        numy += spasi;
        setText(hal, 1, 2, numy, "#");
        setText(hal, 1, x, numy, menu[a]);
    }
}

void lcdFrame::setText(int hal, int idfont, uint8_t x, uint8_t y, String val)
{
    Halaman[hal].ModelTxt[countTxt[hal]].idfont = idfont;
    Halaman[hal].ModelTxt[countTxt[hal]].x = x;
    Halaman[hal].ModelTxt[countTxt[hal]].y = y;
    Halaman[hal].ModelTxt[countTxt[hal]].value = val;
    countTxt[hal] = countTxt[hal] + 1;
}
void lcdFrame::setGrafikGaris(int hal, uint8_t x, uint8_t y, uint8_t x2, uint8_t y2)
{
    Halaman[hal].ModelGrf[countGrf[hal]].jenis = "garis";
    Halaman[hal].ModelGrf[countGrf[hal]].x = x;
    Halaman[hal].ModelGrf[countGrf[hal]].y = y;
    Halaman[hal].ModelGrf[countGrf[hal]].w = x2;
    Halaman[hal].ModelGrf[countGrf[hal]].h = y2;
    countGrf[hal] = countGrf[hal] + 1;
}
void lcdFrame::setGrafikFrame(int hal, uint8_t x, uint8_t y, uint8_t w, uint8_t h)
{
    Halaman[hal].ModelGrf[countGrf[hal]].jenis = "frame";
    Halaman[hal].ModelGrf[countGrf[hal]].x = x;
    Halaman[hal].ModelGrf[countGrf[hal]].y = y;
    Halaman[hal].ModelGrf[countGrf[hal]].w = w;
    Halaman[hal].ModelGrf[countGrf[hal]].h = h;
    countGrf[hal] = countGrf[hal] + 1;
}
void lcdFrame::setGrafikLogo0(int hal, uint8_t x, uint8_t y, uint8_t w, uint8_t h)
{
    Halaman[hal].ModelGrf[countGrf[hal]].jenis = "logo0";
    Halaman[hal].ModelGrf[countGrf[hal]].x = x;
    Halaman[hal].ModelGrf[countGrf[hal]].y = y;
    Halaman[hal].ModelGrf[countGrf[hal]].w = w;
    Halaman[hal].ModelGrf[countGrf[hal]].h = h;
    countGrf[hal] = countGrf[hal] + 1;
}
void lcdFrame::Add()
{
    hal = hal + 1;
    Serial.println(hal);
}
void lcdFrame::Run()
{
    unsigned long curMills = millis();
    if ((curMills - prevMills) >= FC)
    {
        ugs.firstPage();
        do
        {
            ugs.clearBuffer();

            for (int a = 0; a < 50; a++)
            {
                if (Halaman[hal].ModelGrf[a].jenis == "garis")
                {
                    ugs.drawLine(Halaman[hal].ModelGrf[a].x,
                                 Halaman[hal].ModelGrf[a].y,
                                 Halaman[hal].ModelGrf[a].w,
                                 Halaman[hal].ModelGrf[a].h);
                }
                else if (Halaman[hal].ModelGrf[a].jenis == "frame")
                {
                    ugs.drawFrame(Halaman[hal].ModelGrf[a].x,
                                  Halaman[hal].ModelGrf[a].y,
                                  Halaman[hal].ModelGrf[a].w,
                                  Halaman[hal].ModelGrf[a].h);
                }
                else if (Halaman[hal].ModelGrf[a].jenis == "logo0")
                {

                    ugs.drawXBMP(Halaman[hal].ModelGrf[a].x,
                                 Halaman[hal].ModelGrf[a].y,
                                 Halaman[hal].ModelGrf[a].w,
                                 Halaman[hal].ModelGrf[a].h,
                                 logo0);
                }
            }

            for (int a = 0; a < 50; a++)
            {
                switch (Halaman[hal].ModelTxt[a].idfont)
                {
                case 1:
                    ugs.setFont(u8g2_font_helvR08_tr);
                    break;

                default:
                    break;
                }

                ugs.setCursor(Halaman[hal].ModelTxt[a].x, Halaman[hal].ModelTxt[a].y);
                ugs.print(Halaman[hal].ModelTxt[a].value);
            }

            ugs.sendBuffer();
        } while (ugs.nextPage());

        //================
        prevMills = curMills;
    }
}