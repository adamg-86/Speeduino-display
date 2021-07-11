#ifndef SDLOGGER_H
#define SDLOGGER_H

#include <SPI.h>
#include <SD.h>

void SDlog();

// SD logger//
File myFile;
const byte chipSelect = 3;
String logBuffer = "";
bool noSDcard = 0;

/*const char header1[] PROGMEM  = {"\
"hasSync",\
"RPM",\
"MAP", \
"TPS", \
"tpsDOT",\
"mapDOT",\
"rpmDOT",\
"VE1", \
"VE2",\
"AFR",\
"AFR_2",\
"CLT",\
"IAT",\
"Dwell",\
"battery10",\
"advance",\
"advance1",\
"advance2",\
"corrections",\
"AEamount",\
"Gego",\
"Gwarm",\
"Gbattery",\
"Gair",\
"Gbaro",\
"launchCorrection",\
"flexCorrection",\
"fuelTempCorrection",\
"flexIgnCorrection",\
"AFR Target",\
"idleDuty",\
"CLIdleTarget",\
"idleUpActive",\
"CTPSActive",\
"fanOn",\
"ethanolPct",\
"fuelTemp",\
"AEEndTime",\
"status1",\
"spark",\
"spark2",\
"engine",\
"PW1",\
"PW2",\
"PW3",\
"PW4",\
"PW5",\
"PW6",\
"PW7",\
"PW8",\
"runSecs",\
"secl",\
"loopsPerSecond",\
"launchingSoft",\
"launchingHard",\
"freeRAM",\
"startRevolutions",\
"boostTarget",\
"testOutputs",\
"testActive",\
"boostDuty",\
"idleLoad",\
"status3",\
"flexBoostCorrection",\
"nitrous_status",\
"fuelLoad",\
"fuelLoad2",\
"ignLoad",\
"fuelPumpOn",\
"syncLossCounter",\
"knockRetard",\
"knockActive",\
"toothLogEnabled",\
"compositeLogEnabled",\
"vvt1Angle",\
"vvt1Angle",\
"vvt1TargetAngle",\
"vvt1Duty",\
"injAngle",\
"ASEValue",\
"vss",\
"idleUpOutputActive",\
"gear",\
"fuelPressure",\
"oilPressure",\
"engineProtectStatus",\
"wmiPW", \
"DutyCycle",\
"Time",\
"};
*/

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

#endif