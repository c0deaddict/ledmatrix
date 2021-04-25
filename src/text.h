#pragma once

void handlePostMessage(AsyncWebServerRequest *request);
void setText(const char *newText);
bool resetText();
void textLoop();
