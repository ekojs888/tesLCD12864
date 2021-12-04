#include "lcdFrame.h"
lcdFrame::lcdFrame(U8G2 &u)
{
    ugs = u;
}

void lcdFrame::Begin()
{
    ugs.begin();

    FrameMain();
    FrameMenu();
    FrameSetting();
    FrameSetATS();
}
//=============frame===========================================

void lcdFrame::FrameMain()
{
    int idHal = 0;
    // setText(0, 1, 0, 9, "Menu");

    setGrafikLogo0(idHal, 64, 0, 64, 64);
    setGrafikGaris(idHal, 0, 10, 128, 10);

    setMenu(idHal, menua);
}
void lcdFrame::FrameMenu()
{
    int idHal = 1;

    setGrafikLogo0(idHal, 64, 0, 64, 64);
    setText(idHal, 1, 0, 9, "Menu");
    setGrafikGaris(idHal, 0, 10, 128, 10);

    setMenu(idHal, menuUt);
}
void lcdFrame::FrameSetting()
{
    int idHal = 2;

    setGrafikLogo0(idHal, 64, 0, 64, 64);
    setText(idHal, 1, 0, 9, "Setting");
    setGrafikGaris(idHal, 0, 10, 128, 10);

    setMenu(idHal, menuSetting);
}
void lcdFrame::FrameSetATS()
{
    int idHal = 3;
    setGrafikLogo0(idHal, 64, 0, 64, 64);
    setText(idHal, 1, 0, 9, "Ats Switch");
    setGrafikGaris(idHal, 0, 10, 128, 10);

    setMenu(idHal, menuAts);
}

