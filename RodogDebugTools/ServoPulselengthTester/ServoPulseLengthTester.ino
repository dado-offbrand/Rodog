#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

/*
 * Old default minumum: 150
 * Old default maximum: 600
 */

uint16_t currentMin = 215; // default min
uint16_t currentMax = 675; // default max
uint16_t currentPulse = currentMin; // minumum SAFE angle by default

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pwm.begin();
  pwm.setPWMFreq(60);
  Serial.println("Initialized");

  Serial.println("Commands: setmin X, setmax X, setcurrent X, sweep, topulse");
}

void loop() 
{
  if (Serial.available() > 0) 
  {
    // get command
    String command = Serial.readStringUntil(' ');
    command.trim();
    uint16_t commandParam = 0;

    // get param
    if (Serial.available() > 0) 
    {
      commandParam = Serial.parseInt();  
    }

    // handle command with param
    if (command == "setmin") 
    {
      currentMin = commandParam;
      Serial.print("Set min to: ");
      Serial.println(commandParam);
    }
    else if (command == "setmax") 
    {
      currentMax = commandParam;
      Serial.print("Set max to: ");
      Serial.println(commandParam);
    }
    else if (command == "setcurrent") 
    {
      currentPulse = commandParam;
      Serial.print("Set current pulse to: ");
      Serial.println(commandParam);
    }
    else if (command == "topulse") 
    {
      pwm.setPWM(0, 0, currentPulse);
      Serial.println("Moved to current pulselength");
    }
    else if (command == "sweep") 
    {
      Serial.println("Resetting servo position");
      pwm.setPWM(0, 0, currentMin);
      delay(1000);
      
      Serial.println("Starting sweep");
      for (uint16_t i = currentMin; i < currentMax; i++) 
      {
        pwm.setPWM(0, 0, i);
        delay(5);
      }
      Serial.println("Swept from min to max");
    }
  }
}
