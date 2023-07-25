#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVO_PMIN 150 // 600 is MICROSECONDS
#define SERVO_PMAX 600 // 2400 is MICROSECONDS

#define SHOULDER_CHANNEL 0
#define UPPER_CHANNEL 1
#define LOWER_CHANNEL 2

uint8_t shoulderRot = 90;
uint8_t upperLegRot = 90;
uint8_t lowerLegRot = 90;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pwm.begin();
  pwm.setPWMFreq(60);
  Serial.println("Initialized\n");
  Serial.println("Commands: toShoulder, toUpper, toLower, toAll");
  Serial.println("setShoulder, setUpper, setLower");
}

void loop() {
  if (Serial.available() > 0) 
  {
    String command = Serial.readStringUntil(' ');
    command.trim();
    uint16_t commandParam = 0;

    if (Serial.available() > 0) 
    {
      commandParam = Serial.parseInt();  
    }
    else 
    {
      commandParam = 0; 
    }

    processCommand(command, commandParam);
    delay(5);
  }
}

void processCommand(String command, int commandParam) {
  Serial.print("Processing command: ");
  Serial.println(command); 
  
  if (command == "toShoulder") {
    pwm.setPWM(SHOULDER_CHANNEL, 0, shoulderRot);
  } else if (command == "toUpper") {
    pwm.setPWM(UPPER_CHANNEL, 0, upperLegRot);
  } else if (command == "toLower") {
    pwm.setPWM(LOWER_CHANNEL, 0, lowerLegRot);
  } else if (command == "toAll") {
    pwm.setPWM(SHOULDER_CHANNEL, 0, shoulderRot);
    pwm.setPWM(UPPER_CHANNEL, 0, upperLegRot);
    pwm.setPWM(LOWER_CHANNEL, 0, lowerLegRot);
  } else if (command == "setShoulder") {
    shoulderRot = commandParam;
  } else if (command == "setUpper") {
    upperLegRot = commandParam;
  } else if (command == "setLower") {
    lowerLegRot = commandParam;
  }
  else 
  {
    Serial.print("Command was unknown");
  }
}

uint16_t angleToPulse(int angle) { // do not optimize to uint8_t
  uint16_t pulse = map(angle, 0, 180, SERVO_PMIN, SERVO_PMAX);
  Serial.print("angleToPulse requested, pulse: ");
  Serial.println(pulse);
  return pulse;
}
