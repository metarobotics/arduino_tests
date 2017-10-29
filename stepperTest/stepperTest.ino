int smDirectionPinLeft = 9;
int smStepPinLeft = 10;
int smDirectionPinRight = 11;
int smStepPinRight = 12;
int nMotionDelay = 1500;

void setup() {
  // put your setup code here, to run once:
  pinMode(smDirectionPinLeft, OUTPUT);
  pinMode(smStepPinLeft, OUTPUT);
  pinMode(smDirectionPinRight, OUTPUT);
  pinMode(smStepPinRight, OUTPUT);

  digitalWrite(smDirectionPinLeft, LOW);
  digitalWrite(smDirectionPinRight, HIGH);
}

void loop(){

//best result 260

int nAccerationStep = 2;
int nMaxDelay = 1010;
int nCurDelay = 1010;
int nMinDelay = 260;

for(int i = 0; i < 16000; i++)
{
  if(nCurDelay > nMinDelay)
    nCurDelay = nCurDelay - nAccerationStep;
  
  digitalWrite(smStepPinLeft,HIGH);
  digitalWrite(smStepPinRight,HIGH);
  delayMicroseconds(nCurDelay);
  digitalWrite(smStepPinLeft, LOW);
  digitalWrite(smStepPinRight, LOW);
  delayMicroseconds(nCurDelay);
}

delay(1500);
  /*
  rotate(32000, 0.8);
  delay(nMotionDelay);
  rotate(32000, 0.8);
  delay(nMotionDelay);
  rotate(-32000, 0.8);
  delay(nMotionDelay);
  rotate(-32000, 0.8);
  delay(nMotionDelay);
  */
}

void rotate(int steps, float speed){
  int direction;

  if(steps > 0){
    direction = HIGH;
  }else{
    direction = LOW;
  }

  speed = 1/speed * 10;
  steps = abs(steps);

  digitalWrite(smDirectionPinLeft, direction);

  for(int i = 0; i < steps; i++){
    digitalWrite(smStepPinLeft, HIGH);
    delayMicroseconds(speed);
    digitalWrite(smStepPinLeft, LOW);
    delayMicroseconds(speed);
  }
}

