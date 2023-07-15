#include <ESP8266WiFi.h>

const char* ssid = "OPPO";
const char* password = "1234567890";

const int lm35Pin = A0;

WiFiServer server(80);

String readLM35Temperature() {
  int rawValue = analogRead(lm35Pin);
  float voltage = (rawValue / 1023.0) * 5.0;
  float temperature = voltage * 100.0;

  Serial.println(temperature);
  return String(temperature);
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());

  server.begin();

  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected");

    String temperature = readLM35Temperature();

    client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close");
client.println();

// Read the contents of the HTML file and send it to the client
File htmlFile = SPIFFS.open("/index.html", "r");
if (htmlFile) {
  while (htmlFile.available()) {
    client.write(htmlFile.read());
  }
  htmlFile.close();
}
    client.print("Temperature: ");
    client.println(temperature);
    client.println();

    delay(10);
    client.stop();
    Serial.println("Client disconnected");
  }
}
