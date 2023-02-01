/*
// Move function
void moveServo(int sV, ESP32Servo servo) {
  //.. MOVE SERVO IN DIRECTION
  if (sV < cur) {
    //move forwards (++)
    for (int i = cur; i <= sV; i++) {
      servo.write(i);
      delay(15);
    }
  }
  else if (sV > cur) {
    // move backwards (--)
    for (int i = cur; i >= sV; i--) {
      servo.write(i);
      delay(15);
    }
  }

  servo.write(sV);
  delay(200); // temp delay
  requestOngoing = false;
}*/

// Calibration move funciton
void tbMoveServo(int des) {
  //.. DEBUG STATEMENT
  Serial.println("request received");

  //.. TEST INFORMATION
  int cur = testServo.read();
  Serial.println(String(des) + " :: " + String(cur));

  //.. MOVE SERVO IN DIRECTION
  //.. debug: MathTest.js: https://codehs.com/sandbox/karelseviltwin/mathtest
  if (des > cur) {
    //move forwards (++)
    Serial.println("action: moving forwards");
    for (int i = cur; i <= des; i++) {
      testServo.write(i);
      Serial.println("wrote iteration: opt a");
      delay(15);
    }
  }
  else if (des < cur) {
    // move backwards (--)
    Serial.println("action: moving backwards");
    for (int i = cur; i >= des; i--) {
      testServo.write(i);
      Serial.println("wrote iteration: opt b");
      delay(15);
    }
  }

  Serial.println("--------");

  testServo.write(des);
  delay(200); // <- TEMPORARY DELAY
  requestOngoing = false;
}