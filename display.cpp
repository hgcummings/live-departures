#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

#include "display.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
Adafruit_7segment numeric = Adafruit_7segment();

int increment_digit(int digit) {
  if (digit == 1) {
    return 3;
  } else {
    return digit + 1;
  }
}

void display_init() {
  matrix.begin(0x70);
  matrix.clear();
  numeric.begin(0x74);
  numeric.clear();
}

void display_loading(const uint8_t icon[]) {
  matrix.drawBitmap(0, 0, icon, 8, 8, LED_ON);
  matrix.writeDisplay();

  numeric.blinkRate(1);
  numeric.drawColon(true);
  numeric.writeDisplay();
}

