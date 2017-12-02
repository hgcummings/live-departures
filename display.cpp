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
