#include "comms.h"

void sendComms(byte command, uint8_t canID, uint8_t cmd, uint16_t offset, uint16_t length)  //void sendComms(byte command, uint8_t canID = 0, uint8_t cmd = 0x30, uint16_t offset = 0, uint16_t length = 118)
{
  switch (command)
  {
  case 'A':
    Serial1.write('A');
    break;

  case 'n':
    Serial1.write('n');
    break;

  case 'r':
    Serial1.write('r');
    Serial1.write(canID);            //canID
    Serial1.write(cmd);              //cmd
    Serial1.write(lowByte(offset));  //offset low byte
    Serial1.write(highByte(offset)); //offset high byte
    Serial1.write(lowByte(length));  //length low byte
    Serial1.write(highByte(length)); //length high byte
    break;

  case 'S':
    Serial1.write('S');
    break;

  case 'G': // to send aux input data

    break;
  }
}

void reciveComms(byte command, byte offset, byte length)  //void reciveComms(byte command, byte length = 0, byte offset = 0)
{
  byte cmdr = 0;
  
  if (Serial1.available())
  {
    command = Serial1.read();
  }

  switch (command)
  {
    case 'A':
        GetData(0, 75);
    break;

    case 'n':
      if (Serial1.available() >= 2)
        {
          cmdr = Serial1.read();
          length = Serial1.read();
        }
      GetData(0, length);
    break;

    case 'r':
      if (Serial1.available())
        {
          cmdr = Serial1.read();
        }
      GetData(0, length);
    break;

    case 'R': //CANcoms for aux inputs 

    break;
  }
}

//******** get serial data *************//

void GetData(uint8_t offset, uint8_t length)
{

  uint liveOffset; //number of byte to recive

  liveOffset = offset + length;

  while (Serial1.available()) //read the serial buffer
  {
    for (offset; offset <= (liveOffset); offset++)
    {
      Data[offset] = Serial1.read();
    }
  }
}

String getVersion()
{
  sendComms('S');
  delay(100);
  String msg = "";
  char temp;

  while (Serial1.available()) { 
    //for (uint8_t sig = 0; sig < 3 ; sig++)
      //{
      temp = Serial1.read();
      msg += char(temp); 
     // }
  }
  return msg;
}