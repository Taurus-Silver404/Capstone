#include <Servo.h>
const int touchSensor1 = 4; //connected to Digital pin 
const int touchSensor2 = 5; //connected to Digital pin 
Servo esc;
 
void setup()
{
   pinMode(touchSensor1, INPUT);
  pinMode(touchSensor2, INPUT);
esc.attach(9);

// esc.write(45);

}
 
void loop()
{

 if(digitalRead(touchSensor1)==HIGH)      //Read Touch sensor signal
   { 
esc.write(100);
   }
else
{
  esc.write(0);
}

  if(digitalRead(touchSensor2)==HIGH)     //Read Touch sensor signal
  {
 esc.write(20);
  }
else
{
  esc.write(0);
  
}

}
