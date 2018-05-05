//   _   _            _                    _             
//  | | | |          | |                  (_)            
//  | |_| | ___  _ __| | ___   __ _  ___   _ _ __   ___  
//  |  _  |/ _ \| '__| |/ _ \ / _` |/ _ \ | | '_ \ / _ \ 
//  | | | | (_) | |  | | (_) | (_| |  __/_| | | | | (_) |
//  \_| |_/\___/|_|  |_|\___/ \__, |\___(_)_|_| |_|\___/ 
//                             __/ |                     
//                            |___/                      
//Developped by Florian LOBERT 2015
//Based on 75HC595 registers and RTC 3231
//Work In Progress....


#include <Arduino.h>
#include <Wire.h>
#include "pins.h"
#include "rtc3231.h"
#include "clockManager.h"

int ligne = 0;
unsigned long lastTimeUpdate;

void setup() {
// Serial.begin(9600);
  //Serial.println("T1130157190317");
  
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  Wire.begin();
  lastTimeUpdate = millis();
  get3231Date();
  matrixUpdate();
}

void loop() {
  //Serial.println(minutes);
  long now = millis();
  if(lastTimeUpdate + 10000 < now) {
    get3231Date();
    matrixUpdate();
    delayMicroseconds(200);
    lastTimeUpdate = now;
    
  }
  selectionLigne(ligne);
  gestionLigne(ligne);
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, octet3);
  shiftOut(dataPin, clockPin, LSBFIRST, octet2);   
  shiftOut(dataPin, clockPin, LSBFIRST, octet1);
  digitalWrite(latchPin, HIGH);
  ligne++;
  if(ligne>9) ligne=0;
  delayMicroseconds(400);
  //delay(500);
}


