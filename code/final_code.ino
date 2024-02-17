#include <Stepper_28BYJ_48.h>
#include <Servo.h> 
#include <Wire.h>                                                   
Stepper_28BYJ_48 stepper(8,9,10,11);

Servo servo;

#define S0 3
#define S1 4
#define S2 5
#define S3 6
#define sensorOut 2
                                      
int bt = 100;
int leftPos = 144;
int rightPos = 30;
int storona_red    = 0;
int storona_purple  = 0;
int storona_yellow   = 0;
int storona_black = 0;
int r, g, b;
int flag;
int startpos=73;

void setup()
{ 
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  servo.attach(12);
  servo.write(73);
  // выставляем контакт sensorOut в режим INPUT:
  pinMode(sensorOut, INPUT);
  // задаем масштабирование частоты:
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  // запускаем последовательную коммуникацию: 
  Serial.begin(9600);
                                                
} 

void loop() 
{
  if (Serial.available())
  {
    bt = Serial.read();
    Serial.println(bt);
  } 
  if (bt == 2)
  { storona_red    = rightPos;}
  if (bt == 3)
  { storona_red    = leftPos;}
  if (bt == 4)
  { storona_purple  = rightPos;}
  if (bt == 5)
  { storona_purple  = leftPos;}
  if (bt == 6)
  { storona_yellow   = rightPos;}
  if (bt == 7)
  { storona_yellow   = leftPos;}
  if (bt == 8)
  { storona_black = rightPos;}
  if (bt == 9)
  { storona_black = leftPos;} 
                                                                   
  if(bt == 1)
  {
    r = process_red_value();
    delay(200);
    g = process_green_value();
    delay(200);
    b = process_blue_value();
    delay(200);
    Serial.print("r = ");
    Serial.print(r);
    Serial.print(" ");
    Serial.print("g = ");
    Serial.print(g);
    Serial.print(" ");
    Serial.print("b = ");
    Serial.print(b);
    Serial.print(" ");
    Serial.println();
  
    flag = 1;

      if (( 28<=r and r<=38 ) and ( 94 <= g and g <= 110 ) and ( 75 <= b and b <= 88))
      {Serial.println("red");
      flag=1;
      delay(2000);
      flag=0;
      delay(1500);
      servo.write(storona_red);
      delay(500);
      servo.write(startpos);
      delay(500);}
      
      else if (( 12<=r and r<=30 ) and ( 24 <= g and g <= 48 ) and ( 50 <= b and b <= 64))
      {Serial.println("yellow");
        flag=1;
      delay(2000);
      flag=0;
      delay(1500);
      servo.write(storona_yellow);
      delay(500);
      servo.write(startpos);
      delay(500);}
      
      else if(( 40<=r and r<=50 ) and ( 65 <= g and g <= 82 ) and ( 35 <= b and b <= 52))
      {Serial.println("purple");
        flag=1;
      delay(2000);
      flag=0;
      delay(1500);
      servo.write(storona_purple);
      delay(500);
      servo.write(startpos);
      delay(500);}
      
      else if (( 98<=r and r<= 113 ) and ( 140 <= g and g <= 153 ) and ( 95 <= b and b <= 137))
      {Serial.println("black");
        flag=1;
      delay(2000);
      flag=0;
      delay(1500);
      servo.write(storona_black);
      delay(500);
      servo.write(startpos);
      delay(500);}
  

  if(bt == 0)
  {
    flag = 0;
  }}
  
}

int process_red_value()
{
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  int pulse_length = pulseIn(sensorOut, LOW);
  return pulse_length;
}
int process_green_value()
{
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  int pulse_length = pulseIn(sensorOut, LOW);
  return pulse_length;
}
int process_blue_value()
{
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  int pulse_length = pulseIn(sensorOut, LOW);
  return pulse_length;
}
                    
void yield() 
{
  if (flag == 1)
  { stepper.step(1);}
}

                                                         
