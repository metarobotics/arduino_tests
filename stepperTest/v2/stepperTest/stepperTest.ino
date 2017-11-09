/*
MACHINE TYPE : SNSD-TY
*/

#include "WGM63.h"
#include "DriveMission.h"
#include "QueueArray.h"

#define ONE_TURN_STEPS ROTATE_FULL * CLOCK_DIVIDE * GEAR_RATIO * 1L
#define MOTOR_COUNT 2

WGM63 steppers[2] = {WGM63(1, 9, 10, 0, 1), WGM63(2, 7, 8, 0, -1)};
QueueArray<DriveMission*> _missions;

void move(int direction)
{
  for(int i = 0; i < MOTOR_COUNT; i++)
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
  for(int i = 0; i < MOTOR_COUNT; i++)
  {
    steppers[i].stop();
  }
}

void setup() {

  Serial.begin(9600);  
  Serial.println("--- Start Serial Monitor SEND_RCVE ---");

  _missions.enqueue(new DriveMission(enDriveAction::MoveForward, ONE_TURN_STEPS * 5));
  _missions.enqueue(new DriveMission(enDriveAction::MoveBackward, ONE_TURN_STEPS * 5));
  _missions.enqueue(new DriveMission(enDriveAction::TurnLeft, ONE_TURN_STEPS * 0.5));
  _missions.enqueue(new DriveMission(enDriveAction::MoveForward, ONE_TURN_STEPS * 5));
  _missions.enqueue(new DriveMission(enDriveAction::MoveBackward, ONE_TURN_STEPS * 5));
  _missions.enqueue(new DriveMission(enDriveAction::TurnRight, ONE_TURN_STEPS * 0.5));
  
}

void loop(){

  while (!_missions.isEmpty ())
  {
    DriveMission *currentMission = _missions.front();
    switch(currentMission->GetAction())
    {
      case enDriveAction::MoveForward: move(MOVE_FORWARD); break;
      case enDriveAction::MoveBackward: move(MOVE_BACKWARD); break;
      case enDriveAction::TurnLeft: turnLeft(); break;
      case enDriveAction::TurnRight: turnRight(); break;
      case enDriveAction::Stop: stop(); break;
    }

    currentMission->update();
    if(currentMission->IsComplete())
    {
      Serial.println("Mission complete");
      _missions.dequeue();
      currentMission->reset();
      _missions.enqueue(currentMission);
    }
    else
    {
      for(int i = 0; i < MOTOR_COUNT; i++)
      {
        steppers[i].loop();
      }
      break;
    }
  }
}

