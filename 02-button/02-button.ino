
//Gunnar är bäst

volatile int counter = 0;
void setup (){
  //pullup means that the pin internally gets connected to HIGH through a 20Mohm resistor.
  //The button should then get connected between the pin and GND.
  //This means that digitalRead returns LOW (GND) when the button is pressed.
  pinMode(0, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if(!digitalRead(0)) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }  
}
