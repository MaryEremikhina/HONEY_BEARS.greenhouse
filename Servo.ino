#include <Servo.h>

Servo myservo1;

 
void setup() 
{

  myservo1.attach(2);
  
} 
 
void loop() 
{
 
  myservo1.write(30);
  delay(500);
  
  myservo1.write(45);
  delay(500);
  
  myservo1.write(90);
  delay(500);

  myservo1.write(120);
  delay(500);

  myservo1.write(0);
  delay(500);
}
