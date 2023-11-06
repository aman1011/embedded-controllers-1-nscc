
//the pins of 4-digit 7-segment display attached to arduino board digital pins 2 - 13 respectively
const int a = 2;
const int b = 3;
const int c = 4;
const int d = 5;
const int e = 6;
const int f = 7;
const int g = 8;
const int DP = 9;// dot is not used in this project
const int D1 = 10;
const int D2 = 11;
const int D3 = 12;
const int D4 = 13;

int dig1 = 0;
int dig2 = 0;
int dig3 = 2;
int dig4 = 0;

int segments[] = {a,b,c,d,e,f,g,DP};

int num_array[10][7] = { 
  { 1,1,1,1,1,1,0 },    // 0
  { 0,1,1,0,0,0,0 },    // 1
  { 1,1,0,1,1,0,1 },    // 2
  { 1,1,1,1,0,0,1 },    // 3
  { 0,1,1,0,0,1,1 },    // 4
  { 1,0,1,1,0,1,1 },    // 5
  { 1,0,1,1,1,1,1 },    // 6
  { 1,1,1,0,0,0,0 },    // 7
  { 1,1,1,1,1,1,1 },    // 8
  { 1,1,1,0,0,1,1 }     // 9
};



//*************************************************************
void setup()
{
//set all the pins of the LED display as output
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(DP, OUTPUT);
}

void loop()
{
  digitalWrite(D4, HIGH);   // setting the Digit 4 as HIGH to activate it.

  // Display each segment.
  displaySpecificSegment(a);
  displaySpecificSegment(b);
  displaySpecificSegment(c);
  displaySpecificSegment(d);
  displaySpecificSegment(e);
  displaySpecificSegment(f);
  displaySpecificSegment(g);

  // Time to display numbers
  displayNumber(0);
  displayNumber(1);
  displayNumber(2);
  displayNumber(3);
  displayNumber(4);
  displayNumber(5);
  displayNumber(6);
  displayNumber(7);
  displayNumber(8);
  displayNumber(9);

}
    

// Function to display  specific segemnt
// Keep the one that needs to lighten as LOW
// and rest as HIGH.
void displaySpecificSegment(int segment) {
  for (int i = 0; i< 8; i++) {
    if (segments[i] == segment) {
      digitalWrite(segments[i], LOW);
    }
    else {
      digitalWrite(segments[i], HIGH);
    }
  }
  delay(1000); // delay of 1 second.
}


// Function to display number using
// the predefined array. Iterate through each number
// and set each segment as HIGH and LOW.
void displayNumber(int number) {
  for( int i = 0; i < 7; i++) {
    if (num_array[number][i]) {
      digitalWrite(segments[i], LOW);
    } else {
      digitalWrite(segments[i], HIGH);
    }
    digitalWrite(DP, HIGH); // we dont want decimal point.
  }
  delay(1000);    // delay of 1 second.
}