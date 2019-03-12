// This #include statement was automatically added by the Particle IDE.
#include <WS2812FX.h>

#include "neopixel.h"

// SYSTEM_MODE(MANUAL);

#define LED_PIN D2
#define LED_COUNT 126
#define PIXEL_TYPE WS2812B

#define DOOR_PIN D6
#define CURRENT_PIN D4
#define ANALOG_THRESHOLD 512



// https://github.com/kitesurfer1404/WS2812FX
// multiplies led count by 4 to make the rainbow effect show less color at once
WS2812FX ws2812fx = WS2812FX(LED_COUNT*4, LED_PIN, WS2812B);

bool shouldPatternReset = TRUE;

// segmented pixel values for side specific patterns, if desired
int firstPixel = 0;
int topStartPixel = 42;
int leftStartPixel = 63;
int bottomStartPixel = 105;
int lastPixel = 126;

void setup() {
    ws2812fx.init();
    ws2812fx.setBrightness(180);
    resetPattern();
    ws2812fx.start();
}

void loop() {

    ws2812fx.service();

    if(digitalRead(DOOR_PIN) == LOW) {
        ws2812fx.setColor(0xFFFFFF);
        ws2812fx.setMode(FX_MODE_STATIC);
        shouldPatternReset = TRUE;
    } else {
        resetPattern();
    }
}

void resetPattern() {
    if(shouldPatternReset == TRUE) {
        ws2812fx.setSpeed(15000);
        ws2812fx.setMode(FX_MODE_RAINBOW_CYCLE);
        shouldPatternReset = FALSE;
    }
}
