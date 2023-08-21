// Library Untuk LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Library Untuk RTC
#include <RTClib.h>
RTC_DS1307 rtc;

// Library Untuk Modul SD Card
#include <DHT.h>
#include <SPI.h>
#include <SD.h>
const int chipSelect = 53; // Pin untuk koneksi SD card

#define DHTPIN_1 4  // Pin untuk sensor DHT11 1
#define DHTPIN_2 5  // Pin untuk sensor DHT11 2
#define DHTPIN_3 6  // Pin untuk sensor DHT11 3
#define DHTPIN_4 22  // Pin untuk sensor DHT11 4
#define DHTPIN_5 23  // Pin untuk sensor DHT11 5
#define DHTPIN_6 24  // Pin untuk sensor DHT11 6
#define DHTPIN_7 25  // Pin untuk sensor DHT11 7
#define DHTPIN_8 26  // Pin untuk sensor DHT11 8
#define DHTPIN_9 27  // Pin untuk sensor DHT11 9
#define DHTPIN_10 28  // Pin untuk sensor DHT11 10
#define DHTPIN_11 29  // Pin untuk sensor DHT11 11
#define DHTPIN_12 30  // Pin untuk sensor DHT11 12
#define DHTPIN_13 31  // Pin untuk sensor DHT11 13
#define DHTPIN_14 32  // Pin untuk sensor DHT11 14
#define DHTPIN_15 33  // Pin untuk sensor DHT11 15
#define DHTPIN_16 34  // Pin untuk sensor DHT11 16
#define DHTPIN_17 35  // Pin untuk sensor DHT11 17
#define DHTPIN_18 36  // Pin untuk sensor DHT11 18
#define DHTPIN_19 37  // Pin untuk sensor DHT11 19

#define DHTTYPE DHT11 // Tipe sensor DHT11

DHT dht1(DHTPIN_1, DHTTYPE);
DHT dht2(DHTPIN_2, DHTTYPE);
DHT dht3(DHTPIN_3, DHTTYPE);
DHT dht4(DHTPIN_4, DHTTYPE);
DHT dht5(DHTPIN_5, DHTTYPE);
DHT dht6(DHTPIN_6, DHTTYPE);
DHT dht7(DHTPIN_7, DHTTYPE);
DHT dht8(DHTPIN_8, DHTTYPE);
DHT dht9(DHTPIN_9, DHTTYPE);
DHT dht10(DHTPIN_10, DHTTYPE);
DHT dht11(DHTPIN_11, DHTTYPE);
DHT dht12(DHTPIN_12, DHTTYPE);
DHT dht13(DHTPIN_13, DHTTYPE);
DHT dht14(DHTPIN_14, DHTTYPE);
DHT dht15(DHTPIN_15, DHTTYPE);
DHT dht16(DHTPIN_16, DHTTYPE);
DHT dht17(DHTPIN_17, DHTTYPE);
DHT dht18(DHTPIN_18, DHTTYPE);
DHT dht19(DHTPIN_19, DHTTYPE);

const unsigned long interval = 3600000; // Interval waktu (1 jam dalam milisekon)
// const unsigned long interval = 300000; // Interval waktu (1 jam dalam milisekon)

unsigned long previousMillis = 0;

