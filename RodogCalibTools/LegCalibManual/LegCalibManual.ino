#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVO_PMIN 215 // 600 is MICROSECONDS
#define SERVO_PMAX 675 // 2400 is MICROSECONDS

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pwm.begin();
  pwm.setPWMFreq(60);
  Serial.println("Initialized\n");
  Serial.println("Commands: m1 0-180, m2 0-180, m3 0-180");
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

    if (command == "m1") 
    {
      pwm.setPWM(0, 0, angleToPulse(commandParam));  
    }
    else if (command == "m2")
    {
      pwm.setPWM(1, 0, angleToPulse(commandParam));  
    }
    else if (command == "m3") 
    {
      pwm.setPWM(2, 0, angleToPulse(commandParam));  
    }
    
    delay(5);
  }
}

uint16_t angleToPulse(int angle) { // do not optimize to uint8_t
  uint16_t pulse = map(angle, 0, 180, SERVO_PMIN, SERVO_PMAX);
  Serial.print("angleToPulse requested, pulse: ");
  Serial.println(pulse);
  return pulse;
}
