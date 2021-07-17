#ifndef SDLOGGER_H
#define SDLOGGER_H

#include <SPI.h>
#include <SD.h>

#define logSize 111
#define headerSize logSize*2

void SDlog();

// SD logger//
File myFile;
const byte chipSelect = 3;
String logBuffer = "";
bool noSDcard = 0;




const char *header[] PROGMEM  = {"secl","s",\
"status1_inj1Status", "",\
"status1_inj2Status", "",\
"status1_inj3Status", "",\
"status1_inj4Status", "",\
"status1_DFCOOn", "",\
"status1_boostCutFuel", "",\
"status1_toothLog1Ready", "",\
"status1_toothLog2Ready", "",\
"engine_running", "",\
"engine_crank", "",\
"engine_ase", "",\
"engine_warmup", "",\
"engine_tpsaccaen", "",\
"engine_tpsaccden", "",\
"engine_mapaccaen", "",\
"engine_mapaccden", "",\
"dwell", "ms",\
"MAP", "kpa",\
"IAT", "C",\
"CLT", "C",\
"batCorrection", "%",\
"BAT", "V",\
"AFR", "afr",\
"EGO", "%",\
"iatCorrection", "%",\
"wueCorrection", "%",\
"RPM", "rpm",\
"AEamount", "%",\
"corrections", "%",\
"VE", "",\
"AFR_T", "afr",\
"PW1", "ms",\
"tpsDOT", "%/s",\
"advance", "deg",\
"TPS", "%",\
"loopsPerSeconds", "",\
"freeRAM", "",\
"boostTarget", "kpa",\
"boostDuty", "%",\
"launchHard", "",\
"launchSoft", "",\
"hardLimitOn", "",\
"softLimitOn", "",\
"boostCutSpark", "",\
"error", "",\
"idleControlOn", "",\
"sync", "",\
"rpmDOT", "kpa/s",\
"ethanolPct", "%",\
"flexCorrection", "%",\
"flexIngCorrection", "deg",\
"idleLoad", "",\
"testEnable", "",\
"testActive", "",\
"AFR2", "afr",\
"baro", "kpa",\
"tpsADC", "",\
"error_Num", "",\
"error_currentError", "",\
"launchCorrection", "deg",\
"PW2", "ms",\
"PW3", "ms",\
"PW4", "ms",\
"resetLockOn", "",\
"nitrousOn", "",\
"fuel2Active", "",\
"vssRefresh", "",\
"halfSync", "",\
"nSquirts", "",\
"engineProtection_RPM", "",\
"engineProtection_MAP", "",\
"engineProtection_OIL", "",\
"engineProtection_AFR", "",\
"fuelLoad", "",\
"ingLoad", "",\
"injAngle", "deg",\
"idleDuty", "",\
"CLIdleTarget", "rpm",\
"mapDot", "kpa/s",\
"vvt1Angle", "deg",\
"vvt1TargetAngle", "deg",\
"vvt1Duty", "%",\
"flexBoostCorrection", "kpa",\
"baroCorrection", "%",\
"ASEValue", "%",\
"VSS_kph", "kph",\
"gear", "",\
"fuelPressure", "kpa",\
"oilPressure", "kpa",\
"wmiPW", "ms",\
"wmiEmpty", "",\
"vvt1Error", "",\
"vvt2Error", "",\
"vvt2Angle", "deg",\
"vvt2TargetAngle", "deg",\
"vvt2Duty", "%",\
"programmableOutput_1", "",\
"programmableOutput_2", "",\
"programmableOutput_3", "",\
"programmableOutput_4", "",\
"programmableOutput_5", "",\
"programmableOutput_6", "",\
"programmableOutput_7", "",\
"programmableOutput_8", "",\
"fuelTemp", "C",\
"fuelTempCorrection", "%",\
"VE1", "",\
"VE2", "",\
"advance1", "deg",\
"advance2", "deg",\
"nitrous_status", "",\
"TS_SD_Status", "",\
};

#endif