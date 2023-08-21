#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
int mq135_analog_pin = A0;
const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

ESP8266WebServer server(80);

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  server.on("/get_air_quality", HTTP_GET, [](){
    float sensorValue = analogRead(mq135_analog_pin);
    float airQualityIndex = map(sensorValue, 0, 1023, 0, 100);
    String response = String(airQualityIndex);
    server.send(200, "text/plain", response);
  });

  server.begin();

  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  server.handleClient();

  float sensorValue = analogRead(mq135_analog_pin);
  float airQualityIndex = map(sensorValue, 0, 1023, 0, 100);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Kualitas Udara:");
  lcd.setCursor(0, 1);
  lcd.print("AQI: ");
  lcd.print(airQualityIndex);

  Serial.print("Kualitas Udara: ");
  Serial.println(airQualityIndex);

  delay(5000); // Jeda selama 5 detik, sebelum melakukan pengukuran kembali
}
