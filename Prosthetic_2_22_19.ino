#include <Servo.h>
const int touchSensor1 = 6; //connected to Digital pin 
const int touchSensor2 = 7; //connected to Digital pin 
Servo esc;
Servo fingerServo;    
Servo thumbServo;

// constants
const int iFingerServoPin = 3;
const int iThumbServoPin = 5;              // servo pin number
const int iSensorPin = A3;            // muscle sensor pin number
const int iMaxServoVal = 880;        // HS-7940's fully extracted claw servo position PWM value (in microseconds)
const int iMinServoVal = 1800;        // HS-7940's fully retracted claw servo position PWM value (in microseconds) 
const int iMinThreshVal = 200;        // muscle sensor threshold value to begin controlled extension
const int iServoStep = 10;            // controls claw extension speed - increase to speed up
const unsigned long lLockOut = 3000L;   // duration to hold max threshval to toggle the lock state (in milliseconds)

// global variables
unsigned long lStartTime = 0L;        // variable to store the time the timer was started
bool bStartLockTimer = false;         // if true, the timer has been started; false otherwise
bool bActiveLock = false;       

void setup()
{
  pinMode(touchSensor1, INPUT);
  pinMode(touchSensor2, INPUT);
  esc.attach(9);
  fingerServo.attach(iFingerServoPin); 
  thumbServo.attach(iThumbServoPin);  // attaches the pin to the servo object
  delay(1000); 
// esc.write(45);

}
 
void loop()
{

 while(digitalRead(touchSensor1)==HIGH)      //Read Touch sensor signal
   { 
esc.write(1750);
   }
  while(digitalRead(touchSensor2)==HIGH)     //Read Touch sensor signal
  {
 esc.write(1000);
  }
  esc.write(0);

    // read muscle sensor value
  int iSensorVal = analogRead(iSensorPin);
  int iServoVal = iMinServoVal;
 //fingerServo.writeMicroseconds(iMinServoVal); 
// thumbServo.writeMicroseconds(iMaxServoVal);     // intialize to min value 

  // determine what state to put the claws in based on the sensor value  
  // three possible states
  if(iSensorVal < iMinThreshVal)        
  { 
    // state 1 - below threshold - fully retract claws
    fingerServo.write(iMaxServoVal);
    thumbServo.write(iMinServoVal);
      iServoVal = 0; 
  }
  else 
  { 
    // state 2 - above max threshold - fully extend claws
    fingerServo.writeMicroseconds(iMinServoVal); 
    thumbServo.writeMicroseconds(iMaxServoVal); 
      iServoVal = 1; 
  } 
  
  // if sensor is in state 2, start timer to trigger lLockOut
  if(iServoVal == 1)
  {
    // if the timer hasn't been started, then start it.
   if(!bStartLockTimer) 
    {
      lStartTime = millis();
      bStartLockTimer = true;
    }
  }
  else
  {
    // reset timer variables
    lStartTime = 0L;
    bStartLockTimer = false;
 }
    
  // check to see if the timer was started and it runs for the amount of time required to trigger lock/unlock
  if(bStartLockTimer && millis()-lStartTime >= lLockOut)
  {      
    // toggle lock state
    bActiveLock = !bActiveLock;
    
    // reset timer variables
    lStartTime = 0L;
    bStartLockTimer = false;
    
    // set servo value to max when locking
    if(bActiveLock) 
    {
     fingerServo.writeMicroseconds(iMinServoVal); 
     thumbServo.writeMicroseconds(iMaxServoVal); 
     // iServoVal = iMinServoVal;  
    }
    else // reset servo value to min when unlocking
    {
        fingerServo.writeMicroseconds(iMaxServoVal);
       thumbServo.writeMicroseconds(iMinServoVal);
    // iServoVal = iMaxServoVal;
    }
    
    // pause for a second to allow the user to adjust to the new setting
    delay(1000);
  }

  // move the servo to the desired postion
   if(bActiveLock)
   {
    fingerServo.writeMicroseconds(iMinServoVal);
    thumbServo.writeMicroseconds(iMaxServoVal);
   }
  else    
  {
 //   fingerServo.writeMicroseconds(iServoVal);
 //   thumbServo.writeMicroseconds(iServoVal);
  }
  // delay to not overload the ADC
  delay(100);
 

}
