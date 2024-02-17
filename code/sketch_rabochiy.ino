// библиотеки
#include <Stepper_28BYJ_48.h>
#include <Servo.h> 
#include <Wire.h>  
// пины моторов                                                 
Stepper_28BYJ_48 stepper(8,9,10,11);

Servo servo;
    // объявляем 
int s0=3,s1=4,s2=5,s3=6;
#define sensorOut 2
    // переменные                                  
int bt = 100;
int leftPos = 144;
int rightPos = 30;
int storona_red    = 0;
int storona_green  = 0;
int storona_blue   = 0;
int storona_yellow = 0;
int r, g, b;
int flag;
int qwe=0;
byte counter=0;
byte countR=0,countG=0,countB=0;
//запуск
void setup()
{ 
  // пины датчика цвета 
 pinMode(s0,OUTPUT);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT); 
  digitalWrite(2, HIGH); 
  servo.attach(12); // пин серво
  servo.write(73);  // старт позиция
  // выставляем контакт sensorOut в режим INPUT:
  
  // задаем масштабирование частоты:

  // запускаем последовательную коммуникацию: 
  Serial.begin(9600);
                                           
} 
void TCS(){
 qwe=0;
 digitalWrite(s1,HIGH);
 digitalWrite(s0,HIGH);
 digitalWrite(s2,LOW);
 digitalWrite(s3,LOW);
 attachInterrupt(0, ISR_INTO, CHANGE);
 timer0_init();}

void ISR_INTO(){
 counter++;
}
void timer0_init(void){
  TCCR2A=0x00;
  TCCR2B=0x07;   
  TCNT2= 100;    
  TIMSK2 = 0x01;}

ISR(TIMER2_OVF_vect)
{
    TCNT2=100;
    qwe++;
 if(qwe==1)
  {
    countR=counter;

    digitalWrite(s2,HIGH);
    digitalWrite(s3,HIGH);
  }
  else if(qwe==2)
   {
    countG=counter;

    digitalWrite(s2,LOW);
    digitalWrite(s3,HIGH);
   }
   else if(qwe==3)
    {
    countB=counter;


    digitalWrite(s2,LOW);
    digitalWrite(s3,LOW);

    }
    else if(qwe==4)
     {
     qwe=0;
     }
       counter=0;
}
// работа
void loop() 

{
  if (Serial.available())   // если данные получены:
  {
    bt = Serial.read();     // переменная для посылаемых значений с приложения
    Serial.println(bt);
  } 
  // обрабатываем значения посылаемые из приложения
  if (bt == 2)
  { storona_red    = rightPos;}
  if (bt == 3)
  { storona_red    = leftPos;}
  if (bt == 4)
  { storona_green  = rightPos;}
  if (bt == 5)
  { storona_green  = leftPos;}
  if (bt == 6)
  { storona_blue   = rightPos;}
  if (bt == 7)
  { storona_blue   = leftPos;}
  if (bt == 8)
  { storona_yellow = rightPos;}
  if (bt == 9)
  { storona_yellow = leftPos;}
  delay(10) ;
  TCS();
       // если из приложения послана 1 конвейер запускается                                                            
  if(bt == 1)
  {
    delay(200);
    Serial.print("r = ");
    Serial.print(countR);
    Serial.print(" ");
    Serial.print("g = ");
    Serial.print(countG);
    Serial.print(" ");
    Serial.print("b = ");
    Serial.print(countB);
    Serial.print(" ");
    Serial.println();
  
    flag = 1;

    if ((90 < countR and countR <139 ) and ( 190< countG and countG <220 ) and ( 10< countB and countB < 50))       // значения для красного кубика
    {
      delay(500);
      flag = 0;
      delay(1500);
      flag = 1;
      delay(2000);
      flag = 0;
      servo.write(storona_red);
      delay(1000);
      servo.write(73);
      delay(500);
      flag = 1;
    }
    if ((55 < countR and countR <89 ) and ( 220< countG and countG <260 ) and ( 50< countB and countB < 90))     // значения для зеленого кубика
    {
      delay(500);
      flag = 0;
      delay(1500);
      flag = 1;
      delay(500);
      flag = 0;
      servo.write(storona_green);
      delay(1000);
      servo.write(73);
      delay(500);
      flag = 1;
    }
    if ((0 < countR and countR <51 ) and ( 210< countG and countG <240 ) and ( 80< countB and countB < 125))     // значения для синего кубика
    {
      delay(500);
      flag = 0;
      delay(1500);
      flag = 1;
      delay(500);
      flag = 0;
      servo.write(storona_blue);
      delay(1000);
      servo.write(73);
      delay(500);
      flag = 1;
    }
    if ((100 < countR and countR <130 ) and ( 230< countG and countG <250 ) and ( 49< countB and countB < 70)) // значения для желтого кубика
    {
      delay(500);
      flag = 0;
      delay(1500);
      flag = 1;
      delay(2000);
      flag = 0;
      servo.write(storona_yellow);
      delay(1000);
      servo.write(73);
      delay(500);
      flag = 1;
    }
  }

  if(bt == 0)
  {
    flag = 0;
  }
  
}

                
void yield() 
{
  if (flag == 1)
  { stepper.step(1);}             
}

                                                         
