#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

RTC_DS3231 rtc;

LiquidCrystal_I2C lcd(0x3F, 20, 4); // Alamat I2C LCD dan ukuran (20x4)

void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(9600);
  Wire.begin();

  // Inisialisasi RTC
  if (!rtc.begin()) {
    Serial.println("Gagal inisialisasi RTC!");
    while (1);
  }

  // Inisialisasi LCD I2C
  lcd.init();
  lcd.backlight();
}

void loop() {
  // Baca waktu dari RTC
  DateTime now = rtc.now();

  // Format waktu
  String waktuSekarang = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());

  // Tampilkan waktu di Serial Monitor
  Serial.print("Waktu sekarang: ");
  Serial.println(waktuSekarang);

  // Tampilkan waktu di LCD I2C
  lcd.setCursor(0, 0);
  lcd.print("Waktu: ");
  lcd.print(waktuSekarang);

  // Tunggu sebentar sebelum membaca waktu berikutnya
  delay(1000); // Tunggu 1 detik
}
