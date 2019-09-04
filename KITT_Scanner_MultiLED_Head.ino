#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 30

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3
#define CLOCK_PIN 13
#define DELAY 70
#define RED 100
#define FADE 150  //nscale 150
#define BRT 84 //84
#define LEADERS 3

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
	Serial.begin(57600);
	Serial.println("resetting");
	LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
	LEDS.setBrightness(BRT);
}

void fadeall() { 
  for(int i = 0; i < NUM_LEDS; i++) { 
    leds[i].nscale8(FADE);
  } 
}

void loop() { 
	static uint8_t hue = 255;
	Serial.print("x");
	// First slide the led in one direction
	for(int i = 0; i < NUM_LEDS-LEADERS; i++) {
		// Set the i'th led to red 
    for(int l = 0; l < LEADERS; l++) {
		  leds[i+l] = CHSV(RED, 255, 255);
    }
		// Show the leds
		FastLED.show(); 
		// now that we've shown the leds, reset the i'th led to black
		// leds[i] = CRGB::Black;
		fadeall();
		// Wait a little bit before we loop around and do it again
		delay(DELAY);
	}
	Serial.print("x");

	// Now go in the other direction.  
	for(int i = (NUM_LEDS-LEADERS)-1; i >= 0; i--) {
		// Set the i'th led to red
    for(int l = 0; l < LEADERS; l++) {
      leds[i+l] = CHSV(RED, 255, 255);
    }
		// Show the leds
		FastLED.show();
		// now that we've shown the leds, reset the i'th led to black
		// leds[i] = CRGB::Black;
		fadeall();
		// Wait a little bit before we loop around and do it again
		delay(DELAY);
	}
}
