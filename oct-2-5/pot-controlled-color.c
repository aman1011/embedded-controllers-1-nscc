int redLed = 9;         
int greenLed = 10;
int blueLed = 11;
int button = 12;
int brightness = 0;  // how bright the LED is
int leds []= {redLed, greenLed, blueLed};
int counter = 0;
int dynamicLed;
int flag = 0;   // to determine the user has started tinkering with the led.
int index;

int rgbStates [] = {255, 255, 255};

// the setup routine runs once when you press reset:
void setup() {

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);

  // Initial setup as every LED with 255 i.e. white light.
  analogWrite(greenLed, rgbStates[0]);
  analogWrite(blueLed, rgbStates[1]);
  analogWrite(redLed, rgbStates[2]);
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 9:
  
  
  int buttonValue = digitalRead(button);
  int sensorValue = analogRead(A0);

  // Debouce logic.
  if (buttonValue) {
    delay(10);
    int newButtonValue = digitalRead(button);
    
    if (newButtonValue == buttonValue) {
      flag = 1; // someone has activated the button.
      
      // Resetting the counter
      if (counter == 3) {
        counter = 0;
      }
      dynamicLed = leds[counter];
      counter++;
    } 
  }

  // if the led is being used
  // then check whats the dynamic led at the moment
  // and store its current state. This is mainly
  // for debugging purpose.
  // Can add display to show the current level of intensity
  // for each LED ..
  if (flag) {
    if (dynamicLed == 9) {
      index = 0;
    } else if (dynamicLed == 10) {
      index = 1;
    } else if (dynamicLed == 11) {
      index = 2;
    } else {
      ;
    }
    
    int brightness = map(sensorValue, 0, 1023, 0, 255);
    rgbStates[index] = brightness; // storing brightness states
    analogWrite(dynamicLed, sensorValue);  //Actively change the color.
  }
  
  /* debugging statements.
    Serial.println("Starting to display rgb states ....");
    Serial.println(rgbStates[0]);
    Serial.println(rgbStates[1]);
    Serial.println(rgbStates[2]);
    delay(100);
  */
}