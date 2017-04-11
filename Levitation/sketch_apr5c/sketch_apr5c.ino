#define PWMA 3
#define DIRA 4
#define POSA 0
#define TOGGLE 8

#define CALIBRATION 59.55  // millimeters
#define REPEL   LOW
#define ATTRACT HIGH
#define READS 80

#define LEVITATION_TARGET 44.0 // 28-36mm
#define SAMPLEFREQ 120.0
#define MEMORY 1.0
#define THRESHOLD 0.5
#define DELTA 15
#define BIAS -110

#define Kp 120.0
#define Ki 0.0
#define Kd 0.0

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
  static long setting1, setting2;
  if(setting1 = Serial.parseInt())
    setting2 = setting1;
  electromagnet(setting2);
  delay(100);
}


void printStats() {
}


void electromagnet(int duty) {
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

  Serial.println(duty);
  
  digitalWrite(DIRA, magPol);
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
