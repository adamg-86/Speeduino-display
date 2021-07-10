#ifndef COMMS_H
#define COMMS_H

uint8_t Data[117]; //Data buffer for serial read

void GetData();
void sendComms(byte command, uint8_t canID = 0, uint8_t cmd = 0x30, uint16_t offset = 0, uint16_t length = 118);
void reciveComms(byte command, byte offset = 0, byte length = 0);

#endif 