#include "alarms.h"
#include "statuses.h"

///// Set Alarms to display on the screen ///////
bool Alarm()
{
  //char alarmType[20];
  bool alarm;

  if (status.CLT > 110)
  {
    alarm = 1;
    alarmType = "Engine HOT";
  }

  else if (status.IAT > 80)
  {
    alarm = 1;
    alarmType = "Intake HOT";
  }

  else if ((status.TPS > 80) && (status.AFR > 14))
  {
    alarm = 1;
    alarmType = "  LEAN...";
  }

  else
    alarm = 0;

  return alarm;
}