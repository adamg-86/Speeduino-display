#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Fonts/FreeSansBold9pt7b.h>

void updateScreen();
void displayPage();
void graph();
void drawLine();
void drawMark();
void FourDataPage();
void logging();

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA (4), SCL (5) for seeeduino XIAO)

#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//////graph buffer/////////
float _circularBuffer[128]; // value storage for the graph display
byte _curWriteIndex = 0;    // tracks where we are in the circular buffer

//status bar over the graph
int _graphHeight = SCREEN_HEIGHT - 22; // 22 is the number of pixels over the graph to display numbers or names

/////// page //////////
byte page = 0;
byte lastPage = 0;
byte maxPage = 9;

///// logging flag /////
bool logFlag = 0; 

#endif 