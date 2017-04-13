#define   LEVTESTSTART  100
#define   THRESHLIFT    2.0 // mm

int liftoff() {
  static float originalDistance;
  static int   levPower;

  levPower          = LEVTESTSTART;
  originalDistance  = readDistance();

  while( abs(originalDistance - readDistance()) < THRESHLIFT ) {
    electromagnetDrive(electromagnetLinearization(--levPower));
    delay(50);

    if(levPower < -100) {
      levPower = 6969;
      break;
    }
  }

  if(PRINTDIAGNOSTICS) {
    Serial.println("Liftoff at: ");
    Serial.print(  "Levpower = "); Serial.println(levPower);
    Serial.print(  "Duty     = "); Serial.println(electromagnetLinearization(levPower));
  }

  return levPower;
}
