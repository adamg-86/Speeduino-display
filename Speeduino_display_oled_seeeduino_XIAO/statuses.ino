# include "statuses.h"
#include "comms.h"

////////convert recived Data to readable data ////////////
void convertData()
{
  status.secl     = Data[0];
  status.status1  = Data[1];
    status.status1_inj1Status     = (Data[1] & 0x01);
    status.status1_inj2Status     = (Data[1] & 0x02);
    status.status1_inj3Status     = (Data[1] & 0x04);
    status.status1_inj4Status     = (Data[1] & 0x08);
    status.status1_DFCOOn         = (Data[1] & 0x10);
    status.status1_boostCutFuel   = (Data[1] & 0x20);
    status.status1_toothLog1Ready = (Data[1] & 0x40);
    status.status1_toothLog2Ready = (Data[1] & 0x80);

  status.engine = Data[2];
    status.engine_running   = (Data[2] & 0x01);
    status.engine_crank     = (Data[2] & 0x02);
    status.engine_ase       = (Data[2] & 0x04);
    status.engine_warmup    = (Data[2] & 0x08);
    status.engine_tpsaccaen = (Data[2] & 0x10);
    status.engine_tpsaccden = (Data[2] & 0x20);
    status.engine_mapaccaen = (Data[2] & 0x40);
    status.engine_mapaccden = (Data[2] & 0x80);

  status.dwell = (float)Data[3] / 10;
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
  status.PW1 = (float)((Data[21] << 8) | Data[20]) / 1000;
  status.tpsDOT = Data[22];
  status.advance = Data[23];
  status.TPS = Data[24];
  status.loopsPerSeconds = ((Data[26] << 8) | Data[25]);
  status.freeRAM = ((Data[28] << 8) | Data[27]);
  status.boostTarget = Data[29] << 1; // multiply by 2
  status.boostDuty = Data[30];
  status.spark = Data[31]; /////// rendu ici pour tester//////////////////////////////////////////
    status.spark_launchHard     = (Data[31] & 0x01);
    status.spark_launchSoft     = (Data[31] & 0x02);
    status.spark_hardLimitOn    = (Data[31] & 0x04);
    status.spark_softLimitOn    = (Data[31] & 0x08);
    status.spark_boostCutSpark  = (Data[31] & 0x10);
    status.spark_error          = (Data[31] & 0x20);
    status.spark_idleControlOn  = (Data[31] & 0x40);
    status.spark_sync           = (Data[31] & 0x80);

  status.rpmDOT = ((Data[33] << 8) | Data[32]);
  status.ethanolPct = Data[34];
  status.flexCorrection = Data[35];
  status.flexIngCorrection = Data[36];
  status.idleLoad = Data[37];
  status.testOutputs = Data[38];
    status.testOutputs_testEnabled = (Data[38] & 0x01);
    status.testOutputs_testActive = (Data[38] & 0x02);

  status.AFR2 = (float)Data[39] / 10;
  status.baro = Data[40];
  status.tpsADC = Data[73];
  status.error = Data[74];
    status.error_Num          = (Data[74] & 0x01);
    status.error_currentError = (Data[74] & 0xfe) >> 1; ////////////to test//////////////

  status. launchCorrection = Data[75];
  status.PW2 = (float)((Data[77] << 8) | Data[76]) / 1000;
  status.PW3 = (float)((Data[79] << 8) | Data[78]) / 1000;
  status.PW4 = (float)((Data[81] << 8) | Data[80]) / 1000;
  status.status3 = Data[82];
    status.status3_resetLockOn = (Data[82] & 0x01);
    status.status3_nitrousOn    = (Data[82] & 0x02);
    status.status3_fuel2Active  = (Data[82] & 0x04);
    status.status3_vssRefresh   = (Data[82] & 0x08);
    status.status3_halfSync     = (Data[82] & 0x10);
    status.status3_nSquirts     = (Data[82] & 0xe0) >> 5;

  status.engineProtectStatus = Data[83];
    status.engineProtectStatus_RPM = (Data[83] & 0x01);
    status.engineProtectStatus_MAP = (Data[83] & 0x02);
    status.engineProtectStatus_OIL = (Data[83] & 0x04);
    status.engineProtectStatus_AFR = (Data[83] & 0x08);

  status.fuelLoad = ((Data[85] << 8) | Data[84]);
  status.ingLoad = ((Data[87] << 8) | Data[86]);
  status.injAngle = ((Data[89] << 8) | Data[88]);
  status.idleDuty = Data[90];
  status.CLIdleTarget = Data[91] * 2;
  status.mapDOT = Data[92] * 2;
  status.vvt1Angle = (float)Data[93] / 2;
  status.vvt1TargetAngle = Data[94];
  status.vvt1Duty = Data[95];
  status.flexBoostCorrection = ((Data[97] << 8) | Data[96]);
  status.baroCorrection = Data[98];
  status.ASEValue = Data[99];
  status.VSS = ((Data[101] << 8) | Data[100]); //combine the high and low byte
  status.gear = Data[102];
  status.fuelPressure = Data[103];
  status.oilPressure = Data[104];
  status.wmiPW = Data[105];
  status.status4 = Data[106];
    status.status4_wmiEmpty   = (Data[106] & 0x01);
    status.status4_vvt1Error  = (Data[106] & 0x02);
    status.status4_vvt2Error  = (Data[106] & 0x04);

  status.vvt2Angle = (float)Data[107] / 2;
  status.vvt2TargetAngle = (float)Data[108] / 2;
  status.vvt2Duty = (float)Data[109] / 2;
  status.outputsStatus = Data[110];
    status.outputsStatus_1 = (Data[110] & 0x01);
    status.outputsStatus_2 = (Data[110] & 0x02);
    status.outputsStatus_3 = (Data[110] & 0x04);
    status.outputsStatus_4 = (Data[110] & 0x08);
    status.outputsStatus_5 = (Data[110] & 0x10);
    status.outputsStatus_6 = (Data[110] & 0x20);
    status.outputsStatus_7 = (Data[110] & 0x40);
    status.outputsStatus_8 = (Data[110] & 0x80);

  status.fuelTemp = Data[111];
  status.fuelTempCorrection = Data[112];
  status.VE1 = Data[113];
  status.VE2 = Data[114];
  status.advance1 = Data[115];
  status.advance2 = Data[116];
  status.nitrous_status = Data[117];
  status.TS_SD_Status = Data[118];

  status.PSI = ((float)status.MAP * 0.145) - 14.5; //convert Kpa to psi
  //status.PSI = (float)(status.baro - status.MAP) * 0.145;
}