#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address (usually 0x27 or 0x3F for a 16x2 LCD)
// You can find the address by running an I2C scanner sketch.
// Replace 0x3F with your LCD's I2C address if it's different.
LiquidCrystal_I2C lcd(0x27,20,4); 

#define _SS_MAX_RX_BUFF 256 // Adjust the buffer size as needed

const int chipSelect = 4;
SoftwareSerial SoftSerial(3, 2); // SoftwareSerial for GPS module (adjust pins as needed)

void setup()
{
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Hello, world!");
  while (!Serial)
  {
    ; // wait for the serial port to connect. Needed for native USB port only
  }
  // Initialize the LCD
  lcd.begin(16, 2);

  // Turn on the backlight (optional)
  lcd.setCursor(0,0);

  // Print a welcome message to the LCD
  lcd.print("Hello!");

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

      // Extract latitude and longitude from the GPS data
      String latitude = getValue(gpsData, ',', 2);  
      String longitude = getValue(gpsData, ',', 4); 

      // Display latitude and longitude on the LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Lat: " + latitude);
      lcd.setCursor(0, 1);
      lcd.print("Long: " + longitude);

      // Write GPS data to the SD card
      File dataFile = SD.open("gpsdata.txt", FILE_WRITE);

      if (dataFile)
      {
        dataFile.println(gpsData); // Add a newline character for better readability
        dataFile.close();
      }
      else
      {
        Serial.println("Error opening gpsdata.txt");
      }
    }
  }
}

// Function to extract values from a comma-separated string
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++)
  {
    if (data.charAt(i) == separator || i == maxIndex)
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
