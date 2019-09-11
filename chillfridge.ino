#include <WS2812FX.h>
#include "neopixel.h"

#define LED_PIN D2
#define LED_COUNT 126

#define DOOR D6
#define CURRENT A0

#define RAINBOW 0
#define WHITE 1
#define RED 2

long start;
int data;
int localMax = 0;
int localMin = 0;
int threshold = 1900;
int interval = 500;

int split = 0;

int targetEffect = RAINBOW;
int currentEffect = RAINBOW;

bool gettingPower = true;

// multiplies led count by 4 to make the rainbow effect show less color at once
WS2812FX ws2812fx = WS2812FX(LED_COUNT*4, LED_PIN, WS2812B);

void setup() {
  ws2812fx.init();
  ws2812fx.setBrightness(180);
  //  initialize default effect as RAINBOW
  setEffect(RAINBOW);
  ws2812fx.start();
  
  Particle.variable("split", split);
}

void loop() {
  manageState();
  display();
  //Serial.print("0,4095,");
  //Serial.println(analogRead(CURRENT));
}

void manageState() {
  checkPower();

  if (doorOpen()) {
    targetEffect = WHITE;
  } else {
    if (gettingPower) {
      targetEffect = RAINBOW;
    } else {
      targetEffect = RED;
    }
  }
}

void display() {
  if (targetEffect != currentEffect) {
    setEffect(targetEffect);
  }
  ws2812fx.service();
}

void setEffect(int type) {
  switch (type) {
    case RAINBOW:
      currentEffect = RAINBOW;
      ws2812fx.setSpeed(15000);
      ws2812fx.setMode(FX_MODE_RAINBOW_CYCLE);

      break;
    case WHITE:
      currentEffect = WHITE;
      ws2812fx.setColor(0xFFFFFF);
      ws2812fx.setMode(FX_MODE_STATIC);

      break;
    case RED:
      currentEffect = RED;
      ws2812fx.setColor(0xFF0000);
      ws2812fx.setMode(FX_MODE_STATIC);

      break;
  }
}

bool doorOpen() {
  return !digitalRead(DOOR);
}

void checkPower(void) {
  long currentTime = millis();
  data =analogRead(CURRENT);

  if (data > localMax) {
    localMax = data;
  }
  else if (data < localMin)  {
    localMin = data;
  }

  // conditional to check for loss of current every second
  if (currentTime > start + interval) {
      split = localMax - localMin;
      
      Serial.println(split);
      if (split < threshold)    {
        gettingPower = false;
      }
      else {
        gettingPower = true;
      }
      resetInterval();
  }
}

void resetInterval()  {
  start = millis();
  localMax = 0;
  localMin = 4095;
}
