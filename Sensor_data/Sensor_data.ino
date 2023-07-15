#define ECG A0
#define PULSE_SENSOR A1
#define LM35 A2
#define LO_POS 10
#define LO_NEG 11

int ecgThreshold = 500; // Adjust this threshold based on your ECG sensor's characteristics
int pulseSensorThreshold = 550; // Adjust this threshold based on your pulse sensor's characteristics

void setup() {
  Serial.begin(9600);
  pinMode(LO_POS, INPUT);  // Setup for leads off detection LO +
  pinMode(LO_NEG, INPUT);  // Setup for leads off detection LO -
}

void loop() {
  // Check leads off detection
  // if (digitalRead(LO_POS) == HIGH || digitalRead(LO_NEG) == HIGH) {
  //   Serial.println('!');
  // } else {
    // Read ECG sensor value
    int ecgValue = analogRead(ECG);
    Serial.print("ECG: ");
    Serial.println(ecgValue);

    // Read pulse sensor value
    int pulseValue = analogRead(PULSE_SENSOR);
    Serial.print("Pulse Sensor: ");
    Serial.println(pulseValue);

    // Read temperature from LM35
    float temperature = readLM35Temperature();
    Serial.print("Temperature: ");
    Serial.println(temperature);

    // Perform data processing or calculations with the sensor values
    // ...

  // }

  delay(1000);
}

float readLM35Temperature() {
  int lmValue = analogRead(LM35);
  float voltage = lmValue * (5.0 / 1023.0); // Convert ADC value to voltage
  float temperature = (voltage - 0.5) * 100.0; // Calculate temperature based on LM35 formula
  return temperature;
}
