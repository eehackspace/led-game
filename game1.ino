#include <FastLED.h>

#define LED_PIN     7
#define PAD_LEFT    4
#define PAD_RIGHT   8
#define RESET       2

#define NUM_LEDS    120

#define BRIGHTNESS  63 // 0-255
#define DEBOUNCE_DELAY  200 //ms

CRGB leds[NUM_LEDS];

int leftButton = HIGH;
int rightButton = HIGH;
int leftButtonPrev = HIGH;
int rightButtonPrev = HIGH;
unsigned long leftDebounce = 0;
unsigned long rightDebounce = 0;

int score;
int scorePrev;

void setup() {
    Serial.begin(9600);
    pinMode(PAD_LEFT, INPUT_PULLUP);
    pinMode(PAD_RIGHT, INPUT_PULLUP);
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    // Score starts in the middle
    score = NUM_LEDS / 2;  
    scorePrev = score;
    ledInit();    
    Serial.println("Program Started");
    Serial.println(score);
}

void loop() {
    unsigned long now=millis();

    //read and debounce Left
    leftButton = digitalRead(PAD_LEFT);
    if ((leftButton == HIGH) && (leftButtonPrev == LOW)) {
        leftDebounce = now;
    } else if ((leftButton == LOW) && (leftButtonPrev == HIGH) && (now - leftDebounce > DEBOUNCE_DELAY)) {
        score--;
    }
    leftButtonPrev = leftButton;

    //read and debounce Right
    rightButton = digitalRead(PAD_RIGHT);
    if ((rightButton == HIGH) && (rightButtonPrev == LOW)) {
        rightDebounce = now;
    } else if ((rightButton == LOW) && (rightButtonPrev == HIGH) && (now - rightDebounce > DEBOUNCE_DELAY)) {
        score++;
    }
    rightButtonPrev = rightButton;

    if (score > NUM_LEDS) {
        // trigger win sequence for right player, stop
    } else if (score <0) {
        // trigger win sequence for right player, stop
    }
  
    if (score != scorePrev) {
        Serial.println(score);
        for (int i = 0; i <= (NUM_LEDS-1); i++) {
            if (i < score) {
                leds[i] = CRGB::Blue;
            } else {
                leds[i] = CRGB::Red;
            }
        }
        FastLED.show();
        scorePrev = score;
    }
    //delay(5);
}

void ledInit() {
  // countdown
  for (int i = 0; i <= (NUM_LEDS-1); i++) {
      leds[i] = CRGB::Green;
  }
  FastLED.show();
  FastLED.delay(1000);
  for (int i = NUM_LEDS*0.75; i <= (NUM_LEDS-1); i++) {
      leds[i] = CRGB::Black;
  }
  FastLED.show();
  FastLED.delay(1000);
  for (int i = NUM_LEDS*0.5; i <= (NUM_LEDS*0.75-1); i++) {
      leds[i] = CRGB::Black;
  }
  FastLED.show();
  FastLED.delay(1000);
  for (int i = NUM_LEDS*0.25; i <= (NUM_LEDS*0.5-1); i++) {
      leds[i] = CRGB::Black;
  }
  FastLED.show();
  FastLED.delay(1000);
  for (int i = 0; i <= (NUM_LEDS*0.5-1); i++) {
      leds[i] = CRGB::Black;
  }
  FastLED.show();
  delay(1000);  
  // reset score to the middle
  for (int i = 0; i <= (NUM_LEDS-1); i++) {
    if (i < NUM_LEDS/2) {
      leds[i] = CRGB::Blue;
    } else {
      leds[i] = CRGB::Red;
    }
  }
  FastLED.show();
}
