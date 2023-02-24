#include <Arduino.h>
#include "board.h"

/**
 *  
 */
void setup() {  
  Serial.begin(9600);  

  initBoard();
}

/**
 * 
 */
void loop() {
  scanBoard();

  liftDropAnalisys();

  //plotSquare();
  
  //delay(1000);
  //Serial.println("Nuova lettura");   
} 

