#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

extern Adafruit_8x8matrix matrix;
extern Adafruit_7segment numeric;

int increment_digit(int digit);
void display_init();
void display_loading(const uint8_t icon[]);
