#include <DHT.h>

#define DHTPIN 2 // Pin untuk koneksi data sensor DHT11
#define DHTTYPE DHT11 // Tipe sensor DHT11

DHT dht(DHTPIN, DHTTYPE);

// Selisih suhu yang akan digunakan untuk kalibrasi
float selisihSuhu = -2.0; // Ganti dengan selisih yang sesuai

void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(9600);

  // Inisialisasi sensor DHT11
  dht.begin();
}

void loop() {
  // Baca suhu dari sensor DHT11
  float suhu = dht.readTemperature();

  // Cek apakah berhasil membaca suhu
  if (!isnan(suhu)) {
    // Melakukan kalibrasi suhu
    suhu = suhu + selisihSuhu; // Mengkompensasi hasil pembacaan

    // Tampilkan suhu yang sudah dikalibrasi di Serial Monitor
    Serial.print("Suhu (setelah kalibrasi): ");
    Serial.print(suhu);
    Serial.println(" *C");
  } else {
    Serial.println("Gagal membaca suhu dari sensor DHT11!");
  }

  delay(5000); // Tunggu 5 detik sebelum membaca data berikutnya
}
