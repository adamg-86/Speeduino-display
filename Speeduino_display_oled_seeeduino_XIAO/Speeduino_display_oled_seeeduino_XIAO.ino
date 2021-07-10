/////////////////////////
// Seeeduino Xiao oled display for speeduino
// by Adam Gauthier
// 01/02/2021
////////////////////////

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SD.h>

#include <Fonts/FreeSansBold9pt7b.h>

#include "comms.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA (4), SCL (5) for seeeduino XIAO)

#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

///////// functions //////////
void updateScreen();
bool Button();

void displayCase();
void graph();
void drawLine();
void drawMark();
void convertData();
void FourDataPage();
bool Alarm();
void SDlog();
void logging();

//////graph buffer/////////
float _circularBuffer[128]; // value storage for the graph display
byte _curWriteIndex = 0;    // tracks where we are in the circular buffer

//status bar over the graph
int _graphHeight = SCREEN_HEIGHT - 22; // 22 is the number of pixels over the graph to display numbers or names

///////// engine parameters /////////
//uint8_t Data[117]; //Data buffer for serial read

struct status {
float Time;
uint8_t secl;              //byte 0 counter
uint8_t status1;           //byte 1
uint8_t engine;            //byte 2
uint8_t dwell;             //byte 3 divide by 10
uint16_t MAP;              //byte 4 (lowByte) and 5 (highByte)
int IAT;                   //byte 6
int CLT;                   //byte 7 
uint8_t batCorrection;     //byte 8 
float BAT;                 //byte 9
float AFR;                 //byte 10
uint8_t EGO;               //byte 11
uint8_t iatCorrection;     //byte 12
uint8_t wueCorrection;     //byte 13
uint16_t RPM;              //byte 14 (lowByte) and 15 (highByte)
uint8_t AEamount;          //byte 16
uint16_t corrections;      //byte 17 
uint8_t VE;               //byte 18
float AFR_T;               //byte 19
float PW1;               //byte 20 (lowByte) and 21 (highByte)
uint8_t tpsDOT;            //byte 22
int8_t advance;            //byte 23  live advance can be an average of table 1 and 2
uint8_t TPS;               //byte 24
uint16_t loopsPerSeconds;  //byte 25 (lowByte) and 26 (highByte)
uint16_t freeRAM;          //byte 27 (lowByte) and 28 (highByte)
uint16_t boostTarget;      //byte 29 divide by 2 to fit in a byte in kpa
uint8_t boostDuty;         //byte 30 in %
uint8_t spark;              //byte 31
uint16_t rpmDOT;           //byte 32 (lowByte) and 33 (highByte)
uint8_t ethanolPct;        //byte 34
uint8_t flexCorrection;    //byte 35
uint8_t flexIngCorrection; //byte 36
uint8_t idleLoad;          //byte 37
uint8_t testOutputs;       //byte 38
float O2_2;                //byte 39
uint8_t baro;              //byte 40
//byte 41 to 72 aux input ??
uint8_t tpsADC;            //byte 73
uint8_t error;             //byte 74

uint8_t statusGroup;        //byte 75
uint8_t launchCorrection;   //byte 76

float PW2;               //byte 77 (lowByte) and 78 (highByte)  //Pulsewidth 2 multiplied by 10 in ms. Have to convert from uS to mS.
float PW3;               //byte 79 (lowByte) and 80 (highByte)  //Pulsewidth 3 multiplied by 10 in ms. Have to convert from uS to mS.
float PW4;               //byte 81 (lowByte) and 82 (highByte)  //Pulsewidth 4 multiplied by 10 in ms. Have to convert from uS to mS.
uint8_t status3;           //byte 83
uint8_t engineProtectStatus;//byte 84
uint16_t fuelLoad;         //byte 85 (lowByte) and 86 (highByte)
uint16_t ingLoad;          //byte 87 (lowByte) and 88 (highByte)
uint16_t injAngle;         //byte 89 (lowByte) and 90 (highByte)
uint8_t idleDuty;          //byte 91
uint8_t CLIdleTarget;      //byte 92
uint8_t mapDOT;            //byte 93
uint8_t vvt1Angle;         //byte 94 
uint8_t vvt1TargetAngle;   //byte 95
uint8_t vvt1Duty;          //byte 96
uint16_t flexBoostCorrection; //byte 97 (lowByte) and 98 (highByte)
uint8_t baroCorrection;    //byte 99
uint8_t ASEValue;          //byte 100
uint16_t VSS;              //byte 101 (lowByte) and 102 (highByte)
uint8_t gear;              //byte 103
uint8_t fuelPressure;      //byte 104
uint8_t oilPressure;       //byte 105
uint8_t wmiPW;             //byte 106
uint8_t status4;           //byte 107
uint8_t vvt2Angle;         //byte 108 
uint8_t vvt2TargetAngle;   //byte 109
uint8_t vvt2Duty;          //byte 110
uint8_t outputsStatus;     //byte 111
uint8_t fuelTemp;          //byte 112
uint8_t fuelTempCorrection;//byte 113
uint8_t VE1;               //byte 114
uint8_t VE2;               //byte 115
uint8_t advance1;          //byte 116
uint8_t advance2;          //byte 117
uint8_t nitrous_status;    //byte 118
uint8_t TS_SD_Status;      //byte 119

float PSI; //bar to psi conversion
};

