#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define LM35 A0
const char* ssid = "sanju";
const char* password =  "55555555";
const char* serverName = "http://10.5.49.41:8000/api/data";  // replace with your server address

WiFiClient client;

void setup() 
{
   Serial.begin(9600);
   WiFi.begin(ssid, password);
 
   while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi...");
   }

   Serial.println("Connected to WiFi");
}

void loop() 
{
   if(WiFi.status()== WL_CONNECTED)
   {  Serial.print("WiFi status: ");
Serial.println(WiFi.status());
      float lmvalue=analogRead(LM35);
      float tempr=(lmvalue*500)/1023;
   
      HTTPClient http;

      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
   
      String httpRequestData = "temperature=" + String(tempr);
      int httpResponseCode = http.POST(httpRequestData);
   
      if (httpResponseCode>0) {
         Serial.print("HTTP Response code: ");
         Serial.println(httpResponseCode);
         String response = http.getString();
         Serial.println(response);
      }
      else {
         Serial.print("Error code: ");
         Serial.println(httpResponseCode);
      }
      http.end();
   }
   else {
      Serial.println("WiFi Disconnected");
   }
 delay(1000);
}