void lcdFrame::tess()
{
    Serial.println("hallow dari tes...");
    setChangeValue("xxx");
}
//====================func==========================================
void lcdFrame::setChangeValue(String val)
{
    Halaman[hal].ModelTxtMenu[kursonCount].value = val;
}
void lcdFrame::setStatus(String sts)
{
    Status = sts;
}
void lcdFrame::GoToPageSelect()
{
    for (int a = 0; a < countTxtMenu[hal]; a++)
    {
        if (Halaman[hal].ModelTxtMenu[a].kursonPos)
        {
            if (Halaman[hal].ModelTxtMenu[a].ExcSts == 1)
            {
                hal = Halaman[hal].ModelTxtMenu[a].halExc;
                Serial.println(Halaman[hal].ModelTxtMenu[a].halExc);
                break;
            }
            else if (Halaman[hal].ModelTxtMenu[a].ExcSts == 2)
            {
                Serial.printf("no 2 : %d \n", Halaman[hal].ModelTxtMenu[a].halExc);
                if (Halaman[hal].ModelTxtMenu[a].halExc == 1)
                {
                    tess();
                }
                break;
            }
        }
    }
    kursonCount = -1;
    Serial.printf("hal: %d \n", hal);
}
void lcdFrame::KursonNext()
{
    for (int a = 0; a < countTxtMenu[hal]; a++)
    {
        if (Halaman[hal].ModelTxtMenu[a].kursonPos)
        {
            kursonCount = a;
            break;
        }
    }
    if (kursonCount < (countTxtMenu[hal] - 1))
    {
        kursonCount++;
    }
    for (int a = 0; a < countTxtMenu[hal]; a++)
    {
        if (kursonCount == a)
        {
            Halaman[hal].ModelTxtMenu[a].kursonPos = true;
        }
        else
        {
            Halaman[hal].ModelTxtMenu[a].kursonPos = false;
        }
    }
    String myString = String(kursonCount);
    myString = "k:" + myString + " t:" + String((countTxtMenu[hal] - 1));
    setStatus(myString);
    Serial.printf("kursonp: %d, kursonc: %d \n", kursonCount, (countTxtMenu[hal] - 1));
}
void lcdFrame::KursonPrev()
{
    for (int a = 0; a < countTxtMenu[hal]; a++)
    {
        if (Halaman[hal].ModelTxtMenu[a].kursonPos)
        {
            kursonCount = a;
            break;
        }
    }
    if (kursonCount > 0)
    {
        kursonCount--;
    }
    for (int a = 0; a < countTxtMenu[hal]; a++)
    {
        if (a == kursonCount)
        {
            Halaman[hal].ModelTxtMenu[a].kursonPos = true;
        }
        else
        {
            Halaman[hal].ModelTxtMenu[a].kursonPos = false;
        }
    }
    Serial.printf("kursonp: %d, kursonc: %d \n", kursonCount, countTxtMenu[hal] - 1);
}
void lcdFrame::setMenu(int hal, uint8_t x, uint8_t y, uint8_t spasi, String menu[4])
{
    // uint8_t numx = x;
    uint8_t numy = y;
    for (uint8_t a = 0; a < 4; a++)
    {
        numy += spasi;
        setText(hal, 1, x, numy, menu[a], true);
    }
}
void lcdFrame::setMenu(int hal, uint8_t x, uint8_t y, uint8_t spasi, String menu[4][2])
{
    // uint8_t numx = x;
    uint8_t numy = y;
    for (uint8_t a = 0; a < 4; a++)
    {
        numy += spasi;
        if (menu[a][1] != "")
        {
            setText(hal, 1, x, numy, menu[a][0], true, 1, 1, "");
        }
        else
        {
            setText(hal, 1, x, numy, menu[a][0], true);
        }
    }
}
void lcdFrame::setMenu(int hal, uint8_t x, uint8_t y, uint8_t spasi, modelText menu[4])
{
    // uint8_t numx = x;
    uint8_t numy = y;
    for (uint8_t a = 0; a < 4; a++)
    {
        numy += spasi;
        menu[a].y = numy;
        menu[a].x = x;
        setText(hal, menu[a]);
    }
}
void lcdFrame::setMenu(int hal, modelText menu[4])
{
    for (uint8_t a = 0; a < 4; a++)
    {
        if (menu[a].value != "")
            setTextMenu(hal, menu[a]);
    }
}
void lcdFrame::setMenu(int hal, const modelText menu[4])
{
    for (uint8_t a = 0; a < 4; a++)
    {
        if (menu[a].value != "")
            setTextMenu(hal, menu[a]);
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
void lcdFrame::setText(int hal, int idfont, uint8_t x, uint8_t y, String val, bool kursonEn)
{
    Halaman[hal].ModelTxt[countTxt[hal]].idfont = idfont;
    Halaman[hal].ModelTxt[countTxt[hal]].x = x;
    Halaman[hal].ModelTxt[countTxt[hal]].y = y;
    Halaman[hal].ModelTxt[countTxt[hal]].value = val;
    Halaman[hal].ModelTxt[countTxt[hal]].kursonEn = kursonEn;
    countTxt[hal] = countTxt[hal] + 1;
}
void lcdFrame::setText(int hal, int idfont, uint8_t x, uint8_t y, String val, bool kursonEn, uint8_t excsts, uint8_t halexc, String f)
{
    Halaman[hal].ModelTxt[countTxt[hal]].idfont = idfont;
    Halaman[hal].ModelTxt[countTxt[hal]].x = x;
    Halaman[hal].ModelTxt[countTxt[hal]].y = y;
    Halaman[hal].ModelTxt[countTxt[hal]].value = val;
    Halaman[hal].ModelTxt[countTxt[hal]].kursonEn = kursonEn;
    Halaman[hal].ModelTxt[countTxt[hal]].ExcSts = excsts;
    Halaman[hal].ModelTxt[countTxt[hal]].halExc = halexc;
    Halaman[hal].ModelTxt[countTxt[hal]].ExcName = f;
    countTxt[hal] = countTxt[hal] + 1;
}
void lcdFrame::setText(int hal, modelText mt)
{
    Halaman[hal].ModelTxt[countTxt[hal]] = mt;
    countTxt[hal] = countTxt[hal] + 1;
}

void lcdFrame::setTextMenu(int hal, modelText mt)
{
    Halaman[hal].ModelTxtMenu[countTxtMenu[hal]] = mt;
    countTxtMenu[hal] = countTxtMenu[hal] + 1;
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

            // kurson next
            for (int a = 0; a < countTxtMenu[hal]; a++)
            {
                if (Halaman[hal].ModelTxtMenu[a].kursonEn && Halaman[hal].ModelTxtMenu[a].value != "")
                {
                    switch (Halaman[hal].ModelTxtMenu[a].idfont)
                    {
                    case 1:
                        ugs.setFont(u8g2_font_helvR08_tf);
                        break;

                    default:
                        break;
                    }

                    ugs.setCursor(2, Halaman[hal].ModelTxtMenu[a].y);
                    if (Halaman[hal].ModelTxtMenu[a].kursonPos)
                    {
                        ugs.print("#");
                    }
                    else
                    {
                        ugs.print("-");
                    }
                }
            }

            // write text
            for (int a = 0; a < countTxt[hal]; a++)
            {
                switch (Halaman[hal].ModelTxt[a].idfont)
                {
                case 1:
                    ugs.setFont(u8g2_font_helvR08_tf);
                    break;

                default:
                    break;
                }

                ugs.setCursor(Halaman[hal].ModelTxt[a].x, Halaman[hal].ModelTxt[a].y);
                ugs.print(Halaman[hal].ModelTxt[a].value);
            }

            // write text menu
            for (int a = 0; a < countTxtMenu[hal]; a++)
            {
                switch (Halaman[hal].ModelTxtMenu[a].idfont)
                {
                case 1:
                    ugs.setFont(u8g2_font_helvR08_tf);
                    break;

                default:
                    break;
                }

                ugs.setCursor(Halaman[hal].ModelTxtMenu[a].x, Halaman[hal].ModelTxtMenu[a].y);
                ugs.print(Halaman[hal].ModelTxtMenu[a].value);
            }

            // Write Status
            ugs.setFont(u8g2_font_helvR08_tf);
            ugs.setCursor(64, 9);
            ugs.print(Status);

            ugs.sendBuffer();
        } while (ugs.nextPage());

        //================
        prevMills = curMills;
    }
}