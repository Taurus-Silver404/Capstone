#include <Servo.h>
//const int motor = 9;
const int sensor = A0;
const int iMinThreshVal = 200;

Servo motor;

void setup() {
 motor.attach(9);
 Serial.begin(9600);
}

void loop () {
  
  // put your setup code here, to run once:
 // read muscle sensor value
 const int pSensor = A1;


 Serial.println(pSensor);
 Serial.println(sensor);
 delay(1);
 if(analogRead(pSensor)<1000){
 while(analogRead(sensor) > iMinThreshVal){ 
 

   motor.write(100);
  }
 }
   motor.write(0);
 }
 
 
