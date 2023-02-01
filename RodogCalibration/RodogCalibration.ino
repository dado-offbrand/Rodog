// Libraries
#include <ESPAsyncWebServer.h>
#include <ESP32Servo.h>
#include <AsyncTCP.h>
#include <WiFi.h>

// Variables
const char* inputParameter = "value";
String incomingByte = "";
ESP32_Servo_h Servo testServo;
String sliderValue = "0";

//SERVO_GROUP shoulderServos = {ESP32_Servo_h Servo flServo, ESP32_Servo_h Servo frServo, ESP32_Servo_h Servo blServo, ESP32_Servo_h Servo brServo};
//SERVO_GROUP upperLegServos = {ESP32_Servo_h Servo flServo, ESP32_Servo_h Servo frServo, ESP32_Servo_h Servo blServo, ESP32_Servo_h Servo brServo};
//SERVO_GROUP lowerLegServos = {ESP32_Servo_h Servo flServo, ESP32_Servo_h Servo frServo, ESP32_Servo_h Servo blServo, ESP32_Servo_h Servo brServo};

bool requestOngoing = false;
//AsyncWebServer server(80);

struct SERVO_GROUP
{
  ESP32_Servo_h Servo flServo;
  ESP32_Servo_h Servo frServo;
  ESP32_Servo_h Servo blServo;
  ESP32_Servo_h Servo brServo;  
};

void setup(){
  Serial.begin(115200);

  testServo.attach(13);
  /*shoulderServos.flServo.attach(0);
  shoulderServos.frServo.attach(0);
  shoulderServos.blServo.attach(0);
  shoulderServos.brServo.attach(0);

  upperLegServos.flServo.attach(0);
  upperLegServos.frServo.attach(0);
  upperLegServos.blServo.attach(0);
  upperLegServos.brServo.attach(0);

  lowerLegServos.flServo.attach(0);
  lowerLegServos.frServo.attach(0);
  lowerLegServos.blServo.attach(0);
  lowerLegServos.brServo.attach(0);*/

  Serial.println("Setup complete");
}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.readString();

    Serial.print("received: ");
    Serial.println(incomingByte);

    // Move servo command  (0-180deg) | moveServo:group#:servo#:amount
    if (incomingByte.startsWith("moveServo"))
    {
      //int g = incomingByte.substring(10, 12).toInt(); // 9:X:
      //int s = incomingByte.substring(12, 14).toInt(); // 11:X:
      int sVS = incomingByte.substring(10, incomingByte.length()).toInt(); // 13:X:

      // temp assume same group and servo
      //moveServo(sVS, shoulderServos.flServo);
      tbMoveServo(sVS);
    }
  }
}
