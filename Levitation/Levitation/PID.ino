#define LEVITATION_TARGET   50.0  // 44.0mm   // 50.0

#define SAMPLEFREQ 300.0

#define MEMORY        100.0         // 2.0   // 3.0 
#define THRESHOLD     0.25
#define DELTA         0.15
#define CONTROLBIAS   -8.0

#define KP  00.0       // -12           
#define KI  00.0       // -15           
#define KD  -10.0      // -150

#define ADJUST_UPPER 0.0
#define ADJUST_LOWER  -80.0

float controller(float distance) {
  static float  lastDistance = 0;
  static float  integrator = 0;
  static float  dutyKp, dutyKi, dutyKd;
  static float  Kp, Kd, Ki, bias, adjust = 0;
  static float  hError = 0;
  static float  controlvalue = 0;
  static long   levPower = 0;
  /*
  if(distance > LEVITATION_TARGET)
    hError =  pow((distance - LEVITATION_TARGET), 2);
  else  
    hError = -pow((distance - LEVITATION_TARGET), 2);
  */

  bias = CONTROLBIAS;
  Kp = KP;
  Ki = KI;
  Kd = KD;

  hError   = distance - LEVITATION_TARGET;

  dutyKp   = hError*Kp;
  dutyKd   = (distance - lastDistance)*Kd;
  integrator += hError/SAMPLEFREQ;

  if(integrator > MEMORY)
    integrator = MEMORY;
  else if(integrator < -MEMORY)
    integrator = -MEMORY;
  
  dutyKi  = integrator*Ki;

  controlvalue = dutyKp + dutyKi + dutyKd + bias;

  if(PRINTDIAGNOSTICS & PIDSTATS) {
    adjust = ADJUST_LOWER + (ADJUST_UPPER-ADJUST_LOWER)*(analogRead(1)/1024.0);
    
    Serial.print("Kp: ");
    Serial.print(Kp);
    Serial.print(" ");    
    Serial.print("Ki: ");
    Serial.print(Ki);
    Serial.print(" ");    
    Serial.print("Kd: ");
    Serial.print(Kd);
    Serial.print(" "); 
    Serial.print("Bias: ");
    Serial.print(bias);
    Serial.print(" ");    
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

