/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef WGM63_h
#define WGM63_h


#define MOVE_FORWARD 1
#define MOVE_BACKWARD -1
#define STOP 0
#define ACCELERATION_STEP 2
#define ROTATE_FULL 200
#define CLOCK_DIVIDE 8
#define GEAR_RATIO 10
#define WHEEL_SIZE 220

#define START_DELAY 1010
#define DRIVING_DELAY 260


#include "Arduino.h"

class WGM63
{
  public:
    WGM63(int index, int dirPin, int stepperPin, int enPin, int reverseFactor);
    void setDirection(int nDirection);
    void rotate();
    void stop();
    void loop();
  private:

    void changeDirection(int nDirection);

    int _index;
  
    int _dirPin, _stepperPin, _enPin;
    int _currentState;
    int _destState;

    int _currentDelay;
    int _reverseFactor;
};

#endif
