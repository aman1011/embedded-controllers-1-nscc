#include "SevSeg.h"
SevSeg sevseg; 

int counter = 0;
int pushButton = 12;

void setup(){
    Serial.begin(9600);
    byte numDigits = 1;
    byte digitPins[] = {};
    byte segmentPins[] = {6, 5, 2, 3, 4, 7, 8, 9};
    bool resistorsOnSegments = true;

    byte hardwareConfig = COMMON_CATHODE; 
    sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
    sevseg.setBrightness(90);

    // button specs
    pinMode(pushButton, INPUT);
}

void loop(){
        
        // read input value and store it in val
        int val = digitalRead(pushButton);
        if (val) {
        
          // wait 10 milliseconds
          delay(10);

          // read the input again to check for bounces
          int val2 = digitalRead(pushButton);
        
          if (val == val2) { // the button really was pressed
            counter++;
            Serial.print("You've pressed the button ");
            Serial.print(counter);
            Serial.print(" times\n");
            delay(400); // if you dont do this, the if keep conditions is true. and numbers flash by.
          }
        }  
        sevseg.setNumber(counter);
        sevseg.refreshDisplay();    
}