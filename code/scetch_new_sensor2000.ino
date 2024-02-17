

#include <Servo.h> 
#include <Wire.h>                                               
#include <SparkFun_APDS9960.h> 
#define STEPS 4078
#include <Stepper_28BYJ.h>
SparkFun_APDS9960 apds = SparkFun_APDS9960();        
Stepper_28BYJ stepper(STEPS, 8, 9, 10, 11);


                                     
uint16_t lightAmbient = 0;                                      
uint16_t lightRed     = 0;                                      
uint16_t lightGreen   = 0;                                      
uint16_t lightBlue    = 0;                                      
int grad45 = 4075.7728395 / 8;
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
int bt;

Servo sRotate;

void setup() { 
  Serial.begin(9600);                                          
  sRotate.attach(13);
  stepper.setSpeed(13);                                         
  Serial.println("start");
  digitalWrite(2, HIGH); 
  pinMode(s0,OUTPUT);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);                                                     
} 
void TCS(){
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
    
    digitalWrite(s2,HIGH);
    digitalWrite(s3,HIGH);
  }
  else if(flag==2)
   {
    countG=counter;
    
    digitalWrite(s2,LOW);
    digitalWrite(s3,HIGH);
   }
   else if(flag==3)
    {
    countB=counter;
    
    digitalWrite(s2,LOW);
    digitalWrite(s3,LOW);

    }
    else if(flag==4)
     {
     flag=0;
     }
       counter=0;
}

void loop() {  
  if (Serial.available()){
  bt = Serial.read();  
  Serial.println(bt);}                   
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

TCS();

while ((bt == 1)
&& (bt != 0) ){        
stepper.step(grad45);}  

if ((0 < countR < 50)
   && (140 < countG < 160)
   && (240 < countB < 260)){            
     digitalWrite(9, LOW);
     digitalWrite(10, LOW);
     digitalWrite(11, LOW);
     digitalWrite(12, LOW);
     delay(500);
     sRotate.write(storona_red); 
     delay(1000);
     sRotate.write(storona_red*-1); 
     delay(500);
     digitalWrite(9, HIGH);
     digitalWrite(10, HIGH);
     digitalWrite(11, HIGH);
     digitalWrite(12, HIGH);}
if ((180 < countR < 220) 
   && (180 < countG < 220)
   && (240 < countB < 260)){            
     digitalWrite(9, LOW);
     digitalWrite(10, LOW);
     digitalWrite(11, LOW);
     digitalWrite(12, LOW);
     delay(500);
     sRotate.write(storona_green);               
     delay(1000);
     sRotate.write(storona_green*-1); 
     delay(500);
     digitalWrite(9, HIGH);
     digitalWrite(10, HIGH);
     digitalWrite(11, HIGH);
     digitalWrite(12, HIGH);}
if ((140 < countR < 160)
   && (140 < countG < 160)
   && (0 < countB < 50)){            
     digitalWrite(9, LOW);
     digitalWrite(10, LOW);
     digitalWrite(11, LOW);
     digitalWrite(12, LOW);
     delay(500);
     sRotate.write(storona_blue); 
     delay(1000);
     sRotate.write(storona_blue*-1); 
     delay(500);
     digitalWrite(9, HIGH);
     digitalWrite(10, HIGH);
     digitalWrite(11, HIGH);
     digitalWrite(12, HIGH);}
if ((40 < countR < 60)
   && (190 < countG < 210)
   && (0 < countB < 50)){   
     digitalWrite(9, LOW);
     digitalWrite(10, LOW);
     digitalWrite(11, LOW);
     digitalWrite(12, LOW);
     delay(500);
     sRotate.write(storona_yellow); 
     delay(1000);
     sRotate.write(storona_yellow*-1); 
     delay(500);
     digitalWrite(9, HIGH);
     digitalWrite(10, HIGH);
     digitalWrite(11, HIGH);
     digitalWrite(12, HIGH);}
}                                                       

                                             

                                                         
