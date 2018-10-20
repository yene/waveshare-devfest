
#include <GxEPD.h>

// select the display class to use, only one
//#include <GxGDEP015OC1/GxGDEP015OC1.h>    // 1.54" b/w
//#include <GxGDEW0154Z04/GxGDEW0154Z04.h>  // 1.54" b/w/r 200x200
//#include <GxGDEW0154Z17/GxGDEW0154Z17.h>  // 1.54" b/w/r 152x152
//#include <GxGDE0213B1/GxGDE0213B1.h>      // 2.13" b/w
//#include <GxGDEW0213Z16/GxGDEW0213Z16.h>  // 2.13" b/w/r
//#include <GxGDEH029A1/GxGDEH029A1.h>      // 2.9" b/w
//#include <GxGDEW029Z10/GxGDEW029Z10.h>    // 2.9" b/w/r
#include <GxGDEW027C44/GxGDEW027C44.h>    // 2.7" b/w/r 264x176
//#include <GxGDEW027W3/GxGDEW027W3.h>      // 2.7" b/w
//#include <GxGDEW042T2/GxGDEW042T2.h>      // 4.2" b/w
//#include <GxGDEW042Z15/GxGDEW042Z15.h>    // 4.2" b/w/r
//#include <GxGDEW0583T7/GxGDEW0583T7.h>    // 5.83" b/w
//#include <GxGDEW075T8/GxGDEW075T8.h>      // 7.5" b/w
//#include <GxGDEW075Z09/GxGDEW075Z09.h>    // 7.5" b/w/r

#if !defined(_GxFont_GFX_TFT_eSPI_H_)
// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#endif
#if defined(_ADAFRUIT_TF_GFX_H_)
#include <Fonts/Open_Sans_Bold_12pt.h>
#endif


#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

const uint8_t busy_pin = 4; 
const uint8_t cs_pin = 14;
const uint8_t rst_pin = 15;
const uint8_t dc_pin = 27;

GxIO_Class io(SPI, cs_pin, dc_pin, rst_pin);
GxEPD_Class display(io, rst_pin, busy_pin);

#if defined(_GxGDEW0154Z04_H_) || defined(_GxGDEW0213Z16_H_) || defined(_GxGDEW029Z10_H_) || defined(_GxGDEW027C44_H_) || defined(_GxGDEW042Z15_H_) || defined(_GxGDEW075Z09_H_)
#define HAS_RED_COLOR
#endif

void setup()
{
  Serial.begin(115200);
  display.init(115200); // enable diagnostic output on Serial
  display.setRotation(1);
  Serial.println("setup done");
}

void loop() {
  showName();
  drawQRCode();
  delay(10000);
}

void showName() {
  display.setRotation(1);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeMonoBold24pt7b);
  display.setCursor(20, 20);
  display.println();
  display.println(" Yannick");
#if defined(HAS_RED_COLOR)
  display.setTextColor(GxEPD_RED);
#endif
  display.println("   Weiss");
  display.setFont(&FreeMonoBold12pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setCursor(7, 160);
  display.println(" yannickweiss.com");
  display.update();
  delay(5000);
}

void showWebsite() {
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeMonoBold12pt7b);
  display.setCursor(0, 0);
  display.println();
  display.println(" visit:");
#if defined(HAS_RED_COLOR)
  display.setTextColor(GxEPD_RED);
#endif
  display.println(" yannickweiss.com");
  display.update();
  delay(5000);
}

#include "IMG_QR_CODE.h"
void drawQRCode() {
  int side = 176;
  uint16_t x = (display.width() - side) / 2;
  uint16_t y = (display.height() - side) / 2;
  display.fillScreen(GxEPD_WHITE);
  display.drawBitmap(myBitmap, x, y, side, side, GxEPD_BLACK);
  display.update();
  delay(5000);
}
