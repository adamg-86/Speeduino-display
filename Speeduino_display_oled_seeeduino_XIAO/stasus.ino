# include "statuses.h"
#include "comms.h"

////////convert recived Data to readable data ////////////
void convertData()
{
  status.secl = Data[0];
  status.status1 = Data[1];
    status.status1_inj1Status = (Data[1] & 0x01);
    status.status1_inj2Status = (Data[1] & 0x02);
    status.status1_inj3Status = (Data[1] & 0x04);
    status.status1_inj4Status = (Data[1] & 0x08);
    status.status1_DFCOOn = (Data[1] & 0x10);
    status.status1_boostCutFuel = (Data[1] & 0x20);
    status.status1_toothLog1Ready = (Data[1] & 0x40);
    status.status1_toothLog2Ready = (Data[1] & 0x80);

  status.engine = Data[2];
    status.engine_running = (Data[2] & 0x01);
    status.engine_crank = (Data[2] & 0x02);
    status.engine_ase = (Data[2] & 0x04);
    status.engine_warmup = (Data[2] & 0x08);
    status.engine_tpsaccaen = (Data[2] & 0x10);
    status.engine_tpsaccden = (Data[2] & 0x20);
    status.engine_mapassaen = (Data[2] & 0x40);
    status.engine_mapaccden = (Data[2] & 0x80);

  status.dwell = (float)(Data[3] / 10);
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
  status.PW1 = (float)(((Data[21] << 8) | Data[20]) / 1000.0);
  status.tpsDOT = Data[22];
  status.advance = Data[23];
  status.TPS = Data[24];
  status.loopsPerSeconds = ((Data[26] << 8) | Data[25]);
  status.freeRAM = ((Data[28] << 8) | Data[27]);
  status.boostTarget = Data[29] << 1; // multiply by 2
  status.boostDuty = Data[30];
  status.spark = Data[31]; /////// rendu ici pour tester//////////////////////////////////////////
    status.spark_launchHard = (Data[31] & 0x01);
    status.spark_launchSoft = (Data[31] & 0x02);
    status.spark_hardLimitOn = (Data[31] & 0x04);
    status.spark_softLimitOn = (Data[31] & 0x08);
    status.spark_boostCutSpark = (Data[31] & 0x10);
    status.spark_error = (Data[31] & 0x20);
    status.spark_idleControlOn = (Data[31] & 0x40);
    status.spark_sync = (Data[31] & 0x80);

  status.rpmDOT = ((Data[33] << 8) | Data[32]);
  status.ethanolPct = Data[34];
  status.flexCorrection = Data[35];
  status.flexIngCorrection = Data[36];
  status.idleLoad = Data[37];
  status.testOutputs = Data[38];
    status.testOutputs_testEnabled = (Data[38] & 0x01);
    status.testOutputs_testActive = (Data[31] & 0x02);

  status.O2_2 = Data[39];
  status.baro = Data[40];
  status.tpsADC = Data[73];
  status.error = Data[74];
    status.engineProtectStatus_RPM = (Data[74] & 0x01);
    status.engineProtectStatus_MAP = (Data[74] & 0x02);
    status.engineProtectStatus_OIL = (Data[74] & 0x04);
    status.engineProtectStatus_AFR = (Data[74] & 0x08);

  status.engineProtectStatus = Data[83];

  status.mapDOT = Data[92];
  status.ASEValue = Data[99];

  status.VSS = ((Data[101] << 8) | Data[100]); //combine the high and low byte
  status.gear = Data[102];
  status.outputsStatus = Data[110];

  status.PSI = ((float)status.MAP * 0.145) - 14.5; //convert Kpa to psi
}