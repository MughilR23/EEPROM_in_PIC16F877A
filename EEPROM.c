#include"EEPROM.h"
// EEPROM Single Byte Write
void EEPROM_Write(unsigned char address, unsigned char data)
{
    while (WR);                  // Wait if a write is already in progress

    EEADR = address;             // Set EEPROM address
    EEDATA = data;               // Set data to write

    EECON1 &= ~(1 << 7);         // Clear EEPGD bit -> Point to data EEPROM memory
    EECON1 |= (1 << 2);          // Set WREN bit -> Enable EEPROM write

    INTCON &= ~(1 << 7);         // Disable global interrupts (GIE)
    EECON2 = 0x55;               // Required unlock sequence
    EECON2 = 0xAA;
    EECON1 |= (1 << 1);          // Set WR bit -> Start write
    INTCON |= (1 << 7);          // Re-enable global interrupts

    while (WR);                  // Wait for write to complete
    EECON1 &= ~(1 << 2);         // Clear WREN after write
}

// EEPROM Single Byte Read
unsigned char EEPROM_Read(unsigned char address)
{
    EEADR = address;             // Set EEPROM address
    EECON1 &= ~(1 << 7);         // Clear EEPGD bit -> Data EEPROM access
    EECON1 |= (1 << 0);          // Set RD bit -> Start read
    __delay_us(5);               // Short delay for data to be available
    return EEDATA;               // Return data
}

// EEPROM Block Write
void EEPROM_WriteBlock(unsigned char address, const unsigned char *data, unsigned char length)
{
    for (unsigned char i = 0; i < length; i++) {
        EEPROM_Write(address + i, data[i]);
    }
}

// EEPROM Block Read
void EEPROM_ReadBlock(unsigned char *dest, unsigned char address, unsigned char length)
{
    for (unsigned char i = 0; i < length; i++) {
        dest[i] = EEPROM_Read(address + i);
    }
}

//EEPROM WRITE FLOAT VALUE
void EEPROM_Write_float(unsigned char address, float value) {
    unsigned char *ptr = (unsigned char*)&value;
    for (int i = 0; i < 4; i++) {
        EEPROM_Write(address + i, ptr[i]);
        __delay_ms(10);
    }
}


//EEPROM READ FLOAT VALUE
float EEPROM_Read_float(unsigned char address) {
    float value;
    unsigned char *ptr = (unsigned char*)&value;
    for (int i = 0; i < 4; i++) {
        ptr[i] = EEPROM_Read(address + i);
        __delay_ms(10);
    }
    return value;
}
