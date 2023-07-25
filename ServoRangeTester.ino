#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

/* PWM VALUE MAPPING: (target angle, min angle, max angle, pulse min, pulse max)
 * SET PWM: (servo channel, ignore and put 0, pwm value)
 * PWM ADDRESSES: 0x40, 0x70
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
  pwm.setPWMFreq(60);
  Serial.println("Initialized\n");
}

void loop() {
  for (i = 0; i <= 180; i+=45) 
  {
    pwm.setPWM(0, 0, angleToPulse(i));
    pwm.setPWM(1, 0, angleToPulse(i));
    //pwm.setPWM(2, 0, angleToPulse(i)); testing two different servos instead of all 3 on a leg temporarily
    delay(2000);
  }
}

uint16_t angleToPulse(int angle) {
  uint16_t pulse = map(angle, 0, 180, SERVO_PMIN, SERVO_PMAX);
  Serial.print("angleToPulse requested, pulse: ");
  Serial.println(pulse);
  return pulse;
}