struct status status;

//////// Buttons /////////
struct button {
  uint8_t pin;
  bool state;
  bool lastState;
};

struct button button1;
struct button button2;

bool flag = 0;

/////// case //////////
byte Case = 0;
byte lastCase = 0;
byte maxCase = 9;
String alarmType;

//// timed loop //////
uint long lastTime;

// SD logger//
File myFile;
const byte chipSelect = 3;
String logBuffer = "";
bool logFlag = 0; 
bool noSDcard = 0;
// Time	SecL	RPM	MAP	TPS	AFR	Lambda	MAT	CLT	Engine	DFCO	EGO cor1	Gair	Gbattery	Gwarm	Gbaro	Gammae	Accel Enrich	Current VE	VE1	VE2	PW	AFR Target	Lambda Target	PW2	Duty_Cycle	DutyCycle2	TPS DOT	Advance	Dwell	Battery V	rpm/s	Error #	Error ID	Boost PSI	Boost cut	Hard Launch	Hard Limiter	Idle Control	IAC value	Idle Target RPM	Idle RPM Delta	Baro Pressure	Sync Loss #	Wheel Speed _kph	Wheel Speed _mph	Gear	WB on	Advance 1	Advance 2	Trip Economy	Instant Economy	Fuel Consumption	Trip Meter Km	Odometer Km	Vehicle Speed	Power	Torque	Odometer_KM
const char header1[] PROGMEM  = {"\
Time\t\
SecL\t\
MAP\t\
IAT\t\
CLT\t\
BAT\t\
AFR\t\
EGO\t\
RPM\t\
AFR_T\t\
advanve\t\
TPS\t\
baro\t\
tpsADC\
"};

const char header2[] PROGMEM  = {"\
sec\t\
sec\t\
kpa\t\
C\t\
C\t\
V\t\
AFR\t\
%\t\
RPM\t\
AFR\t\
deg\t\
%\t\
kpa\t\
bit\
"};

char temp;

void setup()
{
  button1.pin = 1;
  button2.pin = 2;

  pinMode(button1.pin, INPUT_PULLUP);
  pinMode(button2.pin, INPUT_PULLUP);

  Serial1.begin(115200);
  // Serial.begin(115200); //  console Serial

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000); // Pause for 2 seconds

  display.clearDisplay();

  noSDcard = !SD.begin(chipSelect);
  
}

void loop()
{
  sendComms('n');

  if (Serial1.available())
  {
    reciveComms('n');
  }

  convertData();
  if (Button(button1))
  {
    if (Case % 2)
    {
      Case++;
    }

    else
    {
      Case += 2;
    }
  }

  if (Button(button2))
  {
    if (Case % 2)
    {
      Case--;
    }

    else
    {
      Case++;
    }
  }

  Alarm();

  display.clearDisplay();

  if (logFlag)
  {
    status.Time = (float)(millis() / 1000.0) ;
    SDlog();
    logging();
  }

  displayCase(Case);
  delay(40);
}

/////////// LCD refresh //////////////////
void updateScreen(char message[5], float data, char unit[4], int j = 0, int y = 0)
{ // data name, data, unit, number after the dot 0.1111, j cursor defautl 10

  display.setTextSize(1); //2 with normal font

  display.setCursor(30, 15); //20, 0
  display.println(message);

  display.setTextSize(3);   //5
  display.setCursor(0, 58); //j, 26
  display.print(data, y);

  display.setCursor(j, 58); //70, 40
  display.setTextSize(1);   //2
  display.print(unit);
}

