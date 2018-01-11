/*
 ESP8266 + BMP085
*/
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include "DHT.h"

#define LED_PIN D5

#define DHT_PIN D6
#define DHT_TYPE DHT11

Adafruit_BMP085 bmp;
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  
  Serial.begin(115200);
  delay(200);

  dht.begin();
  
  Serial.print("Search for valid BMP085");
  
  while (!bmp.begin(BMP085_HIGHRES)) {
    Serial.print(".");
    delay(100);
  }

  Serial.println();
  Serial.println("BMP085 FOUND!");
}

void readDHT() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();  

  Serial.println("DHT11");

  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" *C");

  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");
}

void readBMP() {
  float temperature = bmp.readTemperature();
  float pressurePa = bmp.readPressure();
  int pressureMM = (int)(bmp.readPressure() * 0.0075006);

  Serial.println("BMP180");
  
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(pressurePa);
  Serial.println(" Pa");

  Serial.print("Pressure = ");
  Serial.print(pressureMM);
  Serial.println(" mm. rt. st.");
  
}

void flash() {
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
  delay(300);
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  flash();
  readDHT();
  readBMP();
    
  Serial.println();
  delay(5000);
}
