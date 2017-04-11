#define PWMA 3
#define DIRA 4
#define POSA 0
#define TOGGLE 8

#define CALIBRATION 59.55  // millimeters
#define REPEL LOW

#define LEVITATION_TARGET 50.0
#define SAMPLEFREQ 120.0
#define MEMORY 5.0
#define THRESHOLD 0.5
#define DELTA 15

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
  static float kp = KpSTART;
  static float kd = KdSTART;
  static bool flipflop = false;
  static long i = 0;

  if(i++ > 300) {
    kp += 5;
    i = 0;
  }
  if(kp > KpMAX){
    kp  = KpSTART;
    kd += 5;
    if(kd > KdMAX) {
      electromagnet(0);
      while(1);
    }
  }
  

  flipflop = !flipflop;
  digitalWrite(TOGGLE, flipflop);

  lastDistance = distance;
  distance = readDistance();

  duty    = (distance - LEVITATION_TARGET)*kp;
  duty   += (distance - lastDistance)*kd;
  integrator += (distance - LEVITATION_TARGET)/SAMPLEFREQ;

  if(integrator > MEMORY)
    integrator = MEMORY;
  else if(integrator < -MEMORY)
    integrator = -MEMORY;
  
  duty  += integrator*Ki;

/*
  if((distance - LEVITATION_TARGET) > THRESHOLD)
    duty += DELTA;
  else if((distance - LEVITATION_TARGET) < THRESHOLD)
    duty -= DELTA;
*/
  if(duty > 255)
    duty = 255;
  else if(duty < 0)
    duty = 0;


  electromagnet((int)duty);

  delay(12);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(",");
  Serial.print(kp);
  Serial.print(",");
  Serial.print(kd);
  Serial.print(",");
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
  for(int i=0; i<45; i++) {
    distance = CALIBRATION / (5.0/1024.0*analogRead(POSA));
    accumulator += distance;
  }

  distance = accumulator / 45.0;

//  distance = CALIBRATION / (5.0/1024.0*analogRead(POSA));

  return distance;
}
