#include <Wire.h>

#define LEDPIN 13
#define SENSORPIN 4

int sensorState = 0;
int lastState = 0;
int connection = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(0x08);
  pinMode(LEDPIN, OUTPUT);
  pinMode(SENSORPIN, INPUT_PULLUP);
  Wire.onRequest(sendEvent);
  Wire.onReceive(receiveEvent);

}

void receiveEvent(int starter) {
  Serial.print(starter);
  connection = starter;
}

void sendEvent() {
  Wire.write(sensorState);
}

void loop() {
  
  sensorState = digitalRead(SENSORPIN);
  Serial.println(sensorState);
  
  if (sensorState == LOW) {
    digitalWrite(LEDPIN, HIGH);
  }
  else {
    digitalWrite(LEDPIN, LOW);
  }
  
  if (sensorState && !lastState) {
    Serial.println("The beam is unbroken boss");
  }
  if (!sensorState && lastState) {
    Serial.println("Beam is broken boss");

    delay(5000);
  }
  lastState = sensorState;
  
  delay(500);
  
}