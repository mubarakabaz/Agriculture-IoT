// #include "deklarasi.h"
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
#define PH_PIN 34 // Pin GPIO36
float voltage, phValue;

// inisialisasi pin sensor TDS
#define TDS_PIN 35
#define VREF 3.0      // tegangan referensi analog (Volt) dari ADC
#define SCOUNT  10           // jumlah titik sampel
int analogBuffer[SCOUNT];    // menyimpan nilai analog dalam array, membaca dari ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0,copyIndex = 0;
float averageVoltage = 0, tdsValue = 0, temperature = 25;

#include <ThingerESP32.h>
#include "arduino_secret.h"
ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

RTC_DS1307 rtc;
File dataFile;
const int CS = 5;

byte statusR1, statusR2;

const unsigned long interval = 60000U; // Interval waktu (1 menit dalam milisekon)
unsigned long previousMillis = 0;

void setup() {
  // serial untuk debugging
  Serial.begin(115200);

  // Inisialisasai RTC
  Wire.begin();
  if (!rtc.begin()) {
    Serial.println("Gagal inisialisasi RTC");
    while (1)
      ;
  }

  // Inisialisasi LCD
  lcd.begin();
  lcd.backlight();

  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("Memulai Program");
  lcd.setCursor(0, 1);
  lcd.print("KONOFF Hidroponik");
  lcd.setCursor(0, 3);
  lcd.print("Loading ...");
  delay(1000);

  // inisialisasi sensor pH
  pinMode(PH_PIN, INPUT);

  // inisialisasi sensor TDS
  pinMode(TDS_PIN, INPUT);

  // inisialisasi SD Card
  if (!SD.begin(CS)) {
    Serial.println("Gagal inisialisasi SD Card!");
    return;
  }
  Serial.println(" ");
  Serial.println("SD Card siap untuk menyimpan data!");
  Serial.println(" ");

  // Inisialisasi koneksi WiFi
  thing.add_wifi(SSID, SSID_PASSWORD);

  //mulai koneksi ke Thinger.io
  thing["PH"] >> inputValue(phValue);    // nilai pH yang akan dikirim
  thing["TDS"] >> inputValue(tdsValue);  // nilai TDS yang akan dikirim
  // thing.start();
}

void loop() {
  unsigned long currentMillis = millis();
  // Baca waktu dari RTC
  DateTime now = rtc.now();
  String waktuSekarang = String(now.day(), DEC) + "-"
                         + String(now.month(), DEC) + "-"
                         + String(now.year(), DEC) + " "
                         + String(now.hour(), DEC) + ":"
                         + String(now.minute(), DEC) + ":"
                         + String(now.second(), DEC);

  // Baca data dari sensor TDS
  static unsigned long analogSampleTimepoint = millis();
  if (millis() - analogSampleTimepoint > 40U) {
    analogSampleTimepoint = millis();
    analogBuffer[analogBufferIndex] = analogRead(TDS_PIN);
    analogBufferIndex++;
    if (analogBufferIndex == SCOUNT)
      analogBufferIndex = 0;
  }

  // Baca data dari sensor pH
  int ph = analogRead(PH_PIN);
  float voltage = 3.3 / 4095.0 * ph;
  // kalibrasi sensor ph (menggunakan regresi linear)
  // -5.4 -> nilai minimum pembacaan sensor
  phValue = (-5.400 * voltage) + 18.14;

  static unsigned long printTimepoint = millis();
  if (millis() - printTimepoint > 800U) {
    printTimepoint = millis();
    for (copyIndex = 0; copyIndex < SCOUNT; copyIndex++)
      analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
    averageVoltage = getMedianNum(analogBufferTemp, SCOUNT) * (float)VREF / 1024.0;
    float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);
    float compensationVoltage = averageVoltage / compensationCoefficient;
    tdsValue = (133.42 * compensationVoltage * compensationVoltage * compensationVoltage - 255.86 * compensationVoltage * compensationVoltage + 857.39 * compensationVoltage) * 0.5;
  }

  thing.handle();  // Kirim data Pengukuran Sensor ke Thinger.io

  dataFile = SD.open("data_konoff.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Waktu: " + waktuSekarang);
    dataFile.println("Pengukuran Sensor:");
    dataFile.print("pH: ");
    dataFile.print(phValue);
    dataFile.print(" TDS: ");
    dataFile.print(tdsValue);
    dataFile.print("ppm");
    dataFile.println("Status Selenoid: ");
    dataFile.print("S1: ");
    dataFile.print(statusR1);
    dataFile.print(" S2: ");
    dataFile.print(statusR2);

    dataFile.close();
    Serial.println("Data berhasil disimpan di SD Card.");
  } else {
    Serial.println("Gagal menyimpan data di SD Card!");
  }

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    Serial.print("pH : ");
    Serial.print(phValue, 2);
    Serial.print("*");
    Serial.println(" ");
    Serial.print("TDS : ");
    Serial.print(tdsValue, 2);
    Serial.print("ppm");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(waktuSekarang);

    lcd.setCursor(0, 1);
    lcd.print("pH: ");
    lcd.setCursor(9, 1);
    lcd.print(phValue);
    lcd.seCursor(10, 1);
    lcd.print("TDS: ");
    lcd.setCursor(16, 1);
    lcd.print(tdsValue);

    lcd.setCursor(0, 2);
    lcd.print("R1:");
    lcd.setCursor(4, 2);
    lcd.print(statusR1);
    lcd.setCursor(9, 2);
    lcd.print("R2:");
    lcd.setCursor(13, 2);
    lcd.print(statusR2);

    lcd.setCursor(0, 3);
    lcd.print("SD Card:");
    lcd.setCursor(9, 3);
    lcd.print(statusSdCard);
  }
  delay(5000);  // jeda 5 detik sebelum kembali membaca sensor
}

// deklarasi fungsi 'getMedianNum' yang mengambil dua parameter,
// yaitu, 'bArray' (array data yang akan difilter)
// dan 'iFilterLen' (panjang array data)

int getMedianNum(int bArray[], int iFilterLen) {
  // deklarasi array data yang akan digunakan untuk menyimpan salinan data
  int bTab[iFilterLen];
  // perulangan ini untuk mengambil setiap elemen dari 'bArray' dan menyimpan
  // salinan data dari 'bArray'
  for (byte i = 0; i < iFilterLen; i++)
    bTab[i] = bArray[i];
  int i, j, bTemp;  //deklarasi variabel yang akan digunakan dalam proses filtrasi median.

  /*
  dua loop bersarang. Loop luar (j) digunakan untuk mengulangi 
  proses perbandingan dan pertukaran nilai sampai data diurutkan 
  dari yang terkecil hingga yang terbesar. Loop dalam (i) digunakan 
  untuk melakukan perbandingan dan pertukaran nilai antara dua elemen 
  bersebelahan jika elemen pertama lebih besar dari elemen kedua. 
  Ini adalah langkah yang diperlukan untuk mengurutkan data.
  */
  for (j = 0; j < iFilterLen - 1; j++) {
    for (i = 0; i < iFilterLen - j - 1; i++) {
      if (bTab[i] > bTab[i + 1]) {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }

  /*
  Setelah data diurutkan, kode ini menghitung nilai median. Jika 
  jumlah elemen dalam data adalah ganjil (iFilterLen & 1 menghasilkan 
  nilai yang lebih besar dari 0), maka nilai median adalah elemen tengah.
  Jika jumlah elemen adalah genap, maka nilai median adalah rata-rata
  dari dua elemen tengah.
  */
  if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
  else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  return bTemp;  // mengembalikan nilai median yang telah dihitung.
}
