#pragma once
#include <Adafruit_SSD1306.h>

class ScrollableText {
private:
  int y, x = 0;
  int inc = 10;
  int sep = 10;
  char** text;
  int size;
  int length;

public:
  ScrollableText(char** text, int y, int size)
    : y(y), text(text), size(size) {}

  void render(Adafruit_SSD1306& display)
  {
    x += inc;
    if (x >= 128 + (length + 10) * size) x = 0;

    if (*text == nullptr) return;
    length = strlen(*text);
    Serial.println(length);
    display.setCursor(x - (length + 10) * size, y);
    display.print(*text);
  }
};