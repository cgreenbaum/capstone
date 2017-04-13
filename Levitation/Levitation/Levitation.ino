// Pin definitions
#define TOGGLEPIN 8      // TOGGLEPIN specifies the pin to toggle each time through the main loop of the program

#define MAGNETSTATS 1
#define PIDSTATS    1
#define SENSORSTATS 1

#define PWMA 3
#define DIRA 4
#define POSA 0

#define REPEL   LOW
#define ATTRACT HIGH

#define SAMPLEFREQ 120.0

#define LEVITATION_TARGET   49.0  // 44.0mm   // 50.0

#define MEMORY        2.0         // 2.0   // 3.0 
#define THRESHOLD     0.25
#define DELTA         0.15
#define CONTROLBIAS   33

#define Kp  -1.0                  // 10    // 7.0
#define Ki  -5.0                  // 20   // 14.0
#define Kd  -10.0                 // 40   // 28.0

#define CALIBRATION 59.55 // millimeters

#define READS 80

void  toggle();
float readDistance();
int   electromagnetLinearization(float powerSetting);
void  electromagnetDrive(int duty);
float controller(float distance);

void setup() {
  // Initialize pins for electromagnet driver
  pinMode(PWMA, OUTPUT);
  pinMode(DIRA, OUTPUT);

  // Initialize the toggle pin
  pinMode(TOGGLEPIN, OUTPUT);

  // Open serial port
  Serial.begin(115200);
  Serial.setTimeout(250);
}

void loop() {
  // define variables
  static float  controlvalue    = 0;
  static float  distance        = 0;

  toggle();
  distance      = readDistance();
  controlvalue  = controller(distance);
  electromagnetDrive(electromagnetLinearization(controlvalue));
}

