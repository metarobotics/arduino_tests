/*
  WGM63.cpp - Library for WGM63 stepper code.
  Created by Kisun Park, November 1, 2017.
*/

#include "Arduino.h"
#include "WGM63.h"


WGM63::WGM63(int index, int dirPin, int stepperPin, int enPin, int reverseFactor)
{
  pinMode(dirPin, OUTPUT);
  pinMode(stepperPin, OUTPUT);
  pinMode(enPin, OUTPUT);

  _index = index;
  
  _dirPin = dirPin;
  _stepperPin = stepperPin;
  _enPin = enPin;

  _currentState = STOP;
  _destState = STOP;
  
  _currentDelay = START_DELAY;
  _reverseFactor = reverseFactor;
}

void WGM63::setDirection(int nDirection)
{
  _destState = nDirection;
}

void WGM63::rotate()
{
  digitalWrite(_dirPin, HIGH);
  delay(250);
  digitalWrite(_dirPin, LOW);
  delay(250);  
}

void WGM63::stop()
{
  setDirection(STOP);
}

void WGM63::changeDirection(int nDirection)
{
  _currentState = nDirection;
  int motorDirection = nDirection * _reverseFactor;
  
  if(motorDirection == MOVE_FORWARD)
    digitalWrite(_dirPin, HIGH);
   else
    digitalWrite(_dirPin, LOW);
}


int nDivideCount = 0;
static int nDivideStep = 3;

void WGM63::loop()
{
  if(_currentState == STOP && _destState == STOP)
    return;

  if(_currentState == STOP)
  {
    changeDirection( _destState );
  }
  
  if(_currentState != _destState)
  {
    nDivideCount++;
    if(nDivideCount == nDivideStep)
    {
      _currentDelay += ACCELERATION_STEP;
      nDivideCount = 0;
    }
    
    _currentDelay = constrain(_currentDelay, DRIVING_DELAY, START_DELAY);
    if(_currentDelay == START_DELAY)
    {
      changeDirection( _destState );
    }
  }
  else
  {
    if(_currentDelay != DRIVING_DELAY)
    {
      nDivideCount++;
      if(nDivideCount == nDivideStep)
      {
        _currentDelay -= ACCELERATION_STEP;
        nDivideCount = 0;
      }
      
      _currentDelay = constrain(_currentDelay, DRIVING_DELAY, START_DELAY);
    }
  }
  
  digitalWrite(_stepperPin, HIGH);
  delayMicroseconds(_currentDelay);
  digitalWrite(_stepperPin, LOW);
  delayMicroseconds(_currentDelay);
}

