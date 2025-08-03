#include <htc.h>
#define _XTAL_FREQ 8000000
#ifndef EEPROM_H
#define EEPROM_H
// Function Prototypes
void EEPROM_Write(unsigned char address, unsigned char data);
unsigned char EEPROM_Read(unsigned char address);
void EEPROM_WriteBlock(unsigned char address, const unsigned char *data, unsigned char length);
void EEPROM_ReadBlock(unsigned char *dest, unsigned char address, unsigned char length);
void EEPROM_Write_float(unsigned char address, float value);
float EEPROM_Read_float(unsigned char address);
#endif