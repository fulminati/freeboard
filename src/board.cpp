#include <Arduino.h>

const int ldrDepth = 3;

int board[8][8][ldrDepth];
signed long squareAngle[8][8];
signed long squareQuote[8][8];

const int ldr[8] = {A0, A1, A2, A3, A4, A5, A6, A7};  
const int vccPin[8] = {2, 3, 4, 5, 6, 8, 9, 10};  

int ldrValue;
 
int ldrMaxLastValue = 250;
int ldrMaxNextValue = 800;

long scanTime = 0;

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
  long startScanTime = millis();
  ldrMaxNextValue = 0;  

  for (int i = 0; i < 8; i++) { 
    digitalWrite(vccPin[i], HIGH);  

    for (int j = 0; j < 8; j++) {  
      ldrValue = analogRead(ldr[j]); 
      if (ldrValue > ldrMaxNextValue) {
        ldrMaxNextValue = ldrValue;
      }
      /*if (i == 0 && j == 0) {
        Serial.print("Raw:");
        Serial.println(ldrValue);
      }*/
       
      ldrValue = constrain(ldrValue, 0, ldrMaxLastValue);
      ldrValue = map(ldrValue, 0, ldrMaxLastValue, 0, 255);          
      for (int d = ldrDepth - 1; d > 0; d--) {
         board[i][j][d] = board[i][j][d - 1];
      }
      board[i][j][0] = ldrValue;      
    } 

    digitalWrite(vccPin[i], LOW);      
    delay(10);
  }
  
  //ldrMaxLastValue = ldrMaxNextValue * 0.85;

  //Serial.print("MaxNext:");
  //Serial.println(ldrMaxNextValue);

  scanTime = millis() - startScanTime;
}

void echoBoard() {
  for (int i = 0; i < 8; i++) {     
    
    for (int j = 0; j < 8; j++) {        
      Serial.print(board[i][j][0]);
      Serial.print("  ");      
    }
    Serial.println(); 
  }
}

void liftDropAnalisys() {
  for (int i = 0; i < 8; i++) {         
    for (int j = 0; j < 8; j++) { 
      int xSum = 0;
      int ySum = 0;      
      int x2Sum = 0;
      int xySum = 0;      
      for (int d = 0; d < ldrDepth; d++) {        
        xSum += d;        
        ySum += board[i][j][d];        
        x2Sum += d*d;
        xySum += d*board[i][j][d];        
      }
      squareAngle[i][j] = ((ldrDepth * xySum) - (xSum * ySum)) / ((ldrDepth * x2Sum) - (xSum * xSum));
      squareQuote[i][j] = (ySum - (squareAngle[i][j] * xSum)) / ldrDepth;
    }
  }
}

void plotSquare() {
  Serial.print("ScanTime:");
  Serial.print(scanTime);  
  Serial.print(",");
  Serial.print("Min:");
  Serial.print(0);
  Serial.print(",");
  Serial.print("Max:");
  Serial.print(ldrMaxLastValue);
  Serial.print(",");
  Serial.print("Clock:");
  Serial.print(((millis()/1000)%2)*80+10);
  Serial.print(",");
  String squareLabel = "Square:";
  for (int d = 0; d < ldrDepth; d++) {
    Serial.print(squareLabel);
    Serial.print(board[0][0][d]);
    squareLabel = ",";
  }

  Serial.print(" - ");
  Serial.print(squareQuote[0][0]);
  Serial.print("/");
  Serial.print(squareAngle[0][0]);
  
  Serial.println();
}
