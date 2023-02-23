#include <Arduino.h>

const int ldr[8] = {A0, A1, A2, A3, A4, A5, A6, A7};  
const int vccPin[8] = {2, 3, 4, 5, 6, 8, 9, 10};  

int ldrValue;

void initBoard() {
  pinMode(vccPin[0], OUTPUT);   
  pinMode(vccPin[1], OUTPUT);   
  pinMode(vccPin[2], OUTPUT);   
  pinMode(vccPin[3], OUTPUT);   
  pinMode(vccPin[4], OUTPUT);   
  pinMode(vccPin[5], OUTPUT);  
  pinMode(vccPin[6], OUTPUT);   
  pinMode(vccPin[7], OUTPUT);     
}

void scanBoard() {
  for (int i = 0; i < 8; i++) { 
    digitalWrite( vccPin[i], HIGH);  
    
    for (int j = 0; j < 8; j++) {  
      ldrValue = analogRead(ldr[j]); 
      ldrValue = constrain(ldrValue, 0, 800);
      ldrValue = map(ldrValue, 0, 800, 0, 255);    
      Serial.print(ldrValue);
      Serial.print("  ");
      delay(50);
    } 

    digitalWrite(vccPin[i], LOW);  
    Serial.println(); 
  }
}

