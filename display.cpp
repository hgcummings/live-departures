#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

#include "display.h"

static Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
static Adafruit_7segment numeric = Adafruit_7segment();

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

static int current_digit;

void display_arrivals_begin(const uint8_t icon[]) {
  matrix.clear();
  matrix.drawBitmap(0, 0, icon, 8, 8, LED_ON);
  matrix.writeDisplay();

  numeric.blinkRate(0);
  numeric.clear();
  current_digit = 0;
}

void display_arrivals_end() {
  numeric.writeDisplay();
}

void increment_current_digit() {
  if (current_digit == 1) {
    current_digit = 3;
  } else {
    current_digit += 1;
  }
}

bool can_display_arrival() {
  return current_digit <= 4;
}

void display_arrival(int minutes) {
  int tens = minutes / 10;
  if (tens > 0) {
    if (current_digit >= 4) {
      increment_current_digit();
      return;
    }

    numeric.writeDigitNum(current_digit, tens);
    increment_current_digit();
  }

  numeric.writeDigitNum(current_digit, minutes % 10, true);
  increment_current_digit();
}

