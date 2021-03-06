#define CALIBRATION 59.55 // millimeters
#define READS 5

float readDistance() {
  static float distance, accumulator;

  accumulator = 0;
  for(int i=0; i<READS; i++) {
    distance = CALIBRATION / (5.0/1024.0*analogRead(POSA));
    accumulator += distance;
  }

  distance = accumulator / READS;
  if(PRINTDIAGNOSTICS & SENSORSTATS) {
    Serial.print("D: ");
    Serial.print(distance);
    Serial.print(" ");
  }

  return distance;
}
