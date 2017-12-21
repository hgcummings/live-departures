#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

#include "display.h"
#include "math.h"

static Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
static Adafruit_7segment numeric = Adafruit_7segment();

void display_init() {
  matrix.begin(0x70);
  numeric.begin(0x74);
  display_clear();
}

void display_clear() {
  matrix.clear();
  numeric.clear();
  matrix.writeDisplay();
  numeric.writeDisplay();
}

void display_spinner(const uint8_t icon[]) {
  matrix.setBrightness(15);
  matrix.drawBitmap(0, 0, icon, 8, 8, LED_ON);
  matrix.writeDisplay();

  numeric.clear();
  numeric.writeDisplay();
}

static int spinner_frame = 0;

void display_spinner_animate() {
  matrix.setBrightness(abs(spinner_frame - 14));
  numeric.writeDigitRaw(1, 1 << (spinner_frame % 6));
  numeric.writeDisplay();
  spinner_frame = (spinner_frame + 1) % 30;
}

void display_error() {
  matrix.clear();
  numeric.clear();

  numeric.writeDigitRaw(0, 121);
  numeric.writeDigitRaw(1, 80);
  numeric.writeDigitRaw(3, 80);
  numeric.blinkRate(2);

  matrix.writeDisplay();
  numeric.writeDisplay();
}

static const int VIEWABLE_DIGITS = 3;
static int arrivals[VIEWABLE_DIGITS];
static int arrivals_count;

void display_arrivals_begin(const uint8_t icon[]) {
  matrix.clear();
  matrix.setBrightness(15);
  matrix.drawBitmap(0, 0, icon, 8, 8, LED_ON);
  matrix.writeDisplay();

  numeric.clear();
  numeric.writeDisplay();

  memset(arrivals, -1, sizeof arrivals);
  arrivals_count = 0;
}

bool can_display_arrival() {
  return arrivals_count < VIEWABLE_DIGITS;
}

void display_arrival(int minutes) {
  arrivals[arrivals_count] = minutes;
  arrivals_count += 1;
}

/**
 * The 'digit' at index 3 of the display is actually the colon
 */
int get_display_digit(int digit_index) {
  if (digit_index > 1) {
    return digit_index +1;
  } else {
    return digit_index;
  }
}

void display_arrivals_end() {
  if (arrivals_count > 0) {
    int digit_index = 0;
    for (int arrival_index = 0; arrival_index < arrivals_count; ++arrival_index) {
      int arrival = arrivals[arrival_index];
      if (digit_index < VIEWABLE_DIGITS - 1) {
        if (arrival > 10) {
          numeric.writeDigitNum(get_display_digit(digit_index), arrival / 10);
          digit_index += 1;
          numeric.writeDigitNum(get_display_digit(digit_index), arrival % 10, true);
          digit_index += 1;
        } else if (arrival_index == arrivals_count - 1 ||
                    (digit_index == VIEWABLE_DIGITS - 2 && arrivals[arrival_index + 1] > 10)) {
          digit_index += 1;
        }
      }
      if (digit_index < VIEWABLE_DIGITS && arrival < 10) {
        numeric.writeDigitNum(get_display_digit(digit_index), arrival, true);
        digit_index += 1;
      }
    }
  } else {
    matrix.setBrightness(15);
    numeric.writeDigitRaw(1, 84);
    numeric.writeDigitRaw(3, 92);
  }

  numeric.writeDisplay();
}

