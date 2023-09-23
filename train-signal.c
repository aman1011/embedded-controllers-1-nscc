// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT); // setting the LED controlled by 13
  pinMode(12, OUTPUT); // setting the LED controlled by pin 12.
}

// the loop function runs over and over again forever
void loop() {

  // Setting the 13th Pin RED LED as High
  // and 12th Pin GREEN LED as low
  digitalWrite(LED_BUILTIN, HIGH); 
  digitalWrite(12, LOW);             
  
  delay(500);   // Wait for half a second.
  
  // Setting the 13th Pin RED LED as Low
  // and 12th Pin GREEN LED as High
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(12, HIGH);   
  
  delay(500);         // Wait for half a second.           
}
