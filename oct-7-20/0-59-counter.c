int DS1_pin = 4;
int STCP1_pin =3;
int SHCP1_pin = 2 ;
int tens_anode = 12;
int ones_anode = 13;

int difference = 1000;

int   digits [10][8]{
  {0,1,1,1,1,1,1,0}, // digit 0
  {0,0,1,1,0,0,0,0}, // digit   1
  {0,1,1,0,1,1,0,1}, // digit 2
  {0,1,1,1,1,0,0,1}, // digit 3
  {0,0,1,1,0,0,1,1},   // digit 4
  {0,1,0,1,1,0,1,1}, // digit 5
  {0,1,0,1,1,1,1,1}, // digit 6
   {0,1,1,1,0,0,0,0}, // digit 7
  {0,1,1,1,1,1,1,1}, // digit 8
  {0,1,1,1,1,0,1,1}   // digit 9
};


void display_digit(int d){
  if (digits[d][0]==1)   digitalWrite(7, LOW); else digitalWrite(7, HIGH); //A
  if (digits[d][1]==1)   digitalWrite(8, LOW); else digitalWrite(8, HIGH); //B
  if (digits[d][2]==1)   digitalWrite(9, LOW); else digitalWrite(9, HIGH); //C
  if (digits[d][3]==1)   digitalWrite(2, LOW); else digitalWrite(2, HIGH); //D
  if (digits[d][4]==1)   digitalWrite(3, LOW); else digitalWrite(3, HIGH); //E
  if (digits[d][5]==1)   digitalWrite(5, LOW); else digitalWrite(5, HIGH); //F
  if (digits[d][6]==1)   digitalWrite(4, LOW); else digitalWrite(4, HIGH); //G
}

void DisplayDigit(int   Digit)
{
    digitalWrite(STCP1_pin,LOW);
    for (int i = 7; i>=0; i--)
    {
    digitalWrite(SHCP1_pin,LOW);
    if (digits[Digit][i]==1) digitalWrite(DS1_pin,   LOW); 
    if (digits[Digit][i]==0) digitalWrite(DS1_pin, HIGH);
    digitalWrite(SHCP1_pin,HIGH);
    }
   digitalWrite(STCP1_pin, HIGH); 
}


void setup() {  
  pinMode(DS1_pin, OUTPUT);
  pinMode(STCP1_pin, OUTPUT);
  pinMode(SHCP1_pin,   OUTPUT);
  Serial.begin(9600);
  pinMode(tens_anode, 12);
  pinMode(ones_anode, 13);
  digitalWrite(tens_anode, HIGH);
  digitalWrite(ones_anode, HIGH);
}

void loop() {
  for (int digit1=0; digit1 < 6; digit1++) {
    for (int digit2=0; digit2 < 10; digit2++) {
      unsigned long startTime = millis();
      for (unsigned long elapsed=0; elapsed <= 1000; elapsed = millis() - startTime) {
        digitalWrite(tens_anode, HIGH);
        digitalWrite(ones_anode, LOW);
        DisplayDigit(digit1);
        delay(5);
        digitalWrite(tens_anode, LOW);
        digitalWrite(ones_anode, HIGH);
        DisplayDigit(digit2);
        delay(5);
      }
    }
  }
} 