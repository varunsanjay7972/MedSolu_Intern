const int pulsePin = A0;       

int pulseValue = 0;            
int pulseThreshold = 550;      

unsigned long previousMillis = 0;  
unsigned long interval = 1000;     

void setup() {
  Serial.begin(9600);          
}

void loop() {
  pulseValue = analogRead(pulsePin);  

  unsigned long currentMillis = millis();  
  unsigned long timeDiff = currentMillis - previousMillis;

  if (timeDiff >= interval) {
    float pulseRate = 60000.0 / timeDiff;  
    Serial.print("Pulse Rate: ");
    Serial.print(pulseRate);
    Serial.println(" BPM");

    previousMillis = currentMillis;  
  }

  delay(1000);   
}
