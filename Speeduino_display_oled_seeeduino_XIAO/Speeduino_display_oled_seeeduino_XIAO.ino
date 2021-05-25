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

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA (4), SCL (5) for seeeduino XIAO)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

///////// functions //////////
void GetData();
void updateScreen();
void Button1();
void Button2();
void displayCase();
void graph();
void drawLine();
void drawMark();
void convertData();
void FourDataPage();
bool Alarm();
void SDlog();

//////graph buffer/////////
float _circularBuffer[128]; // fast way to store values (rather than an ArrayList with remove calls)
byte _curWriteIndex = 0;    // tracks where we are in the circular buffer

// status bar over the graph
int _graphHeight = SCREEN_HEIGHT - 22; // 22 is the number of pixels over the graph to display numbers or names

///////// engine parameters /////////
uint8_t Data[117]; //Data buffer for serial read

float Time;
uint8_t secl;              //byte 0 counter
uint8_t status1;           //byte 1
uint8_t engine;            //byte 2
uint8_t syncLossCounter;   //byte 3
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
uint16_t corrections;      //byte 17 (lowByte) and 18 (highByte)
float AFR_T;               //byte 19
uint8_t VE1;               //byte 20
uint8_t VE2;               //byte 21
uint8_t tpsDOT;            //byte 22  multiply by 10 maybe ?
uint8_t advance;           //byte 23
uint8_t TPS;               //byte 24
uint16_t loopsPerSeconds;  //byte 25 (lowByte) and 26 (highByte)
uint16_t freeRAM;          //byte 27 (lowByte) and 28 (highByte)
uint8_t boostTarget;       //byte 29 divide by 2 to fit in a byte
uint8_t boostDuty;         //byte 30
uint8_t spark;             //byte 31
uint16_t rpmDOT;           //byte 32 (lowByte) and 33 (highByte)
uint8_t ethanolPct;        //byte 34
uint8_t flexCorrection;    //byte 35
uint8_t flexIngCorrection; //byte 36
uint8_t idleLoad;          //byte 37
uint8_t testOutputs;       //byte 38
float O2_2;                //byte 39
uint8_t baro;              //byte 40
//byte 41 to 72 aux input ??
uint8_t tpsADC;               //byte 73
uint8_t error;                //byte 74
float PW1;                    //byte 75 (lowByte) and 76 (highByte)  //Pulsewidth 1 multiplied by 10 in ms. Have to convert from uS to mS.
float PW2;                    //byte 77 (lowByte) and 78 (highByte)  //Pulsewidth 2 multiplied by 10 in ms. Have to convert from uS to mS.
float PW3;                    //byte 79 (lowByte) and 80 (highByte)  //Pulsewidth 3 multiplied by 10 in ms. Have to convert from uS to mS.
float PW4;                    //byte 81 (lowByte) and 82 (highByte)  //Pulsewidth 4 multiplied by 10 in ms. Have to convert from uS to mS.
uint8_t status3;              //byte 83
uint8_t engineProtecStatus;   //byte 84
uint16_t fuelLoad;            //byte 85 (lowByte) and 86 (highByte)
uint16_t ingLoad;             //byte 87 (lowByte) and 88 (highByte)
float dwell;                  //byte 89 (lowByte) and 90 (highByte)
uint8_t CLIdleTarget;         //byte 91
uint8_t mapDOT;               //byte 92
uint8_t vvt1Angle;            //byte 93
uint8_t vvt1TargetAngle;      //byte 94
uint8_t vvt1Duty;             //byte 95
uint16_t flexBoostCorrection; //byte 96 (lowByte) and 97 (highByte)
uint8_t baroCorrection;       //byte 98
uint8_t VE;                   //byte 99
uint8_t ASEValue;             //byte 100
uint16_t VSS;                 //byte 101 (lowByte) and 102 (highByte)
uint8_t gear;                 //byte 103
uint8_t fuelPressure;         //byte 104
uint8_t oilPressure;          //byte 105
uint8_t wmiPW;                //byte 106
uint8_t wmiEmpty;             //byte 107
uint8_t vvt2Angle;            //byte 108
uint8_t vvt2TargetAngle;      //byte 109
uint8_t vvt2Duty;             //byte 110
uint8_t outputsStatus;        //byte 111 evry bit is an output
uint8_t fuelTemp;             //byte 112
uint8_t fuelTempCorrection;   //byte 113
uint8_t advance1;             //byte 114 ing advance in table 1
uint8_t advance2;             //byte 115 ing advance in table 2
uint8_t TS_SD_Status;         //byte 116