//////////Button short press function ///////////////// logic to avoid changing case if press for long without delay 
bool Button (button &Button)
{
  Button.state = digitalRead(Button.pin);
  bool flag = 0;

  if ((Button.state != Button.lastState) && (digitalRead(Button.pin) == 0))
  {
    flag = 1;
  }
  Button.lastState = Button.state;

  return flag;
}

///////// Display Cases /////////////
void displayCase(byte page)
{
  display.setTextColor(WHITE);
  display.setFont(&FreeSansBold9pt7b);

  if ((Case > maxCase) && (Case != 100))
  {
    Case = 0;
  }

  if (Alarm())
  {
    if ((Case != lastCase) && (Case != 100))
      lastCase = Case;
      
    Case = 100;
  }
  switch (page)
  {

  case 0:

    if (status.outputsStatus & 0x1)  // look if the first bit (output 1) is 1 = on
    {
      updateScreen("  AFR", status.AFR, "", 100, 1);
    }

    else  // the O2 is off
    {
      display.setTextSize(1);
      display.setCursor(30, 15); 
      display.println("  AFR");

      display.setTextSize(3);
      display.setCursor(0, 58);
      display.print("OFF");
    }
    break;

  case 1:
    graph(status.AFR, 10, 20, "/", 1);

    display.setTextSize(1); //display the AFR target after the AFR reading
    display.setCursor(75, 16);
    display.print(status.AFR_T, 1);

    drawMark(10, 20, 11);
    drawMark(10, 20, 15);
    break;

  case 2:

    if (status.PSI < 0)
    {
      status.PSI = - status.PSI * 2.036; // convert psi to inche of mercury
      updateScreen(" BOOST", status.PSI, " VAC", 80);
    }

    else
    {
      updateScreen(" BOOST", status.PSI, " PSI", 80);
    }
    break;

  case 3:
    graph(status.PSI, -15, 15, "psi", 0); // make a live graph from -15 to 15 psi
    drawMark(-15, 15, 0);
    drawMark(-15, 15, 15); // draw a mark line at 15 psi

    break;

  case 4:
    updateScreen("Speed", status.VSS, "h", 110);

    display.setTextSize(1);
    display.setCursor(100, 40);
    display.print("km");
    display.drawLine(100, 43, 124, 43, WHITE);

    display.setCursor(110, 20);
    display.print(status.gear); // gear indicator in the corner
    break;

  case 5:
    updateScreen("  RPM", status.RPM, "");
    break;

  case 6:
    FourDataPage("IAT C", status.IAT, 0, "CLT C", status.CLT, 0, "BAT V", status.BAT, 1, "baro", status.baro, 0);
    break;

  case 7:
    FourDataPage("MAP", status.MAP, 0, "AFR", status.AFR, 1, "SPARK", status.advance, 0, "AFR T", status.AFR_T, 1);
    break;

  case 8:
    display.setTextSize(1);
    display.setCursor(10, 32);

    if (noSDcard)
    {
      display.print(" No SD card!");
    }

    else
    {
      if (logFlag)
      {
        display.print(" Stop Log?");
      }

      else
      {
        display.print(" Start Log?");
      }
    }
    break;

  case 9:
    noSDcard = !SD.begin(chipSelect);

    if (logFlag && !noSDcard)
    {
      logFlag = 0;
    }

    else if (!noSDcard)
    {
      logFlag = 1;
      myFile = SD.open("logTest.msl", FILE_WRITE);
      if (myFile)
      {
        myFile.println(header1);
        myFile.println(header2);
        myFile.close();
      }
    }
    Case = 8;
    break;

  case 10:
    display.setTextSize(1);
    display.setCursor(10, 32);
    display.print(" Reset ECU?");
    break;

  case 11:
    if (status.VSS == 0)
    {
      display.setTextSize(1);
      display.setCursor(10, 32);
      display.print(" Resetting...");
      display.display();
      delay(1000);
      Serial1.write("U");
      Serial1.write(1); //ECU reset at next byte after the "U" command
      delay(1000);
      Case = 0;
    }
    
    else
    {
      display.setTextSize(1);
      display.setCursor(0, 32);
      display.print("must be stopped");
      display.display();
      delay(1000);
    }
    break;

  case 100:
    display.setTextSize(1);
    display.setCursor(10, 40);
    display.print(alarmType);
    display.display();
    delay(250);
    
    if (Alarm() != 1)
      Case = lastCase;
    break;

  }
  display.display();
}

