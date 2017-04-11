#define PWMA 3
#define DIRA 4
#define POSA 0
#define TOGGLE 8

#define CALIBRATION 59.55  // millimeters
#define REPEL LOW
#define READS 80

#define LEVITATION_TARGET 30.0 // 25-39mm
#define SAMPLEFREQ 120.0
#define MEMORY 1.0
#define THRESHOLD 0.5
#define DELTA 15
#define BIAS 180

#define Kp 15.0
#define Ki 80.0
#define Kd 40.0

#define KpSTART 8
#define KpMAX 30
#define KdSTART 20
#define KdMAX 60

void setup() {
  // put your setup code here, to run once:
  pinMode(PWMA, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(TOGGLE, OUTPUT);
  Serial.begin(115200);
  Serial.setTimeout(250);
}

void loop() {
  // put your main code here, to run repeatedly:
  static long duty = 0;
  static float distance = 0;
  static float lastDistance = 0;
  static float integrator = 0;
  static float dutyKp, dutyKi, dutyKd;
  static bool flipflop = false;
  static long i = 0;

  digitalWrite(TOGGLE, HIGH);

  lastDistance = distance;
  distance = readDistance();

  flipflop = !flipflop;
  digitalWrite(TOGGLE, LOW);

  dutyKp   = (distance - LEVITATION_TARGET)*Kp;
  dutyKd   = (distance - lastDistance)*Kd;
  integrator += (distance - LEVITATION_TARGET)/SAMPLEFREQ;

  if(integrator > MEMORY)
    integrator = MEMORY;
  else if(integrator < -MEMORY)
    integrator = -MEMORY;
  
  dutyKi  = integrator*Ki;

/*
  if((distance - LEVITATION_TARGET) > THRESHOLD)
    duty += DELTA;
  else if((distance - LEVITATION_TARGET) < THRESHOLD)
    duty -= DELTA;
*/

  duty = dutyKp + dutyKi + dutyKd + BIAS;

  if(duty > 255)
    duty = 255;
  else if(duty < 0)
    duty = 0;


  electromagnet((int)duty);

  Serial.print(distance - LEVITATION_TARGET);
  Serial.print(" ");
  Serial.print("D: ");
  Serial.print(distance);
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
  Serial.print("d%: ");
  Serial.println(duty);

}


void printStats() {
}


void electromagnet(int duty) {
  digitalWrite(DIRA, REPEL);
  analogWrite(PWMA, duty);
}

float readDistance() {
  static float distance, accumulator;

  accumulator = 0;
  for(int i=0; i<READS; i++) {
    distance = CALIBRATION / (5.0/1024.0*analogRead(POSA));
    accumulator += distance;
  }

  distance = accumulator / READS;

//  distance = CALIBRATION / (5.0/1024.0*analogRead(POSA));

  return distance;
}
