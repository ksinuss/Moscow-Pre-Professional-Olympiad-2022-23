#include <Servo.h>
int q = 0;
Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo1.attach(A3);  // attaches the servo on pin 9 to the servo object
   myservo2.attach(A5);
   Serial.begin(9600);
   myservo3.attach(A1);
}

void loop() {
  Serial.println(analogRead(A2));
  for (pos = 0; pos <= 180; pos += 10) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    myservo2.write(pos);
    myservo3.write(pos);
    delay(150);                       // waits 15ms for the servo to reach the position
    Serial.println(analogRead(A2));
  }
  for (pos = 180; pos >= 0; pos -= 10) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    myservo2.write(pos);
    myservo3.write(pos);
    delay(150);                       // waits 15ms for the servo to reach the position
    Serial.println(analogRead(A2));
  }
}
