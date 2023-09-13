#include "SDLogger.h"
#include "statuses.h"



// option 1 for datalog and 2 for Pull log
void SDlog(int option)
{

  
  logBuffer += status.Time;
  logBuffer += "\t";
  logBuffer += status.secl;
  logBuffer += "\t";
  logBuffer += status.status1_inj1Status;
  logBuffer += "\t";
  logBuffer += status.status1_inj2Status;
  logBuffer += "\t";
  logBuffer += status.status1_inj3Status;
  logBuffer += "\t";
  logBuffer += status.status1_inj4Status;
  logBuffer += "\t";
  logBuffer += status.status1_DFCOOn;
  logBuffer += "\t";
  logBuffer += status.status1_boostCutFuel;
  logBuffer += "\t";
  logBuffer += status.status1_toothLog1Ready;
  logBuffer += "\t";
  logBuffer += status.status1_toothLog2Ready;
  logBuffer += "\t";
  logBuffer += status.engine_running;
  logBuffer += "\t";
  logBuffer += status.engine_crank;
  logBuffer += "\t";
  logBuffer += status.engine_ase;
  logBuffer += "\t";
  logBuffer += status.engine_warmup;
  logBuffer += "\t";
  logBuffer += status.engine_tpsaccaen;
  logBuffer += "\t";
  logBuffer += status.engine_tpsaccden;
  logBuffer += "\t";
  logBuffer += status.engine_mapaccaen;
  logBuffer += "\t";
  logBuffer += status.engine_mapaccden;
  logBuffer += "\t";
  logBuffer += status.dwell;
  logBuffer += "\t";
  logBuffer += status.MAP;
  logBuffer += "\t";
  logBuffer += status.IAT;
  logBuffer += "\t";
  logBuffer += status.CLT;
  logBuffer += "\t";
  logBuffer += status.batCorrection;
  logBuffer += "\t";
  logBuffer += status.BAT;
  logBuffer += "\t";
  logBuffer += status.AFR;
  logBuffer += "\t";
  logBuffer += status.EGO;
  logBuffer += "\t";
  logBuffer += status.iatCorrection;
  logBuffer += "\t";
  logBuffer += status.wueCorrection;
  logBuffer += "\t";
  logBuffer += status.RPM;
  logBuffer += "\t";
  logBuffer += status.AEamount;
  logBuffer += "\t";
  logBuffer += status.corrections;
  logBuffer += "\t";
  logBuffer += status.VE;
  logBuffer += "\t";
  logBuffer += status.AFR_T;
  logBuffer += "\t";
  logBuffer += status.PW1;
  logBuffer += "\t";
  logBuffer += status.tpsDOT;
  logBuffer += "\t";
  logBuffer += status.advance;
  logBuffer += "\t";
  logBuffer += status.TPS;
  logBuffer += "\t";
  logBuffer += status.loopsPerSeconds;
  logBuffer += "\t";
  logBuffer += status.freeRAM;
  logBuffer += "\t";
  logBuffer += status.boostTarget;
  logBuffer += "\t";
  logBuffer += status.boostDuty;
  logBuffer += "\t";
  logBuffer += status.spark_launchHard;
  logBuffer += "\t";
  logBuffer += status.spark_launchSoft;
  logBuffer += "\t";
  logBuffer += status.spark_hardLimitOn;
  logBuffer += "\t";
  logBuffer += status.spark_softLimitOn;
  logBuffer += "\t";
  logBuffer += status.spark_boostCutSpark;
  logBuffer += "\t";
  logBuffer += status.spark_error;
  logBuffer += "\t";
  logBuffer += status.spark_idleControlOn;
  logBuffer += "\t";
  logBuffer += status.spark_sync;
  logBuffer += "\t";
  logBuffer += status.rpmDOT;
  logBuffer += "\t";
  logBuffer += status.ethanolPct;
  logBuffer += "\t";
  logBuffer += status.flexCorrection;
  logBuffer += "\t";
  logBuffer += status.flexIngCorrection;
  logBuffer += "\t";
  logBuffer += status.idleLoad;
  logBuffer += "\t";
  logBuffer += status.testOutputs_testEnabled;
  logBuffer += "\t";
  logBuffer += status.testOutputs_testActive;
  logBuffer += "\t";
  logBuffer += status.AFR2;
  logBuffer += "\t";
  logBuffer += status.baro;
  logBuffer += "\t";
  logBuffer += status.tpsADC;
  logBuffer += "\t";
  logBuffer += status.error_Num;
  logBuffer += "\t";
  logBuffer += status.error_currentError;
  logBuffer += "\t";
  logBuffer += status.launchCorrection;
  logBuffer += "\t";
  logBuffer += status.PW2;
  logBuffer += "\t";
  logBuffer += status.PW3;
  logBuffer += "\t";
  logBuffer += status.PW4;
  logBuffer += "\t";
  logBuffer += status.status3_resetLockOn;
  logBuffer += "\t";
  logBuffer += status.status3_nitrousOn;
  logBuffer += "\t";
  logBuffer += status.status3_fuel2Active;
  logBuffer += "\t";
  logBuffer += status.status3_vssRefresh;
  logBuffer += "\t";
  logBuffer += status.status3_halfSync;
  logBuffer += "\t";
  logBuffer += status.status3_nSquirts;
  logBuffer += "\t";
  logBuffer += status.engineProtectStatus_RPM;
  logBuffer += "\t";
  logBuffer += status.engineProtectStatus_MAP;
  logBuffer += "\t";
  logBuffer += status.engineProtectStatus_OIL;
  logBuffer += "\t";
  logBuffer += status.engineProtectStatus_AFR;
  logBuffer += "\t";
  logBuffer += status.fuelLoad;
  logBuffer += "\t";
  logBuffer += status.ingLoad;
  logBuffer += "\t";
  logBuffer += status.injAngle;
  logBuffer += "\t";
  logBuffer += status.idleDuty;
  logBuffer += "\t";
  logBuffer += status.CLIdleTarget;
  logBuffer += "\t";
  logBuffer += status.mapDOT;
  logBuffer += "\t";
  logBuffer += status.vvt1Angle;
  logBuffer += "\t";
  logBuffer += status.vvt1TargetAngle;
  logBuffer += "\t";
  logBuffer += status.vvt1Duty;
  logBuffer += "\t";
  logBuffer += status.flexBoostCorrection;
  logBuffer += "\t";
  logBuffer += status.baroCorrection;
  logBuffer += "\t";
  logBuffer += status.ASEValue;
  logBuffer += "\t";
  logBuffer += status.VSS;
  logBuffer += "\t";
  logBuffer += status.gear;
  logBuffer += "\t";
  logBuffer += status.fuelPressure;
  logBuffer += "\t";
  logBuffer += status.oilPressure;
  logBuffer += "\t";
  logBuffer += status.wmiPW;
  logBuffer += "\t";
  logBuffer += status.status4_wmiEmpty;
  logBuffer += "\t";
  logBuffer += status.status4_vvt1Error;
  logBuffer += "\t";
  logBuffer += status.status4_vvt2Error;
  logBuffer += "\t";
  logBuffer += status.vvt2Angle;
  logBuffer += "\t";
  logBuffer += status.vvt2TargetAngle;
  logBuffer += "\t";
  logBuffer += status.vvt2Duty;
  logBuffer += "\t";
  logBuffer += status.outputsStatus_1;
  logBuffer += "\t";
  logBuffer += status.outputsStatus_2;
  logBuffer += "\t";
  logBuffer += status.outputsStatus_3;
  logBuffer += "\t";
  logBuffer += status.outputsStatus_4;
  logBuffer += "\t";
  logBuffer += status.outputsStatus_5;
  logBuffer += "\t";
  logBuffer += status.outputsStatus_6;
  logBuffer += "\t";
  logBuffer += status.outputsStatus_7;
  logBuffer += "\t";
  logBuffer += status.outputsStatus_8;
  logBuffer += "\t";
  logBuffer += status.fuelTemp;
  logBuffer += "\t";
  logBuffer += status.fuelTempCorrection;
  logBuffer += "\t";
  logBuffer += status.VE1;
  logBuffer += "\t";
  logBuffer += status.VE2;
  logBuffer += "\t";
  logBuffer += status.advance1;
  logBuffer += "\t";
  logBuffer += status.advance2;
  logBuffer += "\t";
  logBuffer += status.nitrous_status;
  logBuffer += "\t";
  logBuffer += status.TS_SD_Status;
  logBuffer += "\t";
  logBuffer += status.HPFromVSS;
  logBuffer += "\t";
  logBuffer += status.HPFromRPM;
  logBuffer += "\t";
  logBuffer += status.speedFromRPM;
  logBuffer += "\t";
  logBuffer += CdA;

  if (option == 1)
  {
    myFile = SD.open(logFile, FILE_WRITE);
  }

  if (option == 2)
  {
    myFile = SD.open(pullFile, FILE_WRITE);
  }

  if (myFile)
  {
    myFile.println(logBuffer);
    myFile.close();
  }

  logBuffer = "";
}

void StartLog()
{
  logFile = logName + logNumber + ".msl";
  logNumber += 1;

  LogNumberMem.write(logNumber);

  myFile = SD.open(logFile, FILE_WRITE);
  if (myFile)
  {
    ///// header 1 /////
    myFile.print(codeVersion);

    for (int i = 0; i < headerSize; i++)
    {
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

void StartPull()
{
  pullFile = pullName + pullNumber + ".msl";
  pullNumber += 1;

  PullNumberMem.write(pullNumber);

  myFile = SD.open(pullFile, FILE_WRITE);
  if (myFile)
  {
    ///// header 1 /////
    //myFile.print(codeVersion);
    myFile.print("#\"MS3 202103: MS3 2021.03\"\n\n");

    for (int i = 0; i < headerSize; i++)
    {
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