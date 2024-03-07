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
#define MEASURE_PIN 36 //analog pin
#define LEDPOWER  19 //pin dust sensor
#define MOTOR1PIN1 25 //motor
#define MOTOR1PIN2 26//motor
#define MOTOR2PIN1 32//motor
#define MOTOR2PIN2 33//motor
#define SERVO_PIN 18
#define TIME_RESET 1

//dust sensor setup
#define SAMPLING_TIME 280
#define DELTA_TIME 40
#define SLEEP_TIME 9680

//env
#define WIFI_SSID "" // WiFi Name
#define WIFI_PASSWORD "" // WiFi Password
#define LINE_TOKEN "" // LINE Token

//debug mode
#define DEBUG true

//init jo
JoSlayer JO;

//dustDensity
float voMeasured = 0.0;
float calcVoltage = 0.0;
float dustDensity= 0.0;

void setup(){
  Serial.begin(9600);
  pinMode(LEDPOWER,OUTPUT);
  pinMode(MOTOR1PIN1,OUTPUT);
  pinMode(MOTOR1PIN2,OUTPUT);
  pinMode(MOTOR2PIN1,OUTPUT);
  pinMode(MOTOR2PIN2,OUTPUT);
  initWifi();
  LINE.begin(LINE_TOKEN);
  JO.Begin(DEBUG,MOTOR1PIN1,MOTOR1PIN2,MOTOR2PIN1,MOTOR2PIN2,SERVO_PIN,TIME_RESET);
}

void loop(){
  dustDensity=getDustDensity();
  if (DEBUG)
    Serial.printf("dustDensity : %f \n",dustDensity); 
  if (dustDensity >1000)
    JO.SmokeDetect();
  else
    JO.SmokeReset();
  delay(1000);
}

void initWifi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(10);
  }
  Serial.println(WiFi.localIP());
}

float getDustDensity(){
  digitalWrite(LEDPOWER,LOW);
  delayMicroseconds(SAMPLING_TIME);
  voMeasured = analogRead(MEASURE_PIN); 
  delayMicroseconds(DELTA_TIME);
  digitalWrite(LEDPOWER,HIGH);
  delayMicroseconds(SLEEP_TIME);
  calcVoltage = voMeasured * (5.0 / 1024.0);
  return  170 * calcVoltage - 0.1;
}