/////////draw line graph///////
void graph(float Val, int minVal, int maxVal, char unit[10], int y)
{ // y number of 0.111111

  if (_curWriteIndex >= display.width())
  {
    _curWriteIndex = 0;
  }
  display.setTextSize(1);
  display.setCursor(35, 16);
  display.print(Val, y);
  display.print(unit);

  // Draw the line graph
  _circularBuffer[_curWriteIndex++] = Val;
  int xPos = 0;
  for (int i = _curWriteIndex; i < display.width(); i++)
  {
    // draw the line
    float sensorVal = _circularBuffer[i];
    drawLine(xPos, sensorVal, maxVal, minVal);
    xPos++;
  }

  for (int i = 0; i < _curWriteIndex; i++)
  {
    //draw the line
    float sensorVal = _circularBuffer[i];
    drawLine(xPos, sensorVal, maxVal, minVal);
    xPos++;
    ;
  }
}

////////draw line////////
void drawLine(int xPos, float sensorVal, int maxSensorVal, int minSensorVal)
{

  sensorVal = sensorVal * 10;
  maxSensorVal = maxSensorVal * 10;
  minSensorVal = minSensorVal * 10;

  int lineHeight = map(sensorVal, minSensorVal, maxSensorVal, 0, _graphHeight);
  if (lineHeight >= _graphHeight)
  {
    lineHeight = _graphHeight;
  }
  int yPos = display.height() - lineHeight;
  display.drawFastVLine(xPos, yPos, lineHeight, WHITE); // full line from 0 to value
  //display.drawFastVLine(xPos, yPos, 4, WHITE);
}

//////draw a mark across the graph ///////////
void drawMark(int minSensorVal, int maxSensorVal, int mark)
{

  int lineHeight = map(mark, minSensorVal, maxSensorVal, 0, _graphHeight);
  int yPos = display.height() - lineHeight;
  int valHeight = yPos - 8;
  int yPos2 = yPos - 1;
  byte curs = 121;

  if ((mark < 100) & (mark >= 10))
    curs = 115;
  else if ((mark < 1000) & (mark >= 100))
    curs = 110;

  display.setFont();

  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(curs, valHeight);
  display.print(mark);
  display.setCursor(0, valHeight);
  display.print(mark);

  curs -= 16;
  display.setTextColor(BLACK);
  display.setCursor(curs, valHeight);
  display.print(mark);
  display.setCursor(16, valHeight);
  display.print(mark);

  byte increment = 8;
  byte xStart = 0;
  byte xEnd = 7;
  byte i = 0;

  //draw dotted lines
  while (xEnd <= 127)
  {
    display.drawLine(xStart, yPos, xEnd, yPos, WHITE);
    display.drawLine(xStart, yPos2, xEnd, yPos2, WHITE);
    xStart += increment;
    xEnd += increment;

    display.drawLine(xStart, yPos, xEnd, yPos, BLACK);
    display.drawLine(xStart, yPos2, xEnd, yPos2, BLACK);
    xStart += increment;
    xEnd += increment;
  }
}

