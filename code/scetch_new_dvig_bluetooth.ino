#include <Stepper_28BYJ_48.h>

#include <Servo.h> 
#include <Wire.h>                                                   
Stepper_28BYJ_48 stepper(8,9,10,11);
                                   
uint16_t lightAmbient = 0;                                      
uint16_t lightRed     = 0;                                      
uint16_t lightGreen   = 0;                                      
uint16_t lightBlue    = 0;                                      
int bt = 100;
int leftPos = 144;
int rightPos = 30;
int storona_red = 0;
int storona_green = 0;
int storona_blue = 0;
int storona_yellow = 0;
int s0=3,s1=4,s2=5,s3=6;
int out=2;
int flag=0;
byte counter=0;
byte countR=0,countG=0,countB=0;
int i=0;

Servo sRotate;
void setup() { 
  Serial.begin(9600);                                          
  sRotate.attach(13);
                                        
  Serial.println("start");
  digitalWrite(2, HIGH); 
  pinMode(s0,OUTPUT);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);                                                
} 

void TCS() // TCS - функция для запуска работы датчика 
{ 
 flag=0;
 digitalWrite(s1,HIGH);
 digitalWrite(s0,HIGH);
 digitalWrite(s2,LOW);
 digitalWrite(s3,LOW);
 attachInterrupt(0, ISR_INTO, CHANGE);
 timer0_init();
}

void ISR_INTO(){
 counter++;
}

void timer0_init(void){
  TCCR2A=0x00;
  TCCR2B=0x07;   
  TCNT2= 100;    
  TIMSK2 = 0x01; 
}

ISR(TIMER2_OVF_vect)
{
  TCNT2=100;
  flag++;
  if(flag==1)
  {
    countR=counter;
    Serial.print("red=");
    Serial.println(countR,DEC);
    digitalWrite(s2,HIGH);
    digitalWrite(s3,HIGH);
  }
  else if(flag==2)
  {
    countG=counter;
    Serial.print("green=");
    Serial.println(countG,DEC);
    digitalWrite(s2,LOW);
    digitalWrite(s3,HIGH);
  }
  else if(flag==3)
  {
    countB=counter;
    Serial.print("blue=");
    Serial.println(countB,DEC);
    Serial.println("\n");
    digitalWrite(s2,LOW);
    digitalWrite(s3,LOW);
  }
  else if(flag==4)
  {
    flag=0;
  }
  counter=0;
}
void loop() 
{ 
  if (Serial.available())
  { bt = Serial.read();} 
  if (bt == 2){
    storona_red = rightPos;}
  if (bt == 3){
    storona_red = leftPos;}
  if (bt == 4){
    storona_green = rightPos;}
  if (bt == 5){
    storona_green = leftPos;}
  if (bt == 6){
    storona_blue = rightPos;}
  if (bt == 7){
    storona_blue = leftPos;}
  if (bt == 8){
    storona_yellow = rightPos;}
  if (bt == 9){
    storona_yellow = leftPos;}  
  if(bt == 1)
  {       
    stepper.step(1);
    if(bt == 0)
    { 
      stepper.step(0);   
      Serial.println(bt);
    } 
  }
}                                                     
