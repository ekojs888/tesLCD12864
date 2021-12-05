#include "lcdFrame.h"
lcdFrame::lcdFrame(U8G2 &u)
{
    ugs = u;
}

void lcdFrame::Begin()
{
    ugs.begin();
}

//===============new======================
void lcdFrame::SetPage(int p, Page model)
{
    Halaman2[p] = model;
    for (int a = 0; a < MENU_MAX_PER_HAL; a++)
    {
        if (Halaman2[p].Menu[a].ModelTxt.value != "")
        {
            coMnu[p]++;
        }
    }
    for (int a = 0; a < TXT_MAX_PER_HAL; a++)
    {
        if (Halaman2[p].Txt[a].value != "")
        {
            coTxt[p]++;
        }
    }
    for (int a = 0; a < GRAFIK_MAX_PER_HAL; a++)
    {
        if (Halaman2[p].Grf[a].jenis != "")
        {
            coGrf[p]++;
        }
    }
}
void lcdFrame::SetNextSelect()
{
    SelectNext();
}
void lcdFrame::SetPrevSelect()
{
    SelectPrev();
}
void lcdFrame::SetRenameMenu(String val)
{
    Halaman2[curPage].Menu[selectPosisi].ModelTxt.value = val;
}
void lcdFrame::SetKlikMenu()
{
    SelectKlik();
}
void lcdFrame::SelectKlik()
{
    for (int a = 0; a < coMnu[curPage]; a++)
    {
        ModelMenu menu = Halaman2[curPage].Menu[a];
        if (menu.kursonPos)
        {
            if (menu.ExcSts == 1)
            {
                curPage = menu.halExc;
                break;
            }
        }
    }

    // return value menu , ambil data koordinat menu
    Out.Menu = selectPosisi;
    Out.ExcSts = Halaman2[curPage].Menu[selectPosisi].ExcSts;
    Out.Hal = curPage;
    Out.idProg = Halaman2[curPage].Menu[selectPosisi].halExc;
    //====
}
void lcdFrame::SelectNext()
{
    for (int a = 0; a < coMnu[curPage]; a++)
    {
        ModelMenu menu = Halaman2[curPage].Menu[a];
        if (menu.KursonEn && menu.kursonPos)
        {
            selectPosisi = a;
            break;
        }
    }

    if (selectPosisi < (coMnu[curPage] - 1))
    {
        selectPosisi++;
    }

    for (int a = 0; a < coMnu[curPage]; a++)
    {
        if (selectPosisi == a)
        {
            Halaman2[curPage].Menu[a].kursonPos = true;
        }
        else
        {
            Halaman2[curPage].Menu[a].kursonPos = false;
        }
    }
}
void lcdFrame::SelectPrev()
{
    for (int a = 0; a < coMnu[curPage]; a++)
    {
        ModelMenu menu = Halaman2[curPage].Menu[a];
        if (menu.KursonEn && menu.kursonPos)
        {
            selectPosisi = a;
            break;
        }
    }
    if (selectPosisi > 0)
    {
        selectPosisi--;
    }
    for (int a = 0; a < coMnu[curPage]; a++)
    {
        if (a == selectPosisi)
        {
            Halaman2[curPage].Menu[a].kursonPos = true;
        }
        else
        {
            Halaman2[curPage].Menu[a].kursonPos = false;
        }
    }
}
//=====================================================

void lcdFrame::Run()
{
    unsigned long curMills = millis();
    if ((curMills - prevMills) >= FC)
    {
        ugs.firstPage();
        do
        {
            ugs.clearBuffer();
            ugs.setFont(u8g2_font_helvR08_tf);

            //=========================================
            //====NEW RENDER ==========================
            Page pagex = Halaman2[curPage];
            //== grafik ===
            for (int a = 0; a < coGrf[curPage]; a++)
            {
                ModelGrafik mgrf = pagex.Grf[a];
                if (mgrf.jenis == "garis")
                {
                    ugs.drawLine(mgrf.x, mgrf.y, mgrf.w, mgrf.h);
                }
                else if (mgrf.jenis == "frame")
                {
                    ugs.drawFrame(mgrf.x, mgrf.y, mgrf.w, mgrf.h);
                }
                else if (mgrf.jenis == "logo0")
                {
                    ugs.drawXBMP(mgrf.x, mgrf.y, mgrf.w, mgrf.h, logo0);
                }
            }

            //== menu ====
            for (int a = 0; a < coMnu[curPage]; a++)
            {
                ModelMenu menu = pagex.Menu[a];
                switch (menu.ModelTxt.idFont)
                {
                case 1:
                    ugs.setFont(u8g2_font_helvR08_tf);
                    break;

                default:
                    break;
                }

                ugs.setCursor(menu.ModelTxt.x, menu.ModelTxt.y);
                ugs.print(menu.ModelTxt.value);
            }
            //=========select menu=================
            for (int a = 0; a < coMnu[curPage]; a++)
            {
                ModelMenu menu = pagex.Menu[a];
                switch (menu.ModelTxt.idFont)
                {
                case 1:
                    ugs.setFont(u8g2_font_helvR08_tf);
                    break;

                default:
                    break;
                }

                ugs.setCursor(3, menu.ModelTxt.y);
                if (menu.KursonEn && menu.kursonPos)
                {
                    ugs.print("#");
                }
                else
                {
                    ugs.print("-");
                }
            }
            //== text ===
            for (int a = 0; a < coTxt[curPage]; a++)
            {
                ModelText2 mtxt = pagex.Txt[a];
                switch (mtxt.idFont)
                {
                case 1:
                    ugs.setFont(u8g2_font_helvR08_tf);
                    break;

                default:
                    break;
                }

                ugs.setCursor(mtxt.x, mtxt.y);
                ugs.print(mtxt.value);
            }
            //==========================================

            ugs.sendBuffer();

        } while (ugs.nextPage());

        //================
        prevMills = curMills;
    }
}