////////convert recived Data to readable data ////////////
void convertData()
{
  /*
  float Time;
  uint8_t secl;              //byte 0 counter
  uint8_t status1;           //byte 1
  uint8_t engine;            //byte 2
  uint8_t dwell1;             //byte 3 divide by 10
  uint16_t MAP;              //byte 4 (lowByte) and 5 (highByte)
  int IAT;                   //byte 6
  int CLT;                   //byte 7 
  uint8_t batCorrection;     //byte 8 
  float BAT;                 //byte 9
  float AFR;                 //byte 10
  uint8_t EGO;               //byte 11
  uint8_t iatCorrection;     //byte 12
  uint8_t wueCorrection;     //byte 13
  uint16_t RPM;              //byte 14 (lowByte) and 15 (highByte)
  uint8_t AEamount;          //byte 16
  uint16_t corrections;      //byte 17 
  uint8_t VE;                //byte 18
  float AFR_T;               //byte 19
  float PW1;               //byte 20 (lowByte) and 21 (highByte)
  uint8_t tpsDOT;            //byte 22
  int8_t advance;            //byte 23  live advance can be an average of table 1 and 2
  uint8_t TPS;               //byte 24
  uint16_t loopsPerSeconds;  //byte 25 (lowByte) and 26 (highByte)
  uint16_t freeRAM;          //byte 27 (lowByte) and 28 (highByte)
  uint16_t boostTarget;      //byte 29 divide by 2 to fit in a byte in kpa
  uint8_t boostDuty;         //byte 30 in %
  uint8_t spark;              //byte 31
  uint16_t rpmDOT;           //byte 32 (lowByte) and 33 (highByte)
  uint8_t ethanolPct;        //byte 34
  uint8_t flexCorrection;    //byte 35
  uint8_t flexIngCorrection; //byte 36
  uint8_t idleLoad;          //byte 37
  uint8_t testOutputs;       //byte 38
  float O2_2;                //byte 39
  uint8_t baro;              //byte 40
  //byte 41 to 72 aux input ??
  uint8_t tpsADC;            //byte 73
  uint8_t error;             //byte 74

  uint8_t statusGroup;        //byte 75
  uint8_t launchCorrection;   //byte 76

  float PW2;               //byte 77 (lowByte) and 78 (highByte)  //Pulsewidth 2 multiplied by 10 in ms. Have to convert from uS to mS.
  float PW3;               //byte 79 (lowByte) and 80 (highByte)  //Pulsewidth 3 multiplied by 10 in ms. Have to convert from uS to mS.
  float PW4;               //byte 81 (lowByte) and 82 (highByte)  //Pulsewidth 4 multiplied by 10 in ms. Have to convert from uS to mS.
  uint8_t status3;           //byte 83
  uint8_t engineProtectStatus;//byte 84
  uint16_t fuelLoad;         //byte 85 (lowByte) and 86 (highByte)
  uint16_t ingLoad;          //byte 87 (lowByte) and 88 (highByte)
  uint16_t injAngle;         //byte 89 (lowByte) and 90 (highByte)
  uint8_t idleDuty;          //byte 91
  uint8_t CLIdleTarget;      //byte 92
  uint8_t mapDOT;            //byte 93
  uint8_t vvt1Angle;         //byte 94 
  uint8_t vvt1TargetAngle;   //byte 95
  uint8_t vvt1Duty;          //byte 96
  uint16_t flexBoostCorrection; //byte 97 (lowByte) and 98 (highByte)
  uint8_t baroCorrection;    //byte 99
  uint8_t ASEValue;          //byte 100
  uint16_t VSS;              //byte 101 (lowByte) and 102 (highByte)
  uint8_t gear;              //byte 103
  uint8_t fuelPressure;      //byte 104
  uint8_t oilPressure;       //byte 105
  uint8_t wmiPW;             //byte 106
  uint8_t status4;           //byte 107
  uint8_t vvt2Angle;         //byte 108 
  uint8_t vvt2TargetAngle;   //byte 109
  uint8_t vvt2Duty;          //byte 110
  uint8_t outputsStatus;     //byte 111
  uint8_t fuelTemp;          //byte 112
  uint8_t fuelTempCorrection;//byte 113
  uint8_t VE1;               //byte 114
  uint8_t VE2;               //byte 115
  uint8_t advance1;          //byte 116
  uint8_t advance2;          //byte 117
  uint8_t nitrous_status;    //byte 118
  uint8_t TS_SD_Status;      //byte 119
  */

  status.secl = Data[0];
  status.status1 = Data[1];
  status.engine = Data[2];
  status.dwell = (float)(Data[3] / 10);
  status.MAP = ((Data[5] << 8) | Data[4]); //combine the high and low byte
  status.IAT = (Data[6] - 40);
  status.CLT = (Data[7] - 40);
  status.batCorrection = Data[8];
  status.BAT = (float)Data[9] / 10;
  status.AFR = (float)Data[10] / 10;
  status.EGO = Data[11];
  status.iatCorrection = Data[12];
  status.wueCorrection = Data[13];
  status.RPM = ((Data[15] << 8) | Data[14]); //combine the high and low byte
  status.AEamount = Data[16];
  status.corrections = Data[17];
  status.VE = Data[18];
  status.AFR_T = (float)Data[19] / 10;
  status.PW1 = (float)(((Data[21] << 8) | Data[20]) / 1000.0);
  status.tpsDOT = Data[22];
  status.advance = Data[23];
  status.TPS = Data[24];
  status.loopsPerSeconds = ((Data[26] << 8) | Data[25]);
  status.freeRAM = ((Data[28] << 8) | Data[27]);
  status.boostTarget = Data[29] << 1; // multiply by 2
  status.boostDuty = Data[30];
  status.spark = Data[31]; /////// rendu ici pour tester//////////////////////////////////////////
  status.rpmDOT = ((Data[33] << 8) | Data[32]);
  status.ethanolPct = Data[34];
  status.flexCorrection = Data[35];
  status.flexIngCorrection = Data[36];
  status.idleLoad = Data[37];
  status.testOutputs = Data[38];
  status.O2_2 = Data[39];
  status.baro = Data[40];
  status.tpsADC = Data[73];
  status.error = Data[74];
  
  status.engineProtectStatus = Data[84];

  status.mapDOT = Data[92];
  status.ASEValue = Data[101];

  status.VSS = ((Data[102] << 8) | Data[101]); //combine the high and low byte
  status.gear = Data[103];
  status.outputsStatus = Data[111];

  status.PSI = ((float)status.MAP * 0.145) - 14.5; //convert Kpa to psi
}

