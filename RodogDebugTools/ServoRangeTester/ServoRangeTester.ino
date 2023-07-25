#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

/* PWM VALUE MAPPING: (target angle, min angle, max angle, pulse min, pulse max)
 * SET PWM ARGS: (servo channel, start delay, end time)
 * PWM ADDRESSES: 0x40
 * POSSIBLE PWM FREQUENCIES (hz): 60
 * MINUMUM PULSE WIDTH: 215
 * MAXIMUM PULSE WIDTH: 675
 */

// define replaces text on compilation compared to making a new variable, saves memory
#define SERVO_PMIN 215
#define SERVO_PMAX 675

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pwm.begin();
  pwm.setPWMFreq(60);
  Serial.println("Initialized\n");

  delay(50);
  pwm.setPWM(0, 0, angleToPulse(0));
  Serial.println("Moved servo to initial position.");
  delay(1500);
}

void loop() {
  for (int i = 0; i <= 180; i+=15) // do not optimize to uint16_t or uint8_t
  {
    Serial.println(i);
    pwm.setPWM(0, 0, angleToPulse(i));
    //pwm.setPWM(1, 0, angleToPulse(i));
    //pwm.setPWM(2, 0, angleToPulse(i));
    delay(500);
  }
  Serial.println("Finished a loop");
  delay(3000);

  for (int i = 180; i >= 0; i-=15) // do not optimize to uint16_t or uint8_t
  {
    Serial.println(i);
    pwm.setPWM(0, 0, angleToPulse(i));
    //pwm.setPWM(1, 0, angleToPulse(i));
    //pwm.setPWM(2, 0, angleToPulse(i));
    delay(500);
  }
  Serial.println("Finished a loop");
  delay(3000);
}

uint16_t angleToPulse(int angle) { // do not optimize to uint8_t
  uint16_t pulse = map(angle, 0, 180, SERVO_PMIN, SERVO_PMAX);
  pulse = constrain(pulse, SERVO_PMIN, SERVO_PMAX);
  Serial.print("angleToPulse requested, pulse: ");
  Serial.println(pulse);
  return pulse;
}
