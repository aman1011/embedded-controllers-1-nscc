// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 2;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  long button_used;
  
  // print out the state of the button:
  if (buttonState) {
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    button_used = millis();     // get the timestamp in epoch when the button was used/activated.
  }
  else {
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
  }

  /* The idea for auto switching off is to 
   calculate the time difference between now
   and when the button was active last. In this case,
   , 20000 denotes 20 seconds after which the the leds will
   be auto shut down */
  if (millis() - button_used > 20000) {
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
  delay(10);    // for stability
} 