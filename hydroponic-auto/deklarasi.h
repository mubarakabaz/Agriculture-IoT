
// Inisilaisasi LCD Display
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Import library EEPROM
#include <EEPROM.h>

// Inisialisasi PIN Sensor pH Meter
#define PH_PIN D34 // Pin GPIO36
float voltage, phValue;

#include <GravityTDS.h>
#define TDS_PIN D35 // pin GPIO35
GravityTDS gravityTds;
float tdsValue;