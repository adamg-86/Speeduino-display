#include "display.h"
#include "SDLogger.h"
#include "statuses.h"
#include "alarms.h"

///////// Display Pages /////////////
void displayPage(byte _page)
{
  display.setTextColor(WHITE);
  display.setFont(&FreeSansBold9pt7b);

  switch (_page)
  {

  case 0:
    //displayStatus("AFR");
    displayStatus("speedRPM");
    break;

  case 1:
    displayStatus("AFR_graph");
    break;

  case 2:
    displayStatus("BOOST");
    break;

  case 3:
    displayStatus("BOOST_graph");
    break;

  case 4:
    displayStatus("VSS");
    break;

  case 5:
    displayStatus("RPM");
    break;

  case 6:
    FourStatusDisplay("IAT C", status.IAT, 0, "CLT C", status.CLT, 0, "BAT V", status.BAT, 1, "baro", status.baro, 0);
    break;

  case 7:
    FourStatusDisplay("MAP", status.MAP, 0, "AFR", status.AFR, 1, "SPARK", status.advance, 0, "AFR T", status.AFR_T, 1);
    break;

  case 8:
    displayStatus("LOG");
    break;

  case 9:
    displayStatus("LOG_start");
    break;

  case 10:
    displayStatus("RESET");
    break;

  case 11:
    displayStatus("RESET_resetting");
    break;

  case 100:
      displayStatus("ALARM");
    break;

  }
  display.display();
}

/////////// One status display page //////////////////
void oneStatusDisplay(char message[5], float data, char unit[4], int j = 0, int y = 0)
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

////////4 Data display enter the name to display, the data, 0 for int 1 for float////////////
void FourStatusDisplay(char name1[10], float data1, bool type1, char name2[10], float data2, bool type2, char name3[10], float data3, bool type3, char name4[10], float data4, bool type4)
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

////////// display status formatting for easier page order changes /////////
void displayStatus(char _status[])
{
  if (_status == "AFR")
  {
    if (status.outputsStatus_1)  // look if the first bit (output 1) is 1 = on
    {
      oneStatusDisplay("  AFR", status.AFR, "", 100, 1);
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
  }

  else if (_status == "AFR_graph")
  {
    graph(status.AFR, 10, 20, "/", 1);

    display.setTextSize(1); //display the AFR target after the AFR reading
    display.setCursor(75, 16);
    display.print(status.AFR_T, 1);

    drawMark(10, 20, 11);
    drawMark(10, 20, 15);
  }

  else if (_status == "BOOST")
  {
    if (status.PSI < 0)
    {
      status.PSI = - status.PSI * 2.036; // convert psi to inche of mercury
      oneStatusDisplay(" BOOST", status.PSI, " VAC", 80);
    }

    else
    {
      oneStatusDisplay(" BOOST", status.PSI, " PSI", 80);
    }
  }

  else  if (_status == "BOOST_graph")
  {
    graph(status.PSI, -15, 15, "psi", 0); // make a live graph from -15 to 15 psi
    drawMark(-15, 15, 0);
    drawMark(-15, 15, 15); // draw a mark line at 15 psi
  }
  
  else  if (_status == "VSS")
  {
    oneStatusDisplay("Speed", status.VSS, "h", 110);

    display.setTextSize(1);
    display.setCursor(100, 40);
    display.print("km");
    display.drawLine(100, 43, 124, 43, WHITE);

    display.setCursor(110, 20);
    display.print(status.gear); // gear indicator in the corner
  }

  else  if (_status == "RPM")
  {
    oneStatusDisplay("  RPM", status.RPM, "");
  }

  else  if (_status == "LOG")
  {
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
  }

  else if (_status == "LOG_start")
  {
    noSDcard = !SD.begin(chipSelect);

    if (logFlag && !noSDcard)
    {
      logFlag = 0;
    }

    else if (!noSDcard)
    {
      logFlag = 1;
      fileName = logName + logNumber + ".msl";
      logNumber += 1;

      my_flash_store.write(logNumber);

      myFile = SD.open(fileName, FILE_WRITE);
      if (myFile)
      {
        ///// header 1 /////
        myFile.print(codeVersion);

        for (int i = 0; i < headerSize; i++){
          if (!(i % 2))
          {
            myFile.print(header[i]);
            if (i < headerSize)
            {
              myFile.print("\t");
            }
            else
            {
              myFile.print("");
            }
          }
        }
        myFile.println("");

        ///// header 2 /////
        for (int j = 0; j < headerSize; j++){
          if (j % 2)
          {
            myFile.print(header[j]);
            if (j < headerSize)
            {
              myFile.print("\t");
            }
            else
            {
              myFile.print("");
            }
          }
        }
        myFile.println("");

        myFile.close();
      }
    }
    page--;
  }

  else if (_status == "RESET")
  {
    display.setTextSize(1);
    display.setCursor(10, 32);
    display.print(" Reset ECU?");
  }

  else if (_status == "RESET_resetting")
  {
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
      page = 0;
    }
    
    else
    {
      display.setTextSize(1);
      display.setCursor(0, 32);
      display.print("must be stopped");
      display.display();
      delay(1000);
      page--;
    }
  }

  else if (_status == "ALARM")
  {
    display.setTextSize(1);
    display.setCursor(10, 40);
    display.print(alarmType);
    display.display();
    delay(250);
    
    if (Alarm() != 1)
      page = lastPage;
  }

  else if (_status == "HP")
  {
    oneStatusDisplay("  HP", status.HPFromVSS, "", 100, 1);
  }

  else if (_status == "speedRPM")
  {
    oneStatusDisplay("  speed", status.speedFromRPM, "", 100, 0);
  }
}