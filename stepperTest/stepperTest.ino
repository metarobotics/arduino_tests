/*
MACHINE TYPE : SNSD-TY
*/

#include "WGM63.h"

// MOTOR DRIVER PINS


int nMotorCount = 2;
WGM63 steppers[2] = {WGM63(9, 10, 0, 1), WGM63(11, 12, 0, -1)};

long nTotalStepCount = ROTATE_FULL * CLOCK_DIVIDE * GEAR_RATIO * 100L;
long nCurrentStepCount;

void move(int direction)
{
  for(int i = 0; i < nMotorCount; i++)
  {
    steppers[i].setDirection(MOVE_FORWARD);
  }
}

void turnLeft()
{
  steppers[0].setDirection(MOVE_BACKWARD);
  steppers[1].setDirection(MOVE_FORWARD);
}

void turnRight()
{
  steppers[0].setDirection(MOVE_FORWARD);
  steppers[1].setDirection(MOVE_BACKWARD);
}

void stop()
{
  for(int i = 0; i < nMotorCount; i++)
  {
    steppers[i].stop();
  }
}

void setup() {
  nCurrentStepCount = nTotalStepCount;
}

void loop(){

  if(nCurrentStepCount < 0)
    return;

  for(long i = 0; i < nTotalStepCount; i++)
  {
    if(i < ROTATE_FULL * CLOCK_DIVIDE * GEAR_RATIO * 5L)
      move(MOVE_FORWARD);
    else if(i < ROTATE_FULL * CLOCK_DIVIDE * GEAR_RATIO * 10L)
      turnLeft();
    else if(i < ROTATE_FULL * CLOCK_DIVIDE * GEAR_RATIO * 15L)
      move(MOVE_BACKWARD);
    else
      turnRight(); 
    
    nCurrentStepCount--;
  }

  for(int i = 0; i < nMotorCount; i++)
  {
    steppers[i].loop();
  }
}

