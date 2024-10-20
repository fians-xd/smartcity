#include <MQ135.h> // Memasukan library sensor MQ 135
#include <DHT.h> //  Library Sensor DHT 22
#include <LiquidCrystal_I2C.h> // Library LCD I2C
#include <Wire.h> 


#define PIN_MQ135 A0 // MQ135 Analog Input Pin
#define DHTPIN 6 // DHT Digital Input Pin
#define DHTTYPE DHT22 // DHT11 or DHT22, depends on your sensor

MQ135 mq135_sensor(PIN_MQ135);
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // inisialisasi DHT 22
  dht.begin();

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();

  // Tampilkan pesan awal di LCD
  lcd.setCursor(0,0);
  lcd.print("Pemantauan");
  lcd.setCursor(0,1);
  lcd.print("Kualitas Udara");
  delay (3000); // Tampilkan pesan selama 2 detik
}

void loop() {
  // Inisialisasi variabel sensor DHT 22
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Inisialisasi Variabel Sensor MQ-135
  float ppm = mq135_sensor.getPPM();
  float correctedPPM = mq135_sensor.getCorrectedPPM(temperature, humidity);
  
  // Cek pembacaan dari DHT 22
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  
  // Menampilkan Kadar Gas di Udara pada Serial Monitor
  Serial.print(" \t PPM : ");
  Serial.print(ppm);
  Serial.print(" PPM ");
  Serial.print("\t Corrected PPM : ");
  Serial.print(correctedPPM);
  Serial.println(" PPM ");


  // Tampilkan data kualitas udara di LCD
  lcd.clear(); // 
  lcd.setCursor(0, 0);
  lcd.print("Air Quality(v.1)");
  lcd.setCursor(0, 1);
  lcd.print(ppm);  
  lcd.print(" ppm");  

  delay (1000); // Tunda 2 detik sebelum menampilkan data berikutnya

  // Tampilkan data kualitas udara berdasarkan suhu dan kelembaban
  lcd.clear(); // 
  lcd.setCursor(0, 0);
  lcd.print("Air Quality(v.2)");
  lcd.setCursor(0, 1);
  lcd.print(correctedPPM);  
  lcd.print(" ppm");  
  
  delay(1000); // Tunda 2 detik sebelum menampilkan data berikutnya


  // Tampilkan data Suhu dan Kelembaban di LCD
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Temperature");
  lcd.setCursor(3, 1);
  lcd.print(temperature);
  lcd.print(" C");

  delay(1000); // Tunda 2 detik sebelum menampilkan data berikutnya

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Humidity");
  lcd.setCursor(3, 1);
  lcd.print(humidity);
  lcd.print(" %");
  
  delay(1000); // Tunda 2 detik sebelum menampilkan data berikutnya
  
 

}
