int dirPin = 9;
int stepPin = 10;
//int enablePin = 11;
//int resetPin = 12;

int Distance = 0;  // Record the number of steps we've taken

void setup() {                
  pinMode(dirPin, OUTPUT);     
  pinMode(stepPin, OUTPUT);
  digitalWrite(dirPin, LOW);
  digitalWrite(stepPin, LOW);
  
//  pinMode(enablePin, OUTPUT);
//  pinMode(resetPin, OUTPUT);
  
//  digitalWrite(enablePin, LOW);
//  delayMicroseconds(1000);
//  digitalWrite(enablePin, HIGH);
}

void loop() {
//  digitalWrite(resetPin, HIGH);
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(1000);          
  digitalWrite(stepPin, LOW); 
  delayMicroseconds(1000);
  Distance = Distance + 1;   // record this step
  
  // Check to see if we are at the end of our move
  if (Distance == 360)
  {
    // We are! Reverse direction (invert DIR signal)
    if (digitalRead(dirPin) == LOW)
    {
      digitalWrite(dirPin, HIGH);
    }
    else
    {
      digitalWrite(dirPin, LOW);
    }
    // Reset our distance back to zero since we're
    // starting a new move
    Distance = 0;
    // Now pause for half a second
    delay(2000);
  }
}
