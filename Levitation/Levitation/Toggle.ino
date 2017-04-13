void toggle() {
  static bool flipflop;
  if(flipflop)
    digitalWrite(TOGGLEPIN, HIGH);
  else
    digitalWrite(TOGGLEPIN, LOW);
  flipflop = !flipflop;
}
