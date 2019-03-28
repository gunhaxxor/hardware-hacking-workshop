#include <Wire.h>
#include <LoRa.h>
#include <SPI.h>

#define SCK 5    // GPIO5  -- SX1278's SCK
#define MISO 19  // GPIO19 -- SX1278's MISnO
#define MOSI 27  // GPIO27 -- SX1278's MOSI
#define SS 18    // GPIO18 -- SX1278's CS
#define RST 23   // GPIO14 -- SX1278's RESET
#define DI0 26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND 433E6

SPIClass spiLora(HSPI);

void setup() {
    pinMode(39, INPUT);

    Serial.begin(9600);

    Serial.println();
    Serial.println("LoRa Sender Test");

    Serial.println("LoRa: Init..");
    spiLora.begin(SCK, MISO, MOSI, SS);
    LoRa.setPins(SS, RST, DI0);
    LoRa.setSPI(spiLora);
    if (!LoRa.begin(BAND)) {
        Serial.println("LoRa: Setup failed!");
    }
    LoRa.receive();
    Serial.println("LoRa: Done!");

    delay(1500);
}

bool prevButtonState = 0;
bool buttonStateChanged = false;

void loop() {
    int buttonState = digitalRead(39);
    if (prevButtonState != buttonState) {
        prevButtonState = buttonState;
        buttonStateChanged = true;
    }

    if (buttonStateChanged) {
        if (LoRa.beginPacket() == 1) {
            if (buttonState == 0) {
                LoRa.print("Button is pressed");
            } else {
                LoRa.print("Button is not\npressed");
            }
            LoRa.endPacket();
        } else {
            Serial.println("Cannot send package!");
        }
        buttonStateChanged = false;
    }

    delay(10);
}