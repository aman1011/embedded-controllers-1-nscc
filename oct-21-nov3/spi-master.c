#include <SPI.h>

const int slaveSelectPin = 10; 

void setup() {
  SPI.begin();
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0)); 

  pinMode(slaveSelectPin, OUTPUT);
  digitalWrite(slaveSelectPin, HIGH); // Deselect the slave initially
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char sendData = Serial.read();

    digitalWrite(slaveSelectPin, LOW); // Select the slave
    byte receivedData = SPI.transfer(sendData); // Send and receive data
    digitalWrite(slaveSelectPin, HIGH); // Deselect the slave
  }
}
