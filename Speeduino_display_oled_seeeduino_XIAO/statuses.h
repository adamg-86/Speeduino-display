#ifndef STATUSES_H
#define STATUSES_H

//// HP calculation values ////
#define RHO_AIR 1.23    //kg/m^3
#define CAR_CD 0.38
#define FRONTAL_AREA 0.092903 //in m^2
#define CAR_MASS 1045   //kg
#define DRIVER_MASS 85  //kg

#define TIRE_CIRCUM 1.72385   // Tire circumference in m

#define G_RATIO_1 3.136
#define G_RATIO_2 1.888
#define G_RATIO_3 1.33
#define G_RATIO_4 1
#define G_RATIO_5 0.814
#define G_RATIO_DIFF 4.1

void convertData();
void calculateHP();
void speedFromRPM();

uint16_t massSum = CAR_MASS + DRIVER_MASS;
String codeVersion = "#";
float lastTime;
uint16_t lastSpeed;
uint16_t lastSpeedRPM;

struct status {
float Time;
uint8_t secl;              //byte 0 counter
uint8_t status1;           //byte 1 status1 Bitfield, inj1Status(0), inj2Status(1), inj3Status(2), inj4Status(3), DFCOOn(4), boostCutFuel(5), toothLog1Ready(6), toothLog2Ready(7)
    bool status1_inj1Status;
    bool status1_inj2Status;
    bool status1_inj3Status;
    bool status1_inj4Status;
    bool status1_DFCOOn;
    bool status1_boostCutFuel;
    bool status1_toothLog1Ready;
    bool status1_toothLog2Ready;

uint8_t engine;            //byte 2 Engine Status Bitfield, running(0), crank(1), ase(2), warmup(3), tpsaccaen(4), tpsaccden(5), mapaccaen(6), mapaccden(7)
    bool engine_running;
    bool engine_crank;
    bool engine_ase;
    bool engine_warmup;
    bool engine_tpsaccaen;
    bool engine_tpsaccden;
    bool engine_mapaccaen;
    bool engine_mapaccden;

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
uint8_t VE;                //byte 18
float AFR_T;               //byte 19
float PW1;                 //byte 20 (lowByte) and 21 (highByte)
uint8_t tpsDOT;            //byte 22
int8_t advance;            //byte 23  live advance can be an average of table 1 and 2
uint8_t TPS;               //byte 24
uint16_t loopsPerSeconds;  //byte 25 (lowByte) and 26 (highByte)
uint16_t freeRAM;          //byte 27 (lowByte) and 28 (highByte)
uint16_t boostTarget;      //byte 29 divide by 2 to fit in a byte in kpa
uint8_t boostDuty;         //byte 30 in %
uint8_t spark;             //byte 31 Spark related bitfield, launchHard(0), launchSoft(1), hardLimitOn(2), softLimitOn(3), boostCutSpark(4), error(5), idleControlOn(6), sync(7)
    bool spark_launchHard;
    bool spark_launchSoft;
    bool spark_hardLimitOn;
    bool spark_softLimitOn;
    bool spark_boostCutSpark;
    bool spark_error;
    bool spark_idleControlOn;
    bool spark_sync;

int16_t rpmDOT;           //byte 32 (lowByte) and 33 (highByte)
uint8_t ethanolPct;        //byte 34
int8_t flexCorrection;    //byte 35
uint8_t flexIngCorrection; //byte 36
uint8_t idleLoad;          //byte 37
uint8_t testOutputs;       //byte 38 testOutputs related bitfield, testEnabled(0), testActive(1)
    bool testOutputs_testEnabled;//bit 0
    bool testOutputs_testActive;//bit 1

float AFR2;                //byte 39
uint8_t baro;              //byte 40
//byte 41 to 72 aux input 
uint8_t tpsADC;            //byte 73
uint8_t error;             //byte 74
    bool error_Num;        //bit 0
    int error_currentError;//bit 1-7

int8_t launchCorrection;  //byte 75

float PW2;                 //byte 76 (lowByte) and 77 (highByte)  //Pulsewidth 2 multiplied by 10 in ms. Have to convert from uS to mS.
float PW3;                 //byte 78 (lowByte) and 79 (highByte)  //Pulsewidth 3 multiplied by 10 in ms. Have to convert from uS to mS.
float PW4;                 //byte 80 (lowByte) and 81 (highByte)  //Pulsewidth 4 multiplied by 10 in ms. Have to convert from uS to mS.

uint8_t status3;           //byte 82 status3 related bitfield, resentLockOn(0), nitrousOn(1), fuel2Active(2), vssRefresh(3), halfSync(4), nSquirts(5:7)
    bool status3_resetLockOn;
    bool status3_nitrousOn;
    bool status3_fuel2Active;
    bool status3_vssRefresh;
    bool status3_halfSync;
    uint8_t status3_nSquirts;

uint8_t engineProtectStatus;//byte 83 engineProtectStatus related bitfield, RPM(0), MAP(1), OIL(2), AFR(3), Unused(4:7)
    bool engineProtectStatus_RPM;
    bool engineProtectStatus_MAP;
    bool engineProtectStatus_OIL;
    bool engineProtectStatus_AFR;

int16_t fuelLoad;         //byte 84 (lowByte) and 85 (highByte)
int16_t ingLoad;          //byte 86 (lowByte) and 87 (highByte)
uint16_t injAngle;         //byte 88 (lowByte) and 89 (highByte)
uint8_t idleDuty;          //byte 90
uint16_t CLIdleTarget;      //byte 91
uint16_t mapDOT;            //byte 92
float vvt1Angle;         //byte 93
float vvt1TargetAngle;   //byte 94
float vvt1Duty;          //byte 95
int16_t flexBoostCorrection; //byte 96 (lowByte) and 97 (highByte)
uint8_t baroCorrection;    //byte 98
uint8_t ASEValue;          //byte 99
uint16_t VSS;              //byte 100 (lowByte) and 101 (highByte)
uint8_t gear;              //byte 102
uint8_t fuelPressure;      //byte 103
uint8_t oilPressure;       //byte 104
uint8_t wmiPW;             //byte 105
uint8_t status4;           //byte 106 status4 related bitfield, wmiEmptyBit(0), vvt1Error(1), vvt2Error(2), UnusedBits(3:7)
    bool status4_wmiEmpty;
    bool status4_vvt1Error;
    bool status4_vvt2Error;

float vvt2Angle;         //byte 107 
float vvt2TargetAngle;   //byte 108
float vvt2Duty;          //byte 109
uint8_t outputsStatus;     //byte 110
    bool outputsStatus_1;
    bool outputsStatus_2;
    bool outputsStatus_3;
    bool outputsStatus_4;
    bool outputsStatus_5;
    bool outputsStatus_6;
    bool outputsStatus_7;
    bool outputsStatus_8;

uint8_t fuelTemp;          //byte 111
uint8_t fuelTempCorrection;//byte 112
uint8_t VE1;               //byte 113
uint8_t VE2;               //byte 114
int8_t advance1;          //byte 115
int8_t advance2;          //byte 116
uint8_t nitrous_status;    //byte 117
uint8_t TS_SD_Status;      //byte 118

//// calculated status  ////////////
float PSI; //bar to psi conversion
float BOOST_PSI;
float maxPsi;

int16_t HPFromVSS;
int16_t HPFromRPM;
uint16_t speedFromRPM;
};

struct status status;

#endif