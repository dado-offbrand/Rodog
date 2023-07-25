#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

uint16_t currentMin = 600; // default min
uint16_t currentMax = 2400; // default max
uint16_t currentPulse = currentMin; // minumum SAFE angle by default

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pwm.begin();
  pwm.setPWMFreq(60);
  Serial.println("Initialized");

  Serial.println("Commands: setmin X, setmax X, setcurrent X, sweep, to");
}

void loop() 
{
  if (Serial.available() > 0) 
  {
    String command = Serial.readStringUntil(' ');
    command.trim();
    uint16_t commandParam = 0;

    if Serial.available() > 0) 
    {
      commandParam = Serial.parseInt();  
    }

    switch (command) 
    {
      case "setmin":
        currentMin = commandParam;
        Serial.print("Set min to: ")
        Serial.println(commandParam);
        break;
      case "setmax":
        currentMax = commandParam;
        Serial.print("Set max to: ")
        Serial.println(commandParam);
        break;
      case "setcurrent":
        currentMin = commandParam;
        Serial.print("Set current to: ")
        Serial.println(commandParam);
        break;
      case "sweep":
        Serial.println("Starting sweep");
        for (uint16_t i = currentMin; i <= currentMax; i++) 
        {
          pwm.setPWM(0, 0, i);
          pwm.setPWM(1, 0, i);
          delay(5); // unsure how much time this will take, so small delay only
        }
        Serial.println("Swept from min to max");
        break;
      case "to":
        pwm.setPWM(0, 0, currentPulse);
        pwm.setPWM(1, 0, currentPulse);
        Serial.println("Moved to current pulselength");
        break;
    }
  }
}
