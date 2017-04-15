#define   LEVTESTSTART  100
#define   THRESHLIFT    2.0 // mm

int liftoff() {
  static float originalDistance;
  static int   levPower;

  Serial.println("Starting Offblast Test....");

  levPower          = LEVTESTSTART;
  originalDistance  = readDistance();

  while( abs(originalDistance - readDistance()) < THRESHLIFT ) {
    electromagnetDrive(electromagnetLinearization(--levPower));
    Serial.println("");
    delay(50);

    if(levPower < -100) {
      levPower = 6969;
      break;
    }
  }

  electromagnetDrive(255);

  if(PRINTDIAGNOSTICS) {
    Serial.println(""); 
    Serial.println("Offblast at: ");
    Serial.print(  "Levpower = "); Serial.println(levPower);
    Serial.print(  "Duty     = "); Serial.println(electromagnetLinearization(levPower));
  }
  
  delay(10000);

  return levPower;
}
