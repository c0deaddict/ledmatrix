#include <espbase.h>
#include "display.h"
#include "text.h"

bool showing = false;
bool scrolling = false;
char text[TEXT_MAX_SIZE] = {0, };
unsigned int offset;
unsigned int width;
unsigned int scrollWait = TEXT_DEFAULT_SCROLL_WAIT;
unsigned int scrollSpeed = TEXT_DEFAULT_SCROLL_SPEED;
int showTime;
int defaultShowTime = TEXT_DEFAULT_SHOW_TIME;
unsigned long lastScrollTick;
unsigned long showStartedTime;

void redrawText() {
    u8g2.clearBuffer();
    u8g2.drawStr(1 - offset, 7, text);
    u8g2.sendBuffer();

    lastScrollTick = millis();
}

void handlePostMessage(AsyncWebServerRequest *request) {
    const char *newText = request->getParam("text", true)->value().c_str();
    strncpy(text, newText, TEXT_MAX_SIZE-1);

    if (request->hasParam("showTime", true)) {
        showTime = request->getParam("showTime", true)->value().toInt();
        if (showTime < -1 || showTime == 0) {
            showTime = defaultShowTime;
        }
    } else {
        showTime = defaultShowTime;
    }

    width = u8g2.getStrWidth(text);
    scrolling = width > LED_WIDTH;
    offset = 0;
    showStartedTime = millis();
    showing = true;

    redrawText();

    request->send(200, "text/plain", "Ok");
}

void stopText() {
    showing = false;
    scrolling = false;
    u8g2.clearBuffer();
    u8g2.sendBuffer();
}

// Returns true if text is allowed to be reset, false otherwise.
bool resetText() {
    if (!showing) {
        return true;
    } else if (showTime == -1) {
        stopText();
        return true;
    } else {
        return false;
    }
}

void textLoop() {
    if (showing && showTime != -1) {
        // Explicit unsigned long to handle overflows of millis().
        unsigned long elapsed = millis() - showStartedTime;
        if (elapsed >= (unsigned long)showTime) {
            stopText();
        }
    }

    if (scrolling) {
        unsigned long elapsed = millis() - lastScrollTick;
        if (offset == 0) {
            if (elapsed >= scrollWait) {
                redrawText();
                offset++;
            }
        } else if (offset == width - LED_WIDTH + 2) {
            if (elapsed >= scrollWait) {
                redrawText();
                offset = 0;
            }
        } else if (elapsed >= scrollSpeed) {
            offset++;
            redrawText();
        }
    }
}

Setting scrollWaitSetting(
    "scrollWait",
    [](JsonVariant& value) {
        value.set(scrollWait);
    },
    [](JsonVariant value) {
        int wait = value.as<int>();
        if (wait >= 0 && wait <= 5000) {
            scrollWait = wait;
            return true;
        } else {
            return false;
        }
    }
);

Setting scrollSpeedSetting(
    "scrollSpeed",
    [](JsonVariant& value) {
        value.set(scrollSpeed);
    },
    [](JsonVariant value) {
        int speed = value.as<int>();
        if (speed >= 20 && speed <= 1000) {
            scrollSpeed = speed;
            return true;
        } else {
            return false;
        }
    }
);

Setting defaultShowTimeSetting(
    "showTime",
    [](JsonVariant& value) {
        value.set(defaultShowTime);
    },
    [](JsonVariant value) {
        int time = value.as<int>();
        if (time == -1 || time > 0) {
            defaultShowTime = time;
            return true;
        } else {
            return false;
        }
    }
);
