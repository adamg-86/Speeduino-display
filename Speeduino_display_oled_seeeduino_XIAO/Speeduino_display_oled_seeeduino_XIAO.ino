/////////////////////////
// Arduino oled display for speeduino
// by Adam
// 01/02/2021
////////////////////////

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Fonts/FreeSansBold9pt7b.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA (A5), SCL (A4))
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
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

//////graph buffer/////////
float _circularBuffer[128]; //fast way to store values (rather than an ArrayList with remove calls)
byte _curWriteIndex = 0; // tracks where we are in the circular buffer

// status bar over the graph
int _graphHeight = SCREEN_HEIGHT - 22;  //default 24

///////// engine parameters /////////
uint8_t Data[116];  //Data buffer for serial read

int secl;     //byte 0 counter
int MAP;      //byte 4 (lowByte) and 5 (highByte)
int IAT;      //byte 6
int CLT;      //byte 7
float BAT;    //byte 9
float AFR;    //byte 10
int EGO;      //byte 11
int RPM;      //byte 14 (lowByte) and 15 (highByte)
float AFR_T;  //byte 19
int advance;  //btye 23
int TPS;      //byte 24
int MAPdot;   //gyte 92
int VSS;      //byte 101 (lowByte) and 102 (highByte)
int gear;     //byte 103

float PSI;    //byte MAP to psi conversion

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
byte maxCase = 12;


void setup() {

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);

  Serial1.begin(115200);  //  console Serial 


  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000); // Pause for 2 seconds

  display.clearDisplay();
  flag = 0;

}

void loop() {
  
  GetData();
  Button1();
  Button2();
  delay(25);
  
  if(flag == 1) displayCase(Case); // if serial return A continue
  
  else ;
    
}

//******** get serial data *************//
void GetData(void){
  byte i = 0;
  byte firstByte = 0;
  
  Serial1.write("A");
  
  if (Serial1.available()){
    firstByte = Serial1.read();
  }
  
  if (firstByte == 'A') flag = 1; //
  else flag = 0;
  
  while (Serial1.available()){ //read the serial buffer
    Data[i] = Serial1.read();
    i++;
  }
}

/////////// LCD refresh //////////////////
void updateScreen( char message[5], float data, char unit[4], int j = 0, int y = 0) { // data name, data, unit, number after the dot 0.1111, j cursor defautl 10

  display.setTextSize(1);//2 with normal font
  
  display.setCursor(30, 15);//20, 0
  display.println(message);
  
  display.setTextSize(3);//5
  display.setCursor(0, 58);//j, 26
  display.print(data, y);

  display.setCursor(j, 58);//70, 40
  display.setTextSize(1);//2
  display.print(unit);
}

////////// Button1 to switch case ///////////////// logic to avoid changing case if press for long without delay
void Button1(void){
  buttonState1 = digitalRead(button1);
  if ((buttonState1 != lastButtonState1) && (digitalRead(button1) == 0)){
      
    if ( Case % 2){
      Case++;
    }
      
    else{
      Case += 2;
    }
  }
  lastButtonState1 = buttonState1;
}

////////// Button2 to switch case /////////////////
void Button2(void){
  buttonState2 = digitalRead(button2);
  if ((buttonState2 != lastButtonState2) && (digitalRead(button2) == 0)){

    if ((Case % 2)){
      Case--;
    }

    else{
      Case++;
    }
  }
  lastButtonState2 = buttonState2;
}

