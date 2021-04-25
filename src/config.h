#pragma once

#include "secrets.h"

#define HOSTNAME "ledmatrix"

#define UDP_PORT 1337
#define UDP_MAX_PACKET_SIZE 200

#define LED_WIDTH 64
#define LED_HEIGHT 8

#define LED_DEFAULT_BRIGHTNESS 255

// Maximum length of text message.
#define TEXT_MAX_SIZE 128

// Milliseconds to wait before continuing scrolling at start and end.
#define TEXT_DEFAULT_SCROLL_WAIT 1000 // milliseconds

#define TEXT_DEFAULT_SCROLL_SPEED 100 // milliseconds per pixel

// Milliseconds to show text. -1 = infinite.
#define TEXT_DEFAULT_SHOW_TIME 5000
