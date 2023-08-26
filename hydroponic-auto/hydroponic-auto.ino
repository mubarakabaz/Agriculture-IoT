#include "deklarasi.h"

#include <ThingerESP32.h>
#include "arduino_secret.h"
ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  // serial untuk debugging
  Serial.begin(115200);

  // inisialisasi sensor pH
  pinMode(PH_PIN, INPUT);

  // inisialisasi sensor TDS
  pinMode(TDS_PIN, INPUT);

  // Inisialisasi koneksi WiFi
  thing.add_wifi(SSID, SSID_PASSWORD);

  //mulai koneksi ke Thinger.io
  // thing.start();
}

void loop() {
  // put your main code here, to run repeatedly:
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
  int i, j, bTemp; //deklarasi variabel yang akan digunakan dalam proses filtrasi median.

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
  return bTemp; // mengembalikan nilai median yang telah dihitung.
}
