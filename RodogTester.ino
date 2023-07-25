#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

/* PWM VALUE MAPPING: (target angle, min angle, max angle, pulse min, pulse max)
 * SET PWM: (servo channel, ignore and put 0, pwm value)
 * PWM ADDRESSES: 0x40 (0x40 is default, 0x70 was probably for daisy chains for inland pwm board)
 * POSSIBLE PWM FREQUENCIES (hz): 50, 60
 * MINUMUM PULSE WIDTH: 0
 * MAXIMUM PULSE WIDTH: 4095
 */

// define replaces text on compilation compared to making a new variable, saves memory
#define SERVO_PMIN 600
#define SERVO_PMAX 2400

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pwm.begin();
  pwm.setPWMFreq(50);
  Serial.println("Initialized");
}

void loop() {
  /*pwm.setPWM(15, 0, angleToPulse(0));
  Serial.println("channel 15 0 degrees");
  delay(2000);

  pwm.setPWM(15, 0, angleToPulse(45));
  Serial.println("channel 15 45 degrees");
  delay(2000);*/

  Serial.println("Rotating to 45deg");
  for (int i = 0; i <= 45; i++) 
  {
    pwm.setPWM(15, 0, angleToPulse(i));
    delay(15);
  }
  Serial.println("Finished rotating to 45deg");
  delay(1000);

  Serial.println("Rotating to 0deg");
  for (int i = 45; i >= 0; i--) 
  {
    pwm.setPWM(15, 0, angleToPulse(i));
    delay(15);
  }
  Serial.println("Finished rotating to 0deg");
  delay(1000);
}

int angleToPulse(int angle) {
  int pulse = map(angle, 0, 180, SERVO_PMIN, SERVO_PMAX);
  return pulse;
}
