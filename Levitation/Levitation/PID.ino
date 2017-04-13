float controller(float distance) {
  static float  lastDistance = 0;
  static float  integrator = 0;
  static float  dutyKp, dutyKi, dutyKd;
  static float  hError = 0;
  static float  controlvalue = 0;
  static long   levPower = 0;
  
  if(distance > LEVITATION_TARGET)
    hError =  pow((distance - LEVITATION_TARGET), 2);
  else  
    hError = -pow((distance - LEVITATION_TARGET), 2);

  dutyKp   = hError*Kp;
  dutyKd   = (distance - lastDistance)*Kd;
  integrator += hError/SAMPLEFREQ;

  if(integrator > MEMORY)
    integrator = MEMORY;
  else if(integrator < -MEMORY)
    integrator = -MEMORY;
  
  dutyKi  = integrator*Ki;

  controlvalue = dutyKp + dutyKi + dutyKd + CONTROLBIAS;

  if(PIDSTATS) {
    Serial.print("dH: ");
    Serial.print(distance - LEVITATION_TARGET);
    Serial.print(" ");
    Serial.print("dKp: ");
    Serial.print(dutyKp);
    Serial.print(" ");
    Serial.print("dKi: ");
    Serial.print(dutyKi);
    Serial.print(" ");
    Serial.print("dKd: ");
    Serial.print(dutyKd);
    Serial.print(" ");
  }
  
  lastDistance = distance;

  return controlvalue;
}

void accumulatorcode() {
  /*
  if((distance - LEVITATION_TARGET) < -THRESHOLD)
    accumulator += DELTA;
  else if((distance - LEVITATION_TARGET) > THRESHOLD)
    accumulator -= DELTA;


  if(accumulator > 255)
    accumulator = 255;
  else if(accumulator < -255)
    accumulator = -255;
*/
}

