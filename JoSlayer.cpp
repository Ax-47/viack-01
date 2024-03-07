#include "JoSlayer.h"
#include <WiFi.h>
#include <ArtronShop_LineNotify.h>
#include <ESP32Servo.h>
JoSlayer::JoSlayer() {
}
void JoSlayer::Begin(bool debug, int motor1Pin, int motor1Pin2, int motor2Pin1, int motor2Pin2, int servopin, int time) {
  this->debug = debug;
  this->motor1Pin1 = motor1Pin1;
  this->motor1Pin2 = motor1Pin2;
  this->motor2Pin1 = motor2Pin1;
  this->motor2Pin2 = motor2Pin2;
  this->time = time;
  this->servoMotor.attach(servopin);
  this->stop();
}

void JoSlayer::SmokeDetect() {
  this->somkeDetection++;
  if (this->somkeDetection >= 10)
    this->killJo();
  this->countReset =0;
  if (this->debug)
      Serial.printf("SmokeDetect : [somkeDetection : %d; countReset : %d]\n",this->somkeDetection,this->countReset);
  
}
void JoSlayer::SmokeReset() {
  if (this->countReset < 60*this->time) {
    this->countReset++;
    if (this->debug) {
      Serial.printf("count :  %d\n",this->countReset);
    }
    return;
  }
  if (this->debug) 
    Serial.printf("reset : [somkeDetection : %d; countReset : %d]\n",this->somkeDetection,this->countReset);
  
  this->stop();
}
void JoSlayer::killJo() {
  this->sandLine();
  this->lockDoor();
  this->waterShowerOn();
}
void JoSlayer::stop() {
  this->waterShowerOff();
  this->unLockDoor();
  this->somkeDetection = 0;
  this->countReset=0;
  this->fristTime=true;
}

void JoSlayer::lockDoor() {
  digitalWrite(this->motor2Pin1, LOW);
  digitalWrite(this->motor2Pin2, HIGH);
  this->servoMotor.write(90);
}

void JoSlayer::waterShowerOn() {
  digitalWrite(this->motor1Pin1, LOW);
  digitalWrite(this->motor1Pin2, HIGH);
}
void JoSlayer::waterShowerOff() {
  digitalWrite(this->motor2Pin1, LOW);
  digitalWrite(this->motor2Pin2, LOW);
}
void JoSlayer::unLockDoor() {
  digitalWrite(this->motor1Pin1, LOW);
  digitalWrite(this->motor1Pin2, LOW);
  this->servoMotor.write(0);
}
void JoSlayer::sandLine() {
  if (this->fristTime) {
    LINE.send("มีคนดูด");
    this->fristTime = !this->fristTime;
  }
}

