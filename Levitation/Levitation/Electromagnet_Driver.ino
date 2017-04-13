void electromagnetDrive(int duty) {
  static bool magPol = REPEL;
  Serial.print("d%: ");
  if(duty < 0) {
    duty = -duty;
    magPol = ATTRACT;
    Serial.print("-");
  }
  else {
    magPol = REPEL;
    Serial.print("+");
  }

  if(duty > 255)
    duty = 255;
  else if(duty < 0)
    duty = 0;

  Serial.print(duty);
  
  digitalWrite(DIRA, magPol);
  analogWrite(PWMA, duty);
}
