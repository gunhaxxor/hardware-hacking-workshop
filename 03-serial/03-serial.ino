//Gunnar är bäst

int counter = 0;
void setup (){
  //pullup means that the pin internally gets connected to HIGH through a 20Mohm resistor.
  //The button should then get connected between the pin and GND.
  //This means that digitalRead returns LOW (GND) when the button is pressed.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  counter++;
  Serial.print("counter is: ");
  Serial.println(counter);

  // Serial.printf("counter is: %i \n", counter);

  delay(20);
}
