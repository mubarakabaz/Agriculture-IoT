// insialisasi Modul SD Card
#include <SPI.h>
#include <SD.h>

// Inisialisasi Pin RTC
#include <RTClib.h>
RTC_DS1307 rtc;

// Inisilaisasi LCD Display
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Import library EEPROM
#include <EEPROM.h>

// Inisialisasi PIN Sensor pH Meter
#define PH_PIN D34 // Pin GPIO36
float voltage, phValue;

// inisialisasi pin sensor TDS
#define TdsSensorPin D35
#define VREF 3.0      // analog reference voltage(Volt) of the ADC
#define SCOUNT  30           // sum of sample point
int analogBuffer[SCOUNT];    // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0,copyIndex = 0;
float averageVoltage = 0,tdsValue = 0,temperature = 25;

