// insialisasi Modul SD Card
#include <SPI.h>
#include <SD.h>

// Inisialisasi Pin RTC
#include <Wire.h>
#include <RTClib.h>


// Inisilaisasi LCD Display
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Import library EEPROM
#include <EEPROM.h>

// Inisialisasi PIN Sensor pH Meter
#define PH_PIN D34 // Pin GPIO36
float voltage, phValue;

// inisialisasi pin sensor TDS
#define TDS_PIN D35
#define VREF 3.0      // tegangan referensi analog (Volt) dari ADC
#define SCOUNT  10           // jumlah titik sampel
int analogBuffer[SCOUNT];    // menyimpan nilai analog dalam array, membaca dari ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0,copyIndex = 0;
float averageVoltage = 0, tdsValue = 0, temperature = 25;

