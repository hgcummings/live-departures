typedef struct {
  unsigned char number;
  uint8_t icon[8];
} service;

const uint8_t loading_icon[8] = {
  B00000000,
  B00011100,
  B00100010,
  B01111111,
  B00100010,
  B00011100,
  B00000000,
  B00000000
};

const service buses[] = {
  { 43,
    { B00000000,
      B01010111,
      B01010001,
      B01110111,
      B00010001,
      B00010111,
      B00000000,
      B00000000
    }
  },
  { 134,
    { B00000000,
      B01011001,
      B01001010,
      B01011011,
      B01001001,
      B01011001,
      B00000000,
      B00000000
    }
  }
};
