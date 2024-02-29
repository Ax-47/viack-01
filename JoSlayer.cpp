#include "JoSlayer.h"
#include <WiFi.h>
#include <ArtronShop_LineNotify.h>

JoSlayer::JoSlayer(){

}
void JoSlayer::Begin(bool debug,int motor1Pin,int motor1Pin2,int motor2Pin1,int motor2Pin2) {
  this->debug = debug;
  this->motor1Pin1=motor1Pin1;
  this->motor1Pin2=motor1Pin2;
  this->motor2Pin1=motor2Pin1;
  this->motor2Pin2=motor2Pin2;
}

void JoSlayer::SomkeDetect(){
    this->somkeDetection++;
    if (this->somkeDetection>=10)
      JoSlayer::killJo()  ;
    if ( this->countExacute>=10)
      JoSlayer::stop();
      
      
    Serial.println(countExacute); 
    Serial.println(somkeDetection); 
}
void JoSlayer::killJo() {
  this->sandLine();
  this->lockDoor();
  this->waterShowerOn();
  this->countExacute++;
}
void JoSlayer::stop() {
  this->waterShowerOff();
  this->unLockDoor();
  this->countExacute=0;
  this->somkeDetection=0;
}

void JoSlayer::lockDoor(){
  digitalWrite(this->motor2Pin1, LOW);
  digitalWrite(this->motor2Pin2, HIGH); 
}

void JoSlayer::waterShowerOn(){
  digitalWrite(this->motor1Pin1, LOW);
  digitalWrite(this->motor1Pin2, HIGH); 
}
void JoSlayer::waterShowerOff(){
  digitalWrite(this->motor2Pin1, LOW);
  digitalWrite(this->motor2Pin2, LOW); 
}
void JoSlayer::unLockDoor(){
  digitalWrite(this->motor1Pin1, LOW);
  digitalWrite(this->motor1Pin2, LOW); 
}
void JoSlayer::sandLine(){
  if (this->countExacute ==0)
      LINE.send("มีคนดูด");
}
JoSlayer JO;