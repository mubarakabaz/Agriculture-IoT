//Inisialisasi variabel pin sensor PH meter
const int PH_PIN = A0;
float phValue;
unsigned long waktuMulai = 0; // Inisialisasi waktuMulai

void setup() {
  // inisialisasi pin sensor PH meter
  pinMode(PH_PIN, INPUT);
  Serial.begin(115200); // Mulai komunikasi serial dengan baud rate 115200
}

void loop() {
  // Print Debugging untuk mengecek nilai input
  // setiap 5 detik
  if (millis() - waktuMulai > 5000U){ // U = Unsigned Integer
    waktuMulai = millis();

    // Pembacaan sensor pH
    int ph = analogRead(PH_PIN);
    float voltage = 5.0 / 1024.0 * ph; // Perbaiki 5 menjadi 5.0 agar pembagian berjalan dengan benar
    // kalibrasi sensor ph (menggunakan regresi linear)
    // -5.4 -> nilai minimum pembacaan sensor
    phValue = (-5.4 * voltage) + 18.14;

    Serial.print("pH : ");
    Serial.println(phValue); // Menggunakan println agar setiap nilai pH dicetak pada baris baru
  }
}
