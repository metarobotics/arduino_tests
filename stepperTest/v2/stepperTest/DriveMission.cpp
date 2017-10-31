#include "DriveMission.h"

DriveMission::DriveMission(enDriveAction action, long steps)
{
  _action = action;
  _steps = steps;
  _currentStep = 0;
  _isComplete = false;
}

DriveMission::~DriveMission()
{
  
}

enDriveAction DriveMission::GetAction()
{
  return _action;
}

bool DriveMission::IsComplete()
{
  return _isComplete;
}

void DriveMission::update()
{
  if(IsComplete())
    return;
    
  _currentStep++;

  Serial.print(_currentStep);
  
  if(_steps == _currentStep)
    _isComplete = true;
}

