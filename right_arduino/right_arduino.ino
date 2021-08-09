#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#include <FastLED.h>

#define LED_PIN 2
#define NUM_LEDS 6

#define RED_COLOR CRGB(255, 0, 0);
#define GREEN_COLOR CRGB(0, 255, 0);
#define BLUE_COLOR CRGB(0, 0, 255);

CRGB leds[NUM_LEDS];

//#define LEDS_OFF '0'

RF24 radio(7, 8); // using pin 7 for the CE pin, and pin 8 for the CSN pin

uint8_t address_left[6] = "00002"; // address of left NRF24

/**
 * Turn on all the leds to the same color
 */
int turn_on_same(CRGB color) {
  for(size_t i = 0; i < NUM_LEDS; ++i) {
    leds[i] = color;
  }
  FastLED.show();
}

/**
 * Setup the RGB strip in the corresponding mode
 * ('0' is off)
 */
int set_light(char mode) {
  switch(mode) {
    case '1': turn_on_same(RED_COLOR);
    break;
    case '2': turn_on_same(GREEN_COLOR);
    break;
    case '3': turn_on_same(BLUE_COLOR);
    break;
  }
  return 0;
}

void setup() {
  // Initialize NRF24 module
  radio.begin();
  radio.openWritingPipe(address_left); // open writing channel to left
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  
  // Initialize serial for HC-05 bluetooth
  Serial.begin(9600); 

  // Initialize leds
  FastLED.addLeds<WS2812B, LED_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  // Poll HC-05 bluetooth
  if(Serial.available() > 0) {
    char data = Serial.read();
    if(set_light(data)) {
       
    }
  }
  delay(50);
  //bool wasReceived = radio.write(
  
  //const char text[] = "Hello World";
  //bool wasReceived = radio.write(&text, sizeof(text));
  //delay(1000);
}
