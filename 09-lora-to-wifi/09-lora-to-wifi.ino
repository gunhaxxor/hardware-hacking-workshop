#include <LoRa.h>
#include <SPI.h>
#include <WiFi.h>
#include <Wire.h>
#include "FirebaseESP32.h"
#include "SSD1306.h"

#define FIREBASE_HOST "esp-fun-playtime.firebaseio.com"
#define FIREBASE_AUTH "v7w3CAI9vOrCmCgrESn9meKc0apDsK7ZLM7hLo3C"
#define FIREBASE_PATH "/ESP32_Test/button/1"
#define WIFI_SSID "Interactive"
#define WIFI_PASSWORD "wecanbuildit"

#define SCK 5    // GPIO5  -- SX1278's SCK
#define MISO 19  // GPIO19 -- SX1278's MISO
#define MOSI 27  // GPIO27 -- SX1278's MOSI
#define SS 18    // GPIO18 -- SX1278's CS
#define RST 23   // GPIO14 -- SX1278's RESET
#define DI0 26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND 433E6

SPIClass spiLora(HSPI);
FirebaseData firebaseData;
SSD1306 display(0x3c, 21, 22);

void setup() {
    Serial.begin(9600);

    display.init();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);
    display.clear();

    Serial.println("LoRa: Init..");
    spiLora.begin(SCK, MISO, MOSI, SS);
    LoRa.setPins(SS, RST, DI0);
    LoRa.setSPI(spiLora);
    if (!LoRa.begin(BAND)) {
        Serial.println("LoRa: Setup failed!");
    }
    LoRa.receive();
    Serial.println("LoRa: Done!");

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

    Serial.println("Firebase: Start streaming..");
    Firebase.setStreamCallback(firebaseData, streamCallback,
                               streamTimeoutCallback);

    if (Firebase.beginStream(firebaseData, FIREBASE_PATH)) {
        Serial.println("Firebase: Streaming started!");
    } else {
        Serial.print("Firebase: ") Serial.println(firebaseData.errorReason());
    }
}

void onReceiv(int packetSize) {
    Serial.println(packetSize);
    while (LoRa.available()) {
        Serial.print((char)LoRa.read());
    }

    Serial.println(LoRa.packetRssi());
}

void streamCallback(StreamData data) { printOled(data.stringData()); }

void printOled(String data) {
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, data);
    display.display();
}

void loop() {
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        onReceiv(packetSize);
    }
}

void streamTimeoutCallback(bool timeout) {
    if (timeout) {
        Serial.println("Stream timeout, resume streaming...");
    }
}