////////4 Data display enter the name to display, the data, 0 for int 1 for float////////////
void FourDataPage(char name1[10], float data1, bool type1, char name2[10], float data2, bool type2, char name3[10], float data3, bool type3, char name4[10], float data4, bool type4)
{

  display.drawLine(64, 0, 64, 64, WHITE);
  display.drawLine(0, 32, 128, 32, WHITE);

  display.setFont();
  display.setTextSize(1);
  display.setCursor(20, 0);
  display.print(name1);
  display.setCursor(85, 0);
  display.print(name2);
  display.setCursor(20, 34);
  display.print(name3);
  display.setCursor(85, 34);
  display.print(name4);

  display.setFont(&FreeSansBold9pt7b);
  display.setTextSize(1);
  display.setCursor(10, 25);
  display.print(data1, type1);
  display.setCursor(76, 25);
  display.print(data2, type2);
  display.setCursor(10, 60);
  display.print(data3, type3);
  display.setCursor(76, 60);
  display.print(data4, type4);
}

///// Set Alarms to display on the screen ///////
bool Alarm()
{
  //char alarmType[20];
  bool alarm;

  if (status.CLT > 110)
  {
    alarm = 1;
    alarmType = "Engine HOT";
  }

  else if (status.IAT > 80)
  {
    alarm = 1;
    alarmType = "Intake HOT";
  }

  else if ((status.TPS > 80) && (status.AFR > 14))
  {
    alarm = 1;
    alarmType = "  LEAN...";
  }

  else
    alarm = 0;

  return alarm;
}

void SDlog()
{

  logBuffer += status.Time;
  logBuffer += "\t";
  logBuffer += status.secl;
  logBuffer += "\t";
  logBuffer += status.MAP;
  logBuffer += "\t";
  logBuffer += status.IAT;
  logBuffer += "\t";
  logBuffer += status.CLT;
  logBuffer += "\t";
  logBuffer += status.BAT;
  logBuffer += "\t";
  logBuffer += status.AFR;
  logBuffer += "\t";
  logBuffer += status.EGO;
  logBuffer += "\t";
  logBuffer += status.RPM;
  logBuffer += "\t";
  logBuffer += status.AFR_T;
  logBuffer += "\t";
  logBuffer += status.advance;
  logBuffer += "\t";
  logBuffer += status.TPS;
  logBuffer += "\t";
  logBuffer += status.baro;
  logBuffer += "\t";
  logBuffer += status.tpsADC;
  

  myFile = SD.open("logTest.msl", FILE_WRITE);
  if (myFile)
  {
    myFile.println(logBuffer);
    myFile.close();
  }

  logBuffer = "";
}

////// FLASHING DOT IN THE CORNER WHEN LOGGING ////////////
void logging()
{
  display.setFont(&FreeSansBold9pt7b);

  if (status.secl % 2)
  {
    display.setTextColor(WHITE);
  }

  else
  {
    display.setTextColor(BLACK);
  }

  display.setTextSize(3);
  display.setCursor(0, 5); 
  display.println(".");
}

