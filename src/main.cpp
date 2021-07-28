#include <espbase.h>
#include "display.h"
#include "text.h"
#include "udp.h"

void setup(void) {
    Serial.begin(115200);

    http.on("/message", HTTP_POST, handlePostMessage);

    setupDisplay();
    setupEspbase();
    setupUdp();
}

void loop() {
    handleEspbase();
    handleUdp();
    textLoop();
}

void stop() {
}
