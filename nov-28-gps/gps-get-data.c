#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include 

#define _SS_MAX_RX_BUFF 256 // Adjust the buffer size as needed

const int chipSelect = 4;
SoftwareSerial SoftSerial(3, 2); // SoftwareSerial for GPS module (adjust pins as needed)

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for the serial port to connect. Needed for native USB port only
  }

  SoftSerial.begin(9600); // SoftSerial baud rate for the GPS module (adjust as needed)

  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect))
  {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("Card initialized.");
}

void loop()
{
  if (SoftSerial.available())
  {
    String gpsData = SoftSerial.readStringUntil('\n');

    if (gpsData.startsWith("$GPGGA"))
    {
      // Display GPS data on the Serial Monitor
      Serial.println(gpsData);

      // Write GPS data to the SD card
      File dataFile = SD.open("gpsdata.txt", FILE_WRITE);

      if (dataFile)
      {
        dataFile.println(gpsData);
        dataFile.close();
      }
      else
      {
        Serial.println("Error while opening gpsdata.txt");
      }
    }
  }
}
