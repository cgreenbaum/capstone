// Pin definitions
#define TOGGLEPIN 8      // TOGGLEPIN specifies the pin to toggle each time through the main loop of the program
#define PWMA 3
#define DIRA 4
#define POSA 0

#define PRINTDIAGNOSTICS 1
  #define MAGNETSTATS 1
  #define PIDSTATS    1
  #define SENSORSTATS 1

// Function prototypes
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
  toggle();

  levitationRoutine();
//  liftoff();
  Serial.println("");
}

void levitationRoutine()
{
  // define variables
  static float  controlvalue    = 0;
  static float  distance        = 0;
  
  distance      = readDistance();
  controlvalue  = controller(distance);
  electromagnetDrive(electromagnetLinearization(controlvalue));
}

