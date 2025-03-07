#include <DHT.h>
#include <LiquidCrystal.h>

// Konfigurasi LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(19, 23, 18, 17, 16, 15);

// Konfigurasi DHT22
#define DHTPIN 21
#define DHTTYPE DHT22
#define TIMEDHT 1000

float humidity, celsius;
uint32_t timerDHT = TIMEDHT;
DHT dht(DHTPIN, DHTTYPE);

void getTemperature() {
  if ((millis() - timerDHT) > TIMEDHT) {
    timerDHT = millis();
    
    humidity = dht.readHumidity();
    celsius = dht.readTemperature();
    
    if (isnan(humidity) || isnan(celsius)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    
    // Menampilkan data di Serial Monitor
    Serial.print("Temp: ");
    Serial.println(celsius);
    Serial.print("Humidity: ");
    Serial.println(humidity);
    
    // Menampilkan data di LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(celsius);
    lcd.print("C");
    
    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(humidity);
    lcd.print("%");
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");

  // Inisialisasi sensor DHT
  dht.begin();
  
  // Inisialisasi LCD
  lcd.begin(16, 2);
  lcd.print("Starting...");
  lcd.print("Hello :)");
}

void loop() {
  delay(500);
  getTemperature();
}