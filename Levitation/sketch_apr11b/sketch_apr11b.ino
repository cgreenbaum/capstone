#define PWMA 3
#define DIRA 4
#define POSA 0
#define TOGGLE 8

#define CALIBRATION 59.55  // millimeters
#define REPEL   LOW
#define ATTRACT HIGH
#define READS 80

#define LEVITATION_TARGET 49.0 // 44.0mm   // 50.0
#define SAMPLEFREQ 120.0
#define MEMORY 1.0  // 2.0   // 3.0 
#define THRESHOLD 0.0
#define DELTA 20
#define BIAS 0

#define Kp 35.0     // 10    // 7.0
#define Ki 70.0     // 20   // 14.0
#define Kd 35.0     // 40   // 28.0

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


  if((distance - LEVITATION_TARGET) < -THRESHOLD)
    duty += DELTA;
  else if((distance - LEVITATION_TARGET) > THRESHOLD)
    duty -= DELTA;

  if(duty > 255)
    duty = 255;  
  else if(duty < -255)
    duty = -255;

  electromagnet(powerLookup(duty));

  Serial.print(distance - LEVITATION_TARGET);
  Serial.print(" ");
  Serial.print("D: ");
  Serial.print(distance);
  Serial.print(" ");
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

int powerLookup(float powerSetting)
{
  static int duty;
  static unsigned int index;
  const static int iLookup[201] = { -255, -254, -252, -251, -250, -249, -247, -246, -245, -244, -243, -242, -241, -239, -238, -237, -236, -234, -233, -232, -231, -229, -228, -227, -226, -225, -223, -222, -221, -219, -218, -217, -216, -214, -213, -212, -210, -209, -208, -207, -206, -204, -203, -202, -200, -199, -198, -197, -195, -194, -193, -192, -190, -189, -188, -187, -185, -184, -183, -182, -180, -179, -178, -176, -175, -174, -173, -171, -170, -169, -168, -166, -165, -164, -163, -161, -160, -159, -157, -156, -154, -152, -150, -147, -144, -141, -137, -132, -128, -122, -117, -111, -104, -97, -88, -77, -67, -54, -42, -26, 0, 26, 42, 56, 71, 80, 88, 97, 106, 111, 118, 123, 128, 132, 137, 141, 143, 146, 149, 152, 153, 155, 157, 158, 159, 161, 162, 163, 164, 166, 167, 168, 169, 170, 172, 173, 174, 175, 176, 178, 179, 180, 181, 183, 184, 185, 186, 187, 189, 190, 191, 192, 194, 195, 196, 197, 199, 200, 201, 203, 204, 205, 206, 207, 209, 210, 211, 213, 214, 215, 216, 218, 219, 220, 221, 223, 224, 225, 227, 228, 229, 230, 232, 233, 234, 236, 237, 238, 240, 241, 242, 244, 245, 246, 247, 249, 250, 251, 253, 254, 255 };

  if(powerSetting > 100)
    powerSetting = 100;
  else if(powerSetting < -100)
    powerSetting = -100;

  index = (100 + (int)powerSetting);

  return duty = iLookup[index];
}

