#include <espbase.h>
#include "display.h"

U8G2_MAX7219_64X8_F_4W_SW_SPI u8g2(
    /* rotation */ U8G2_R0, // no rotation
    /* clock */ D5,
    /* data */ D7,
    /* cs */ D4,
    /* dc */ U8X8_PIN_NONE
);

void setupDisplay() {
    u8g2.begin();
    u8g2.setContrast(LED_DEFAULT_BRIGHTNESS);
    u8g2.setFont(u8g2_font_5x7_tf);
}

Setting brightnessSetting(
    "brightness",
    [](JsonVariant& value) {
        value.set(LED_DEFAULT_BRIGHTNESS);
    },
    [](JsonVariant value) {
        int brightness = constrain(value.as<int>(), 0, 255);
        u8g2.setContrast(brightness);
        return true;
    }
);
