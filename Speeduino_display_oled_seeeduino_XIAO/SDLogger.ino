#include "SDLogger.h"
#include "statuses.h"

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