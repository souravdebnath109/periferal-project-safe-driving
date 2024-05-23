#include <SoftwareSerial.h>
#include "NewPing.h"

const String PHONE = "+8801869525928";
#define rxPin 2
#define txPin 3
#define buzzer 7
#define led 12
SoftwareSerial sim800(rxPin, txPin);

#define MAX_DISTANCE 400
#define trigPin 8
#define echoPin 9

NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  
  Serial.begin(115200);

  sim800.begin(9600);
  Serial.println("SIM800L software serial initialize");

  sim800.println("AT");
  delay(1000);
}

void loop() {
  while (sim800.available()) {
    Serial.println(sim800.readString());
  }

  while (Serial.available()) {
    sim800.println(Serial.readString());
  }

  int distance_in_cm = sonar.ping_cm();
  Serial.print(distance_in_cm);
  Serial.println(" cm");

  if (distance_in_cm <= 5) {
    Serial.println("Motion detected!");
    digitalWrite(buzzer, HIGH);
    digitalWrite(led, HIGH);
    delay(2000);
    digitalWrite(buzzer, LOW);
    digitalWrite(led, LOW);

    Serial.println("calling....");
    sim800.println("ATD" + PHONE + ";");
    delay(20000);
  }

delay(500);
}
