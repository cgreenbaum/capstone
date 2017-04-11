#define PWMA 3
#define DIRA 4
#define POSA 0
#define TOGGLE 8

#define CALIBRATION 59.55  // millimeters
#define REPEL   LOW
#define ATTRACT HIGH
#define READS 80

#define LEVITATION_TARGET 33.0 // 28-36mm
#define SAMPLEFREQ 120.0
#define MEMORY 3.0
#define THRESHOLD 0.5
#define DELTA 15
#define BIAS 180
#define THRESHLIFT 1.0
#define LEVTESTSTART 255

#define Kp 40.0
#define Ki 20.0
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
  static int neutralBduty = 0;
  
  neutralBduty = liftoff();

  electromagnet(255);

  Serial.print("neutralBduty: ");
  Serial.println(neutralBduty);
  delay(10000);
}

int liftoff() {
  static float originalDistance;
  static int   levPower;

  originalDistance = 0;
  levPower = LEVTESTSTART;

  originalDistance = readDistance();

  while( (readDistance() - originalDistance) < THRESHLIFT ) {
    electromagnet(--levPower);
    delay(50);

    if(levPower < -255) {
      levPower = 6969;
      break;
    }
  }

  return levPower;
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
