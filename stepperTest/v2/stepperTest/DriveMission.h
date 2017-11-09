/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef DriveMission_h
#define DriveMission_h

#include "Arduino.h"

enum enDriveAction
{
  Stop = 0,
  MoveForward = 1,
  MoveBackward = 2,
  TurnLeft = 3,
  TurnRight = 4,
};

class DriveMission
{
  public:
    DriveMission(enDriveAction action, long steps);
    ~DriveMission();
    void update();
    void reset();

    enDriveAction GetAction();
    bool IsComplete();

  private:
    enDriveAction _action;
    long _steps;
    long _currentStep;
    bool _isComplete;
};

#endif
