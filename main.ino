#include "lib/neopixel.h"

// SYSTEM_MODE(MANUAL);

#define PIXEL_PIN D2
#define PIXEL_COUNT 126
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void setup()
{
  // Initialize all pixels to 'off'
  strip.begin();
  strip.show();

  // Set brightness (0 - 255)
  strip.setBrightness(255);
}

void loop() {
  rainbow(20);
}

void colorTheSides() {
  for (size_t i = 0; i < 42; i++) {
    strip.setPixelColor(i, strip.Color(255,0,0));
  }
  for (size_t i = 42; i < 63; i++) {
    strip.setPixelColor(i, strip.Color(0,255,255));
  }
  for (size_t i = 63; i < 105; i++) {
    strip.setPixelColor(i, strip.Color(255,0,255));
  }
  for (size_t i = 105; i < 126; i++) {
    strip.setPixelColor(i, strip.Color(255,255,255));
  }
  strip.show();
}

void solidColors() {
  for (size_t i = 0; i < 126; i++) {
    strip.setPixelColor(i, strip.Color(255,0,0));
  }
  strip.show();
  delay(2000);

  for (size_t i = 0; i < 126; i++) {
    strip.setPixelColor(i, strip.Color(0,255,0));
  }
  strip.show();
  delay(2000);

  for (size_t i = 0; i < 126; i++) {
    strip.setPixelColor(i, strip.Color(0,0,255));
  }
  strip.show();
  delay(2000);

  for (size_t i = 0; i < 126; i++) {
    strip.setPixelColor(i, strip.Color(255,255,255));
  }
  strip.show();
  delay(2000);
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
