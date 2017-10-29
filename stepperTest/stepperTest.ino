/*
MACHINE TYPE : SNSD-TY
*/

#include "WGM63.h"

// MOTOR DRIVER PINS


int nMotorCount = 2;
WGM63 steppers[2] = {WGM63(1, 9, 10, 0, 1), WGM63(2, 7, 8, 0, -1)};

long nTotalStepCount = ROTATE_FULL * CLOCK_DIVIDE * GEAR_RATIO * 5L;
long nCurrentStepCount;

void move(int direction)
{
  for(int i = 0; i < nMotorCount; i++)
  {
    steppers[i].setDirection(direction);
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

  if(nCurrentStepCount < ROTATE_FULL * CLOCK_DIVIDE * GEAR_RATIO * 2L)
    move(MOVE_FORWARD);
  else if(nCurrentStepCount < ROTATE_FULL * CLOCK_DIVIDE * GEAR_RATIO * 3L)
    turnLeft();
  else if(nCurrentStepCount < ROTATE_FULL * CLOCK_DIVIDE * GEAR_RATIO * 4L)
    move(MOVE_BACKWARD);
  else
    turnRight();

  nCurrentStepCount--;

  for(int i = 0; i < nMotorCount; i++)
  {
    steppers[i].loop();
  }
}

