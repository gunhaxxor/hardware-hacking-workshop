//Gunnar är bäst

int counter = 0;
void setup (){
  Serial.begin(9600);
}

void loop() {
  counter++;
  Serial.print("counter is: ");
  Serial.println(counter);

  //Teensy boards also have support for printf, which is pretty convenient:
  // Serial.printf("counter is: %i \n", counter);

  delay(20);
}