float PSI; //bar to psi conversion

//////// Buttons /////////
byte button1 = 1;
byte button2 = 2;

bool buttonState1 = 1;
bool lastButtonState1 = 1;

bool buttonState2 = 1;
bool lastButtonState2 = 1;

bool flag;

/////// case //////////
byte Case = 0;
byte lastCase = 0;
byte maxCase = 9;
String alarmType;

//// timed loop //////
uint lastTime;

// SD logger//
File myFile;
const byte chipSelect = 3;
String dataString = "";
bool logFlag = 0; 
bool noSDcard = 0;

const char header1[] PROGMEM  = {"Time\tSecL\tMAP\tIAT\tCLT\tBAT\tAFR\tEGO\tRPM\tAFR_T\tadvanve\tTPS\tbaro\ttpsADC"};
const char header2[] PROGMEM  = {"sec\tsec\tkpa\tC\tC\tV\tAFR\t%\tRPM\tAFR\tdeg\t%\tkpa\tbit"};

void setup()
{

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);

  Serial1.begin(115200);
  // Serial.begin(115200); //  console Serial

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000); // Pause for 2 seconds

  display.clearDisplay();
  flag = 0;

  noSDcard = !SD.begin(chipSelect);
  
}

void loop()
{
  if (millis() >= lastTime) //25Hz loop
  {
    GetData(0, 0x30, 0, 117);
    convertData();
    Button1();
    Button2();
    Alarm();

    if (logFlag)
    {
      Time = (float)(millis() / 1000.0) ;
      SDlog();
    }
    //delay(25);

    if (flag == 1)
      displayCase(Case); // if first serial byte is ok display

    //else  //loop back to get new data from serial
    //  ;
    lastTime = millis() + 40; // change this number to change loop time no lower than 25   1000/number = frequency in hz
  }
}

