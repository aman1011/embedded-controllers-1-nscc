int brightness = 0;
int fadeAmount = 4;  // since Analog write values from 0-255, keeping fade as 4 gives 4*60 , values upto 240.
int led = 6;
// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  //pinMode(led, OUTPUT);
  Serial.begin(9600);
  analogWrite(led, 255);
  delay(2000);
  analogWrite(led, 0);
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 9:
  int photoResistorValue = analogRead(A0);
  Serial.println("photoresistorvalue");
  Serial.println(photoResistorValue);
  delay(1000);
  brightness = 0;

  if (photoResistorValue < 45) {
      int count = 0;
      while (count < 61) {
        brightness = brightness + fadeAmount;
        analogWrite(led, brightness);
        Serial.println("brightness");
        Serial.println(brightness);
        delay(1000);
        count++;
      }
  }

  // Reset to turn off the light, once the sequence finishes.
  analogWrite(5,0);
  brightness = 0;
  delay(1000); //some stability
}
