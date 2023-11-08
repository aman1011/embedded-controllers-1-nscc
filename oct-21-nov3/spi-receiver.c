#include <SPI.h>

const int slaveSelectPin = 10; 

void setup() {
  SPI.begin();
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0)); 

  pinMode(slaveSelectPin, INPUT); 
  digitalWrite(slaveSelectPin, HIGH); 
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(slaveSelectPin) == LOW) {
    char receivedData = SPI.transfer(0); // Receive data from the master

    Serial.print(receivedData);
  }
}
