// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  int counter;
  //Serial.begin(9600);
}

void activate(int pin) {
  digitalWrite(pin, HIGH);
  delay(1000);
  digitalWrite(pin, LOW);
  //delay(50);
}

// the loop function runs over and over again forever
void loop() {
  int counter = 13;
  int adding;
  while (counter <=13 && counter >= 4) {
    activate(counter);
    if (counter == 13) {
      adding = -1;
    }
    if (counter == 4) {
      adding = 1;
    }
    counter = counter + adding;
  }
}