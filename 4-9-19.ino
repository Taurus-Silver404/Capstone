#include <Servo.h>
//const int motor = 9;
const int sensor = A0;
const int iMinThreshVal = 200;

Servo motor;

void setup() {
 motor.attach(9);
}

void loop () {
  
  // put your setup code here, to run once:
 // read muscle sensor value

  while(analogRead(sensor) > iMinThreshVal)        
  { 
 
    // state 1 - below threshold - fully retract
   motor.write(100);
   
  
  }
 // else 
 // { 
    // state 2 - above max threshold - fully extend
    motor.write(0);

 // } 
 
}