void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(9600);

  lcd.begin();
  lcd.setCursor(0,0);
  lcd.print("Memulai Program");
  lcd.setCursor(0,1);
  lcd.print("Pengukuran");
  lcd.setCursor(0,2);
  lcd.print("Suhu & Kelembaban");
  delay(1000);

  // Inisialisasi RTC
  if(!rtc.begin()){
    Serial.println("Gagal inisialisasi RTC");
    while(1);
  }

  // Inisialisasi sensor DHT11
  dht1.begin();
  dht2.begin();
  dht3.begin();
  dht4.begin();
  dht5.begin();
  dht6.begin();
  dht7.begin();
  dht8.begin();
  dht9.begin();
  dht10.begin();
  dht11.begin();
  dht12.begin();
  dht13.begin();
  dht14.begin();
  dht15.begin();
  dht16.begin();
  dht17.begin();
  dht18.begin();
  dht19.begin();

  // Inisialisasi SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("Gagal inisialisasi SD card!");
    return;
  }
  Serial.println("SD card siap untuk digunakan.");
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

  // Baca suhu dan kelembaban dari tiga sensor DHT11
  float suhu1 = dht1.readTemperature();
  float kelembaban1 = dht1.readHumidity();
  
  float suhu2 = dht2.readTemperature();
  float kelembaban2 = dht2.readHumidity();
  
  float suhu3 = dht3.readTemperature();
  float kelembaban3 = dht3.readHumidity();
  
  float suhu4 = dht4.readTemperature();
  float kelembaban4 = dht4.readHumidity();
  
  float suhu5 = dht5.readTemperature();
  float kelembaban5 = dht5.readHumidity();
  
  float suhu6 = dht6.readTemperature();
  float kelembaban6 = dht6.readHumidity();
  
  float suhu7 = dht7.readTemperature();
  float kelembaban7 = dht7.readHumidity();
  
  float suhu8 = dht8.readTemperature();
  float kelembaban8 = dht8.readHumidity();
  
  float suhu9 = dht9.readTemperature();
  float kelembaban9 = dht9.readHumidity();
  
  float suhu10 = dht10.readTemperature();
  float kelembaban10 = dht10.readHumidity();
  
  float suhu11 = dht11.readTemperature();
  float kelembaban11 = dht11.readHumidity();
  
  float suhu12 = dht12.readTemperature();
  float kelembaban12 = dht12.readHumidity();
  
  float suhu13 = dht13.readTemperature();
  float kelembaban13 = dht13.readHumidity();
  
  float suhu14 = dht14.readTemperature();
  float kelembaban14 = dht14.readHumidity();
  
  float suhu15 = dht15.readTemperature();
  float kelembaban15 = dht15.readHumidity();
  
  float suhu16 = dht16.readTemperature();
  float kelembaban16 = dht16.readHumidity();
  
  float suhu17 = dht17.readTemperature();
  float kelembaban17 = dht17.readHumidity();
  
  float suhu18 = dht18.readTemperature();
  float kelembaban18 = dht18.readHumidity();
  
  float suhu19 = dht19.readTemperature();
  float kelembaban19 = dht19.readHumidity();

  // Cek apakah berhasil membaca suhu dan kelembaban dari semua sensor
  if (isnan(suhu1) || isnan(kelembaban1) || 
      isnan(suhu2) || isnan(kelembaban2) ||
      isnan(suhu3) || isnan(kelembaban3) ||
      isnan(suhu4) || isnan(kelembaban4) ||
      isnan(suhu5) || isnan(kelembaban5) ||
      isnan(suhu6) || isnan(kelembaban6) ||
      isnan(suhu7) || isnan(kelembaban7) ||
      isnan(suhu8) || isnan(kelembaban8) ||
      isnan(suhu9) || isnan(kelembaban9) ||
      isnan(suhu10) || isnan(kelembaban10) ||
      isnan(suhu11) || isnan(kelembaban11) ||
      isnan(suhu12) || isnan(kelembaban12) ||
      isnan(suhu13) || isnan(kelembaban13) ||
      isnan(suhu14) || isnan(kelembaban14) ||
      isnan(suhu15) || isnan(kelembaban15) ||
      isnan(suhu16) || isnan(kelembaban16) ||
      isnan(suhu17) || isnan(kelembaban17) ||
      isnan(suhu18) || isnan(kelembaban18) ||
      isnan(suhu19) || isnan(kelembaban19)) {
    Serial.println("Gagal membaca data dari sensor DHT11!");
    return;
  }

  // Tampilkan data di Serial Monitor
  Serial.println("Sensor 1:");
  Serial.print("Suhu: ");
  Serial.print(suhu1);
  Serial.print(" *C, Kelembaban: ");
  Serial.print(kelembaban1);
  Serial.println(" %");

  Serial.println("Sensor 2:");
  Serial.print("Suhu: ");
  Serial.print(suhu2);
  Serial.print(" *C, Kelembaban: ");
  Serial.print(kelembaban2);
  Serial.println(" %");
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(waktuSekarang);
  lcd.setCursor(0,1);
  lcd.print("Pengukuran :");
  lcd.setCursor(0,2);
  lcd.print("R1: ");
  lcd.setCursor(5,2);
  lcd.print("S:");
  lcd.setCursor(7,2);
  lcd.print(suhu1);
  lcd.setCursor(13,2);
  lcd.print("K:");
  lcd.setCursor(15,2);
  lcd.print(kelembaban1);

  lcd.setCursor(0,3);
  lcd.print("R2: ");
  lcd.setCursor(5,3);
  lcd.print("S:");
  lcd.setCursor(7,3);
  lcd.print(suhu2);
  lcd.setCursor(13,3);
  lcd.print("K:");
  lcd.setCursor(15,3);
  lcd.print(kelembaban2);
  
  
  // Simpan data ke file di SD card setiap 1 jam
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Simpan data ke file di SD card
    File dataFile = SD.open("data.txt", FILE_WRITE);
    if (dataFile) {
      dataFile.println("Waktu: " + waktuSekarang);

      dataFile.println("Sensor 1:");
      dataFile.print("Suhu: ");
      dataFile.print(suhu1);
      dataFile.print(" *C, Kelembaban: ");
      dataFile.print(kelembaban1);
      dataFile.println(" %");

      dataFile.println("Sensor 2:");
      dataFile.print("Suhu: ");
      dataFile.print(suhu2);
      dataFile.print(" *C, Kelembaban: ");
      dataFile.print(kelembaban2);
      dataFile.println(" %");
      
      dataFile.println("Sensor 3:");
      dataFile.print("Suhu: ");
      dataFile.print(suhu3);
      dataFile.print(" *C, Kelembaban: ");
      dataFile.print(kelembaban3);
      dataFile.println(" %");
      
      dataFile.println("Sensor 4:");
      dataFile.print("Suhu: ");
      dataFile.print(suhu4);
      dataFile.print(" *C, Kelembaban: ");
      dataFile.print(kelembaban4);
      dataFile.println(" %");
      
      dataFile.println("Sensor 5:");
      dataFile.print("Suhu: ");
      dataFile.print(suhu5);
      dataFile.print(" *C, Kelembaban: ");
      dataFile.print(kelembaban5);
      dataFile.println(" %");
      
      dataFile.println("Sensor 6:");
      dataFile.print("Suhu: ");
      dataFile.print(suhu6);
      dataFile.print(" *C, Kelembaban: ");
      dataFile.print(kelembaban6);
      dataFile.println(" %");
      
      dataFile.println("Sensor 7:");
      dataFile.print("Suhu: ");
      dataFile.print(suhu7);
      dataFile.print(" *C, Kelembaban: ");
      dataFile.print(kelembaban7);
      dataFile.println(" %");
      
      dataFile.println("Sensor 8:");
      dataFile.print("Suhu: ");
      dataFile.print(suhu8);
      dataFile.print(" *C, Kelembaban: ");
      dataFile.print(kelembaban8);
      dataFile.println(" %");
      
      dataFile.println("Sensor 9:");
      dataFile.print("Suhu: ");
      dataFile.print(suhu9);
      dataFile.print(" *C, Kelembaban: ");
      dataFile.print(kelembaban9);
      dataFile.println(" %");
      
      dataFile.println("Sensor 10:");
      dataFile.print("Suhu: ");
      dataFile.print(suhu10);
      dataFile.print(" *C, Kelembaban: ");
      dataFile.print(kelembaban10);
      dataFile.println(" %");
      
      dataFile.println("Sensor 11:");
      dataFile.print("Suhu: ");
      dataFile.print(suhu11);
      dataFile.print(" *C, Kelembaban: ");
      dataFile.print(kelembaban11);
      dataFile.println(" %");
      
      dataFile.println("Sensor 12:");
      dataFile.print("Suhu: ");
      dataFile.print(suhu12);
      dataFile.print(" *C, Kelembaban: ");
      dataFile.print(kelembaban12);
      dataFile.println(" %");
      
      dataFile.println("Sensor 13:");
      dataFile.print("Suhu: ");
      dataFile.print(suhu13);
      dataFile.print(" *C, Kelembaban: ");
      dataFile.print(kelembaban13);
      dataFile.println(" %");
      
      dataFile.println("Sensor 14:");
      dataFile.print("Suhu: ");
      dataFile.print(suhu14);
      dataFile.print(" *C, Kelembaban: ");
      dataFile.print(kelembaban14);
      dataFile.println(" %");
      
      dataFile.println("Sensor 15:");
      dataFile.print("Suhu: ");
      dataFile.print(suhu15);
      dataFile.print(" *C, Kelembaban: ");
      dataFile.print(kelembaban15);
      dataFile.println(" %");
      
      dataFile.println("Sensor 16:");
      dataFile.print("Suhu: ");
      dataFile.print(suhu16);
      dataFile.print(" *C, Kelembaban: ");
      dataFile.print(kelembaban16);
      dataFile.println(" %");
      
      dataFile.println("Sensor 17:");
      dataFile.print("Suhu: ");
      dataFile.print(suhu17);
      dataFile.print(" *C, Kelembaban: ");
      dataFile.print(kelembaban17);
      dataFile.println(" %");
      
      dataFile.println("Sensor 18:");
      dataFile.print("Suhu: ");
      dataFile.print(suhu18);
      dataFile.print(" *C, Kelembaban: ");
      dataFile.print(kelembaban18);
      dataFile.println(" %");
      
      dataFile.println("Sensor 19:");
      dataFile.print("Suhu: ");
      dataFile.print(suhu19);
      dataFile.print(" *C, Kelembaban: ");
      dataFile.print(kelembaban19);
      dataFile.println(" %");
      

      dataFile.close();
      Serial.println("Data berhasil disimpan di SD card.");
    } else {
      Serial.println("Gagal menyimpan data di SD card!");
    }
  }

  // Tunggu sebentar sebelum membaca data berikutnya
  delay(1000); // Tunggu 5 detik
}
