#include "DriveMission.h"

DriveMission::DriveMission(enDriveAction action, long steps)
{
  _action = action;
  _steps = steps;
  reset();
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
  
  if(_steps == _currentStep)
    _isComplete = true;
}

void DriveMission::reset()
{
  _currentStep = 0;
  _isComplete = false;
}
