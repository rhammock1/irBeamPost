#include <Wire.h>
#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <SPI.h>

const char* ssid     = "";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "";     // The password of the Wi-Fi network

#define PATH ""

int currentOut = 0;
int currentIn;
int previousIn = 0;

HTTPClient http;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(D2, D1);
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  Wire.beginTransmission(0x08);
  Wire.write(0x02);
  Wire.endTransmission();

}

void handleHttp(int value) {
  http.begin(PATH);
  http.addHeader("Content-Type", "text/plain");
  http.POST(String(value));
  delay(300);
  http.end();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Wire.requestFrom(0x08, 1);
  currentIn = Wire.read();
  Serial.print("currentIn: ");
  Serial.println(currentIn);

  if (currentIn == 0 && previousIn == 1) {
    if (currentOut == 1) {
      currentOut = 0;
    } else {
      currentOut = 1;
    }}
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Connected...");

    if (currentIn == 0) {
      if (currentOut == 0 && previousIn == 1) {
        handleHttp(0);
        delay(4700);
      } else if (currentOut == 1 && previousIn == 0) {
          handleHttp(1);
          delay(4700);
      }
    }
  }
  
  previousIn = currentIn;
  delay(1000);
}