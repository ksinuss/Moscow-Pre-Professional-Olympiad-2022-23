#include <Servo.h>
#include <Stepper_28BYJ.h>
#define STEPS 4078
#define PIN_PHOTO_SENSOR A0

Servo sRotate;
Stepper_28BYJ stepper(STEPS, 9, 10, 11, 12);
int grad45 = 4075.7728395 / 8;
int mGrad45 = -1 * grad45;

int startPos = 107; // Стартовая позиция
int leftPos = 180;
int rightPos = 30;

void setup(){
  stepper.setSpeed(13);
  Serial.begin(9600);
  sRotate.attach(13); // PIN для сервопривода
  
  sRotate.write(startPos);
  delay(20); 
}
void loop(){
  stepper.step(grad45);
}
