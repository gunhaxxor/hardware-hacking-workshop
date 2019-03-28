#include <WiFi.h>
#include <Wire.h>
#include "FirebaseESP32.h"

#define FIREBASE_HOST "esp-fun-playtime.firebaseio.com"
#define FIREBASE_AUTH "v7w3CAI9vOrCmCgrESn9meKc0apDsK7ZLM7hLo3C"




////Sätt en egen path här så ni inte skriver till samma nod i databas-trädet
#define FIREBASE_PATH "/coolio/button/1"
#define WIFI_SSID "Interactive Guest"
#define WIFI_PASSWORD "notsosafe"

FirebaseData firebaseData;

void setup() {
    Serial.begin(9600);

    Serial.println("WiFi: Init..");

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("WiFi: Connecting");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("WiFi: Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println("WiFi: Done!");

    Serial.println("------------------------------------");

    Serial.println("Firebase: Init");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);
}

bool state = false;
void loop() {
  if(state){
    Firebase.setString(firebaseData, FIREBASE_PATH, "true");
  } else {
    Firebase.setString(firebaseData, FIREBASE_PATH, "false");
  }
  delay(1000);

  state = !state;
}