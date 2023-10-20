#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

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


byte mouthClosed[] = {
  B00100,
  B01110,
  B10101,
  B01110,
  B01110,
  B01110,
  B00000,
  B00000
};
byte mouthOpen[] = {
  B00100,
  B01110,
  B10101,
  B01110,
  B00000,
  B01110,
  B01110,
  B00000
};

int startColumn = 7;
void setup() {

  pinMode(firstButtonPin, INPUT);
  pinMode(secondButtonPin, INPUT);
  lcd.begin(16, 2);
  lcd.createChar(1, mouthClosed);
  lcd.createChar(2, mouthOpen);

  lcd.setCursor(startColumn, 1);
  lcd.write(1);
  delay(1000);
  lcd.setCursor(startColumn, 1);
  lcd.write(2);
  delay(1000);

  Serial.begin(9600);
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
    startColumn = startColumn - 1;

    if (startColumn < 0) {
      startColumn = 0;
    }
  }

  if (secondButtonReading) {
    delay(300); // setting delay for stability.
    startColumn = startColumn + 1;
    if (startColumn > 16) {
      startColumn = 16;
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastFirstButtonState = firstButtonReading;
  lastSecondButtonState = secondButtonReading;
  
  lcd.clear();  //lcd.begin() in loop displays gibberish after sometimes Learnt it the hard way.
  /* Link:- https://forum.arduino.cc/t/how-to-fix-all-lcd-problems-read-this/100051 */
  lcd.setCursor(startColumn, 1);
  lcd.write(1);
  delay(500);
  lcd.setCursor(startColumn, 1);
  lcd.write(2);
  delay(500);
}
