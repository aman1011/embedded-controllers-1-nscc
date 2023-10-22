// include the library code:
#include <LiquidCrystal.h>
#include <Keypad.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
float totalCount = 0.00;

const int red_led = 12, green_led = 11;
const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //three columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

const char* password = "A011"; 
String stars;

char input[20]; // dont know how long 
bool led_blinked = false;
int current_index = 0;

void setup() {
  Serial.begin(9600);
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Enter Password");
}


void blink_led(int led) {
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(500);
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(500);
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(500);
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
}


void loop() {
  char key = keypad.getKey();

  if (key == '#') {
    //input = "A011";
    if (!led_blinked) {
      if (strcmp(input, password) == 0) {
        led_blinked = true;
        lcd.clear();
        lcd.print("Access Granted");
        blink_led(green_led);
        delay(2500);
        lcd.clear();
      }
      else {
        led_blinked = true;
        lcd.clear();
        lcd.print("Access Denied");
        blink_led(red_led);
        delay(2500);
        lcd.clear();
      }
    }
  }
  else if (key){
    input[current_index] = key;
    current_index++;
    lcd.setCursor(0,1);
    stars = stars + '*';
    lcd.print(stars);
  }
  else {
    ;
  }
}