//******** get serial data *************//
void GetData(uint8_t canID, uint8_t cmd, uint16_t offset, uint16_t length)
{
  byte firstByte = 0;
  byte cmdr = 0;  //cmd recived
  uint cmdLength; //number of byte to recive

  Serial1.write("r");
  Serial1.write(canID);            //canID
  Serial1.write(cmd);              // cmd
  Serial1.write(lowByte(offset));  //offset low byte
  Serial1.write(highByte(offset)); //offset high byte
  Serial1.write(lowByte(length));  //length low byte
  Serial1.write(highByte(length)); //length high byte

  cmdLength = offset + length;

  if (Serial1.available())
  {
    firstByte = Serial1.read();
    cmdr = Serial1.read(); // will be 0x30
  }

  if ((firstByte == 'r') && (cmdr == cmd))
    flag = 1; //to throw out data out of order
  else
    flag = 0;

  if (Serial1.available()) //read the serial buffer
  {
    for (offset; offset <= (cmdLength); offset++)
    {
      Data[offset] = Serial1.read();
    }
  }
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

////////// Button1 to switch case ///////////////// logic to avoid changing case if press for long without delay
void Button1(void)
{
  buttonState1 = digitalRead(button1);
  if ((buttonState1 != lastButtonState1) && (digitalRead(button1) == 0))
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
  lastButtonState1 = buttonState1;
}

////////// Button2 to switch case /////////////////
void Button2(void)
{
  buttonState2 = digitalRead(button2);
  if ((buttonState2 != lastButtonState2) && (digitalRead(button2) == 0))
  {

    if ((Case % 2))
    {
      Case--;
    }

    else
    {
      Case++;
    }
  }
  lastButtonState2 = buttonState2;
}

///////// Display Cases /////////////
void displayCase(byte page)
{
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setFont(&FreeSansBold9pt7b);

  if ((Case > maxCase) && (Case != 100))
  {
    Case = 0;
  }

  else if (Alarm())
  {
    if (Case != lastCase)
      lastCase == Case;
      
    Case = 100;
  }
  switch (page)
  {

  case 0:
    updateScreen("  AFR", AFR, "", 100, 1);

    /*display.setTextSize(1);
    display.setCursor(100, 20);

    if (outputsStatus & 0x1)
    {
      display.print("on");
    }
    else
    {
      display.print("off");
    }*/
    break;

  case 1:
    graph(AFR, 10, 20, "/", 1);

    display.setTextSize(1); //display the AFR target after the AFR reading
    display.setCursor(75, 16);
    display.print(AFR_T, 1);

    drawMark(10, 20, 11);
    drawMark(10, 20, 15);
    //drawMark(10, 20, 20);
    break;

  case 2:

    if (PSI < 0)
    {
      PSI = -PSI * 2.036; // convert psi to inche of mercury
      updateScreen(" BOOST", PSI, " VAC", 80);
    }

    else
    {
      updateScreen(" BOOST", PSI, " PSI", 80);
    }
    break;

  case 3:
    graph(PSI, -15, 15, "psi", 0); // make a live graph from -15 to 15 psi
    drawMark(-15, 15, 0);
    drawMark(-15, 15, 15); // draw a mark line at 15 psi

    break;

  case 4:
    updateScreen("Speed", VSS, "Km/h", 80);
    display.setTextSize(1);
    display.setCursor(100, 25);
    display.print(gear); // gear indicator in the corner
    break;

  case 5:
    updateScreen("  RPM", RPM, "");
    break;

  case 6:
    FourDataPage("IAT C", IAT, 0, "CLT C", CLT, 0, "BAT V", BAT, 1, "baro", baro, 0);
    //FourDataPage("test", Data[75], 0, "test",Data[76], 0, "test", Data[77], 0, "test",Data[78], 0);
    break;

  case 7:
    FourDataPage("MAP", MAP, 0, "AFR", AFR, 1, "SPARK", advance, 0, "AFR T", AFR_T, 1);
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
    display.setTextSize(1);
    display.setCursor(10, 32);
    display.print(" Resetting...");
    display.display();
    delay(1000);
    Serial1.write("U");
    delay(2000);
    Case = 0;
    break;

  case 12:

    break;

  case 13:
    Case--;
    break;

  case 14:

    break;

  case 15:
    Case--;
    break;

  case 100:
    display.setTextSize(1);
    display.setCursor(10, 40);
    display.print(alarmType);
    display.display();
    delay(500);
    if (Alarm() != 1)
      Case = lastCase;
    break;

  case 17:
    Case--;
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
  uint8_t secl;              //byte 0 counter
  uint8_t status1;           //byte 1
  uint8_t engine;            //byte 2
  uint8_t syncLossCounter;   //byte 3
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
  uint16_t corrections;      //byte 17 (lowByte) and 18 (highByte)
  float AFR_T;               //byte 19
  uint8_t VE1;               //byte 20
  uint8_t VE2;               //byte 21
  uint8_t tpsDOT;            //byte 22  multiply by 10 maybe ?
  uint8_t advance;           //byte 23
  uint8_t TPS;               //byte 24
  uint16_t loopsPerSeconds;  //byte 25 (lowByte) and 26 (highByte)
  uint16_t freeRAM;          //byte 27 (lowByte) and 28 (highByte)
  uint8_t boostTarget;       //byte 29 divide by 2 to fit in a byte
  uint8_t boostDuty;         //byte 30
  uint8_t spark;             //byte 31
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
  uint8_t PW1;               //byte 75 (lowByte) and 76 (highByte)  //Pulsewidth 1 multiplied by 10 in ms. Have to convert from uS to mS.
  uint8_t PW2;               //byte 77 (lowByte) and 78 (highByte)  //Pulsewidth 2 multiplied by 10 in ms. Have to convert from uS to mS.
  uint8_t PW3;               //byte 79 (lowByte) and 80 (highByte)  //Pulsewidth 3 multiplied by 10 in ms. Have to convert from uS to mS.
  uint8_t PW4;               //byte 81 (lowByte) and 82 (highByte)  //Pulsewidth 4 multiplied by 10 in ms. Have to convert from uS to mS.
  uint8_t status3;           //byte 83
  uint8_t engineProtecStatus;//byte 84
  uint16_t fuelLoad;         //byte 85 (lowByte) and 86 (highByte)
  uint16_t ingLoad;          //byte 87 (lowByte) and 88 (highByte)
  float dwell;            //byte 89 (lowByte) and 90 (highByte)
  uint8_t CLIdleTarget;      //byte 91
  uint8_t mapDOT;            //byte 92
  uint8_t vvt1Angle;         //byte 93
  uint8_t vvt1TargetAngle;   //byte 94
  uint8_t vvt1Duty;          //byte 95
  uint16_t flexBoostCorrection; //byte 96 (lowByte) and 97 (highByte)
  uint8_t baroCorrection;    //byte 98
  uint8_t VE;                //byte 99
  uint8_t ASEValue;          //byte 100
  uint16_t VSS;              //byte 101 (lowByte) and 102 (highByte)
  uint8_t gear;              //byte 103
  uint8_t fuelPressure;      //byte 104
  uint8_t oilPressure;       //byte 105
  uint8_t wmiPW;             //byte 106
  uint8_t wmiEmpty;          //byte 107
  uint8_t vvt2Angle;         //byte 108
  uint8_t vvt2TargetAngle;   //byte 109
  uint8_t vvt2Duty;          //byte 110
  uint8_t outputsStatus;     //byte 111
  uint8_t fuelTemp;          //byte 112
  uint8_t fuelTempCorrection;//byte 113
  uint8_t advance1;          //byte 114
  uint8_t advance2;          //byte 115
  uint8_t TS_SD_Status;      //byte 116

  */

  secl = Data[0];
  MAP = ((Data[5] << 8) | Data[4]); //combine the high and low byte
  IAT = (Data[6] - 40);
  CLT = (Data[7] - 40);
  BAT = (float)Data[9] / 10;
  AFR = (float)Data[10] / 10;
  EGO = Data[11];
  RPM = ((Data[15] << 8) | Data[14]); //combine the high and low byte
  AFR_T = (float)Data[19] / 10;
  advance = Data[23];
  TPS = Data[24];
  baro = Data[40];
  tpsADC = Data[73];
  error = Data[74];
  PW1 = (float)(10 * ((Data[76] << 8) | Data[75])); //combine the high and low byte
  engineProtecStatus = Data[84];
  dwell = (float)((Data[90] << 8) | Data[90]); //combine the high and low byte
  mapDOT = Data[92];
  VE = Data[99];
  ASEValue = Data[101];
  VSS = ((Data[102] << 8) | Data[101]); //combine the high and low byte
  gear = Data[103];
  outputsStatus = Data[111];

  PSI = ((float)MAP * 0.145) - 14.5; //convert Kpa to psi
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

  if (CLT > 110)
  {
    alarm = 1;
    alarmType = "Engine HOT";
  }

  else if (IAT > 80)
  {
    alarm = 1;
    alarmType = "Intake HOT";
  }

  else if ((MAP > 70) && (AFR > 14))
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

  dataString += Time;
  dataString += "\t";
  dataString += secl;
  dataString += "\t";
  dataString += MAP;
  dataString += "\t";
  dataString += IAT;
  dataString += "\t";
  dataString += CLT;
  dataString += "\t";
  dataString += BAT;
  dataString += "\t";
  dataString += AFR;
  dataString += "\t";
  dataString += EGO;
  dataString += "\t";
  dataString += RPM;
  dataString += "\t";
  dataString += AFR_T;
  dataString += "\t";
  dataString += advance;
  dataString += "\t";
  dataString += TPS;
  dataString += "\t";
  dataString += baro;
  dataString += "\t";
  dataString += tpsADC;
  

  myFile = SD.open("logTest.msl", FILE_WRITE);
  if (myFile)
  {
    myFile.println(dataString);
    myFile.close();
  }

  dataString = "";
}
