
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int cursor = 0;
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");
  Serial.begin(9600);
  lcd.setCursor(cursor, 0);
}

void loop() { 
  if (Serial.available() > 0) {
    char data = Serial.read();
    lcd.print(data);
    cursor++;
    lcd.setCursor(cursor, 0);

    // Reset the cursor and clear the display after the cursor limit is reached.
    if (cursor > 16) {
      cursor = 0;
      lcd.clear();
    }
  }
}

