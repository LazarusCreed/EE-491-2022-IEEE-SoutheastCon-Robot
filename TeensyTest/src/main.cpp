#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN        1
#define NUMPIXELS  8

//Pin number
//Number of pixels
//Third argument is the frequency and NEO_RGB is the priority
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_KHZ800 + NEO_RGB);

void setup() {
  //pinMode(1, OUTPUT);
  // put your setup code here, to run once:
  pixels.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  pixels.clear();
  //digitalWrite(1, HIGH);

  for(int i=0; i<NUMPIXELS; i++) {

    pixels.setPixelColor(i, pixels.Color(0, 0, 150));
    pixels.show();
    delay(500);
  }
  //pixels.setPixelColor(3, pixels.Color(0, 150, 0));
  //pixels.show();
}
