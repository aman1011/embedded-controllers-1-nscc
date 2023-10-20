// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
float totalCount = 0.00;

/* logic for 2 buttons */

// constants won't change. They're used here to set pin numbers:
const int firstButtonPin = 6;
const int secondButtonPin = 7;


int firstButtonState;
int secondButtonState;
int lastFirstButtonState = LOW;     
int lastSecondButtonState = LOW;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(firstButtonPin, INPUT);
  pinMode(secondButtonPin, INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Total Amount");
  lcd.setCursor(0, 1);
  lcd.print("$ ");
  
  lcd.print(totalCount);

}

void loop() {

  // read the state of the switch into a local variable:
  int firstButtonReading = digitalRead(firstButtonPin);
  int secondButtonReading = digitalRead(secondButtonPin);
 

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (firstButtonReading != lastFirstButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if (secondButtonReading != lastSecondButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (firstButtonReading != firstButtonState) {
      firstButtonState = firstButtonReading;
    }

    if (secondButtonReading != secondButtonState) {
      secondButtonState = secondButtonReading;
    }
  }

  if (firstButtonReading) {
    delay(300); //setting delay for stability.
    totalCount = totalCount + 0.25;
  }

  if (secondButtonReading) {
    delay(300); // setting delay for stability.
    totalCount = totalCount + 1.00;
  }


  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastFirstButtonState = firstButtonReading;
  lastSecondButtonState = secondButtonReading;
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  lcd.print("$ ");
  lcd.print(totalCount);


}