#pragma once

#include <Arduino.h>
#include <U8g2lib.h>

#define FC 100

#define TXT_MAX_PER_HAL 4
#define MENU_MAX_PER_HAL 4
#define GRAFIK_MAX_PER_HAL 2
#define HAL_MAX 20

//===================new===========
struct ModelText2
{
    String value;
    uint8_t x, y;
    uint8_t idFont;
};
struct ModelMenu
{
    ModelText2 ModelTxt;
    bool KursonEn;
    bool kursonPos;
    uint8_t ExcSts; // 1= goto page, 2 = exc function, 0 noting
    uint8_t halExc; // id halaman exc if ExcSts = 1
};

struct ModelGrafik
{
    String jenis;
    u8g2_uint_t x, y, w, h;
};

struct Page
{
    ModelMenu Menu[MENU_MAX_PER_HAL];
    ModelText2 Txt[TXT_MAX_PER_HAL];
    ModelGrafik Grf[GRAFIK_MAX_PER_HAL];
};

struct outPutSelect
{
    int Hal;
    int Menu;
    uint8_t ExcSts;
    uint8_t idProg;
};
//====================end new=============

class lcdFrame
{
public:
    lcdFrame(U8G2 &);
    void Begin();
    void Run();
    //=======new=============
    void SetPage(int p, Page model);
    void SetNextSelect();
    void SetPrevSelect();
    void SetRenameMenu(String val);
    void SetKlikMenu();
    outPutSelect Out;
    //=======================

private:
    unsigned long prevMills;
    U8G2 ugs;
    //=======new============
    int curPage = 0;
    int coTxt[HAL_MAX];
    int coGrf[HAL_MAX];
    int coMnu[HAL_MAX];
    Page Halaman2[HAL_MAX];
    int selectPosisi = 0;
    void SelectNext();
    void SelectPrev();
    void SelectKlik();
    //======================
};

static const unsigned char logo0[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x01, 0x00, 0x07, 0x00, 0x00,
    0x00, 0x00, 0xe0, 0x01, 0x81, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xc2,
    0xc7, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x70, 0xe0, 0x0f, 0x1c, 0x00, 0x00,
    0x00, 0x0c, 0x30, 0xf0, 0x1f, 0x1c, 0x20, 0x00, 0x00, 0x3c, 0x18, 0x78,
    0x3e, 0x18, 0x78, 0x00, 0x00, 0xcc, 0x18, 0x3c, 0x7c, 0x30, 0x7e, 0x00,
    0x00, 0x0c, 0x18, 0x1e, 0x78, 0x30, 0x70, 0x00, 0x00, 0x0c, 0x0c, 0x0e,
    0xf0, 0x30, 0x30, 0x00, 0x00, 0x18, 0x0c, 0x07, 0xe0, 0x30, 0x30, 0x00,
    0x00, 0x19, 0x08, 0x07, 0xe0, 0x31, 0x30, 0x01, 0x80, 0x13, 0x08, 0x03,
    0xc0, 0x31, 0x98, 0x01, 0x80, 0x37, 0x08, 0x03, 0xc0, 0x19, 0xc8, 0x01,
    0x00, 0x67, 0x18, 0x03, 0xc0, 0x19, 0xe4, 0x01, 0x00, 0xcf, 0x10, 0x03,
    0xc0, 0x09, 0xf3, 0x01, 0x40, 0x3e, 0x21, 0x03, 0xc0, 0x8c, 0xf8, 0x04,
    0xc0, 0x20, 0x64, 0x03, 0xc0, 0x06, 0x1c, 0x07, 0xc0, 0x1f, 0x40, 0x02,
    0x40, 0x02, 0xf0, 0x07, 0xc0, 0xff, 0x0f, 0x06, 0x60, 0xf0, 0xff, 0x07,
    0xc0, 0xfd, 0x7f, 0x04, 0x20, 0xfe, 0xbf, 0x03, 0x80, 0xf1, 0xff, 0x09,
    0x90, 0xff, 0x8f, 0x03, 0x80, 0x03, 0xf8, 0x03, 0xc0, 0x7f, 0xc0, 0x01,
    0x00, 0x03, 0x00, 0x06, 0x60, 0x00, 0xc0, 0x00, 0x10, 0x06, 0x00, 0x08,
    0x10, 0x00, 0xe0, 0x08, 0x0c, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x70, 0x30,
    0x1c, 0x38, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x38, 0x38, 0xf0, 0x00, 0x00,
    0x18, 0x00, 0x0f, 0x1c, 0xe0, 0x81, 0x0f, 0x06, 0x71, 0xe0, 0x01, 0x0f,
    0x80, 0x1f, 0xc0, 0x41, 0xc3, 0x03, 0xf8, 0x03, 0x00, 0x00, 0x7e, 0x60,
    0x06, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x30, 0x0e, 0x3c, 0x00, 0x00,
    0x00, 0x00, 0xfc, 0x1f, 0xfc, 0x1f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f,
    0xf8, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x01, 0xe0, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
