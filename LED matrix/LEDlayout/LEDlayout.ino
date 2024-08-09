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
  
  // Clear all LEDs
  FastLED.clear();
  FastLED.show();
  
  // Print XY mappings
  Serial.println("XY Mappings:");
  for (int y = 0; y < MATRIX_HEIGHT; y++) {
    for (int x = 0; x < MATRIX_WIDTH; x++) {
      uint16_t index = XY(x, y);
      Serial.print("(");
      Serial.print(x);
      Serial.print(",");
      Serial.print(y);
      Serial.print(") -> ");
      Serial.print(index);
      Serial.print("  ");
    }
    Serial.println(); // New line for each row
  }
}

// Helper function to make 2D matrix to 1D array, each number represents the LED #
// Starting from bottom right of 0 and then it goes right to 15 up one, and then its 16 goes left 
// VIEWING ALOGN WITH NUMBERS UPRIGHT
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

void loop() {
  // Clear all LEDs
  FastLED.clear();
  FastLED.show();
  delay(1000);  // Wait a second before starting
  // Draw the X
  for (int i = 0; i < MATRIX_WIDTH; i++) {
    leds[XY(i, i)] = CRGB::Red; // Main diagonal
    Serial.print("Return from XY");
    Serial.print(XY(i,i));
    Serial.println();
    FastLED.show();
    delay(100);
    leds[XY(i, MATRIX_HEIGHT - 1 - i)] = CRGB::Red; // Anti-diagonal
    FastLED.show();
    delay(100);
    Serial.print(i);
  }
  
  delay(2000);
}