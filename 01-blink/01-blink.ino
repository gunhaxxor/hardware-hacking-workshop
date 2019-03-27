//Gunnar är bäst

void setup () {

  // configure the pin to be an output. different microcontrollers have the onboard led on different pins. 
  // LED_BUILTIN is a way to refer to that pin, regardless of microcontroller. 
  // For teensy and most arduinos that is pin 13.
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {

  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  
}