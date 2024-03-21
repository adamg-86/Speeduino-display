#ifndef SDLOGGER_H
#define SDLOGGER_H

#include <SPI.h>
#include <SD.h>
#include <FlashStorage.h>

#define logSize 118 //the number of line of the header from line 30 to 147 147-30 = 117
#define headerSize logSize*2

FlashStorage(LogNumberMem, int);
FlashStorage(PullNumberMem, int);
void SDlog(int);
void StartLog();
void StartPull();

File myFile;
const byte chipSelect = 3;
String logBuffer = "";
bool noSDcard = 0;
String logName = "Log-";
String pullName = "Pull-";
int logNumber = 1;
int pullNumber = 1;
String logFile = "";
String pullFile = "";



// Status to log, units of the status,
const char *header[] PROGMEM  = {"Time","s",\
"Secl", "s",\
"inj1 Status", "",\
"inj2 Status", "",\
"inj3 Status", "",\
"inj4 Status", "",\
"DFCO On", "",\
"Boost Cut Fuel", "",\
"Tooth Log1 Ready", "",\
"Tooth Log2 Ready", "",\
"Engine running", "",\
"Engine crank", "",\
"Engine ase", "",\
"Engine warmup", "",\
"Engine tpsaccaen", "",\
"Engine tpsaccden", "",\
"Engine mapaccaen", "",\
"Engine mapaccden", "",\
"Dwell", "ms",\
"MAP", "kpa",\
"IAT", "C",\
"CLT", "C",\
"Gbattery", "%",\
"Battery V", "V",\
"AFR", "afr",\
"EGO cor1", "%",\
"Gair", "%",\
"Gwarm", "%",\
"RPM", "rpm",\
"Accel Enrich", "%",\
"Gammae", "%",\
"Current VE", "",\
"AFR Target", "afr",\
"PW1", "ms",\
"TPS DOT", "%/s",\
"advance", "deg",\
"TPS", "%",\
"loops Per Seconds", "",\
"free RAM", "",\
"boost Target", "kpa",\
"boost Duty", "%",\
"launch Hard", "",\
"launch Soft", "",\
"hard LimitOn", "",\
"soft LimitOn", "",\
"boost CutSpark", "",\
"error", "",\
"Idle Control On", "",\
"sync", "",\
"rpmDOT", "kpa/s",\
"ethanol Pct", "%",\
"flex Correction", "%",\
"flex Ing Correction", "deg",\
"idleLoad", "",\
"test Enable", "",\
"test Active", "",\
"AFR2", "afr",\
"Baro Pressure", "kpa",\
"tps ADC", "",\
"error #", "",\
"error ID", "",\
"launch Correction", "deg",\
"PW2", "ms",\
"PW3", "ms",\
"PW4", "ms",\
"reset Lock On", "",\
"nitrous On", "",\
"fuel2 Active", "",\
"vss Refresh", "",\
"half Sync", "",\
"n Squirts", "",\
"engine Protection RPM", "",\
"engine Protection MAP", "",\
"engine Protection OIL", "",\
"engine Protection AFR", "",\
"fuel Load", "",\
"ing Load", "",\
"inj Angle", "deg",\
"idle Duty", "",\
"Idle Target", "rpm",\
"MAP Dot", "kpa/s",\
"vvt1 Angle", "deg",\
"vvt1 TargetAngle", "deg",\
"vvt1 Duty", "%",\
"Flex Boost Correction", "kpa",\
"Baro Correction", "%",\
"ASE Value", "%",\
"Wheel Speed _kph", "km/h",\
"Gear", "",\
"fuel Pressure", "kpa",\
"oil Pressure", "kpa",\
"wmi PW", "ms",\
"wmi Empty", "",\
"vvt1 Error", "",\
"vvt2 Error", "",\
"vvt2 Angle", "deg",\
"vvt2 Target Angle", "deg",\
"vvt2 Duty", "%",\
"Wide band O2 On", "",\
"Shift Light", "",\
"programmable Output 3", "",\
"programmable Output 4", "",\
"programmable Output 5", "",\
"programmable Output 6", "",\
"programmable Output 7", "",\
"programmable Output 8", "",\
"fuel Temp", "C",\
"fuel Temp Correction", "%",\
"VE1", "",\
"VE2", "",\
"Advance 1", "deg",\
"Advance 2", "deg",\
"Nitrous Status", "",\
"TS_SD_Status", "",\
"HP From Speed", "hp",\
"HP From RPM", "hp",\
"Wheel Speed RPM/gear", "km/h",\
"CdA", "",\
};

#endif