#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);
int storona_red = 1;
int storona_green = 1;
int storona_blue = 1;
int storona_yellow = 1;
void setup() {
   Serial.begin(9600);
   mySerial.begin(9600);
   Serial.println("----");
}

void loop() {
if (Serial.available() > 0) {
  Serial.println("данные переданы");
  if (Serial.read() == '2') 
  { storona_red = 1;}
  if (Serial.read() == '3') 
  { storona_red = -1;}
  if (Serial.read() == '4') 
  { storona_green = 1;}
  if (Serial.read() == '5') 
  { storona_green = -1;}
  if (Serial.read() == '6') 
  { storona_blue = 1;}
  if (Serial.read() == '7') 
  { storona_blue = -1;}
  if (Serial.read() == '8') 
  { storona_yellow = 1;}
  if (Serial.read() == '9') 
  { storona_yellow = -1;}
  Serial.println("storona_red=");Serial.println(storona_red);
  Serial.println("storona_green=");Serial.println(storona_green);
  Serial.println("storona_blue=");Serial.println(storona_green);
  Serial.println("storona_yellow=");Serial.println(storona_green);
  delay(10000);
  }
}