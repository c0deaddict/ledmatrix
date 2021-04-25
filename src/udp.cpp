#include <espbase.h>
#include "display.h"
#include "text.h"

WiFiUDP udpSocket;
byte packetBuffer[UDP_MAX_PACKET_SIZE];

void setupUdp() {
    if (udpSocket.begin(UDP_PORT) != 1) {
        Serial.printf("Failed to start UDP socket on port %d\n\r", UDP_PORT);
    }
}

void handleUdp() {
    int packetSize = udpSocket.parsePacket();
    if (packetSize) {
        int len = udpSocket.read(packetBuffer, sizeof(packetBuffer));
        if (len == LED_WIDTH*LED_HEIGHT/8) {
            if (resetText()) {
                u8g2.drawXBM(0, 0, LED_WIDTH, LED_HEIGHT, packetBuffer);
                u8g2.sendBuffer();
            }
        }
    }
}

