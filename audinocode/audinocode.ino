#include <SoftwareSerial.h>

SoftwareSerial espSerial(0, 1); // RX, TX
const int lm35Pin = A0;

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
}

void loop() {
  // Read sensor data
  float sensorData = readSensor();

  // Convert sensor data to string
  String dataString = String(sensorData);

  // Send sensor data to ESP8266WiFi module
  espSerial.println(dataString);

  delay(1000);
}

float readSensor() {
  int lm35Value = analogRead(lm35Pin);
  float voltage = lm35Value * (5.0 / 1023.0); // Convert ADC value to voltage (assuming 5V reference)
  float temperature = voltage * 100.0; // Convert voltage to temperature in Celsius
  return temperature;
}
