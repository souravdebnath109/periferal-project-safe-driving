#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD setup

#define sensorDigital 2 //digital pin connected to alcohol
#define sensorAnalog A1  //analog pin connected to alcohol
#define sensorPin 5 // Pin connected to the IR sensor
#define motorPin 8  // Pin connected to the motor
#define buzzerPin 13 // Pin connected to the buzzer
#define flameSensorPin 7 //Pin connected to the flame sensor
#define led 9  //pin connected to led

void setup() {  
  pinMode(led,OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(flameSensorPin, INPUT);
  pinMode(sensorDigital, INPUT);


  lcd.init();
  lcd.backlight();
}

void loop() {
  sleep();
}

void sleep() {
  if(digitalRead(sensorPin) == HIGH) {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(motorPin, LOW);
    digitalWrite(led,LOW);
    alcohol();
    flame();
  } else {
    delay(3000); // Wait for 3 seconds before activating again
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(motorPin, HIGH);
    digitalWrite(led,HIGH);
    delay(1000);
    digitalWrite(led,LOW);
    lcd.clear();
    lcd.print("Please Wake Up ");
    delay(3000);
    lcd.clear();
    
  }
}

void alcohol() {
  bool digital = digitalRead(sensorDigital);
  int analog = analogRead(A1); // Assuming alcohol sensor is connected to A1
   if (digital == HIGH) {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(led,LOW);
  } else {
    digitalWrite(buzzerPin, HIGH);
    // digitalWrite(led,HIGH);
    // delay(2000);
    // digitalWrite(led,LOW);
    lcd.clear();
    lcd.print("Alcohol Detected ");
    delay(3000);
    lcd.clear();
    //delay(320);
  }
}

void flame() {
  int flamePin = digitalRead(flameSensorPin);
  if (flamePin == HIGH) {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(motorPin, LOW);
  } else {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(motorPin, HIGH);
    digitalWrite(led,HIGH);
    delay(2000);
    digitalWrite(led,LOW);
    lcd.clear();
     lcd.print("Flame detected ");
     delay(3000);
     lcd.clear();
  }
delay(500);
}
