#include "eeprom_controller.h"
#define EEPROM_FLOAT_START_ADDRESS 4090

void writeFloatToEEPROM(int data)
{
  eeprom_write_block(&data, (void *)EEPROM_FLOAT_START_ADDRESS, 4);
}

int readFloatFromEEPROM()
{
  int data;
  eeprom_read_block(&data, (const void *)EEPROM_FLOAT_START_ADDRESS, 4);
  return data;
}