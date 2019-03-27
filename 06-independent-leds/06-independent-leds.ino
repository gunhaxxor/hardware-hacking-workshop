// basic example to show how we can "fake" asynchronous algorithms where things happen independently of each other.
// this example make use of the millis() function, which returns elapsed milliseconds since the device was powered on.
// we then use "timestamps" to keep track of when the leds toggles, and can from that then determine when they should toggle again.

// the thinking behind the method is as follows:
// how long time since we previously toggled the led? Is it more than the interval we have chosen? 
// If so, then toggle the led. Also, set current time as the "timestamp".


unsigned long led1Stamp = 0;
unsigned long led1Interval = 500;


unsigned long led2Stamp = 0;
unsigned long led2Interval = 510;

int led1Pin = 11, led2Pin = 12;

void setup () {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  
}

void loop () {
  if(millis() - led1Stamp > led1Interval){
    led1Stamp = millis();

    digitalWrite(led1Pin, !digitalRead(led1Pin));
  }

  if(millis() - led2Stamp > led2Interval){
    led2Stamp = millis();

    digitalWrite(led2Pin, !digitalRead(led2Pin));
  }

}