///////// Display Cases /////////////
void displayCase(byte X){
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setFont(&FreeSansBold9pt7b);
  convertData();

  if (Case > maxCase) {
        Case = 0;
      }
  
  switch (X){
    
    case 0:
    updateScreen("  AFR", AFR, "", 100, 1);
    break;

    case 1:
    graph(AFR, 10, 20, "/", 1);
    
    display.setTextSize(1);  //display the AFR target after the AFR reading
    display.setCursor(75, 16);
    display.print(AFR_T, 1);
  
    drawMark(10, 20, 11);
    drawMark(10, 20, 15);
    //drawMark(10, 20, 20);
    break;

    case 2:

    if (PSI < 0){
      PSI = -PSI * 2.036; // convert psi to inche of mercury
      updateScreen(" BOOST", PSI, " VAC", 80);
    }

    else{
      updateScreen(" BOOST", PSI, " PSI", 80);
    }
    break;

    case 3:
    graph(PSI, -15, 15, "psi", 0); // make a live graph from -15 to 15 psi
    drawMark(-15, 15, 0);
    drawMark(-15, 15, 15); // draw a mark line at 15 psi
    
    break;

    case 4:
    updateScreen("  RPM", RPM, "");
    break;

    case 5:
    updateScreen("Speed", VSS, "Km/h", 80);
    break;

    case 6:
    updateScreen("  IAT", IAT, "°C", 100);
    break;

    case 7:
    graph(IAT, 0, 150, "deg", 0);
    drawMark(20, 150, 100);
    break;

    case 8:
    updateScreen("  CLT", CLT, "°C", 100);
    break;

    case 9:
    Case--;
    break;

    case 10:
    updateScreen("  TPS", TPS, "%", 100);
    break;

    case 11:
    Case--;
    break;

    case 12:
    updateScreen("  BAT", BAT, " V", 100, 1);
    break;

  }
  display.display();
    
}

/////////draw line graph///////
void graph(float Val, int minVal, int maxVal, char unit[3], int y){ // y number of 0.111111

   
      
  if(_curWriteIndex >= display.width()){
    _curWriteIndex = 0;
  }  
  display.setTextSize(1);
  display.setCursor(35, 16);
  display.print(Val, y);
  display.print(unit);

  // Draw the line graph
  _circularBuffer[_curWriteIndex++] = Val;
  int xPos = 0; 
  for (int i = _curWriteIndex; i < display.width(); i++){
    // draw the line
    float sensorVal = _circularBuffer[i];
    drawLine(xPos, sensorVal, maxVal, minVal);
    xPos++;
  }
  
  for(int i = 0; i < _curWriteIndex; i++){
    //draw the line
    float sensorVal = _circularBuffer[i];
    drawLine(xPos, sensorVal, maxVal, minVal);
    xPos++;;
  }
}

////////draw line////////
void drawLine(int xPos, float sensorVal, int maxSensorVal, int minSensorVal){
  
  sensorVal = sensorVal * 10;
  maxSensorVal = maxSensorVal * 10;
  minSensorVal = minSensorVal * 10;
  
  int lineHeight = map(sensorVal, minSensorVal, maxSensorVal, 0, _graphHeight);
  if (lineHeight >= _graphHeight){
    lineHeight = _graphHeight;
  }
  int yPos = display.height() - lineHeight;
  display.drawFastVLine(xPos, yPos, lineHeight, WHITE); // full line from 0 to value
  //display.drawFastVLine(xPos, yPos, 4, WHITE);
}

//////draw a mark across the graph ///////////
void drawMark(int minSensorVal, int maxSensorVal, int mark){
  
  int lineHeight = map(mark, minSensorVal, maxSensorVal, 0, _graphHeight);
  int yPos = display.height() - lineHeight;
  int valHeight = yPos - 8;
  int yPos2 = yPos - 1;
  byte curs = 121;

  if ((mark < 100)&(mark >= 10)) curs = 115;
  else if ( (mark < 1000)&(mark >= 100)) curs = 110;

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
  while (xEnd <= 127){
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
void convertData(){
  /*
  secl    byte 0 counter
  MAP     byte 4 (lowByte) and 5 (highByte)
  IAT;    byte 6
  CLT     byte 7
  BAT     byte 9
  AFR     byte 10
  EGO     byte 11
  RPM     byte 14 (lowByte) and 15 (highByte)
  fAFR_T  byte 19
  advance byte 23
  TPS     byte 24
  MAPdot  byte 92
  VSS     byte 101 (lowByte) and 102 (highByte)
  gear    byte 103
  */

  secl = Data[0];
  MAP = (int)((Data[5] << 8) | Data[4]); //combine the high and low byte
  IAT = (int)(Data[6] - 40);
  CLT = (int)(Data[7] - 40);
  BAT = (float)Data[9]/10;
  AFR = (float)Data[10]/10;
  EGO = Data[11];
  RPM = (int)((Data[15] << 8) | Data[14]); //combine the high and low byte
  AFR_T = (float)Data[19]/10;
  advance = Data[23];
  TPS = Data[24];
  MAPdot = Data[92];
  VSS = (int)((Data[101] << 8) | Data[102]); //combine the high and low byte
  gear = Data[103];

  PSI = ((float)MAP*0.145) - 14.5; //convert Kpa to psi

}
