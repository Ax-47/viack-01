//                 +++             ++
//                 + ++           ++++
//                ++  +++        ++  +
//               ++     ++++++++++    +
//               +                    +
//       +       +                    +
//     ++++++   ++   ───       #==    +
//    ++    +++ +                     +
//   ++      ++ +           ___       +
// +++        +++       ___ \  \     ++
// +           ++        \-____|     +
// +         +++                    ++
// +         +                      +
// +        ++                      +
// +        ++                      +
// ++       +                      +
//  +      ++       +  +        +  +
//  ++    +++++++++ +  +        +  +
//   ++   +       + +  +    +   +  +
//    ++  +       + +  +    +   +  +
//    +++++       +++  +    +   +  +
//       ++       +++  ++++++   +  +
//        +++++++++++  +++  +++++  +++
//                  ++++++      ++++++
#include "WiFi.h"
#include <ArtronShop_LineNotify.h>
#include "JoSlayer.h"

//pin setup
#define measurePin 36 //analog pin
#define ledPower  17 //pin dust sensor

#define motor1Pin1 25 //motor
#define motor1Pin2 26//motor

#define motor2Pin1 32//motor
#define motor2Pin2 33//motor

#define servo_pin 19

//dust sensor setup
#define samplingTime 280
#define deltaTime 40
#define sleepTime 9680

float voMeasured = 0.0;
float calcVoltage = 0.0;
float dustDensity= 0.0;

//env
#define WIFI_SSID "" // WiFi Name
#define WIFI_PASSWORD "" // WiFi Password
#define LINE_TOKEN "" // LINE Token

//debug mode
#define DEBUG false

void setup(){
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
  pinMode(motor1Pin1,OUTPUT);
  pinMode(motor1Pin2,OUTPUT);
  pinMode(motor2Pin1,OUTPUT);
  pinMode(motor2Pin2,OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
   LINE.begin(LINE_TOKEN);
   JO.Begin(DEBUG,motor1Pin1,motor1Pin2,motor2Pin1,motor2Pin2,servo_pin);
}

void loop(){
  digitalWrite(ledPower,LOW);
  delayMicroseconds(samplingTime);
  voMeasured = analogRead(measurePin); 
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH);
  delayMicroseconds(sleepTime);
  calcVoltage = voMeasured * (5.0 / 1024.0);
  dustDensity = 170 * calcVoltage - 0.1;
  Serial.println(dustDensity); 
  if (dustDensity >1000)
    JO.SomkeDetect();
  delay(1000);
}
