int sensorValue;

void setup () {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop () {

  sensorValue = analogRead(A0);

  Serial.printf("sensorValue: %i \n", sensorValue);

  delay(50);
}