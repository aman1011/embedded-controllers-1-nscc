#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust the I2C address if needed

const int buzzerPin = 8; // Connect the buzzer to digital pin 8

void setup() {
  rtc.begin();
  lcd.init();
  lcd.backlight();

  lcd.print("Current Time:");
  pinMode(buzzerPin, OUTPUT); // Set the buzzer pin as an output
}

void loop() {
  DateTime now = rtc.now();

  lcd.setCursor(0, 1);
  lcd.print(now.timestamp(DateTime::TIMESTAMP_TIME));

  // Check the current time and activate the buzzer at a specific time
  int currentHour = now.hour();
  int currentMinute = now.minute();

  // Alarm for 16:06.
  if (currentHour == 16 && currentMinute == 6) {
    soundBuzzer(3000); 
  }

  delay(1000); // Update the time display every second
}

void soundBuzzer(int frequency) {
  tone(buzzerPin, frequency); // Activate the buzzer with the specified frequency
  delay(2000); // Buzzer sounds for 2 seconds (adjust as needed)
  noTone(buzzerPin); // Turn off the buzzer
}
