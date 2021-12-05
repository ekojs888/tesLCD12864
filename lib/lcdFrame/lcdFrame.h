#ifndef __LCDFRAME__
#define __LCDFRAME__

#include <Arduino.h>
#include <U8g2lib.h>

// #include <joyPad.h>

#define FC 100

#define MAX_HAL 10

struct modelGrafik
{
    String jenis;
    u8g2_uint_t x, y, w, h;
};
struct modelText
{
    String value;
    uint8_t x;
    uint8_t y;
    uint8_t idfont;
    bool kursonEn;
    bool kursonPos;
    uint8_t ExcSts; // 1= goto page, 2 = exc function, 0 noting
    uint8_t halExc; // id halaman yang di eksekusi jika excsts = 1;
    String ExcName; // nama fungsi yang akan dieksekusi;
};
struct halaman
{
    modelGrafik ModelGrf[MAX_HAL];
    modelText ModelTxt[MAX_HAL];
    modelText ModelTxtMenu[MAX_HAL];
};
struct outPutSelect
{
    int Hal;
    int Menu;
    uint8_t ExcSts;
    uint8_t idProg;
};
class lcdFrame
{
public:
    lcdFrame(U8G2 &);
    void Begin();
    void Run();
    void Add();
    void KursonNext();
    void KursonPrev();
    void GoToPageSelect();
    outPutSelect getOutPutMenu();
    outPutSelect Out;
    void SetMenuNameSelect(String val);

private:
    void setText(int, int, uint8_t, uint8_t, String);
    void setText(int, int, uint8_t, uint8_t, String, bool);
    // void setText(int, int, uint8_t, uint8_t, String, bool, uint8_t, uint8_t, String);
    void setText(int, modelText);

    void setTextMenu(int, modelText);

    void setGrafikFrame(int hal, uint8_t x, uint8_t y, uint8_t w, uint8_t h);
    void setGrafikGaris(int, uint8_t, uint8_t, uint8_t, uint8_t);
    void setGrafikLogo0(int, uint8_t, uint8_t, uint8_t, uint8_t);

    void setMenu(int hal, uint8_t x, uint8_t y, uint8_t spasi, String menu[4]);
    // void setMenu(int hal, uint8_t x, uint8_t y, uint8_t spasi, String menu[4][2]);
    void setMenu(int hal, uint8_t x, uint8_t y, uint8_t spasi, modelText menu[4]);
    void setMenu(int hal, modelText menu[4]);
    void setMenu(int hal, const modelText menu[4]);
    void setCurson(int hal, uint8_t x, uint8_t y, uint8_t spasi, String menu[4]);

    // status
    void setStatus(String sts);

    void FrameMain();
    void FrameSetting();
    void FrameMenu();
    void FrameSetATS();

    unsigned long prevMills;
    U8G2 ugs;
    int a = 1;
    halaman Halaman[20];
    int hal;
    int countGrf[MAX_HAL];
    int countTxt[MAX_HAL];
    int countTxtMenu[MAX_HAL];

    int kursonCount = -1;

    String Status;

    uint8_t tessv;
    void tess();
    void setChangeValue(String val);
};
static const modelText menua[4] PROGMEM = {
    {"Menu", 10, 61, 1, true, false, 1, 1, ""},
};
static const modelText menuUt[4] PROGMEM = {
    {"Setting", 10, 22, 1, true, false, 1, 2, ""},
    {"Menu Utama", 10, 35, 1, true, false, 1, 0, ""},
};

static const modelText menuSetting[4] PROGMEM = {
    {"Pompa", 10, 22, 1, true, false, 0, 1, ""},
    {"ATS", 10, 35, 1, true, false, 1, 3, ""},
    {"Kembali", 10, 48, 1, true, false, 1, 1, ""},
};

static const modelText menuAts[4] PROGMEM = {
    {"On/Off", 10, 22, 1, true, false, 2, 1, ""},
    {"Ups/Pln", 10, 35, 1, true, false, 2, 2, ""},
    {"Back", 10, 48, 1, true, false, 1, 2, ""},
    // {"PLN Switch", 10, 61, 1, true, false, 2, 1, ""},
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
#endif