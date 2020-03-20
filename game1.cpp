#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    120

#define Brightness  50 // 8-Bit

#define PAD_LEFT    4
#define PAD_RIGHT   8

CRGB leds[NUM_LEDS];

int LeftButton = LOW;
int RightButton = LOW;

int LeftButtonPrev = LOW;
int RightButtonPrev = LOW;

int LeftButtonPrev2 = LOW;
int RightButtonPrev2 = LOW;

int Score;
int ScorePrev;

unsigned long lastDebounceTimeLeft = 0;
unsigned long lastDebounceTimeRight = 0;
unsigned long debounceDelay = 50;

void setup() {
    Serial.begin(9600);
    pinMode(PAD_LEFT, INPUT);
    pinMode(PAD_RIGHT, INPUT);
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    Score = NUM_LEDS / 2;  // start in the middle
    ScorePrev = Score;
    
    // set middle marker
    //leds[Score] = CRGB (255, 255, 255);
    //FastLED.show();

    for (int i = 0; i <= (NUM_LEDS-1); i++) {
        if (i < Score) {
            leds[i] = CRGB ( 0, 0, Brightness);
        } else {
            leds[i] = CRGB ( Brightness, 0, 0);        
        }
        FastLED.show();
    }
    Serial.println(Score);

}

void loop() {
    //read and debounce Left
    int reading = digitalRead(PAD_LEFT);
    if (reading != LeftButtonPrev) {
        lastDebounceTimeLeft = millis();
    }
    if ((millis() - lastDebounceTimeLeft) > debounceDelay) {
        LeftButton = reading;
        if ((LeftButton == HIGH) && (LeftButtonPrev == LOW)) {
            Score = Score - 1;
        }
        if (Score < 0 ) {
            // trigger win sequence for left player
        }
    }
    LeftButtonPrev = reading;

    //read and debounce Right
    reading = digitalRead(PAD_RIGHT);
    if (reading != RightButtonPrev) {
        lastDebounceTimeRight = millis();
    }
    if ((millis() - lastDebounceTimeRight) > debounceDelay) {
        RightButton = reading;
        if ((RightButton == HIGH) && (RightButtonPrev == LOW))  {
            Score = Score + 1;
        }
        if (Score > NUM_LEDS) {
            // trigger win sequence for right player
        }
    }
    RightButtonPrev = reading;
    
    if (Score != Scoreprev) {
        Serial.println(Score);
        for (int i = 0; i <= (NUM_LEDS-1); i++) {
            if (i < Score) {
                leds[i] = CRGB ( 0, 0, Brightness);
            } else {
                leds[i] = CRGB ( Brightness, 0, 0);        
            }
            FastLED.show();
        }
        Scoreprev = Score;
    }
    //delay(5);
}
