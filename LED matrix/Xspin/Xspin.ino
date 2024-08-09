#include <FastLED.h>

#define LED_PIN     12    
#define NUM_LEDS    256  // 16x16 matrix
#define BRIGHTNESS  5   
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define MATRIX_WIDTH 16
#define MATRIX_HEIGHT 16

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

// Helper function to make 2D matrix to 1D array, each number represents the LED #
uint16_t XY(uint8_t x, uint8_t y) {
  if (y & 0x01) {
    // odd rows run left
    uint8_t reverseX = (MATRIX_WIDTH - 1) - x;
    return (y * MATRIX_WIDTH) + reverseX;
  } else {
    // Even rows run right
    return (y * MATRIX_WIDTH) + x;
  }
}

// Function to draw an X
void drawX(int offsetX, int offsetY, CRGB color) {
  for (int i = 0; i < MATRIX_WIDTH; i++) {
    int x1 = (i + offsetX) % MATRIX_WIDTH;
    int x2 = (MATRIX_WIDTH - 1 - i + offsetX) % MATRIX_WIDTH;
    int y = (i + offsetY) % MATRIX_HEIGHT;
    leds[XY(x1, y)] = color;
    leds[XY(x2, y)] = color;
  }
}

void loop() {
  // Clear all LEDs
  FastLED.clear();
  FastLED.show();
  delay(1000);  // Wait a second before starting

  // Spin the X pattern
  for (int offset = 0; offset < MATRIX_WIDTH; offset++) {
    FastLED.clear();
    drawX(offset, offset, CRGB::Red);
    FastLED.show();
    delay(100);
  }
}