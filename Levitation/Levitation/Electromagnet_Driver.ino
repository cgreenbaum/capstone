#define REPEL   LOW
#define ATTRACT HIGH

void electromagnetDrive(int duty) {
  static bool magPol = REPEL;
  
  if(PRINTDIAGNOSTICS & MAGNETSTATS) {
    Serial.print("d%: ");
//    analogWrite(10, 128 + 0.5*duty);
  }
  
  if(duty < 0) {
    duty = -duty;
    magPol = ATTRACT;
    if(PRINTDIAGNOSTICS & MAGNETSTATS)
      Serial.print("-");
  }
  else {
    magPol = REPEL;
    if(PRINTDIAGNOSTICS & MAGNETSTATS)
      Serial.print("+");
  }

  if(duty > 255)
    duty = 255;
  else if(duty < 0)
    duty = 0;
  
  if(PRINTDIAGNOSTICS & MAGNETSTATS)
    Serial.print(duty);
  
  digitalWrite(DIRA, magPol);
  analogWrite(PWMA, duty);
}
