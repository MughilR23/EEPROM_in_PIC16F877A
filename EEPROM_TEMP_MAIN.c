#include"ADC.h"
#include"EEPROM.h"
#include"GPIO.h"
#include"LCD8.h"
#include<stdio.h>
#define _XTAL_FREQ 8000000
__CONFIG(0X3FBB);
int a;
float temp;
char str[20];
void main()
{
pinMode(1,1,INPUT);
ADC_init();
LCD_init();
__delay_ms(20);
LCD_clear();
temp   =EEPROM_Read_float(0X00);
__delay_ms(20);
LCD_setcursor(0,0);
sprintf(str,"tempR=%.2fC  ",temp);
LCD_print(str);
__delay_ms(100);
while(1)
{
a=analogRead(1);
temp=a*0.0048*100;
EEPROM_Write_float(0X00,temp);
__delay_ms(20);
LCD_setcursor(1,0);
sprintf(str,"tempW=%.2fC  ",temp);
LCD_print(str);
__delay_ms(100);

}
}