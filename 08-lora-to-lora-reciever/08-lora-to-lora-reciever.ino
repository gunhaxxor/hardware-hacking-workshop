#include <LoRa.h>
#include <SPI.h>
#include <Wire.h>
#include "SSD1306.h"

#define SCK 5    // GPIO5  -- SX1278's SCK
#define MISO 19  // GPIO19 -- SX1278's MISO
#define MOSI 27  // GPIO27 -- SX1278's MOSI
#define SS 18    // GPIO18 -- SX1278's CS
#define RST 23   // GPIO14 -- SX1278's RESET
#define DI0 26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND 433E6

SPIClass spiLora(HSPI);
SSD1306 display(0x3c, 21, 22);

void setup() {
    Serial.begin(9600);

    display.init();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_16);
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
}

void onReceiv(int packetSize) {
    String msg = "";
    while (LoRa.available()) {
        msg += (char) LoRa.read();
        delay(1);
    }

    printOled(msg);
}

void printOled(String data) {
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(0, 0, data);
    display.display();
}

void loop() {
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        onReceiv(packetSize);
    }
}
